//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_ZMQ_SERVER_H
#define PROCONT_EX_ZMQ_SERVER_H

#include "dto.h"
#include "zmq_client.h"
#include "zmq_config.h"
#include "api_driver.h"

#include <cppzmq/zmq.hpp>
#include <cppzmq/zmq_addon.hpp>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <functional>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

class ZmqServerException : public std::runtime_error {
public:
    explicit ZmqServerException(const std::string& msg)
            : std::runtime_error(msg) {}
};

enum class ServerState {
    STOPPED,     // Сервер остановлен
    STARTING,    // Сервер запускается
    RUNNING,     // Сервер работает
    STOPPING,    // Сервер останавливается
    ERROR        // Ошибка в работе сервера
};

class IMessageHandler {
public:
    virtual ~IMessageHandler() = default;
    virtual void handleMessage(const std::string& client_id,
                               const std::string& message) = 0;
};

class ZmqServer : public IClientCallback
{
public:
    // IClientCallback implementation
    void onInit() override {
        std::cout << "ZmqServer initialized as registry client\n";
        // Можно добавить инициализацию ресурсов при необходимости
    }

    void onExit() override {
        if (reg_client_) {
            reg_client_->unsubscribeAll();  // Отписываемся от всех регистров
            reg_client_.reset();           // Освобождаем клиента
        }
        std::cout << "ZmqServer unsubscribed from registry\n";
    }

    void updateInputs() override {
        // Пустая реализация, так как ZMQ серверу не нужны входные данные
    }

    void updateOutputs(const std::vector<OnDataChange> &changes) override;

public:
    // Удаляем конструкторы копирования и присваивания
    ZmqServer(const ZmqServer&) = delete;
    ZmqServer& operator=(const ZmqServer&) = delete;

    // Метод для получения экземпляра синглтона
    static ZmqServer& instance(const std::string& configPath = "");

    // Основные методы управления сервером
    void start();
    void stop();

    void pushTagUpdates(const std::vector<Tag>& tags);
    void setMessageHandler(std::shared_ptr<IMessageHandler> handler);

    // Получение состояния сервера
    ServerState getState() const { return state_; }
    const cfg::ZmqServerConfig& getConfig() const { return config_;}


private:
    // Приватный конструктор (только для внутреннего использования)
    explicit ZmqServer(const std::string& configPath);
    //explicit ZmqServer(const cfg::ZmqServerConfig& config);
    ~ZmqServer() override;

    // Приватные методы для работы с соединениями
    Response handleConnectRequest(const Request& request);
    void     disconnectClient(const std::string& key);

    // Приватные методы для работы с подписками
    void processTagUpdates(const std::vector<Tag>& tags);
    void processSubscribe(const Subscribe& sub);
    void processUnsubscribe(const Unsubscribe& unsub);

    // Приватные методы управления сокетами
    void initSockets();
    void cleanupSockets();

    // Приватные методы управления потоками
    void startWorkerThreads();
    void stopWorkerThreads();

    // Рабочие потоки
    void admWorker();
    void pubWorker();

    void heartbeatWorker();
    void tagProcessingWorker();

    // Обработчик административных сообщений
    void processAdminMessage(const std::string& message);

    // Конфигурация сервера
    const cfg::ZmqServerConfig config_;
    std::atomic<ServerState> state_{ServerState::STOPPED};

    // ZMQ ресурсы
    std::unique_ptr<zmq::context_t> context_;
    std::unique_ptr<zmq::socket_t> adm_socket_;
    std::unique_ptr<zmq::socket_t> pub_socket_;

    // Рабочие потоки
    std::thread adm_thread_;
    std::thread pub_thread_;
    std::thread heartbeat_thread_;
    std::thread tag_processing_thread_;

    // Управление клиентами
    std::shared_ptr<IRegClient> reg_client_; // клиент IRegClient
    std::unordered_map<std::string, std::shared_ptr<ZmqClient>> clients_;
    mutable std::mutex clients_mutex_;

    // Подписка на теги: tag -> [clientIds]
    std::unordered_map<std::string, std::vector<std::string>> tagSubscriptions_;
    mutable std::mutex subscriptions_mutex_;

    // Обработчик сообщений
    std::shared_ptr<IMessageHandler> message_handler_;

    // Очередь обновлений тегов (pushTagUpdates)
    std::queue<std::vector<Tag>>    tagUpdatesQueue_;
    mutable std::mutex              tag_queue_mutex_;
    std::condition_variable         tag_queue_cv_;
    std::atomic<bool>               stop_tag_processing_{false};

    // Добавляем структуру для хранения состояния передачи файлов
    struct FileTransfer {
        std::string             client_id;      // Ключ (ID) клиента
        std::string             prog_name;      // Имя программы (не файла)
        uint64_t                prog_hash;      // crc32 (orig)
        std::string             file_name;      // Имя файла
        uint64_t                file_size;      // Размер файла
        uint64_t                bytes_received; // Количество принятых байтов
        uint32_t                file_crc;       // Для накопления CRC32 файла
        std::filesystem::path   save_path;      // Путь расположения файла
        //std::chrono::steady_clock::time_point last_update; // Для таймаутов
        std::ofstream           file_stream{};  // выходной поток для записи
    };

    std::mutex transfer_mutex_;
    std::unordered_map<std::string, FileTransfer> active_transfers_;

    // Базовый каталог для сохранения программ
    std::filesystem::path programs_dir_{"modules"};

    // Обработчики состояния
    void handleExecutionStart(const Request& request);
    void handleExecutionStop(const Request& request);
    void handleExecutionPause(const Request& request);
    void handleExecutionResume(const Request& request);

    // Обработчики файловых операций
    void handleProgStart(const ProgStart& prog_start);
    void handleFileStart(const FileStart& file_start);
    void handleFileChunk(const FileChunk& file_chunk);
    void handleFileEnd(const FileEnd& file_end);
    void handleProgEnd(const ProgEnd& prog_end);

    // Вспомогательные методы
    void changeState(ServerState new_state);
    void sendResponse(const std::string &client_id, const std::shared_ptr<IDto> &dto);
    void sendDtoToClient(const std::string& client_id, const std::shared_ptr<IDto>& dto);

    template <typename T> void broadcast(const T& dto);
};

#endif //PROCONT_EX_ZMQ_SERVER_H