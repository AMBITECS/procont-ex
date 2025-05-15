//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "client.h"

#include <chrono>
#include <utility>
#include <stdexcept>
#include <iostream>

Client::Client(std::string key)
        : key_(std::move(key)),
          workerThread_(&Client::processData, this) {
    if (key_.empty()) {
        throw std::invalid_argument("Client key cannot be empty");
    }
}

Client::~Client() {
    shutdown();
}

void Client::setDataHandler(DataHandler handler) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    dataHandler_ = std::move(handler);
    queueCV_.notify_one();
}

void Client::onDataReceived(std::shared_ptr<Recv> data) {
    if (!data || data->key() != key_) {
        return;
    }

    std::unique_lock<std::mutex> lock(queueMutex_);
    if (dataQueue_.size() >= MAX_QUEUE_SIZE) {
        std::cerr << "Client " << key_ << " queue overflow, message dropped\n";
        return;
    }

    dataQueue_.push(std::move(data));
    lock.unlock();

    if (dataHandler_ && !isProcessing_.exchange(true)) {
        queueCV_.notify_one();
    }
}

void Client::processData() {
    while (running_) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        queueCV_.wait(lock, [this]() {
            return !running_ || (!dataQueue_.empty() && dataHandler_);
        });

        if (!running_) break;

        try {
            // Обрабатываем все сообщения в очереди
            while (!dataQueue_.empty()) {
                auto data = std::move(dataQueue_.front());
                dataQueue_.pop();

                lock.unlock();

                try {
                    if (dataHandler_) {
                        dataHandler_(std::move(data));
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Client " << key_
                              << " handler error: " << e.what() << "\n";
                }

                lock.lock();
            }
        } catch (...) {
            isProcessing_ = false;
            throw;
        }

        isProcessing_ = false;
    }
}

size_t Client::getQueueSize() const {
    std::lock_guard<std::mutex> lock(queueMutex_);
    return dataQueue_.size();
}

void Client::shutdown() {
    if (!running_.exchange(false)) {
        return;
    }

    queueCV_.notify_all();

    if (workerThread_.joinable()) {
        workerThread_.join();
    }

    // Очищаем очередь
    std::lock_guard<std::mutex> lock(queueMutex_);
    while (!dataQueue_.empty()) {
        dataQueue_.pop();
    }
}

