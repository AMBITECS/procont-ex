#ifndef DATA_SERVER_H
#define DATA_SERVER_H

#include <map>
#include <set>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>
#include "variant.h"
#include "on_data_change.h"

class DataServer {
public:
    using Callback = std::function<void(const std::string& key, const OnDataChange&)>;
    using ClientID = std::string;
    using Topic = std::string;
    using TopicMap = std::map<Topic, Callback>;
    using SubscriptionMap = std::map<Topic, std::set<std::string>>;

    // Элемент данных клиента
    struct ClientItem {
        size_t index{};       // Позиция в ObservableVector
        uint64_t mask{};      // Отслеживаемая битовая маска
        VAR_TYPE type{};      // Ожидаемый тип данных
        VARIANT value{};      // Текущее значение
    };
    using ItemMap = std::map<std::string, ClientItem>;

    // Данные клиента
    struct ClientData {
        ItemMap items;          // Упорядоченные по key
        TopicMap topics;        // Упорядоченные по topic
        SubscriptionMap subscriptions; // Упорядоченные подписки
    };
    using ClientMap = std::map<ClientID, ClientData>;

    DataServer() : worker_thread_(&DataServer::worker_function, this) {}
    ~DataServer() { stop_processing(); }

    // API для клиентов
    void addClient(const ClientID& id) {
        std::unique_lock lock(clients_mutex_);
        clients_.try_emplace(id);
    }

    void removeClient(const ClientID& id) {
        std::unique_lock lock(clients_mutex_);
        clients_.erase(id);
    }

    void addItems(const ClientID& id, const std::vector<std::pair<std::string, ClientItem>>& items) {
        std::unique_lock lock(clients_mutex_);
        auto& client = clients_[id];
        for (const auto& [key, item] : items) {
            client.items[key] = item;
        }
    }

    void addTopic(const ClientID& id, const Topic& topic, Callback callback) {
        std::unique_lock lock(clients_mutex_);
        clients_[id].topics[topic] = std::move(callback);
    }

    void subscribe(const ClientID& id, const Topic& topic, const std::vector<std::string>& keys) {
        std::unique_lock lock(clients_mutex_);
        auto& subs = clients_[id].subscriptions[topic];  // Исправлено: было subscriptions -> subscriptions
        for (const auto& key : keys) {
            subs.insert(key);
        }
    }

    void unsubscribe(const ClientID& id, const Topic& topic, const std::vector<std::string>& keys) {
        std::unique_lock lock(clients_mutex_);
        if (auto it = clients_[id].subscriptions.find(topic);
                it != clients_[id].subscriptions.end()) {
            for (const auto& key : keys) {
                it->second.erase(key);
            }
        }
    }

    void enqueue(const std::string& key, OnDataChange&& change) {
        {
            std::lock_guard lock(queue_mutex_);
            processing_queue_.emplace(key, std::move(change));
        }
        queue_cv_.notify_one();
    }

    void stop_processing() noexcept {
        if (worker_running_.exchange(false)) {
            queue_cv_.notify_all();
            if (worker_thread_.joinable()) {
                worker_thread_.join();
            }
        }
    }

private:
    ClientMap clients_;
    mutable std::shared_mutex clients_mutex_;

    std::queue<std::pair<std::string, OnDataChange>> processing_queue_;
    mutable std::mutex queue_mutex_;
    std::condition_variable queue_cv_;

    std::thread worker_thread_;
    std::atomic<bool> worker_running_{true};

    void worker_function() {
        while (worker_running_) {
            std::unique_lock lock(queue_mutex_);
            queue_cv_.wait(lock, [this] {
                return !processing_queue_.empty() || !worker_running_;
            });

            if (!worker_running_) break;
            if (processing_queue_.empty()) continue;

            auto [key, change] = std::move(processing_queue_.front());
            processing_queue_.pop();
            lock.unlock();

            process_change(key, change);
        }
    }

    void process_change(const std::string& key, const OnDataChange& change) {
        std::shared_lock lock(clients_mutex_);

        for (auto& [client_id, client_data] : clients_) {
            if (!client_data.items.count(key)) continue;

            for (auto& [topic, callback] : client_data.topics) {
                if (auto subs = client_data.subscriptions.find(topic);
                        subs != client_data.subscriptions.end() && subs->second.count(key))
                {
                    try {
                        callback(key, change);
                    } catch (...) {
                        // Логирование ошибки
                    }
                }
            }
        }
    }
};

#endif // DATA_SERVER_H

//#ifndef PROCONT_EX_PROCESSOR_H
//#define PROCONT_EX_PROCESSOR_H
//
//#include <map>
//#include <queue>
//#include <mutex>
//#include <shared_mutex>
//#include <thread>
//#include <functional>
//#include <condition_variable>
//#include <atomic>
//#include <unordered_set>
//#include "on_data_change.h"
//#include "variant.h"
//
//class DataProcessor {
//public:
//    using Callback = std::function<void(const OnDataChange&)>;
//    using TagType = int;
//
//    struct Subscription {
//        size_t index;
//        uint64_t bit_mask;
//        Callback callback;
//    };
//
//    DataProcessor() : worker_thread_(&DataProcessor::worker_function, this) {}
//
//    ~DataProcessor() {
//        stop_processing();
//    }
//
//    void subscribe(size_t index, uint64_t bit_mask, Callback callback, TagType tag = 0) {
//        std::unique_lock lock(subscriptions_mutex_);
//        tag_to_subscriptions_[tag].emplace_back(Subscription{index, bit_mask, std::move(callback)});
//        tracked_indices_.insert(index);
//    }
//
//    void unsubscribe_by_tag(TagType tag) {
//        std::unique_lock lock(subscriptions_mutex_);
//        if (auto it = tag_to_subscriptions_.find(tag); it != tag_to_subscriptions_.end()) {
//            tag_to_subscriptions_.erase(it);
//            rebuild_tracked_indices();
//        }
//    }
//
//    void enqueue(OnDataChange&& change) {
//        {
//            std::lock_guard lock(queue_mutex_);
//            processing_queue_.push(std::move(change));
//        }
//        queue_cv_.notify_one();
//    }
//
//    void stop_processing() noexcept {
//        if (worker_running_.exchange(false)) {
//            queue_cv_.notify_all();
//            if (worker_thread_.joinable()) {
//                worker_thread_.join();
//            }
//        }
//    }
//
//    template<typename ValueGetter>
//    void verify_values(ValueGetter&& getter) {
//        std::shared_lock lock(subscriptions_mutex_);
//        for (const auto& index : tracked_indices_) {
//            for (const auto& [tag, subs] : tag_to_subscriptions_) {
//                for (const auto& sub : subs) {
//                    if (sub.index == index) {
//                        try {
//                            auto current_value = getter(index);
//                            OnDataChange change{
//                                    index,
//                                    0, // bit_mask
//                                    VARIANT(), // old_value (не используется при verify)
//                                    convert_to_variant(current_value),
//                                    std::chrono::system_clock::now()
//                            };
//                            enqueue(std::move(change));
//                        } catch (...) {
//                            // Логирование ошибки
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//private:
//    std::map<TagType, std::vector<Subscription>> tag_to_subscriptions_;
//    std::unordered_set<size_t> tracked_indices_;
//    mutable std::shared_mutex subscriptions_mutex_;
//
//    std::queue<OnDataChange> processing_queue_;
//    mutable std::mutex queue_mutex_;
//    std::condition_variable queue_cv_;
//
//    std::thread worker_thread_;
//    std::atomic<bool> worker_running_{true};
//
//    void rebuild_tracked_indices() {
//        tracked_indices_.clear();
//        for (const auto& [tag, subs] : tag_to_subscriptions_) {
//            for (const auto& sub : subs) {
//                tracked_indices_.insert(sub.index);
//            }
//        }
//    }
//
//    void process_change(const OnDataChange& change) {
//        std::shared_lock lock(subscriptions_mutex_);
//        for (const auto& [tag, subs] : tag_to_subscriptions_) {
//            for (const auto& sub : subs) {
//                if (sub.index == change.index &&
//                    (sub.bit_mask == 0 || (sub.bit_mask & change.bit_mask))) {
//                    try {
//                        sub.callback(change);
//                    } catch (...) {
//                        // Логирование ошибки
//                    }
//                }
//            }
//        }
//    }
//
//    void worker_function() {
//        while (worker_running_) {
//            std::unique_lock lock(queue_mutex_);
//            queue_cv_.wait(lock, [this] {
//                return !processing_queue_.empty() || !worker_running_;
//            });
//
//            if (!worker_running_) break;
//            if (processing_queue_.empty()) continue;
//
//            OnDataChange change = std::move(processing_queue_.front());
//            processing_queue_.pop();
//            lock.unlock();
//
//            process_change(change);
//        }
//    }
//
//    template<typename T>
//    static VARIANT convert_to_variant(const T& value) {
//        return VARIANT(value);
//    }
//};
//
//#endif // PROCONT_EX_PROCESSOR_H