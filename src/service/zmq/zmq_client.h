//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "dto.h"
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

using stdclk = std::chrono::steady_clock;

//-----------------------------------------------------------------------------
// ZmqClient - класс, отражающий поведение одного клиента на стороне сервера
//-----------------------------------------------------------------------------
class ZmqClient {
public:
    // Структура подписки
    struct Subscription {
        std::string              topic;         // тема
        std::vector<std::string> keys;          // ключи тегов
        stdclk::time_point       lastUpdate;    // время последнего обновления
    };

private:
    std::string         id_;
    std::string         host_;
    stdclk::time_point  last_activity_;

    mutable std::mutex                  mutex_;
    std::condition_variable             cv_;
    std::queue<std::shared_ptr<IDto>>   messageQueue_;

    std::unordered_map<std::string, Subscription> subscriptions_;

public:
    explicit ZmqClient(std::string id) : id_(std::move(id)) {}

    void addSubscription(const Subscribe& sub) {
        std::lock_guard<std::mutex> lock(mutex_);
        subscriptions_[sub.topic] = Subscription {sub.topic, sub.keys, stdclk::now()};
    }

    void removeSubscription(const std::string& topic) {
        std::lock_guard<std::mutex> lock(mutex_);
        subscriptions_.erase(topic);
    }

    // постановка в очередь
    void enqueueMessage(const std::shared_ptr<IDto>& dto) {
        std::lock_guard<std::mutex> lock(mutex_);
        messageQueue_.push(dto);
        cv_.notify_one();
    }

    // выборка из очереди
    std::shared_ptr<IDto> getNextMessage(int timeoutMs = 100) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_for(
                lock,
                std::chrono::milliseconds(timeoutMs),
                [this](){ return !messageQueue_.empty(); })
        ) {
            auto dto = messageQueue_.front();
            messageQueue_.pop();
            return dto;
        }
        return nullptr;
    }

    [[nodiscard]] const std::string& getId() const { return id_; }
    [[nodiscard]] std::string getHost() const { return host_; }

    void setHost(const std::string& host) { host_ = host; }

    void updateLastActivity() { last_activity_ = stdclk::now(); }
    [[nodiscard]] auto getLastActivity() const { return last_activity_; }

    [[nodiscard]] std::vector<Subscription> getSubscriptions() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<Subscription> result;
        for (const auto& [_, sub] : subscriptions_) {
            result.push_back(sub);
        }
        return result;
    }
};
