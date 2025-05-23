#pragma once

#include "client.h"
#include "iserver.h"
#include "igate.h"
#include "dto.h"
#include "server_stat.h"
#include <memory>
#include <unordered_map>
#include <future>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>
#include <chrono>
#include <functional>
#include <vector>

namespace sft::dtm::gateway {

/**
 * @class Server
 * @brief Основной серверный класс для управления клиентами и маршрутизации сообщений
 *
 * Реализует паттерн Singleton и интерфейс IServer. Обеспечивает:
 * - Регистрацию/удаление клиентов
 * - Отправку запросов с таймаутами
 * - Публикацию сообщений
 * - Обработку входящих сообщений
 */
    class Server : public IServer {
    public:
        /**
         * @brief Получение экземпляра сервера (Singleton)
         * @return std::shared_ptr<Server> Общий указатель на экземпляр сервера
         */
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

        // Запрет копирования и присваивания
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        /**
         * @brief Конструктор сервера
         * @param gate Шлюз для отправки/получения сообщений
         */
        explicit Server(std::shared_ptr<IGate> gate);

        /**
         * @brief Деструктор сервера
         */
        ~Server() override;

        // ========== Реализация методов IServer ==========

        void registerClient(std::shared_ptr<Client> client) override;
        void unregisterClient(std::shared_ptr<Client> client) override;

        std::future<Resp> sendRequest(
                std::shared_ptr<Client> client,
                std::shared_ptr<DtoBase> request,
                long timeoutMs) override;

        void publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) override;

        std::vector<std::weak_ptr<Client>> getConnectedClients() const override;
        ServerStats getStats() const override;
        bool isClientConnected(std::shared_ptr<Client> client) const override;
        std::string getVersion() const override;

        /**
         * @brief Проверка активности сервера
         * @return true Сервер активен
         * @return false Сервер остановлен
         */
        bool isActive() const { return active_; }

        // Приватный конструктор по умолчанию для Singleton
        Server() = default;

    private:

        // Структура для хранения ожидающих запросов
        struct PendingRequest {
            std::promise<Resp> promise;
            std::chrono::system_clock::time_point timestamp;
            std::string originalKey;
        };

        // ========== Внутренние методы ==========
        void handleResponse(const Resp& resp);
        void dispatchToClient(const Recv& recv);
        void handleInboundMessage(const std::shared_ptr<DtoBase>& message);
        void cleanupPendingRequests();
        void clearPendingRequests();
        void scheduleRequestTimeout(const std::string& requestId,
                                    std::shared_ptr<PendingRequest> request,
                                    long timeoutMs);

        static std::string generateRequestKey(const std::shared_ptr<Client>& client,
                                              const std::shared_ptr<DtoBase>& request);
        static void changeRequestKey(const std::shared_ptr<DtoBase>& request,
                                     const std::string& newKey);
        static std::string getRequestKey(const std::shared_ptr<DtoBase>& request);

        void checkServerActive() const;
        void validateClientRegistration(const std::shared_ptr<Client>& client) const;

        // ========== Поля класса ==========
        std::shared_ptr<IGate> gate_;       // Шлюз для сообщений
        std::atomic<bool> active_{false}; // Флаг активности сервера

        // Потокобезопасные контейнеры
        std::unordered_map<std::string, std::shared_ptr<Client>> clients_;
        std::unordered_map<std::string, std::shared_ptr<PendingRequest>> pendingRequests_;
        mutable std::mutex clientsMutex_;
        mutable std::mutex requestsMutex_;

        // Поток для очистки
        std::thread cleanupThread_;
        static constexpr std::chrono::seconds CLEANUP_INTERVAL{60};
    };

} // namespace sft::dtm::gateway
