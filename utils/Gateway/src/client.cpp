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

// Инициализация статического члена
    Reg<Item> Client::itemRegistry_{};

    Client::Client(const std::string& key, const std::string& accountName)
            : key_(key),
              server_(Server::getInstance()) {  // Исправлено использование Server
        if (key.empty()) {
            throw std::invalid_argument("Client key cannot be empty");
        }
        initExecutors();
    }

    Client::~Client() {
        disconnect();
    }

    void Client::connect() {
        if (isConnected()) {
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
        if (!isConnected() || disconnecting_) return;

        disconnecting_ = true;
        try {
            sendExitNotification();
            unsubscribeAll();
            connected_ = false;
        } catch (const std::exception& e) {
            std::cerr << "Graceful disconnect failed: " << e.what() << std::endl;
        }
        cleanup();
        disconnecting_ = false;
    }

    std::future<Resp> Client::init() {
        Init initMsg(key_, "urlWrite", "urlScada", "urlModel");
        return std::async(std::launch::async, [this]() {
            return Resp::success(this->key_);
        });
    }

    std::future<Resp> Client::exit() {
        Exit exitMsg(key_);
        return std::async(std::launch::async, [this]() {
            return Resp::success(this->key_);
        });
    }

    std::future<Resp> Client::subscribe(const std::vector<Item>& items) {
        if (!isConnected()) {
            throw std::runtime_error("Client is not connected");
        }

        std::vector<std::string> addresses;  // Изменено на std::string
        for (const auto& item : items) {
            auto itemPtr = std::make_shared<Item>(item);
            size_t address = itemRegistry_.reg(itemPtr);
            addresses.push_back(std::to_string(address));  // Конвертация в строку
        }

        Subs subs(key_, addresses);  // Теперь принимает vector<string>
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Subs>(subs),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    std::future<Resp> Client::unsubscribe(const std::vector<size_t>& addresses) {
        if (!isConnected()) {
            throw std::runtime_error("Client is not connected");
        }

        std::vector<std::string> strAddresses;
        for (auto addr : addresses) {
            strAddresses.push_back(std::to_string(addr));
        }

        Subs subs(key_, strAddresses);
        return server_->sendRequest(shared_from_this(),
                                    std::make_shared<Subs>(subs),
                                    REQUEST_DEFAULT_TIMEOUT_MS);
    }

    void Client::unsubscribeAll() {
        auto addresses = itemRegistry_.getAllAddresses();
        if (!addresses.empty()) {
            std::vector<size_t> addrVec(addresses.begin(), addresses.end());
            unsubscribe(addrVec).get();
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
        std::async(std::launch::async, [this, future = std::move(future)]() {
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
        auto addresses = itemRegistry_.getAllAddresses();
        if (addresses.empty()) {
            return std::async(std::launch::async, [this]() {
                return Resp::success(this->key_);
            });
        }

        std::vector<Item> itemsToRestore;
        for (auto addr : addresses) {
            if (auto item = itemRegistry_.get(addr)) {
                itemsToRestore.push_back(*item);
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
