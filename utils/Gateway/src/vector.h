#ifndef PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H
#define PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H

#include <utility>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <limits>
#include <chrono>
#include <string>
#include <type_traits>
#include <atomic>
#include <algorithm>
#include "processor.h"
#include "on_data_change.h"
#include "variant.h"

template <typename T>
class RangeObservableVector {
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
        using VectorType = std::conditional_t<IsConst, const RangeObservableVector, RangeObservableVector>;
        using ValueType = std::conditional_t<IsConst, const T, T>;

        BasicProxy(VectorType& vec, size_t index) : vec_(vec), index_(index) {}

        operator value_type() const {
            return vec_.get_at_index(index_);
        }

        template <bool C = IsConst, std::enable_if_t<!C, int> = 0>
        BasicProxy& operator=(const value_type& value) {
            vec_.set(index_, value);
            return *this;
        }

        template <bool C = IsConst, std::enable_if_t<!C, int> = 0>
        BasicProxy& operator=(value_type&& value) {
            vec_.set(index_, std::move(value));
            return *this;
        }

    private:
        VectorType& vec_;
        size_t index_;
    };

    using Proxy = BasicProxy<false>;
    using ConstProxy = BasicProxy<true>;

    RangeObservableVector() : processor_(std::make_shared<DataProcessor>()) {}

    explicit RangeObservableVector(std::shared_ptr<DataProcessor> processor)
            : processor_(std::move(processor)) {}

    explicit RangeObservableVector(size_type count)
            : processor_(std::make_shared<DataProcessor>()) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.resize(count);
        if constexpr (is_pointer) {
            for (auto& ptr : data_) {
                ptr = new value_type();
            }
        }
    }

    RangeObservableVector(size_type count, const value_type& defaultValue)
            : processor_(std::make_shared<DataProcessor>()) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        data_.resize(count);
        if constexpr (is_pointer) {
            for (auto& ptr : data_) {
                ptr = new value_type(defaultValue);
            }
        } else {
            std::fill(data_.begin(), data_.end(), defaultValue);
        }
    }

    RangeObservableVector(std::initializer_list<value_type> init)
            : processor_(std::make_shared<DataProcessor>()) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            data_.reserve(init.size());
            for (const auto& val : init) {
                data_.push_back(new value_type(val));
            }
        } else {
            data_ = init;
        }
    }

    template<class InputIt>
    RangeObservableVector(InputIt first, InputIt last)
            : processor_(std::make_shared<DataProcessor>()) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            data_.reserve(std::distance(first, last));
            for (auto it = first; it != last; ++it) {
                data_.push_back(new value_type(*it));
            }
        } else {
            data_.assign(first, last);
        }
    }

    RangeObservableVector(const RangeObservableVector& other) {
        std::shared_lock<std::shared_mutex> other_lock(other.data_mutex_);
        std::unique_lock<std::shared_mutex> this_lock(data_mutex_);
        if constexpr (is_pointer) {
            data_.reserve(other.data_.size());
            for (const auto& ptr : other.data_) {
                data_.push_back(ptr ? new value_type(*ptr) : nullptr);
            }
        } else {
            data_ = other.data_;
        }
        processor_ = other.processor_;
    }

    RangeObservableVector(RangeObservableVector&& other) noexcept {
        std::unique_lock<std::shared_mutex> other_lock(other.data_mutex_);
        std::unique_lock<std::shared_mutex> this_lock(data_mutex_);
        data_ = std::move(other.data_);
        processor_ = std::move(other.processor_);
        other.data_.clear();
    }

    ~RangeObservableVector() {
        if constexpr (is_pointer) {
            std::unique_lock<std::shared_mutex> lock(data_mutex_);
            for (auto ptr : data_) {
                delete ptr;
            }
        }
    }

    RangeObservableVector& operator=(const RangeObservableVector& other) {
        if (this != &other) {
            std::unique_lock<std::shared_mutex> lock1(data_mutex_, std::defer_lock);
            std::shared_lock<std::shared_mutex> lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);

            if constexpr (is_pointer) {
                for (auto ptr : data_) {
                    delete ptr;
                }
                data_.resize(other.data_.size());
                for (size_type i = 0; i < other.data_.size(); ++i) {
                    data_[i] = other.data_[i] ? new value_type(*other.data_[i]) : nullptr;
                }
            } else {
                data_ = other.data_;
            }
            processor_ = other.processor_;
        }
        return *this;
    }

    RangeObservableVector& operator=(RangeObservableVector&& other) noexcept {
        if (this != &other) {
            std::unique_lock<std::shared_mutex> lock1(data_mutex_, std::defer_lock);
            std::unique_lock<std::shared_mutex> lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);

            if constexpr (is_pointer) {
                for (auto ptr : data_) {
                    delete ptr;
                }
            }
            data_ = std::move(other.data_);
            processor_ = std::move(other.processor_);
            other.data_.clear();
        }
        return *this;
    }

    RangeObservableVector& operator=(std::initializer_list<value_type> ilist) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            for (auto ptr : data_) {
                delete ptr;
            }
            data_.clear();
            data_.reserve(ilist.size());
            for (const auto& val : ilist) {
                data_.push_back(new value_type(val));
            }
        } else {
            data_ = ilist;
        }
        lock.unlock();

        for (size_type i = 0; i < data_.size(); ++i) {
            notify_change(i, value_type{}, get_at_index(i));
        }
        return *this;
    }

    Proxy at(size_type pos) {
        if (pos >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return Proxy(*this, pos);
    }

    ConstProxy at(size_type pos) const {
        if (pos >= size()) {
            throw std::out_of_range("Index out of range");
        }
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

//    void set(size_type pos, const value_type& value) {
//        std::unique_lock<std::shared_mutex> lock(data_mutex_);
//        if (pos >= data_.size()) {
//            throw std::out_of_range("Index out of range");
//        }
//
//        value_type old_value = get_at_index(pos);
//        if constexpr (is_pointer) {
//            if (data_[pos] == nullptr) {
//                data_[pos] = new value_type(value);
//            } else {
//                *data_[pos] = value;
//            }
//        } else {
//            data_[pos] = value;
//        }
//
//        lock.unlock();
//        notify_change(pos, old_value, get_at_index(pos));
//    }
    void set(size_type pos, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }

        if constexpr (is_pointer) {
            if (data_[pos] == nullptr) {
                // Создаём новый объект, но не генерируем уведомление
                data_[pos] = new value_type(value);
            } else {
                // Генерируем уведомление только если значение изменилось
                value_type old_value = *data_[pos];
                if (old_value != value) {
                    *data_[pos] = value;
                    lock.unlock();
                    notify_change(pos, old_value, value);
                }
            }
        } else {
            value_type old_value = data_[pos];
            if (old_value != value) {
                data_[pos] = value;
                lock.unlock();
                notify_change(pos, old_value, value);
            }
        }
    }

//    void set(size_type pos, value_type&& value) {
//        std::unique_lock<std::shared_mutex> lock(data_mutex_);
//        if (pos >= data_.size()) {
//            throw std::out_of_range("Index out of range");
//        }
//
//        value_type old_value = get_at_index(pos);
//        if constexpr (is_pointer) {
//            if (data_[pos] == nullptr) {
//                data_[pos] = new value_type(std::move(value));
//            } else {
//                *data_[pos] = std::move(value);
//            }
//        } else {
//            data_[pos] = std::move(value);
//        }
//
//        lock.unlock();
//        notify_change(pos, old_value, get_at_index(pos));
//    }
    void set(size_type pos, value_type&& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (pos >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }

        if constexpr (is_pointer) {
            if (data_[pos] == nullptr) {
                // Создаём новый объект, но не генерируем уведомление
                data_[pos] = new value_type(std::move(value));
            } else {
                // Генерируем уведомление только если значение изменилось
                value_type old_value = *data_[pos];
                if (old_value != value) {
                    *data_[pos] = std::move(value);
                    lock.unlock();
                    notify_change(pos, old_value, *data_[pos]);
                }
            }
        } else {
            value_type old_value = data_[pos];
            if (old_value != value) {
                data_[pos] = std::move(value);
                lock.unlock();
                notify_change(pos, old_value, data_[pos]);
            }
        }
    }

    Proxy front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return Proxy(*this, 0);
    }

    ConstProxy front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return ConstProxy(*this, 0);
    }

    Proxy back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return Proxy(*this, size() - 1);
    }

    ConstProxy back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
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

    void clear() noexcept {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            for (auto ptr : data_) {
                delete ptr;
            }
        }
        data_.clear();
    }

    void push_back(const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        if constexpr (is_pointer) {
            data_.push_back(new value_type(value));
        } else {
            data_.push_back(value);
        }
        lock.unlock();

        notify_change(index, value_type{}, value);
    }

    void push_back(value_type&& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        if constexpr (is_pointer) {
            data_.push_back(new value_type(std::move(value)));
        } else {
            data_.push_back(std::move(value));
        }
        value_type& new_value = get_at_index(index);
        lock.unlock();

        notify_change(index, value_type{}, new_value);
    }

    template<class... Args>
    value_type& emplace_back(Args&&... args) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type index = data_.size();
        if constexpr (is_pointer) {
            data_.push_back(new value_type(std::forward<Args>(args)...));
        } else {
            data_.emplace_back(std::forward<Args>(args)...);
        }
        value_type& new_value = get_at_index(index);
        lock.unlock();

        notify_change(index, value_type{}, new_value);
        return new_value;
    }

    void pop_back() {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if (data_.empty()) {
            throw std::out_of_range("Vector is empty");
        }
        value_type old_value = get_at_index(data_.size() - 1);
        if constexpr (is_pointer) {
            delete data_.back();
        }
        data_.pop_back();
        lock.unlock();

        notify_change(data_.size(), old_value, value_type{});
    }

    void resize(size_type count) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        size_type old_size = data_.size();
        if constexpr (is_pointer) {
            if (count > old_size) {
                data_.reserve(count);
                for (size_type i = old_size; i < count; ++i) {
                    data_.push_back(new value_type());
                }
            } else if (count < old_size) {
                for (size_type i = count; i < old_size; ++i) {
                    delete data_[i];
                }
                data_.resize(count);
            }
        } else {
            data_.resize(count);
        }
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
        if constexpr (is_pointer) {
            if (count > old_size) {
                data_.reserve(count);
                for (size_type i = old_size; i < count; ++i) {
                    data_.push_back(new value_type(value));
                }
            } else if (count < old_size) {
                for (size_type i = count; i < old_size; ++i) {
                    delete data_[i];
                }
                data_.resize(count);
            }
        } else {
            data_.resize(count, value);
        }
        lock.unlock();

        if (count > old_size) {
            for (size_type i = old_size; i < count; ++i) {
                notify_change(i, value_type{}, value);
            }
        }
    }

    void swap(RangeObservableVector& other) noexcept {
        if (this != &other) {
            std::unique_lock<std::shared_mutex> lock1(data_mutex_, std::defer_lock);
            std::unique_lock<std::shared_mutex> lock2(other.data_mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            data_.swap(other.data_);
        }
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            for (auto ptr : data_) {
                delete ptr;
            }
            data_.clear();
            data_.reserve(std::distance(first, last));
            for (auto it = first; it != last; ++it) {
                data_.push_back(new value_type(*it));
            }
        } else {
            data_.assign(first, last);
        }
        lock.unlock();

        for (size_type i = 0; i < data_.size(); ++i) {
            notify_change(i, value_type{}, get_at_index(i));
        }
    }

    void assign(std::initializer_list<value_type> ilist) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            for (auto ptr : data_) {
                delete ptr;
            }
            data_.clear();
            data_.reserve(ilist.size());
            for (const auto& val : ilist) {
                data_.push_back(new value_type(val));
            }
        } else {
            data_.assign(ilist);
        }
        lock.unlock();

        for (size_type i = 0; i < data_.size(); ++i) {
            notify_change(i, value_type{}, get_at_index(i));
        }
    }

    void assign(size_type count, const value_type& value) {
        std::unique_lock<std::shared_mutex> lock(data_mutex_);
        if constexpr (is_pointer) {
            for (auto ptr : data_) {
                delete ptr;
            }
            data_.clear();
            data_.reserve(count);
            for (size_type i = 0; i < count; ++i) {
                data_.push_back(new value_type(value));
            }
        } else {
            data_.assign(count, value);
        }
        lock.unlock();

        for (size_type i = 0; i < data_.size(); ++i) {
            notify_change(i, value_type{}, value);
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
            std::vector<value_type> values;
            values.reserve(data_.size());
            for (auto ptr : data_) {
                values.push_back(ptr ? *ptr : value_type{});
            }
            func(values);
            for (size_type i = 0; i < data_.size(); ++i) {
                if (data_[i]) {
                    *data_[i] = values[i];
                } else {
                    data_[i] = new value_type(values[i]);
                }
            }
        } else {
            func(data_);
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

private:
    VARIANT convert_to_variant(const value_type& value) const {
        return VARIANT(value);
    }

    void notify_change(size_type index, const value_type& old_value, const value_type& new_value) {
        VARIANT old_var = convert_to_variant(old_value);
        VARIANT new_var = convert_to_variant(new_value);

        OnDataChange change{
                index,
                old_var,
                new_var,
                std::chrono::system_clock::now()
        };

        if (processor_) {
            processor_->enqueue(std::move(change));
        }
    }

    std::vector<T> data_;
    mutable std::shared_mutex data_mutex_;
    std::shared_ptr<DataProcessor> processor_;
};

#endif // PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H
