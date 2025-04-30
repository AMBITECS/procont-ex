//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_PROCESSOR_H
#define PROCONT_EX_PROCESSOR_H

#include <vector>
#include <map>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <functional>
#include <condition_variable>
#include <string>
#include <atomic>

//#include <stdexcept>
//#include <initializer_list>
//#include <utility>

using namespace std;

template <typename T>
class DataProcessor {
public:
    using TimePoint = chrono::system_clock::time_point;
    struct OnDataChange {
        size_t      index{};
        T           old_value{};
        T           new_value{};
        TimePoint   timestamp;
    };

    using Range = pair<size_t, size_t>;
    using Callback = function<void(const OnDataChange&)>;
    using CallbackID = string;

private:
    queue<OnDataChange> processing_queue_;
    mutex queue_mutex_;
    condition_variable queue_cv_;
    thread worker_thread_;
    atomic<bool> worker_running_{true};
    map<CallbackID, pair<Range, Callback>> subscriptions_;
    mutable shared_mutex subscriptions_mutex_;
    static const Range FULL_RANGE;


    // Проверка диапазона
    bool is_in_range(size_t index, Range range) const {
        return range == FULL_RANGE || (index >= range.first && index <= range.second);
    }

//    bool is_in_range(size_t index, Range range) const {
//        static const Range FULL_RANGE = {0, numeric_limits<size_t>::max()};
//        return range == FULL_RANGE || (index >= range.first && index <= range.second);
//    }

    static CallbackID generate_callback_id() {
        static atomic<size_t> counter{0};
        return "cb_" + to_string(counter++);
    }

public:
    DataProcessor() : worker_thread_(&DataProcessor::worker_function, this) {

    }

    ~DataProcessor() {
        stop_processing();
    }

    // Подписка на изменения
    CallbackID subscribe(Range range, Callback callback, const CallbackID& id_prefix = "") {
        unique_lock lock(subscriptions_mutex_);
        CallbackID id = id_prefix.empty() ? generate_callback_id() : id_prefix + "_" + generate_callback_id();
        subscriptions_.emplace(id, make_pair(range, move(callback)));
        return id;
    }

    // Удобные методы-обёртки
    CallbackID subscribe_to_element(size_t index, Callback callback, const CallbackID& id_prefix = "") {
        return subscribe({index, index}, move(callback), id_prefix);
    }

    CallbackID subscribe_to_all_changes(Callback callback, const CallbackID& id_prefix = "") {
        return subscribe(FULL_RANGE, move(callback), id_prefix);
    }

    // Отписка
    void unsubscribe(const CallbackID& id) {
        unique_lock lock(subscriptions_mutex_);
        subscriptions_.erase(id);
    }

    // Добавление изменения в очередь
    void enqueue(OnDataChange&& change) {
        {
            unique_lock lock(queue_mutex_);
            processing_queue_.push(move(change));
        }
        queue_cv_.notify_one();
    }

    // Остановка обработки
    void stop_processing() {
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
                unique_lock lock(queue_mutex_);
                queue_cv_.wait(lock, [this] {
                    return !processing_queue_.empty() || !worker_running_;
                });

                if (!worker_running_) break;
                if (processing_queue_.empty()) continue;

                change = move(processing_queue_.front());
                processing_queue_.pop();
            }

            process_change(change);
        }
    }

    void process_change(const OnDataChange& change) {
        shared_lock lock(subscriptions_mutex_);
        for (const auto& [id, sub] : subscriptions_) {
            if (is_in_range(change.index, sub.first)) {
                sub.second(change);
            }
        }
    }

};

template <typename T>
const typename DataProcessor<T>::Range DataProcessor<T>::FULL_RANGE =
        {0, numeric_limits<size_t>::max()};


#endif //PROCONT_EX_PROCESSOR_H
