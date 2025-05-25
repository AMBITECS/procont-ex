#include "server.h"
#include "ikeyholder.h"
#include "dto.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std::chrono_literals;

namespace sft::dtm::gateway {

// Конструктор с инициализацией шлюза
    Server::Server(std::shared_ptr<IGate> gate)
            : gate_(std::move(gate)) {
        if (!gate_) {
            throw std::invalid_argument("Gate cannot be null");
        }

        // Устанавливаем обработчик входящих сообщений
        gate_->setInboundHandler([this](std::shared_ptr<void> msg) {
            handleInboundMessage(std::static_pointer_cast<DtoBase>(msg));
        });

        // Запускаем фоновый поток для очистки устаревших запросов
        active_ = true;
        cleanupThread_ = std::thread([this]() {
            while (active_) {
                std::this_thread::sleep_for(CLEANUP_INTERVAL);
                cleanupPendingRequests();
            }
        });
    }

// Деструктор с остановкой потока очистки
    Server::~Server() {
        active_ = false;
        if (cleanupThread_.joinable()) {
            cleanupThread_.join();
        }
        clearPendingRequests();
    }

// Регистрация нового клиента
    void Server::registerClient(std::shared_ptr<Client> client) {
        if (!client) {
            throw std::invalid_argument("Client cannot be null");
        }

        std::lock_guard<std::mutex> lock(clientsMutex_);
        if (clients_.find(client->getKey()) != clients_.end()) {
            throw std::runtime_error("Client already registered");
        }
        clients_[client->getKey()] = client;
    }

// Удаление клиента
    void Server::unregisterClient(std::shared_ptr<Client> client) {
        if (!client) {
            throw std::invalid_argument("Client cannot be null");
        }

        std::lock_guard<std::mutex> lock(clientsMutex_);
        clients_.erase(client->getKey());
    }

// Отправка запроса с таймаутом
    std::future<Resp> Server::sendRequest(
            std::shared_ptr<Client> client,
            std::shared_ptr<DtoBase> request,
            long timeoutMs) {
        checkServerActive();
        validateClientRegistration(client);

        if (!request) {
            throw std::invalid_argument("Request cannot be null");
        }
        if (timeoutMs < 0) {
            throw std::invalid_argument("Timeout cannot be negative");
        }

        // Генерируем уникальный ключ запроса
        std::string requestId = generateRequestKey(client, request);
        auto pendingRequest = std::make_shared<PendingRequest>();
        pendingRequest->timestamp = std::chrono::system_clock::now();
        pendingRequest->originalKey = getRequestKey(request);

        // Получаем future до перемещения promise
        auto future = pendingRequest->promise.get_future();

        {
            std::lock_guard<std::mutex> lock(requestsMutex_);
            pendingRequests_[requestId] = pendingRequest;
        }

        try {
            // Временно заменяем ключ на ID запроса
            changeRequestKey(request, requestId);
            gate_->send(request);
        } catch (...) {
            std::lock_guard<std::mutex> lock(requestsMutex_);
            pendingRequests_.erase(requestId);
            throw;
        }

        // Восстанавливаем оригинальный ключ
        changeRequestKey(request, pendingRequest->originalKey);

        // Устанавливаем таймаут для запроса
        if (timeoutMs > 0) {
            scheduleRequestTimeout(requestId, pendingRequest, timeoutMs);
        }

        return future;
    }

// Публикация данных
    void Server::publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) {
        checkServerActive();
        validateClientRegistration(client);

        if (!data) {
            throw std::invalid_argument("Data cannot be null");
        }

        // Для публикации не модифицируем ключ
        gate_->send(data);
    }

// Получение списка подключенных клиентов (weak_ptr)
    std::vector<std::weak_ptr<Client>> Server::getConnectedClients() const {
        std::vector<std::weak_ptr<Client>> result;
        std::lock_guard<std::mutex> lock(clientsMutex_);
        result.reserve(clients_.size());
        for (const auto& pair : clients_) {
            result.emplace_back(pair.second);
        }
        return result;
    }

// Получение статистики сервера
    ServerStats Server::getStats() const {
        ServerStats stats;
        stats.active = active_.load();
        {
            std::lock_guard<std::mutex> lock(clientsMutex_);
            stats.clientsCount = clients_.size();
        }
        {
            std::lock_guard<std::mutex> lock(requestsMutex_);
            stats.pendingRequestsCount = pendingRequests_.size();
        }
        return stats;
    }

// Проверка подключения клиента
    bool Server::isClientConnected(std::shared_ptr<Client> client) const {
        if (!client) return false;
        std::lock_guard<std::mutex> lock(clientsMutex_);
        return clients_.find(client->getKey()) != clients_.end();
    }

// Получение версии сервера
    std::string Server::getVersion() const {
        return "1.0.0";
    }

// ========== Приватные методы ==========

// Обработка входящего сообщения
    void Server::handleInboundMessage(const std::shared_ptr<DtoBase>& message) {
        try {
            if (auto resp = std::dynamic_pointer_cast<Resp>(message)) {
                handleResponse(*resp);
            }
            else if (auto recv = std::dynamic_pointer_cast<Recv>(message)) {
                dispatchToClient(*recv);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
        }
    }

// Обработка ответа
    void Server::handleResponse(const Resp& resp) {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        auto it = pendingRequests_.find(resp._key());
        if (it != pendingRequests_.end()) {
            // Восстанавливаем оригинальный ключ в ответе
            Resp modifiedResp = resp;
            modifiedResp._key(it->second->originalKey);

            it->second->promise.set_value(modifiedResp);
            pendingRequests_.erase(it);
        }
    }

// Маршрутизация сообщения клиенту
    void Server::dispatchToClient(const Recv& recv) {
        std::shared_ptr<Client> client;
        {
            std::lock_guard<std::mutex> lock(clientsMutex_);
            auto it = clients_.find(recv._key());
            if (it != clients_.end()) {
                client = it->second;
            }
        }

        if (client) {
            client->onDataReceived(std::make_shared<Recv>(recv));
        }
    }

// Очистка устаревших запросов
    void Server::cleanupPendingRequests() {
        auto now = std::chrono::system_clock::now();
        std::lock_guard<std::mutex> lock(requestsMutex_);

        for (auto it = pendingRequests_.begin(); it != pendingRequests_.end(); ) {
            if (now - it->second->timestamp > CLEANUP_INTERVAL) {
                it->second->promise.set_exception(
                        std::make_exception_ptr(std::runtime_error("Request timed out")));
                it = pendingRequests_.erase(it);
            } else {
                ++it;
            }
        }
    }

// Очистка всех ожидающих запросов
    void Server::clearPendingRequests() {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        for (auto& [id, req] : pendingRequests_) {
            req->promise.set_exception(
                    std::make_exception_ptr(std::runtime_error("Server shutdown")));
        }
        pendingRequests_.clear();
    }

// Установка таймаута для запроса
    void Server::scheduleRequestTimeout(
            const std::string& requestId,
            std::shared_ptr<PendingRequest> request,
            long timeoutMs
    )
    {
        std::thread([this, requestId, request, timeoutMs]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));

            std::lock_guard<std::mutex> lock(requestsMutex_);
            if (pendingRequests_.count(requestId)) {
                request->promise.set_exception(
                        std::make_exception_ptr(std::runtime_error("Request timeout")));
                pendingRequests_.erase(requestId);
            }
        }).detach();
    }

// Генерация ключа запроса
    std::string Server::generateRequestKey(
            const std::shared_ptr<Client>& client,
            const std::shared_ptr<DtoBase>& request) {
        return client->getKey() + "_" +
               std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }

// Изменение ключа в DTO
    void Server::changeRequestKey(
            const std::shared_ptr<DtoBase>& request,
            const std::string& newKey) {
        if (request) {
            request->_key(newKey);
        }
    }

// Получение ключа из DTO
    std::string Server::getRequestKey(const std::shared_ptr<DtoBase>& request) {
        return request ? request->_key() : "";
    }

// Проверка активности сервера
    void Server::checkServerActive() const {
        if (!active_) {
            throw std::runtime_error("Server is not active");
        }
    }

// Проверка регистрации клиента
    void Server::validateClientRegistration(const std::shared_ptr<Client>& client) const {
        if (!isClientConnected(client)) {
            throw std::runtime_error("Client is not registered");
        }
    }

} // namespace sft::dtm::gateway
