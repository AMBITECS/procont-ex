//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "server.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>

Server::Server(std::shared_ptr<IGate> gate)
        : gate_(std::move(gate)) {
    if (!gate_) {
        throw std::invalid_argument("Gate cannot be null");
    }

    // Устанавливаем обработчик входящих сообщений
    gate_->setInboundHandler([this](std::shared_ptr<void> msg) {
        this->handleInboundMessage(std::move(msg));
    });

    // Запускаем фоновую задачу очистки
    cleanupThread_ = std::thread([this]() {
        while (running_) {
            std::unique_lock<std::mutex> lock(requestsMutex_);
            cleanupCV_.wait_for(lock, std::chrono::minutes(1),
                                [this]() { return !running_; });

            if (running_) {
                cleanupPendingRequests();
            }
        }
    });
}

Server::~Server() {
    shutdown();
}

void Server::registerClient(std::shared_ptr<Client> client) {
    if (!client) {
        throw std::invalid_argument("Client cannot be null");
    }

    std::lock_guard<std::mutex> lock(clientsMutex_);
    auto [it, inserted] = clients_.emplace(client->getKey(), client);
    if (!inserted) {
        throw std::runtime_error("Client already registered: " + client->getKey());
    }
}

void Server::unregisterClient(std::shared_ptr<Client> client) {
    if (!client) {
        return;
    }

    std::lock_guard<std::mutex> lock(clientsMutex_);
    clients_.erase(client->getKey());
}

std::future<Resp> Server::sendRequest(std::shared_ptr<Client> client,
                                      std::shared_ptr<void> request,
                                      long timeoutMs) {
    if (!client) {
        throw std::invalid_argument("Client cannot be null");
    }
    if (!request) {
        throw std::invalid_argument("Request cannot be null");
    }
    if (timeoutMs < 0) {
        throw std::invalid_argument("Timeout cannot be negative");
    }

    std::promise<Resp> promise;
    auto future = promise.get_future();
    std::string requestKey = generateRequestKey(client, request);

    {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        pendingRequests_.emplace(requestKey, PendingRequest{std::move(promise),
                                                            std::chrono::system_clock::now()});
    }

    if (timeoutMs > 0) {
        std::thread([this, requestKey, timeoutMs]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
            std::lock_guard<std::mutex> lock(requestsMutex_);
            auto it = pendingRequests_.find(requestKey);
            if (it != pendingRequests_.end() && !it->second.promise._Is_ready()) {
                it->second.promise.set_exception(
                        std::make_exception_ptr(
                                std::runtime_error("Request timeout: " + requestKey)));
                pendingRequests_.erase(it);
            }
        }).detach();
    }

    try {
        auto modifiedRequest = addRequestKey(request, requestKey);
        gate_->send(modifiedRequest);
    } catch (...) {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        pendingRequests_.erase(requestKey);
        throw;
    }

    return future;
}

void Server::publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) {
    if (!client || !data) {
        return;
    }

    gate_->send(data);
}

void Server::handleInboundMessage(std::shared_ptr<void> message) {
    try {
        if (auto resp = std::dynamic_pointer_cast<Resp>(message)) {
            std::string respKey = resp->key();
            size_t delimiterPos = respKey.find('|');

            if (delimiterPos != std::string::npos) {
                std::string requestKey = respKey.substr(delimiterPos + 1);
                std::lock_guard<std::mutex> lock(requestsMutex_);
                auto it = pendingRequests_.find(requestKey);

                if (it != pendingRequests_.end()) {
                    it->second.promise.set_value(*resp);
                    pendingRequests_.erase(it);
                } else {
                    // Логируем "запоздалый" ответ
                }
            }
        } else if (auto recv = std::dynamic_pointer_cast<Recv>(message)) {
            std::lock_guard<std::mutex> lock(clientsMutex_);
            auto it = clients_.find(recv->key());
            if (it != clients_.end()) {
                it->second->onDataReceived(recv);
            }
        }
    } catch (const std::exception& e) {
        // Логируем ошибку обработки сообщения
    }
}

std::string Server::generateRequestKey(const std::shared_ptr<Client>& client,
                                       const std::shared_ptr<void>& request) {
    std::string prefix;

    if (dynamic_cast<Init*>(request.get())) {
        prefix = "INIT";
    } else if (dynamic_cast<Exit*>(request.get())) {
        prefix = "EXIT";
    } else if (dynamic_cast<Subs*>(request.get())) {
        prefix = "SUBS";
    } else {
        prefix = "REQ";
    }

    std::ostringstream oss;
    oss << prefix << "-" << client->getKey() << "-" << requestCounter_++;
    return oss.str();
}

std::shared_ptr<void> Server::addRequestKey(std::shared_ptr<void> request,
                                            const std::string& requestKey) {
    if (auto init = std::dynamic_pointer_cast<Init>(request)) {
        return std::make_shared<Init>(init->key() + "|" + requestKey,
                                      init->urlWrite(),
                                      init->urlScada(),
                                      init->urlModel());
    }
    else if (auto exit = std::dynamic_pointer_cast<Exit>(request)) {
        return std::make_shared<Exit>(exit->key() + "|" + requestKey);
    }
    else if (auto subs = std::dynamic_pointer_cast<Subs>(request)) {
        return std::make_shared<Subs>(subs->key() + "|" + requestKey,
                                      subs->keys());
    }

    return request;
}

void Server::cleanupPendingRequests() {
    auto cutoff = std::chrono::system_clock::now() - std::chrono::minutes(5);
    int cleaned = 0;

    std::lock_guard<std::mutex> lock(requestsMutex_);
    for (auto it = pendingRequests_.begin(); it != pendingRequests_.end(); ) {
        if (it->second.timestamp < cutoff && !it->second.promise._Is_ready()) {
            it->second.promise.set_exception(
                    std::make_exception_ptr(
                            std::runtime_error("Request cleaned up: " + it->first)));
            it = pendingRequests_.erase(it);
            cleaned++;
        } else {
            ++it;
        }
    }

    if (cleaned > 0) {
        // Логируем количество очищенных запросов
    }
}

void Server::shutdown() {
    running_ = false;
    cleanupCV_.notify_all();

    if (cleanupThread_.joinable()) {
        cleanupThread_.join();
    }

    {
        std::lock_guard<std::mutex> lock(requestsMutex_);
        for (auto& [key, pr] : pendingRequests_) {
            if (!pr.promise._Is_ready()) {
                pr.promise.set_exception(
                        std::make_exception_ptr(
                                std::runtime_error("Server shutdown")));
            }
        }
        pendingRequests_.clear();
    }

    {
        std::lock_guard<std::mutex> lock(clientsMutex_);
        clients_.clear();
    }
}
