//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H
#define PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H

#include <utility>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <initializer_list>
#include <limits>
#include <chrono>
#include <string>
#include <type_traits>
#include <atomic>
#include <algorithm>
#include <optional>
#include "processor.h"
#include "on_data_change.h"
#include "variant.h"

template <typename T>
class ObservableVector {
    static_assert(
            std::is_same_v<T, T_BOOL>   || std::is_same_v<T, T_BOOL*>   ||
            std::is_same_v<T, T_SINT8>  || std::is_same_v<T, T_SINT8*>  ||
            std::is_same_v<T, T_SINT16> || std::is_same_v<T, T_SINT16*> ||
            std::is_same_v<T, T_SINT32> || std::is_same_v<T, T_SINT32*> ||
            std::is_same_v<T, T_SINT64> || std::is_same_v<T, T_SINT64*> ||
            std::is_same_v<T, T_UINT8>  || std::is_same_v<T, T_UINT8*>  ||
            std::is_same_v<T, T_UINT16> || std::is_same_v<T, T_UINT16*> ||
            std::is_same_v<T, T_UINT32> || std::is_same_v<T, T_UINT32*> ||
            std::is_same_v<T, T_UINT64> || std::is_same_v<T, T_UINT64*> ||
            std::is_same_v<T, T_REAL32> || std::is_same_v<T, T_REAL32*> ||
            std::is_same_v<T, T_REAL64> || std::is_same_v<T, T_REAL64*> ||
            std::is_same_v<T, std::string> || std::is_same_v<T, std::string*>,
            "Type T must be VAR_TYPE compatible or pointer to VAR_TYPE compatible"
    );

    template<typename U>
    struct is_pointer_to_var_type : std::false_type {};

    template<typename U>
    struct is_pointer_to_var_type<U*> :
            std::bool_constant<
                    std::is_same_v<U, T_BOOL>   ||
                    std::is_same_v<U, T_SINT8>  ||
                    std::is_same_v<U, T_SINT16> ||
                    std::is_same_v<U, T_SINT32> ||
                    std::is_same_v<U, T_SINT64> ||
                    std::is_same_v<U, T_UINT8>  ||
                    std::is_same_v<U, T_UINT16> ||
                    std::is_same_v<U, T_UINT32> ||
                    std::is_same_v<U, T_UINT64> ||
                    std::is_same_v<U, T_REAL32> ||
                    std::is_same_v<U, T_REAL64> ||
                    std::is_same_v<U, std::string>
            > {};

protected:
    static constexpr bool is_pointer = is_pointer_to_var_type<T>::value;
    using value_type = std::conditional_t<is_pointer, std::remove_pointer_t<T>, T>;

public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using TimePoint = std::chrono::system_clock::time_point;

    template <bool IsConst>
    class BasicProxy {
    public:
        using VectorType = std::conditional_t<IsConst, const ObservableVector, ObservableVector>;
        //using ValueType = std::conditional_t<IsConst, const value_type, value_type>;
        using reference = std::conditional_t<IsConst, const value_type&, value_type&>;

        BasicProxy(VectorType& vec, size_t index) : vec_(vec), index_(index) {
            if constexpr (!IsConst && is_pointer) {
                if (auto ptr = vec_.get_pointer(index_)) {
                    old_value_ = *ptr;
                }
            }
        }

        operator value_type() const { //NOLINT
            return vec_.get_at_index(index_);
        }

        template <bool C = IsConst, typename = std::enable_if_t<!C>>
        BasicProxy& operator=(const value_type& value) {
            if constexpr (is_pointer) {
                auto ptr = vec_.get_pointer(index_);
                if (!ptr) throw std::runtime_error("Cannot assign to nullptr");

                value_type old_value = *ptr;
                *ptr = value;
                if (old_value != value) {
                    vec_.notify_change(index_, old_value, value);
                }
            } else {
                vec_.set(index_, value);
            }
            return *this;
        }

        reference operator*() {
            if constexpr (is_pointer) {
                auto ptr = vec_.get_pointer(index_);
                if (!ptr) throw std::runtime_error("Dereferencing nullptr");
                if constexpr (!IsConst) {
                    old_value_ = *ptr;
                }
                return *ptr;
            } else {
                return vec_[index_];
            }
        }

        const value_type& operator*() const {
            if constexpr (is_pointer) {
                auto ptr = vec_.get_pointer(index_);
                if (!ptr) throw std::runtime_error("Dereferencing nullptr");
                return *ptr;
            } else {
                return vec_[index_];
            }
        }

        ~BasicProxy() {
            if constexpr (!IsConst && is_pointer) {
                if (old_value_) {
                    auto ptr = vec_.get_pointer(index_);
                    if (ptr && *ptr != *old_value_) {  // Проверка изменения
                        vec_.notify_change(index_, *old_value_, *ptr);
                    }
                }
            }
        }

    private:
        VectorType& vec_;
        size_t index_;
        std::optional<value_type> old_value_;
    };

    using Proxy = BasicProxy<false>;
    using ConstProxy = BasicProxy<true>;

    ObservableVector() = default;
    explicit ObservableVector(std::shared_ptr<DataProcessor> processor)
            : processor_(std::move(processor)) {}

    explicit ObservableVector(size_type count) {
        data_.resize(count);
    }

    ObservableVector(size_type count, const value_type& defaultValue) {
        if constexpr (!is_pointer) {
            data_.resize(count, defaultValue);
        } else {
            data_.resize(count, nullptr);
        }
    }

    ObservableVector(std::initializer_list<value_type> init) : data_(init) {}

    template<class InputIt>
    ObservableVector(InputIt first, InputIt last) : data_(first, last) {}

    ObservableVector(const ObservableVector& other) {
        std::shared_lock lock(other.data_mutex_);
        data_ = other.data_;
        processor_ = other.processor_;
    }

    ObservableVector(ObservableVector&& other) noexcept {
        std::unique_lock lock(other.data_mutex_);
        data_ = std::move(other.data_);
        processor_ = std::move(other.processor_);
        other.data_.clear();
    }

    ~ObservableVector() noexcept {
        try {
            std::unique_lock lock(data_mutex_);
            data_.clear();
        } catch (...) {
            // Подавить исключения
        }
    }

    ObservableVector& operator=(const ObservableVector& other) {
        if (this != &other) {
            std::unique_lock lock1(data_mutex_, std::defer_lock);
            std::shared_lock lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_ = other.data_;
            processor_ = other.processor_;
        }
        return *this;
    }

    ObservableVector& operator=(ObservableVector&& other) noexcept {
        if (this != &other) {
            std::unique_lock lock1(data_mutex_, std::defer_lock);
            std::unique_lock lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_ = std::move(other.data_);
            processor_ = std::move(other.processor_);
            other.data_.clear();
        }
        return *this;
    }

    ObservableVector& operator=(std::initializer_list<value_type> ilist) {
        std::unique_lock lock(data_mutex_);
        data_ = ilist;
        lock.unlock();

        for (size_type i = 0; i < data_.size(); ++i) {
            notify_change(i, value_type{}, get_at_index(i));
        }
        return *this;
    }

    Proxy at(size_type pos) {
        if (pos >= size()) throw std::out_of_range("Index out of range");
        return Proxy(*this, pos);
    }

    ConstProxy at(size_type pos) const {
        if (pos >= size()) throw std::out_of_range("Index out of range");
        return ConstProxy(*this, pos);
    }

    Proxy operator[](size_type pos) {
        return Proxy(*this, pos);
    }

    ConstProxy operator[](size_type pos) const {
        return ConstProxy(*this, pos);
    }

    value_type get_at_index(size_type pos) const {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        if constexpr (is_pointer) {
            if (data_[pos] == nullptr) {
                throw std::runtime_error("Null pointer dereference");
            }
            return *data_[pos];
        } else {
            return data_[pos];
        }
    }

    pointer get_pointer(size_type pos) {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) return nullptr;
        if constexpr (is_pointer) {
            return data_[pos]; // Возвращаем хранимый указатель
        } else {
            return &data_[pos]; // Возвращаем адрес элемента
        }
    }

    void set(size_type pos, const value_type& value, uint64_t bit_mask = 0) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) throw std::out_of_range("Index out of range");

        value_type old_value = get_at_index(pos);
        if (old_value != value) {
            if constexpr (is_pointer) {
                if (!data_[pos]) throw std::runtime_error("Cannot set value for nullptr pointer");
                *data_[pos] = value;
            } else {
                data_[pos] = value;
            }
            lock.unlock();
            notify_change(pos, old_value, value, bit_mask);
        }
    }

    Proxy front() {
        if (empty())  throw std::out_of_range("Vector is empty");
        return Proxy(*this, 0);
    }

    ConstProxy front() const {
        if (empty())  throw std::out_of_range("Vector is empty");
        return ConstProxy(*this, 0);
    }

    Proxy back() {
        if (empty())  throw std::out_of_range("Vector is empty");
        return Proxy(*this, size() - 1);
    }

    ConstProxy back() const {
        if (empty())  throw std::out_of_range("Vector is empty");
        return ConstProxy(*this, size() - 1);
    }

    pointer data() noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.data();
    }

    const_pointer data() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.data();
    }

    iterator begin() noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.begin();
    }

    const_iterator begin() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.begin();
    }

    const_iterator cbegin() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.cbegin();
    }

    iterator end() noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.end();
    }

    const_iterator end() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.end();
    }

    const_iterator cend() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.cend();
    }

    bool empty() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.empty();
    }

    size_type size() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.size();
    }

    size_type max_size() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.max_size();
    }

    size_type capacity() const noexcept {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        return data_.capacity();
    }

    void reserve(size_type new_cap) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.reserve(new_cap);
    }

    void shrink_to_fit() {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.shrink_to_fit();
    }

    void clear() {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);

        if constexpr (is_pointer) {
            // Для указателей сначала собираем старые значения
            std::vector<value_type> old_values;
            old_values.reserve(data_.size());
            for (auto ptr : data_) {
                old_values.push_back(ptr ? *ptr : value_type{});
            }

            // Очищаем вектор (без удаления памяти, так как не владеем указателями)
            data_.clear();
            lock.unlock();

            // Уведомляем об удалении всех элементов
            for (size_type i = 0; i < old_values.size(); ++i) {
                notify_change(i, old_values[i], value_type{});
            }
        } else {
            // Для обычных значений просто очищаем
            data_.clear();
            // Уведомления не требуются, так как весь вектор очищен
        }
    }

    // Версия с count и value
    void assign(size_type count, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.assign(count, value);
        lock.unlock();

        // Уведомляем об изменении всех элементов
        for (size_type i = 0; i < count; ++i) {
            notify_change(i, value_type{}, is_pointer ? (value ? *value : value_type{}) : value);
        }
    }

    // Версия с итераторами
    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.assign(first, last);
        lock.unlock();

        // Уведомляем об изменении всех элементов
        for (size_type i = 0; i < data_.size(); ++i) {
            value_type new_value;
            if constexpr (is_pointer) {
                new_value = data_[i] ? *data_[i] : value_type{};
            } else {
                new_value = data_[i];
            }
            notify_change(i, value_type{}, new_value);
        }
    }

// Вставка одного элемента
    iterator insert(const_iterator pos, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = pos - data_.cbegin();
        auto it = data_.insert(pos, value);
        lock.unlock();

        notify_change(index, value_type{}, is_pointer ? (value ? *value : value_type{}) : value);
        return it;
    }

// Вставка с перемещением
    iterator insert(const_iterator pos, value_type&& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = pos - data_.cbegin();
        auto it = data_.insert(pos, std::move(value));
        lock.unlock();

        value_type new_value;
        if constexpr (is_pointer) {
            new_value = *data_[index];
        } else {
            new_value = data_[index];
        }
        notify_change(index, value_type{}, new_value);
        return it;
    }

// Вставка count элементов
    iterator insert(const_iterator pos, size_type count, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = pos - data_.cbegin();
        auto it = data_.insert(pos, count, value);
        lock.unlock();

        for (size_type i = 0; i < count; ++i) {
            notify_change(index + i, value_type{}, is_pointer ? (value ? *value : value_type{}) : value);
        }
        return it;
    }

    // Вставка диапазона
    template<class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = pos - data_.cbegin();
        auto it = data_.insert(pos, first, last);
        size_type count = std::distance(first, last);
        lock.unlock();

        for (size_type i = 0; i < count; ++i) {
            value_type new_value;
            if constexpr (is_pointer) {
                new_value = data_[index + i] ? *data_[index + i] : value_type{};
            } else {
                new_value = data_[index + i];
            }
            notify_change(index + i, value_type{}, new_value);
        }
        return it;
    }

// Удаление одного элемента
    iterator erase(const_iterator pos) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = pos - data_.cbegin();
        value_type old_value = get_at_index(index);
        auto it = data_.erase(pos);
        lock.unlock();

        notify_change(index, old_value, value_type{});
        return it;
    }

    // Удаление диапазона
    iterator erase(const_iterator first, const_iterator last) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type first_index = first - data_.cbegin();
        size_type count = std::distance(first, last);

        // Собираем старые значения
        std::vector<value_type> old_values;
        old_values.reserve(count);
        for (auto it = first; it != last; ++it) {
            if constexpr (is_pointer) {
                old_values.push_back(*it ? **it : value_type{});
            } else {
                old_values.push_back(*it);
            }
        }

        auto it = data_.erase(first, last);
        lock.unlock();

        // Уведомляем об удалении
        for (size_type i = 0; i < count; ++i) {
            notify_change(first_index + i, old_values[i], value_type{});
        }
        return it;
    }

    void push_back(const T& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        data_.push_back(value);
        lock.unlock();

        if constexpr (is_pointer) {
            notify_change(index, value_type{}, *value);
        } else {
            notify_change(index, value_type{}, value);
        }
    }

    void push_back(T&& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        data_.push_back(std::move(value));
        lock.unlock();

        if constexpr (is_pointer) {
            notify_change(index, value_type{}, *data_.back());
        } else {
            notify_change(index, value_type{}, data_.back());
        }
    }

    template<class... Args>
    T& emplace_back(Args&&... args) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        data_.emplace_back(std::forward<Args>(args)...);
        T& new_value = data_.back();
        lock.unlock();

        if constexpr (is_pointer) {
            notify_change(index, value_type{}, *new_value);
        } else {
            notify_change(index, value_type{}, new_value);
        }
        return new_value;
    }

    void pop_back() {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (data_.empty()) {
            throw std::out_of_range("Vector is empty");
        }
        value_type old_value = get_at_index(data_.size() - 1);
        data_.pop_back();
        lock.unlock();

        notify_change(data_.size(), old_value, value_type{});
    }

    void resize(size_type count) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type old_size = data_.size();
        data_.resize(count);
        lock.unlock();

        if (count > old_size) {
            for (size_type i = old_size; i < count; ++i) {
                notify_change(i, value_type{}, get_at_index(i));
            }
        }
    }

    void resize(size_type count, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type old_size = data_.size();

        if (count == old_size) return;

        if (count < old_size) {
            // Уменьшение размера
            for (size_type i = count; i < old_size; ++i) {
                value_type old_value = get_at_index(i); // Используем существующий метод
                lock.unlock();
                notify_change(i, old_value, value_type{});
                lock.lock();
            }
            data_.resize(count);
        } else {
            // Увеличение размера
            data_.reserve(count);
            for (size_type i = old_size; i < count; ++i) {
                data_.push_back(value); // Просто копируем значение (для указателей - копируем сам указатель)
                value_type new_value;
                if constexpr (is_pointer) {
                    new_value = value ? *value : value_type{};
                } else {
                    new_value = value;
                }
                lock.unlock();
                notify_change(i, value_type{}, new_value);
                lock.lock();
            }
        }
    }

    void swap(ObservableVector& other) noexcept {
        if (this != &other) {
            std::unique_lock<std::shared_mutex> lock1(data_mutex_, std::defer_lock);
            std::unique_lock<std::shared_mutex> lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_.swap(other.data_);
        }
    }

    template <typename U = T, std::enable_if_t<std::is_integral_v<value_type>, int> = 0>
    value_type fetch_add(size_type pos, value_type value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        value_type old_value = get_at_index(pos);
        value_type new_value = old_value + value;
        if constexpr (is_pointer) {
            *data_[pos] = new_value;
        } else {
            data_[pos] = new_value;
        }
        lock.unlock();

        notify_change(pos, old_value, new_value);
        return old_value;
    }

    template <typename U = T, std::enable_if_t<std::is_integral_v<value_type>, int> = 0>
    value_type fetch_sub(size_type pos, value_type value) {
        return fetch_add(pos, -value);
    }

    template<typename F>
    void access(F&& func) const {
        std::shared_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            std::vector<value_type> values;
            values.reserve(data_.size());
            for (auto ptr : data_) {
                values.push_back(ptr ? *ptr : value_type{});
            }
            func(values);
        } else {
            func(data_);
        }
    }

    template<typename F>
    void modify(F&& func) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);

        if constexpr (is_pointer) {
            // Для случая с указателями
            std::vector<value_type> old_values;
            old_values.reserve(data_.size());
            for (auto ptr : data_) {
                old_values.push_back(ptr ? *ptr : value_type{});
            }

            // Создаем копию для модификации
            std::vector<value_type> new_values = old_values;

            // Применяем функцию модификации
            func(new_values);

            // Применяем изменения и отправляем уведомления
            for (size_type i = 0; i < data_.size(); ++i) {
                if (data_[i]) {
                    if (new_values[i] != old_values[i]) {
                        *data_[i] = new_values[i];
                        lock.unlock();
                        notify_change(i, old_values[i], new_values[i]);
                        lock.lock();
                    }
                }
            }
        } else {
            // Для обычных значений
            std::vector<value_type> old_values = data_;

            // Применяем функцию модификации
            func(data_);

            // Отправляем уведомления об изменениях
            for (size_type i = 0; i < data_.size(); ++i) {
                if (data_[i] != old_values[i]) {
                    lock.unlock();
                    notify_change(i, old_values[i], data_[i]);
                    lock.lock();
                }
            }
        }
    }

    std::shared_ptr<DataProcessor> get_processor() noexcept {
        return processor_;
    }

    std::shared_ptr<const DataProcessor> get_processor() const noexcept {
        return processor_;
    }

    void set_processor(std::shared_ptr<DataProcessor> processor) {
        processor_ = std::move(processor);
    }

    void notify_change(
            size_type index,
            const value_type& old_value,
            const value_type& new_value,
            uint8_t bit_mask = 0
    ) {
        if (!processor_ || old_value == new_value) return;

        processor_->enqueue(OnDataChange(
                index,
                bit_mask,
                convert_to_variant(old_value),
                convert_to_variant(new_value)
        ));
    }

protected:
    VARIANT convert_to_variant(const value_type& value) const {
        return VARIANT(value);
    }

private:
    std::vector<T> data_;
    mutable std::shared_mutex data_mutex_;
    std::shared_ptr<DataProcessor> processor_;
};

#endif // PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H