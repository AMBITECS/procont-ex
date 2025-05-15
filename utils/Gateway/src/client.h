//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
//#include "dto.h"
#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

class Client {
public:
    using DataHandler = std::function<void(std::shared_ptr<Recv>)>;

    explicit Client(std::string key);
    ~Client();

    // Запрет копирования
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    std::string getKey() const { return key_; }

    void setDataHandler(DataHandler handler);
    void onDataReceived(std::shared_ptr<Recv> data);
    void shutdown();

    size_t getQueueSize() const;

private:
    void processData();

    const std::string key_;
    static constexpr size_t MAX_QUEUE_SIZE = 1000;

    mutable std::mutex queueMutex_;
    std::queue<std::shared_ptr<Recv>> dataQueue_;
    std::condition_variable queueCV_;

    DataHandler dataHandler_;
    std::atomic<bool> running_{true};
    std::atomic<bool> isProcessing_{false};
    std::thread workerThread_;
};