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

protected:
    static constexpr bool is_pointer = std::is_pointer_v<T>;
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

    template <bool IsConst>
    class BasicProxy {
    public:
        using VectorType = std::conditional_t<IsConst, const ObservableVector, ObservableVector>;

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
                *ptr = value;
            } else {
                vec_.set(index_, value);
            }
            return *this;
        }

        ~BasicProxy() {
            if constexpr (!IsConst && is_pointer) {
                if (old_value_) {
                    auto ptr = vec_.get_pointer(index_);
                    if (ptr && *ptr != *old_value_) {
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

    // Конструкторы
    ObservableVector() = default;
    explicit ObservableVector(std::shared_ptr<DataProcessor> processor)
            : processor_(std::move(processor)) {}

    explicit ObservableVector(size_type count) : data_(count) {}

    ObservableVector(size_type count, const T& value) : data_(count, value) {}

    ObservableVector(std::initializer_list<T> init) : data_(init) {}

    template<class InputIt>
    ObservableVector(InputIt first, InputIt last) : data_(first, last) {}

    ObservableVector(const ObservableVector& other) {
        std::shared_lock lock(other.mutex_);
        data_ = other.data_;
        processor_ = other.processor_;
    }

    ObservableVector(ObservableVector&& other) noexcept {
        std::unique_lock lock(other.mutex_);
        data_ = std::move(other.data_);
        processor_ = std::move(other.processor_);
    }

    // Операторы присваивания
    ObservableVector& operator=(const ObservableVector& other) {
        if (this != &other) {
            std::unique_lock lock1(mutex_, std::defer_lock);
            std::shared_lock lock2(other.mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_ = other.data_;
            processor_ = other.processor_;
        }
        return *this;
    }

    ObservableVector& operator=(ObservableVector&& other) noexcept {
        if (this != &other) {
            std::unique_lock lock1(mutex_, std::defer_lock);
            std::unique_lock lock2(other.mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_ = std::move(other.data_);
            processor_ = std::move(other.processor_);
        }
        return *this;
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
        std::shared_lock lock(mutex_);
        return data_.empty() ? nullptr : data_.data();
    }

    const_pointer data() const noexcept {
        std::shared_lock lock(mutex_);
        return data_.empty() ? nullptr : data_.data();
    }

    iterator begin() noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.begin();
    }

    const_iterator begin() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.begin();
    }

    const_iterator cbegin() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.cbegin();
    }

    iterator end() noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.end();
    }

    const_iterator end() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.end();
    }

    const_iterator cend() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.cend();
    }

    bool empty() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.empty();
    }

    size_type size() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.size();
    }

    size_type max_size() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.max_size();
    }

    size_type capacity() const noexcept {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.capacity();
    }

    void reserve(size_type new_cap) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_.reserve(new_cap);
    }

    void shrink_to_fit() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_.shrink_to_fit();
    }

    void clear() {
        std::unique_lock lock(mutex_);

        if constexpr (is_pointer) {
            // Собираем старые значения и освобождаем память
            for (size_type i = 0; i < data_.size(); ++i) {
                if (data_[i]) {
                    value_type old = *data_[i];
                    delete data_[i];
                    notify_change(i, old, value_type{});
                }
            }
        } else {
            // Для обычных типов
            for (size_type i = 0; i < data_.size(); ++i) {
                notify_change(i, data_[i], value_type{});
            }
        }
        data_.clear();
    }

    // Доступ к элементам
    Proxy operator[](size_type pos) { return {*this, pos}; }
    ConstProxy operator[](size_type pos) const { return {*this, pos}; }

    Proxy at(size_type pos) {
        if (pos >= size()) throw std::out_of_range("Index out of range");
        return {*this, pos};
    }

    ConstProxy at(size_type pos) const {
        if (pos >= size()) throw std::out_of_range("Index out of range");
        return {*this, pos};
    }

    // Основные методы
    void resize(size_type count, const T& value = T{}) {
        std::unique_lock lock(mutex_);
        size_type old_size = data_.size();
        data_.resize(count, value);

        // Уведомления для новых элементов
        for (size_type i = old_size; i < count; ++i) {
            notify_change(i, value_type{}, get_at_index(i));
        }
    }

    void push_back(const T& value) {
        std::unique_lock lock(mutex_);
        size_type index = data_.size();
        data_.push_back(value);
        notify_change(index, value_type{}, get_at_index(index));
    }

    void set(size_type pos, const value_type& value, uint64_t bit_mask = 0) {
        std::unique_lock lock(mutex_);
        value_type old_value = get_at_index(pos);
        if (old_value == value) return;

        if constexpr (is_pointer) {
            if (!data_[pos]) throw std::runtime_error("Null pointer");
            *data_[pos] = value;
        } else {
            data_[pos] = value;
        }
        notify_change(pos, old_value, value, bit_mask);
    }

    value_type get_at_index(size_type pos) const {
        std::shared_lock lock(mutex_);
        if (pos >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }

        if constexpr (is_pointer) {
            if (!data_[pos]) {
                throw std::runtime_error("Null pointer dereference");
            }
            return *data_[pos];
        } else {
            return data_[pos];
        }
    }

    pointer get_pointer(size_type pos) noexcept {
        std::shared_lock lock(mutex_);
        return (pos < data_.size()) ? data_[pos] : nullptr;
    }

protected:
    void notify_change(size_type index,
                       const value_type& old_value,
                       const value_type& new_value,
                       uint64_t bit_mask = 0) {
        if (!processor_ || old_value == new_value) return;

        processor_->enqueue(OnDataChange{
                index,
                bit_mask,
                convert_to_variant(old_value),
                convert_to_variant(new_value)
        });
    }

    VARIANT convert_to_variant(const value_type& value) const {
        return VARIANT(value);
    }

private:
    std::vector<T> data_;
    mutable std::shared_mutex mutex_;
    std::shared_ptr<DataProcessor> processor_;
};

#endif // PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H