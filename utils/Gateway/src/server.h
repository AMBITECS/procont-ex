#pragma once

#include "client.h"
#include "iserver.h"
#include "igate.h"
#include "dto.h"
#include <memory>
#include <unordered_map>
#include <future>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>
#include <chrono>
#include <functional>

namespace sft::dtm::gateway {

    class Server : public IServer {
    public:
        static std::shared_ptr<Server> getInstance() {
            static std::weak_ptr<Server> weakInstance;
            static std::mutex mutex;

            std::lock_guard<std::mutex> lock(mutex);
            auto instance = weakInstance.lock();
            if (!instance) {
                instance = std::make_shared<Server>();
                weakInstance = instance;
            }
            return instance;
        }

    private:
        Server() = default;

    public:
        // Конструктор/деструктор
        explicit Server(std::shared_ptr<IGate> gate);
        ~Server() override;

        // Основные методы IServer
        void registerClient(std::shared_ptr<Client> client) override;
        void unregisterClient(std::shared_ptr<Client> client) override;

        std::future<Resp> sendRequest(
                std::shared_ptr<Client> client,
                std::shared_ptr<void> request,
                long timeoutMs);

        void publish(const std::shared_ptr<Client>& client, std::shared_ptr<Send> data);

        // Состояние сервера
        bool isActive() const { return active_; }

    private:
        // Внутренняя структура для ожидающих запросов
        struct PendingRequest {
            std::promise<Resp> promise;
            std::chrono::system_clock::time_point timestamp;
            std::string originalKey;
        };

        void handleResponse(const Resp& resp);
        void dispatchToClient(const Recv& recv);

        // Вспомогательные методы
        void handleInboundMessage(const std::shared_ptr<void>& message);
        void cleanupPendingRequests();
        void clearPendingRequests();
        void scheduleRequestTimeout(const std::string& requestId, std::shared_ptr<PendingRequest> request, long timeoutMs);

        static std::string generateRequestKey(const std::shared_ptr<Client>& client, const std::shared_ptr<void>& request);
        static void changeRequestKey(const std::shared_ptr<void>& request, const std::string& newKey);
        static std::string getRequestKey(const std::shared_ptr<void>& request);

        // Поля класса
        std::shared_ptr<IGate> gate_;
        std::atomic<bool> active_{false};

        // Потокобезопасные контейнеры
        std::unordered_map<std::string, std::shared_ptr<Client>> clients_;
        std::unordered_map<std::string, std::shared_ptr<PendingRequest>> pendingRequests_;
        std::mutex clientsMutex_;
        std::mutex requestsMutex_;

        // Поток для очистки
        std::thread cleanupThread_;
        static constexpr std::chrono::seconds CLEANUP_INTERVAL{60};
    };

} // namespace sft::dtm::gateway
