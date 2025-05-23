#include "server.h"
#include "ikeyholder.h"
#include "dto.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std::chrono_literals;
namespace sft::dtm::gateway {

    Server::Server(std::shared_ptr<IGate> gate)
            : gate_(std::move(gate)) {
        if (!gate_) {
            throw std::invalid_argument("Gate cannot be null");
        }

        // Устанавливаем обработчик входящих сообщений
        gate_->setInboundHandler([this](std::shared_ptr<void> msg) {
            handleInboundMessage(msg);
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

    Server::~Server() {
        active_ = false;
        if (cleanupThread_.joinable()) {
            cleanupThread_.join();
        }
        clearPendingRequests();
    }

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

    void Server::unregisterClient(std::shared_ptr<Client> client) {
        if (!client) {
            throw std::invalid_argument("Client cannot be null");
        }

        std::lock_guard<std::mutex> lock(clientsMutex_);
        clients_.erase(client->getKey());
    }

    std::future<Resp> Server::sendRequest(
            std::shared_ptr<Client> client,
            std::shared_ptr<void> request,
            long timeoutMs) {
        if (!client || !request) {
            throw std::invalid_argument("Client and request cannot be null");
        }
        if (timeoutMs < 0) {
            throw std::invalid_argument("Timeout cannot be negative");
        }

        // Генерируем уникальный ключ для запроса
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

    void Server::publish(const std::shared_ptr<Client>& client, std::shared_ptr<Send> data) {
        if (!client || !data) {
            throw std::invalid_argument("Client and data cannot be null");
        }

        // Для публикации не модифицируем ключ
        gate_->send(data);
    }

    void Server::handleInboundMessage(const std::shared_ptr<void>& message) {
        try {
            // Приводим к базовому классу DtoBase
            auto dto = std::static_pointer_cast<DtoBase>(message);

            // Теперь можно безопасно использовать dynamic_cast
            if (auto resp = std::dynamic_pointer_cast<Resp>(dto)) {
                handleResponse(*resp);
            }
            else if (auto recv = std::dynamic_pointer_cast<Recv>(dto)) {
                dispatchToClient(*recv);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
        }
    }

    void Server::handleResponse(const Resp& resp) {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        auto it = pendingRequests_.find(resp._key());
        if (it != pendingRequests_.end()) {
            it->second->promise.set_value(resp);
            pendingRequests_.erase(it);
        }
    }

    void Server::dispatchToClient(const Recv& recv) {
        std::lock_guard<std::mutex> lock(clientsMutex_);
        auto it = clients_.find(recv._key());
        if (it != clients_.end()) {
            it->second->onDataReceived(recv);
        }
    }

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

    void Server::clearPendingRequests() {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        for (auto& [id, req] : pendingRequests_) {
            req->promise.set_exception(
                    std::make_exception_ptr(std::runtime_error("Server shutdown")));
        }
        pendingRequests_.clear();
    }

    void Server::scheduleRequestTimeout(
            const std::string& requestId,
            std::shared_ptr<PendingRequest> request,
            long timeoutMs) {
        std::thread([this, requestId, request, timeoutMs]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));

            std::lock_guard<std::mutex> lock(requestsMutex_);
            if (pendingRequests_.count(requestId)) {
                request->promise.set_exception(
                        std::make_exception_ptr(std::runtime_error("Request timeout")));
                pendingRequests_.erase(requestId);
            }
        }).detach();
    }

    std::string Server::generateRequestKey(
            const std::shared_ptr<Client>& client,
            const std::shared_ptr<void>& request)
    {

        return client->getKey() + "_" + std::to_string(
                std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Server::changeRequestKey(const std::shared_ptr<void>& request, const std::string& newKey) {
        // 1. Приводим к базовому интерфейсу IKeyHolder
        auto keyHolder = std::static_pointer_cast<IKeyHolder>(request);

        // 2. Устанавливаем новый ключ
        keyHolder->_key(newKey);
    }

    std::string Server::getRequestKey(const std::shared_ptr<void>& request) {
        if (auto keyHolder = std::static_pointer_cast<IKeyHolder>(request)) {
            return keyHolder->_key();
        }
        return "";
    }

} // namespace sft::dtm::gateway
