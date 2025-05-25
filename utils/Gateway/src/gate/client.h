#pragma once
#include "dto.h"
#include "iserver.h"
#include "item.h"
#include <memory>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <unordered_map>

namespace sft::dtm::gateway {

/**
 * @class Client
 * @brief Клиент для взаимодействия с шлюзом DTM
 *
 * Обеспечивает:
 * - Установку/разрыв соединения
 * - Подписку на данные
 * - Обработку входящих сообщений
 * - Автоматическое восстановление соединения
 */
    class Client : public std::enable_shared_from_this<Client> {
    public:
        using DataHandler = std::function<void(const Recv&)>;

        // Константы
        static constexpr int REQUEST_DEFAULT_TIMEOUT_MS = 5000;
        static constexpr int RECONNECT_DELAY_MS = 5000;
        static constexpr size_t DEFAULT_QUEUE_SIZE = 512;
        static constexpr int MAX_RECONNECT_ATTEMPTS = 3;

        /**
         * @brief Конструктор клиента
         * @param key Уникальный идентификатор клиента
         * @param accountName Имя учетной записи (необязательно)
         */
        Client(const std::string& key, const std::string& accountName = "");
        ~Client();

        // Управление соединением
        void connect();
        void disconnect();
        //bool isConnected() const;

        // Основные методы
        std::string getKey() const;
        void setDataHandler(DataHandler handler);
        void onDataReceived(std::shared_ptr<Recv> data);

        // Подписки
        std::future<Resp> subscribe(const std::vector<Item>& items);
        std::future<Resp> unsubscribe(const std::vector<std::string>& itemKeys);
        void unsubscribeAll();

        // Статус
        size_t getQueueSize() const;
        bool isActive() const;

    private:
        // Внутренние методы
        void processData();
        void initExecutors();
        void cleanup();
        std::future<Resp> init();
        std::future<Resp> exit();
        void sendInitRequest();
        void sendExitNotification();
        void scheduleReconnect();
        bool recoverConnection();
        std::future<Resp> restoreSubscriptions();

        // Состояние
        const std::string key_;
        std::shared_ptr<IServer> server_;
        std::atomic<bool> connected_{false};
        std::atomic<bool> disconnecting_{false};
        std::atomic<bool> reconnecting_{false};
        std::atomic<bool> running_{true};
        std::atomic<int> reconnectAttempts_{0};

        // Подписки (заменили Reg на простой map)
        std::unordered_map<std::string, Item> subscriptions_;
        mutable std::mutex subscriptionsMutex_;

        // Очередь данных
        std::queue<std::shared_ptr<Recv>> dataQueue_;
        mutable std::mutex queueMutex_;
        std::condition_variable queueCV_;
        DataHandler dataHandler_;

        // Потоки
        std::thread workerThread_;
        std::thread reconnectThread_;
    };

} // namespace sft::dtm::gateway