#include "server.h"
#include <chrono>
#include <stdexcept>

// Конструктор сервера, принимает шлюз для коммуникации
Server::Server(std::shared_ptr<IGate> gate)
        : gate_(std::move(gate)) {
    if (!gate_) {
        throw std::invalid_argument("Gate cannot be null");
    }

    // Запускаем фоновый поток для очистки устаревших запросов
    running_ = true;
    cleanupThread_ = std::thread([this]() {
        while (running_) {
            std::this_thread::sleep_for(std::chrono::seconds(10)); // Проверка каждые 10 секунд
            cleanupPendingRequests();
        }
    });
}

// Деструктор сервера
Server::~Server() {
    running_ = false;
    if (cleanupThread_.joinable()) {
        cleanupThread_.join();
    }
}

// Регистрация нового клиента
void Server::registerClient(std::shared_ptr<Client> client) {
    if (!client) {
        throw std::invalid_argument("Client cannot be null");
    }

    std::lock_guard<std::mutex> lock(clientsMutex_);
    clients_[client->getId()] = client;
}

// Удаление клиента
void Server::unregisterClient(std::shared_ptr<Client> client) {
    if (!client) {
        throw std::invalid_argument("Client cannot be null");
    }

    std::lock_guard<std::mutex> lock(clientsMutex_);
    clients_.erase(client->getId());
}

// Отправка запроса с таймаутом
std::future<Response> Server::sendRequest(
        std::shared_ptr<Client> client,
        std::shared_ptr<void> request,
        long timeoutMs) {
    if (!client || !request) {
        throw std::invalid_argument("Client and request cannot be null");
    }

    // Генерируем уникальный ключ для запроса
    std::string key = generateRequestKey(client, request);

    // Создаем объект ожидаемого запроса
    PendingRequest pendingRequest;
    pendingRequest.timestamp = std::chrono::system_clock::now();

    // Получаем future до перемещения promise
    auto future = pendingRequest.promise.get_future();

    {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        pendingRequests_[key] = std::move(pendingRequest);
    }

    // Отправляем запрос через шлюз
    gate_->send(client->getId(), request);

    // Устанавливаем таймаут для запроса
    if (timeoutMs > 0) {
        std::thread([this, key, timeoutMs]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));

            std::lock_guard<std::mutex> lock(requestsMutex_);
            auto it = pendingRequests_.find(key);
            if (it != pendingRequests_.end()) {
                it->second.promise.set_exception(
                        std::make_exception_ptr(std::runtime_error("Request timeout")));
                pendingRequests_.erase(it);
            }
        }).detach();
    }

    return future;
}

// Публикация данных для клиента
void Server::publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) {
    if (!client || !data) {
        throw std::invalid_argument("Client and data cannot be null");
    }

    gate_->send(client->getId(), data);
}

// Обработка входящих сообщений
void Server::handleInboundMessage(std::shared_ptr<void> message) {
    // Здесь должна быть логика обработки входящих сообщений
    // и завершения соответствующих промисов из pendingRequests_
    // В реальной реализации нужно преобразовать message в Response
    // и найти соответствующий promise по ключу

    // Примерная логика:
    /*
    auto response = std::static_pointer_cast<Response>(message);
    std::string key = response->getRequestKey();
    
    std::lock_guard<std::mutex> lock(requestsMutex_);
    auto it = pendingRequests_.find(key);
    if (it != pendingRequests_.end()) {
        it->second.promise.set_value(*response);
        pendingRequests_.erase(it);
    }
    */
}

// Очистка устаревших запросов
void Server::cleanupPendingRequests() {
    auto now = std::chrono::system_clock::now();
    std::lock_guard<std::mutex> lock(requestsMutex_);

    for (auto it = pendingRequests_.begin(); it != pendingRequests_.end(); ) {
        // Удаляем запросы, которые висят дольше 1 часа
        if (std::chrono::duration_cast<std::chrono::hours>(
                now - it->second.timestamp).count() >= 1) {
            it->second.promise.set_exception(
                    std::make_exception_ptr(std::runtime_error("Request expired")));
            it = pendingRequests_.erase(it);
        } else {
            ++it;
        }
    }
}

// Генерация уникального ключа для запроса
std::string Server::generateRequestKey(
        std::shared_ptr<Client> client,
        std::shared_ptr<void> request) {
    // В реальной реализации нужно использовать уникальные идентификаторы
    // клиента и запроса. Здесь упрощенный вариант.
    return client->getId() + "_" + std::to_string(requestCounter_++);
}