//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "client.h"
#include "server.h"
#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std::chrono_literals;

namespace sft::dtm::gateway {

    Client::Client(const std::string& key, const std::string& accountName):
            key_(key),
            server_(Server::getInstance())
    {
        if (key.empty()) {
            throw std::invalid_argument("Client key cannot be empty");
        }
        initExecutors();
    }

    Client::~Client() {
        disconnect();
    }

    void Client::connect() {
        if (connected_) {
            throw std::runtime_error("Already connected");
        }

        try {
            server_->registerClient(shared_from_this());
            sendInitRequest();
            connected_ = true;
        } catch (const std::exception& e) {
            cleanup();
            throw std::runtime_error(std::string("Connection failed: ") + e.what());
        }
    }

    void Client::disconnect() {
        if (!connected_ || disconnecting_) return;

        disconnecting_ = true;
        try {
            sendExitNotification();
            unsubscribeAll();
            server_->unregisterClient(shared_from_this());
            connected_ = false;
        } catch (const std::exception& e) {
            std::cerr << "Graceful disconnect failed: " << e.what() << std::endl;
        }
        cleanup();
        disconnecting_ = false;
    }

    std::future<Resp> Client::init() {
        Init initMsg(key_, "urlWrite", "urlScada", "urlModel");
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Init>(initMsg),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    std::future<Resp> Client::exit() {
        Exit exitMsg(key_);
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Exit>(exitMsg),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    std::future<Resp> Client::subscribe(const std::vector<Item>& items) {
        if (!connected_) {
            throw std::runtime_error("Client is not connected");
        }

        std::vector<std::string> itemKeys;
        {
            std::lock_guard<std::mutex> lock(subscriptionsMutex_);
            for (const auto& item : items) {
                subscriptions_[item.getKey()] = item;
                itemKeys.push_back(item.getKey());
            }
        }

        Subs subs(key_, itemKeys);
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Subs>(subs),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    std::future<Resp> Client::unsubscribe(const std::vector<std::string>& itemKeys) {
        if (!connected_) {
            throw std::runtime_error("Client is not connected");
        }

        {
            std::lock_guard<std::mutex> lock(subscriptionsMutex_);
            for (const auto& key : itemKeys) {
                subscriptions_.erase(key);
            }
        }

        Subs subs(key_, itemKeys);
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Subs>(subs),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    void Client::unsubscribeAll() {
        std::vector<std::string> keys;
        {
            std::lock_guard<std::mutex> lock(subscriptionsMutex_);
            for (const auto& [key, _] : subscriptions_) {
                keys.push_back(key);
            }
        }

        if (!keys.empty()) {
            unsubscribe(keys).wait();
        }
    }

    size_t Client::getQueueSize() const {
        std::lock_guard<std::mutex> lock(queueMutex_);
        return dataQueue_.size();
    }

    bool Client::isActive() const {
        return running_;
    }

    void Client::processData() {
        while (running_) {
            std::shared_ptr<Recv> data;

            {
                std::unique_lock<std::mutex> lock(queueMutex_);
                queueCV_.wait(lock, [this]() {
                    return !dataQueue_.empty() || !running_;
                });

                if (!running_) break;

                if (!dataQueue_.empty()) {
                    data = dataQueue_.front();
                    dataQueue_.pop();
                }
            }

            if (data && dataHandler_) {
                try {
                    dataHandler_(*data);
                } catch (const std::exception& e) {
                    std::cerr << "Error processing data: " << e.what() << std::endl;
                }
            }
        }
    }

    void Client::initExecutors() {
        workerThread_ = std::thread(&Client::processData, this);
    }

    void Client::cleanup() {
        running_ = false;
        queueCV_.notify_all();

        if (workerThread_.joinable()) {
            workerThread_.join();
        }

        std::lock_guard<std::mutex> lock(queueMutex_);
        while (!dataQueue_.empty()) {
            dataQueue_.pop();
        }
    }

    void Client::sendInitRequest() {
        auto future = init();
        // Замена then на обработку через async
        (void)std::async(std::launch::async, [this, future = std::move(future)]() mutable
        {
            try {
                auto resp = future.get();
                if (!resp.isSuccess()) {
                    scheduleReconnect();
                }
            } catch (...) {
                scheduleReconnect();
            }
        });
    }

    void Client::sendExitNotification() {
        auto future = exit();
        try {
            future.get();
        } catch (...) {
            // Игнорируем ошибки при выходе
        }
    }

    void Client::scheduleReconnect() {
        if (reconnecting_.exchange(true)) {
            return;
        }

        if (reconnectAttempts_++ >= MAX_RECONNECT_ATTEMPTS) {
            reconnecting_ = false;
            return;
        }

        reconnectThread_ = std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(RECONNECT_DELAY_MS));
            if (isActive()) {
                recoverConnection();
            }
            reconnecting_ = false;
        });
        reconnectThread_.detach();
    }

    bool Client::recoverConnection() {
        try {
            auto initResp = init().get();
            if (!initResp.isSuccess()) {
                return false;
            }

            auto subs = restoreSubscriptions();
            auto subsResp = subs.get();
            return subsResp.isSuccess();
        } catch (...) {
            return false;
        }
    }

    std::future<Resp> Client::restoreSubscriptions() {
        std::vector<Item> itemsToRestore;

        {
            std::lock_guard<std::mutex> lock(subscriptionsMutex_);
            if (subscriptions_.empty()) {
                return std::async(std::launch::async, [this]() {
                    return Resp::success(this->key_);
                });
            }

            // Копируем все текущие подписки для восстановления
            itemsToRestore.reserve(subscriptions_.size());
            for (const auto& [_, item] : subscriptions_) {
                itemsToRestore.push_back(item);
            }
        }

        return subscribe(itemsToRestore);
    }

    void Client::onDataReceived(std::shared_ptr<Recv> data) {
        if (!data || data->key != key_) {
            return;
        }

        std::unique_lock<std::mutex> lock(queueMutex_);
        if (dataQueue_.size() >= DEFAULT_QUEUE_SIZE) {
            throw std::runtime_error("Client queue is full");
        }

        dataQueue_.push(data);
        lock.unlock();
        queueCV_.notify_one();
    }

    std::string Client::getKey() const {
        return key_;
    }

    void Client::setDataHandler(DataHandler handler) {
        dataHandler_ = std::move(handler);
        if (dataHandler_) {
            std::thread(&Client::processData, this).detach();
        }
    }

} // namespace sft::dtm::gateway
