//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "dto.h"

#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

class Client {
public:
    using DataHandler = std::function<void(std::shared_ptr<Receive>)>;

    explicit Client(const std::string& key, size_t maxQueueSize = 1000);
    ~Client();

    [[nodiscard]] std::string getKey() const;
    void setDataHandler(DataHandler handler);
    void onDataReceived(std::shared_ptr<Receive> data);
    void shutdown();
    [[nodiscard]] size_t getQueueSize() const;

private:
    void processData();

    const std::string key_;
    const size_t maxQueueSize_;
    std::queue<std::shared_ptr<Receive>> dataQueue_;
    mutable std::mutex queueMutex_;
    std::condition_variable queueCV_;
    DataHandler dataHandler_;
    std::atomic<bool> running_{true};
    std::thread workerThread_;
    std::atomic<bool> processing_{false};
};