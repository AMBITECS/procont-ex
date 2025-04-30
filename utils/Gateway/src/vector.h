//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_VECTOR_H
#define PROCONT_EX_VECTOR_H

#include "processor.h"
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class RangeObservableVector
{
// ----------------------------------------------------------------------------
// vector specific
// ----------------------------------------------------------------------------
// Data
private:
    vector<T> data_;
    mutable shared_mutex data_mutex_;

// Definitions
public:
    using iterator = typename vector<T>::iterator;
    using const_iterator = typename vector<T>::const_iterator;

// Constructor
public:
    ~RangeObservableVector() = default;

    // 1. Конструктор по умолчанию
    RangeObservableVector() = default;

    // 2. Конструктор с указанием размера
    explicit RangeObservableVector(size_t count) {
        unique_lock lock(data_mutex_);
        data_.resize(count);
    }

    // 3. Конструктор с указанием размера и значения по умолчанию
    RangeObservableVector(size_t count, const T& defaultValue) {
        unique_lock lock(data_mutex_);
        data_.assign(count, defaultValue);
    }

    // 4. Конструктор из initializer_list
    RangeObservableVector(initializer_list<T> init) {
        unique_lock lock(data_mutex_);
        data_ = init;
    }

    // 5. Конструктор диапазона [first, last)
    template <class InputIt>
    RangeObservableVector(InputIt first, InputIt last) {
        unique_lock lock(data_mutex_);
        data_.assign(first, last);
    }

    // 6. Конструктор копирования
    RangeObservableVector(const RangeObservableVector& other) {
        shared_lock other_lock(other.data_mutex_);
        unique_lock this_lock(data_mutex_);
        data_ = other.data_;
    }

    // 7. Конструктор перемещения
    RangeObservableVector(RangeObservableVector&& other) noexcept {
        unique_lock other_lock(other.data_mutex_);
        unique_lock this_lock(data_mutex_);
        data_ = move(other.data_);
    }

    // 8. Конструктор с аллокатором (опционально)
    template <class Alloc>
    explicit RangeObservableVector(const Alloc& alloc) : data_(alloc) {}

    // Оператор присваивания
    RangeObservableVector& operator=(const RangeObservableVector& other) {
        if (this != &other) {
            unique_lock lock1(data_mutex_, defer_lock);
            shared_lock lock2(other.data_mutex_, defer_lock);
            lock(lock1, lock2);
            data_ = other.data_;
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    RangeObservableVector& operator=(RangeObservableVector&& other) noexcept {
        if (this != &other) {
            unique_lock lock1(data_mutex_, defer_lock);
            unique_lock lock2(other.data_mutex_, defer_lock);
            lock(lock1, lock2);
            data_ = move(other.data_);
        }
        return *this;
    }

    // Оператор присваивания из initializer_list
    RangeObservableVector& operator=(initializer_list<T> ilist) {
        unique_lock lock(data_mutex_);
        data_ = ilist;
        return *this;
    }

    // Методы доступа к итераторам
    iterator        begin()         { shared_lock lock(data_mutex_); return data_.begin(); }
    const_iterator  begin() const   { shared_lock lock(data_mutex_); return data_.begin(); }
    iterator        end()           { shared_lock lock(data_mutex_); return data_.end();   }
    const_iterator  end() const     { shared_lock lock(data_mutex_); return data_.end();   }

    // Оператор доступа по индексу (без проверки границ)
    T& operator[](size_t index) { shared_lock lock(data_mutex_); return data_[index]; }

    // Константная версия оператора []
    const T& operator[](size_t index) const { shared_lock lock(data_mutex_); return data_[index]; }

    // Метод at() с проверкой границ
    T& at(size_t index) {
        shared_lock lock(data_mutex_);
        if (index >= data_.size()) { throw out_of_range("Index out of range"); }
        return data_[index];
    }

    // Константная версия at()
    const T& at(size_t index) const {
        shared_lock lock(data_mutex_);
        if (index >= data_.size()) { throw out_of_range("Index out of range"); }
        return data_[index];
    }

    // Доступ к первому элементу
    T& front() { shared_lock lock(data_mutex_); return data_.front(); }
    const T& front() const { shared_lock lock(data_mutex_); return data_.front(); }

    // Доступ к последнему элементу
    T& back() { shared_lock lock(data_mutex_); return data_.back(); }
    const T& back() const { shared_lock lock(data_mutex_); return data_.back(); }

    // Прямой доступ к данным (аналог data() у vector)
    T* data() noexcept { shared_lock lock(data_mutex_); return data_.data(); }
    const T* data() const noexcept { shared_lock lock(data_mutex_); return data_.data(); }

    // Размер вектора
    size_t size() const { shared_lock lock(data_mutex_); return data_.size(); }

    // Безопасный доступ ко всему вектору
    template <typename F>
    void access(F&& func) const { shared_lock lock(data_mutex_); func(data_); }

// ----------------------------------------------------------------------------
// callback specific
// ----------------------------------------------------------------------------
public:
    using TimePoint = chrono::system_clock::time_point;
    struct ChangeEvent {
        size_t index{};
        T old_value{};
        T new_value{};
        TimePoint timestamp{};
    };

//    using CallbackID    = string;
//    using Range         = pair<size_t, size_t>;
//    using Processor     = typename DataProcessor<T>::Callback;
//    using OnDataChange  = typename DataProcessor<T>::OnDataChange;
//    using RangeCallback = function<void(const ChangeEvent&)>;

private:
//    map<CallbackID, pair<Range, RangeCallback>> subscriptions_;
//    mutable mutex subscriptions_mutex_;
//    static const Range FULL_RANGE;

    DataProcessor<T> processor_;

//    // Добавление элемента
//    void push_back(const T& value) {
//        unique_lock lock(data_mutex_);
//        size_t index = data_.size();
//        data_.push_back(value);
//        lock.unlock();
//
//        notify_add(index, value);
//    }
//
//    // Изменение элемента
//    void set(size_t index, const T& value) {
//        unique_lock lock(data_mutex_);
//        if (index >= data_.size()) {
//            throw out_of_range("Index out of range");
//        }
//
//        T old_value = data_[index];
//        data_[index] = value;
//        lock.unlock();
//
//        notify_change(index, old_value, value);
//    }

// Добавление элемента
    void push_back(const T& value) {
        unique_lock lock(data_mutex_);
        size_t index = data_.size();
        data_.push_back(value);
        lock.unlock();

        notify_change(index, T{}, value);
    }

    // Изменение элемента
    void set(size_t index, const T& value) {
        unique_lock lock(data_mutex_);
        if (index >= data_.size()) {
            throw out_of_range("Index out of range");
        }

        T old_value = data_[index];
        data_[index] = value;
        lock.unlock();

        notify_change(index, old_value, value);
    }

//    // Установка обработчика для процессора
//    void set_processor(Processor callback) {
//        processor_.set_callback(move(callback));
//    }

    // Доступ к процессору для управления подписками
    DataProcessor<T>& get_processor() { return processor_; }
    const DataProcessor<T>& get_processor() const { return processor_; }

//    // Подписка на изменения
//    // ------------------------------------------------------------------------
//    CallbackID subscribe(Range range, RangeCallback callback, const CallbackID& id_prefix = "") {
//        unique_lock lock(subscriptions_mutex_);
//        CallbackID id = id_prefix.empty() ? generate_callback_id() : id_prefix + "_" + generate_callback_id();
//        subscriptions_.emplace(id, make_pair(range, move(callback)));
//        return id;
//    }
//
//    // Удобные методы-обёртки
//    CallbackID subscribe_to_element(size_t index, RangeCallback callback, const CallbackID& id_prefix = "") {
//        return subscribe({index, index}, move(callback), id_prefix);
//    }
//
//    CallbackID subscribe_to_all_changes(RangeCallback callback, const CallbackID& id_prefix = "") {
//        return subscribe(FULL_RANGE, move(callback), id_prefix);
//    }
//
//    // Отписка
//    void unsubscribe(const CallbackID& id) {
//        unique_lock lock(subscriptions_mutex_);
//        subscriptions_.erase(id);
//    }

private:
//    // Генерация уникального ID
//    static CallbackID generate_callback_id() {
//        static atomic<size_t> counter{0};
//        return "cb_" + to_string(counter++);
//    }

//    // Проверка диапазона
//    bool is_in_range(size_t index, Range range) const {
//        return range == FULL_RANGE || (index >= range.first && index <= range.second);
//    }

    // Уведомление об изменении
//    void notify_change(size_t index, const T& old_value, const T& new_value) {
//        ChangeEvent event{
//                index,
//                old_value,
//                new_value,
//                chrono::system_clock::now()
//        };
//
//        // Отправка в процессор
//        processor_.enqueue({new_value, event.timestamp, index});
//
//        // Вызов подписчиков
//        shared_lock lock(subscriptions_mutex_);
//        for (const auto& [id, sub] : subscriptions_) {
//            if (is_in_range(index, sub.first)) {
//                sub.second(event);
//            }
//        }
//    }

    void notify_change(size_t index, const T& old_value, const T& new_value) {
        typename DataProcessor<T>::OnDataChange change{
                index,
                old_value,
                new_value,
                chrono::system_clock::now()
        };
        processor_.enqueue(move(change));
    }

//    // Уведомление о добавлении
//    void notify_add(size_t index, const T& new_value) {
//        static T empty{};
//        notify_change(index, empty, new_value);
//    }
};

//template <typename T>
//const typename RangeObservableVector<T>::Range RangeObservableVector<T>::FULL_RANGE =
//        {0, numeric_limits<size_t>::max()};
//
#endif //PROCONT_EX_VECTOR_H
