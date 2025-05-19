#pragma once

#include "igate.h"
#include "iserver.h"
#include "client.h"
#include "dto.h"

#include <memory>
#include <unordered_map>
#include <future>
#include <mutex>
#include <atomic>
#include <thread>

class Server : public IServer {
public:
    explicit Server(std::shared_ptr<IGate> gate);
    ~Server() override;

    void registerClient(std::shared_ptr<Client> client) override;// override;
    void unregisterClient(std::shared_ptr<Client> client) override;// override;

    std::future<Response> sendRequest(
            std::shared_ptr<Client> client,
            std::shared_ptr<void> request,
            long timeoutMs) override;

    void publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) override;

private:
    struct PendingRequest {
        std::promise<Response> promise;
        std::chrono::system_clock::time_point timestamp;
    };

    void handleInboundMessage(std::shared_ptr<void> message);
    void cleanupPendingRequests();
    std::string generateRequestKey(std::shared_ptr<Client> client, std::shared_ptr<void> request);

    std::shared_ptr<IGate> gate_;
    std::mutex clientsMutex_;
    std::mutex requestsMutex_;

    std::unordered_map<std::string, std::shared_ptr<Client>> clients_;
    std::unordered_map<std::string, PendingRequest> pendingRequests_;

    std::atomic<bool> running_{false};
    std::atomic<long> requestCounter_{0};
    std::thread cleanupThread_;
};
