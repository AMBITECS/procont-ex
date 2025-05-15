//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <unordered_map>
#include <mutex>
#include <future>
#include <chrono>
#include <atomic>
#include <thread>
#include <memory>
#include <condition_variable>

#include "igate.h"
#include "client.h"
//#include "dto.hpp"

class Server {
public:
    explicit Server(std::shared_ptr<IGate> gate);
    ~Server();

    // Запрет копирования и присваивания
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void registerClient(std::shared_ptr<Client> client);
    void unregisterClient(std::shared_ptr<Client> client);
    std::future<Resp> sendRequest(std::shared_ptr<Client> client,
                                  std::shared_ptr<void> request,
                                  long timeoutMs);
    void publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data);

private:
    struct PendingRequest {
        std::promise<Resp> promise;
        std::chrono::system_clock::time_point timestamp;
    };

    void handleInboundMessage(std::shared_ptr<void> message);
    void cleanupPendingRequests();
    std::string generateRequestKey(const std::shared_ptr<Client>& client,
                                   const std::shared_ptr<void>& request);
    std::shared_ptr<void> addRequestKey(std::shared_ptr<void> request,
                                        const std::string& requestKey);
    void shutdown();

    std::shared_ptr<IGate> gate_;
    std::unordered_map<std::string, std::shared_ptr<Client>> clients_;
    std::unordered_map<std::string, PendingRequest> pendingRequests_;
    std::mutex clientsMutex_;
    std::mutex requestsMutex_;
    std::atomic<long> requestCounter_{0};
    std::atomic<bool> running_{true};
    std::thread cleanupThread_;
    std::condition_variable cleanupCV_;
};