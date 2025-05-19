//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------

#include "gate.h"
#include "dto.h"
#include "../../libzmq/include/zmq.h"
#include "../../cppzmq/zmq.hpp"

#include <chrono>
#include <stdexcept>
#include <sstream>

#include <cmath>

using namespace std::chrono_literals;

// Конструктор с инициализацией ZMQ сокетов
Gate::Gate(const Props& props)
        : props_(props),
          context_(1), // Инициализация контекста с 1 I/O thread
          admSocket_(context_, ZMQ_REQ), // Сокет для административных запросов (REQ-REP)
          subSocket_(context_, ZMQ_SUB), // Сокет для подписки (SUB)
          pubSocket_(context_, ZMQ_PUB)  // Сокет для публикации (PUB)
{
    // Установка таймаутов для административного сокета
    admSocket_.set(zmq::sockopt::rcvtimeo, props_.timeout);
    admSocket_.set(zmq::sockopt::sndtimeo, props_.timeout);
    log("Gate initialized with host: {}:{}", props_.host, props_.admPort);
}

// Деструктор с гарантированным освобождением ресурсов
Gate::~Gate() {
    disconnect();
    log("Gate destroyed");
}

// Отправка сообщения в очередь на передачу
void Gate::send(std::shared_ptr<void> message) {
    if (!message) {
        throw std::invalid_argument("Message cannot be null");
    }

    std::unique_lock<std::mutex> lock(queueMutex_);

    // Проверка переполнения очереди
    if (outboundQueue_.size() >= props_.maxQueueSize) {
        log("Outbound queue overflow (max: {})", props_.maxQueueSize);
        throw std::runtime_error("Outbound queue is full");
    }

    outboundQueue_.push(message);
    lock.unlock();

    queueCV_.notify_one(); // Уведомляем поток отправителя
    log("Message queued for sending");
}

// Установка обработчика входящих сообщений
void Gate::setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) {
    std::lock_guard<std::mutex> lock(listenersMutex_);
    inboundHandler_ = handler;
    log("Inbound handler {}", handler ? "set successfully" : "cleared");
}

// Подключение к серверу
bool Gate::connect() {
    if (state_ == State::CONNECTED) {
        return true;
    }

    changeState(State::CONNECTING);
    log("Attempting to connect...");

    try {
        // Подключение административного сокета
        admSocket_.connect("tcp://" + props_.host + ":" +
                           std::to_string(props_.admPort));

        // Подключение сокета подписки
        subSocket_.connect("tcp://" + props_.host + ":" +
                           std::to_string(props_.subPort));
        subSocket_.set(zmq::sockopt::subscribe, ""); // Подписка на все сообщения

        // Привязка сокета публикации
        pubSocket_.bind("tcp://*:" + std::to_string(props_.pubPort));

        // Запуск рабочих потоков
        running_ = true;
        receiverThread_ = std::thread(&Gate::recvLoop, this);
        senderThread_ = std::thread(&Gate::sendLoop, this);
        heartbeatThread_ = std::thread(&Gate::startHeartbeat, this);

        changeState(State::CONNECTED);
        log("Successfully connected to gateway");
        return true;
    } catch (const zmq::error_t& e) {
        log("Connection failed: {}", e.what());
        disconnect();
        changeState(State::FAILED);
        return false;
    }
}

// Отключение от сервера
void Gate::disconnect() {
    if (state_ == State::DISCONNECTED ||
        state_ == State::DISCONNECTING) {
        return;
    }

    changeState(State::DISCONNECTING);
    log("Disconnecting...");

    running_ = false; // Флаг для остановки потоков
    queueCV_.notify_all(); // Разблокировать ожидающие потоки

    // Остановка потоков с таймаутом
    if (receiverThread_.joinable()) {
        receiverThread_.join();
    }
    if (senderThread_.joinable()) {
        senderThread_.join();
    }
    if (heartbeatThread_.joinable()) {
        heartbeatThread_.join();
    }

    // Закрытие сокетов
    try {
        context_.close();
    } catch (const zmq::error_t& e) {
        log("Error closing context: {}", e.what());
    }

    // Очистка очереди
    std::lock_guard<std::mutex> lock(queueMutex_);
    while (!outboundQueue_.empty()) {
        outboundQueue_.pop();
    }

    changeState(State::DISCONNECTED);
    log("Disconnected successfully");
}

// Цикл приема сообщений
void Gate::recvLoop() {
    zmq::poller_t<> poller;
    poller.add(admSocket_, ZMQ_POLLIN);
    poller.add(subSocket_, ZMQ_POLLIN);

    log("Receiver thread started");

    while (running_) {
        try {
            auto events = poller.wait(100ms); // Неблокирующее ожидание

            if (!running_) break;

            for (auto& event : events) {
                if (event.socket == admSocket_ &&
                    event.events & ZMQ_POLLIN) {
                    handleAdminMessage();
                } else if (event.socket == subSocket_ &&
                           event.events & ZMQ_POLLIN) {
                    handleSubscription();
                }
            }
        } catch (const zmq::error_t& e) {
            if (e.num() != ETERM) { // Игнорировать ошибки при завершении
                log("Receive error: {}", e.what());
                handleConnectionError();
            }
        } catch (...) {
            if (running_) {
                log("Unexpected receive error");
                handleConnectionError();
            }
        }
    }
    log("Receiver thread stopped");
}

// Обработка административных сообщений
void Gate::handleAdminMessage() {
    zmq::message_t msg;
    if (admSocket_.recv(msg, zmq::recv_flags::none)) {
        try {
            auto resp = Response::fromJSON(
                    std::string(static_cast<char*>(msg.data()), msg.size()));

            std::lock_guard<std::mutex> lock(listenersMutex_);
            if (inboundHandler_) {
                inboundHandler_(std::make_shared<Response>(resp));
            }
        } catch (...) {
            log("Failed to parse admin message");
        }
    }
}

// Обработка подписок
void Gate::handleSubscription() {
    zmq::message_t msg;
    if (subSocket_.recv(msg, zmq::recv_flags::none)) {
        try {
            auto recv = Receive::fromJSON(
                    std::string(static_cast<char*>(msg.data()), msg.size()));

            std::lock_guard<std::mutex> lock(listenersMutex_);
            if (inboundHandler_) {
                inboundHandler_(std::make_shared<Receive>(recv));
            }
        } catch (...) {
            log("Failed to parse subscription message");
        }
    }
}

// Цикл отправки сообщений
void Gate::sendLoop() {
    log("Sender thread started");

    while (running_) {
        std::shared_ptr<void> msg;
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            queueCV_.wait_for(lock, 100ms,
                              [this]() { return !outboundQueue_.empty() || !running_; });

            if (!running_) break;

            if (!outboundQueue_.empty()) {
                msg = outboundQueue_.front();
                outboundQueue_.pop();
            }
        }

        if (msg) {
            try {
                sendToSocket(msg);
            } catch (const zmq::error_t& e) {
                log("Send error: {}", e.what());
                handleConnectionError();
            } catch (...) {
                if (running_) {
                    log("Unexpected send error");
                    handleConnectionError();
                }
            }
        }
    }
    log("Sender thread stopped");
}

// Отправка сообщения через соответствующий сокет
void Gate::sendToSocket(std::shared_ptr<void> msg) {
    std::string json;
    if (auto init = std::dynamic_pointer_cast<Init>(msg)) {
        json = init->toJSON();
    } else if (auto exit = std::dynamic_pointer_cast<Exit>(msg)) {
        json = exit->toJSON();
    } else if (auto subs = std::dynamic_pointer_cast<Subs>(msg)) {
        json = subs->toJSON();
    } else if (auto send = std::dynamic_pointer_cast<Send>(msg)) {
        json = send->toJSON();
    } else {
        throw std::invalid_argument("Unsupported message type");
    }

    zmq::message_t zmqMsg(json.begin(), json.end());
    if (std::dynamic_pointer_cast<Send>(msg)) {
        pubSocket_.send(zmqMsg, zmq::send_flags::none);
    } else {
        admSocket_.send(zmqMsg, zmq::send_flags::none);
    }
    log("Message sent successfully");
}

// Проверка соединения (heartbeat)
bool Gate::checkConnection() {
    try {
        zmq::message_t ping("PING", 4);
        if (!admSocket_.send(ping, zmq::send_flags::dontwait)) {
            return false;
        }

        zmq::message_t pong;
        if (!admSocket_.recv(pong, zmq::recv_flags::dontwait)) {
            return false;
        }

        return std::string_view(static_cast<char*>(pong.data()), pong.size()) == "PONG";
    } catch (...) {
        return false;
    }
}

// Запуск проверки соединения
void Gate::startHeartbeat() {
    log("Heartbeat started with interval: {}ms", props_.heartbeatInterval);

    while (running_) {
        std::this_thread::sleep_for(
                std::chrono::milliseconds(props_.heartbeatInterval));

        if (!running_) break;

        if (!checkConnection()) {
            log("Heartbeat failed, attempting to reconnect...");
            reconnect();
        }
    }
    log("Heartbeat stopped");
}

// Переподключение при сбое
void Gate::reconnect() {
    if (state_ == State::DISCONNECTING ||
        state_ == State::DISCONNECTED) {
        return;
    }

    changeState(State::FAILED);
    log("Starting reconnection attempts...");

    for (int attempt = 1; attempt <= props_.maxRetries && running_; ++attempt) {
        log("Reconnection attempt {}/{}", attempt, props_.maxRetries);

        disconnect();
        if (connect()) {
            return; // Успешное переподключение
        }

        if (running_) {
            std::this_thread::sleep_for(
                    std::chrono::seconds(attempt)); // Экспоненциальная задержка
        }
    }

    if (running_) {
        log("All reconnection attempts failed");
        disconnect();
    }
}

// Изменение состояния с уведомлением слушателей
void Gate::changeState(State newState) {
    State oldState = state_.exchange(newState);

    if (oldState != newState) {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        for (auto& listener : stateListeners_) {
            try {
                listener(oldState, newState);
            } catch (...) {
                // Гарантированно не бросать исключения
            }
        }
        log("State changed: {} -> {}", toString(oldState), toString(newState));
    }
}

// Обработка ошибок соединения
void Gate::handleConnectionError() {
    if (state_ == State::CONNECTED) {
        reconnect();
    }
}

// Вспомогательный метод для логирования состояний
std::string Gate::toString(State state) {
    switch (state) {
        case State::DISCONNECTED: return "DISCONNECTED";
        case State::CONNECTING: return "CONNECTING";
        case State::CONNECTED: return "CONNECTED";
        case State::DISCONNECTING: return "DISCONNECTING";
        case State::FAILED: return "FAILED";
        default: return "UNKNOWN";
    }
}

// Добавление слушателя изменений состояния
void Gate::addStateChangeListener(std::function<void(State, State)> listener) {
    std::lock_guard<std::mutex> lock(listenersMutex_);
    stateListeners_.push_back(listener);
}

// Получение текущего состояния
Gate::State Gate::getState() const {
    return state_.load();
}
