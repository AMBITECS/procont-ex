//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
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
#include <string>
#include <atomic>
#include <limits>
#include <utility>
#include <memory>
#include "on_data_change.h"

/**
 * @brief Class for processing data change notifications
 */
class DataProcessor {
public:
    using TimePoint = std::chrono::system_clock::time_point;
    using Range = std::pair<size_t, size_t>;
    using Callback = std::function<void(const OnDataChange&)>;
    using CallbackID = std::string;

    /**
     * @brief Construct a new DataProcessor object
     */
    DataProcessor() : worker_thread_(&DataProcessor::worker_function, this) {}

    /**
     * @brief Destroy the DataProcessor object
     */
    ~DataProcessor() { stop_processing(); }

    /**
     * @brief Subscribe to changes within a specific range
     * @param range Range of indices to monitor
     * @param callback Callback function
     * @param id_prefix Optional prefix for callback ID
     * @return Unique callback ID
     */
    CallbackID subscribe(Range range, Callback callback, const CallbackID& id_prefix = "") {
        std::unique_lock<std::shared_mutex> lock(subscriptions_mutex_);
        CallbackID id = id_prefix.empty() ? generate_callback_id() : id_prefix + "_" + generate_callback_id();
        subscriptions_.emplace(id, std::make_pair(range, std::move(callback)));
        return id;
    }

    /**
     * @brief Subscribe to changes of a single element
     * @param index Index of element to monitor
     * @param callback Callback function
     * @param id_prefix Optional prefix for callback ID
     * @return Unique callback ID
     */
    CallbackID subscribe_to_one(size_t index, Callback callback, const CallbackID& id_prefix = "") {
        return subscribe({index, index}, std::move(callback), id_prefix);
    }

    /**
     * @brief Subscribe to all changes
     * @param callback Callback function
     * @param id_prefix Optional prefix for callback ID
     * @return Unique callback ID
     */
    CallbackID subscribe_to_all(Callback callback, const CallbackID& id_prefix = "") {
        return subscribe(FULL_RANGE, std::move(callback), id_prefix);
    }

    /**
     * @brief Unsubscribe from changes
     * @param id Callback ID returned by subscribe
     */
    void unsubscribe(const CallbackID& id) {
        std::unique_lock<std::shared_mutex> lock(subscriptions_mutex_);
        subscriptions_.erase(id);
    }

    /**
     * @brief Enqueue a change notification for processing
     * @param change Change data to enqueue
     */
    void enqueue(OnDataChange&& change) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            processing_queue_.push(std::move(change));
        }
        queue_cv_.notify_one();
    }

    /**
     * @brief Stop processing thread
     */
    void stop_processing() noexcept {
        if (worker_running_.exchange(false)) {
            queue_cv_.notify_all();
            if (worker_thread_.joinable()) {
                worker_thread_.join();
            }
        }
    }

private:
    void worker_function() {
        while (worker_running_) {
            OnDataChange change;

            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                queue_cv_.wait(lock, [this] {
                    return !processing_queue_.empty() || !worker_running_;
                });

                if (!worker_running_) break;
                if (processing_queue_.empty()) continue;

                change = std::move(processing_queue_.front());
                processing_queue_.pop();
            }

            try {
                process_change(change);
            } catch (...) {
                // Log or handle exception
            }
        }
    }

    void process_change(const OnDataChange& change) {
        std::shared_lock<std::shared_mutex> lock(subscriptions_mutex_);
        for (const auto& [id, sub] : subscriptions_) {
            if (is_in_range(change.index, sub.first)) {
                try {
                    sub.second(change);
                } catch (...) {
                    // Log or handle callback exception
                }
            }
        }
    }

    static bool is_in_range(size_t index, Range range) noexcept {
        return range == FULL_RANGE || (index >= range.first && index <= range.second);
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

    std::map<CallbackID, std::pair<Range, Callback>> subscriptions_;
    mutable std::shared_mutex subscriptions_mutex_;

    constexpr static const Range FULL_RANGE = {0, std::numeric_limits<size_t>::max()};
};

//const DataProcessor::Range DataProcessor::FULL_RANGE = {0, std::numeric_limits<size_t>::max()};

#endif //PROCONT_EX_PROCESSOR_H