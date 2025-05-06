//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_PROCESSOR_H
#define PROCONT_EX_PROCESSOR_H

#include <map>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <variant>
#include "on_data_change.h"
#include "variant.h"

class DataProcessor //: public IDataProcessor
{
public:
    using Callback = std::function<void(const OnDataChange&)>;
    using CallbackID = std::string;

    DataProcessor() : worker_thread_(&DataProcessor::worker_function, this) {}

    ~DataProcessor() { stop_processing(); }

    CallbackID subscribe(size_t index, uint64_t bit_mask, Callback callback) {
        std::unique_lock<std::shared_mutex> lock(subscriptions_mutex_);
        CallbackID id = generate_callback_id();
        subscriptions_[id] = {index, bit_mask, std::move(callback)};
        return id;
    }

    void unsubscribe(const CallbackID& id) {
        std::unique_lock<std::shared_mutex> lock(subscriptions_mutex_);
        subscriptions_.erase(id);
    }

    void enqueue(OnDataChange&& change) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            processing_queue_.push(std::move(change));
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
    struct Subscription {
        size_t index{};
        uint64_t bit_mask{}; // 0 - все изменения, иначе маска битов
        Callback callback{};
    };

    void worker_function() {
        while (worker_running_) {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            queue_cv_.wait(lock, [this] {
                return !processing_queue_.empty() || !worker_running_;
            });

            if (!worker_running_) break;
            if (processing_queue_.empty()) continue;

            OnDataChange change = std::move(processing_queue_.front());
            processing_queue_.pop();
            lock.unlock();

            try {
                process_change(change);
            } catch (...) { /* Log exception */ }
        }
    }

    void process_change(const OnDataChange& change) {
        std::shared_lock<std::shared_mutex> lock(subscriptions_mutex_);

        for (const auto& [id, sub] : subscriptions_) {
            if (sub.index == change.index) {
                // Если подписка на все изменения или совпадают маски
                if (sub.bit_mask == 0 || (sub.bit_mask & change.bit_mask)) {
                    try {
                        sub.callback(change);
                    } catch (...) {
                        // Обработка ошибок
                    }
                }
            }
        }
    }

    static CallbackID generate_callback_id() {
        static std::atomic<size_t> counter{0};
        return "cb_" + std::to_string(counter++);
    }

    std::queue<OnDataChange> processing_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::thread worker_thread_;
    std::atomic<bool> worker_running_{true};

    std::map<CallbackID, Subscription> subscriptions_;
    mutable std::shared_mutex subscriptions_mutex_;

};

#endif //PROCONT_EX_PROCESSOR_H