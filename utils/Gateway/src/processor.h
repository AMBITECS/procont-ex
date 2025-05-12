//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <map>
#include <set>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>
#include <exception>
#include <iostream>
#include "variant.h"

struct OnDataChange {
    using TimeStamp = std::chrono::system_clock::time_point;

    std::string key;
    uint64_t bit_mask;
    VARIANT old_value;
    VARIANT new_value;
    TimeStamp timestamp;

    OnDataChange(std::string k, uint64_t mask, VARIANT old_val, VARIANT new_val,
                 TimeStamp time = std::chrono::system_clock::now())
            : key(std::move(k)), bit_mask(mask),
              old_value(std::move(old_val)),
              new_value(std::move(new_val)),
              timestamp(time) {}

    [[nodiscard]] bool is_bit_change() const noexcept {
        return bit_mask != 0;
    }
};

class DataServer {
public:
    using Callback = std::function<void(const std::vector<OnDataChange>&)>;
    using ClientID = std::string;
    using Topic = std::string;
    using TopicMap = std::map<Topic, Callback>;
    using SubscriptionMap = std::map<Topic, std::set<std::string>>;

    struct ClientItem {
        size_t index{};
        uint64_t mask{};
        VAR_TYPE type{};
        VARIANT value{};
    };
    using ItemMap = std::map<std::string, ClientItem>;

    struct ClientData {
        ItemMap items;
        TopicMap topics;
        SubscriptionMap subscriptions;
    };
    using ClientMap = std::map<ClientID, ClientData>;

    DataServer() : worker_thread_(&DataServer::worker_function, this) {}
    ~DataServer() { stop_processing(); }

    void addClient(const ClientID& id) {
        std::unique_lock lock(clients_mutex_);
        clients_.try_emplace(id);
    }

    void removeClient(const ClientID& id) {
        std::unique_lock lock(clients_mutex_);
        clients_.erase(id);
    }

    void addItems(const ClientID& id, const ItemMap& items) {
        std::unique_lock lock(clients_mutex_);
        auto& client = clients_[id];
        client.items.insert(items.begin(), items.end());
    }

    void addTopic(const ClientID& id, const Topic& topic, Callback callback) {
        std::unique_lock lock(clients_mutex_);
        clients_[id].topics[topic] = std::move(callback);
    }

    void removeTopic(const ClientID& id, const Topic& topic) {
        std::unique_lock lock(clients_mutex_);
        clients_[id].topics.erase(topic);
    }

    void subscribe(const ClientID& id, const Topic& topic, const std::set<std::string>& keys) {
        std::unique_lock lock(clients_mutex_);
        auto& subs = clients_[id].subscriptions[topic];
        subs.insert(keys.begin(), keys.end());
    }

    void unsubscribe(const ClientID& id, const Topic& topic, const std::set<std::string>& keys) {
        std::unique_lock lock(clients_mutex_);
        if (auto it = clients_[id].subscriptions.find(topic); it != clients_[id].subscriptions.end()) {
            for (const auto& key : keys) {
                it->second.erase(key);
            }
        }
    }

    void enqueue(const std::string& key, OnDataChange&& change) {
        if (enable_logging_) {
            log_message(change);
        }

        {
            std::lock_guard lock(queue_mutex_);
            processing_queue_.emplace(key, std::move(change));
        }
        queue_cv_.notify_one();
    }

    void stop_processing() noexcept {
        if (worker_running_.exchange(false)) {
            queue_cv_.notify_all();
        }
    }

    void enable_logging(bool enable) noexcept {
        enable_logging_ = enable;
    }

private:
    ClientMap clients_;
    mutable std::mutex clients_mutex_;
    std::queue<std::pair<std::string, OnDataChange>> processing_queue_;
    mutable std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::thread worker_thread_;
    std::atomic<bool> worker_running_{true};
    std::atomic<bool> enable_logging_{false};

    void worker_function() {
        using namespace std::chrono_literals;

        std::vector<OnDataChange> batch_changes;

        while (worker_running_) {
            batch_changes.clear();

            {
                std::unique_lock lock(queue_mutex_);
                queue_cv_.wait_for(lock, 100ms, [this] {
                    return !processing_queue_.empty() || !worker_running_;
                });

                if (!worker_running_) break;

                while (!processing_queue_.empty()) {
                    batch_changes.emplace_back(std::move(processing_queue_.front().second));
                    processing_queue_.pop();
                }
            }

            if (!batch_changes.empty()) {
                process_changes(batch_changes);
            }
        }
    }

    void process_changes(const std::vector<OnDataChange>& changes) {
        std::lock_guard lock(clients_mutex_);

        for (auto& [client_id, client_data] : clients_) {
            for (auto& [topic, callback] : client_data.topics) {
                std::vector<OnDataChange> filtered_changes;

                for (const auto& change : changes) {
                    if (auto subs = client_data.subscriptions.find(topic);
                            subs != client_data.subscriptions.end() &&
                            subs->second.count(change.key) &&
                            client_data.items.count(change.key)) {
                        filtered_changes.push_back(change);
                    }
                }

                if (!filtered_changes.empty()) {
                    try {
                        callback(filtered_changes);
                    } catch (const std::exception& e) {
                        log_error(client_id, topic, e.what());
                    } catch (...) {
                        log_error(client_id, topic, "Unknown error");
                    }
                }
            }
        }
    }

    void log_message(const OnDataChange& change) {
        std::lock_guard lock(queue_mutex_);
        std::cout << "[LOG] Key: " << change.key
                  << " Old: " << change.old_value
                  << " New: " << change.new_value
                  << std::endl;
    }

    void log_error(const ClientID& client, const Topic& topic, const std::string& error) {
        std::lock_guard lock(queue_mutex_);
        std::cerr << "[ERROR] Client: " << client
                  << " Topic: " << topic
                  << " Error: " << error
                  << std::endl;
    }
};
