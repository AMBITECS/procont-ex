//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H
#define PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H

#include <assert.h>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <string>
#include <iostream>
#include <variant>
#include <chrono>
#include <type_traits>
#include <utility>
#include "processor.h"
#include "variant.h"
#include "iec_types.h"

// Настройка экспорта для Windows
#ifdef _WIN32
#ifdef GATEWAY_EXPORTS  // Определяется при компиляции DLL
        #define GATEWAY_API __declspec(dllexport)
    #else
        #define GATEWAY_API __declspec(dllimport)
    #endif
#else  // Linux/macOS
#define GATEWAY_API __attribute__((visibility("default")))
#endif

template <typename T>
class GATEWAY_API ObservableVector {
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

    static constexpr bool is_pointer = std::is_pointer_v<T>;
    using value_type = std::conditional_t<is_pointer, std::remove_pointer_t<T>, T>;

    std::vector<T> data_;
    //std::vector<std::unique_ptr<T>> data_;

    mutable std::shared_mutex mutex_;
    std::shared_ptr<DataServer> data_server_;
    std::string key_prefix_ = "vec_";

    void notify_change(size_t index, const value_type& old_value,
                       const value_type& new_value, uint64_t bit_mask = 0) noexcept {
        if (!data_server_) return;

        try {
            const auto key = key_prefix_ + std::to_string(index);
            data_server_->enqueue(key, OnDataChange{
                    key,
                    bit_mask,
                    convert_to_variant(old_value),
                    convert_to_variant(new_value),
                    std::chrono::system_clock::now()
            });
        } catch (...) {
            // Логирование ошибки
        }
    }

    VARIANT convert_to_variant(const value_type& val) const {
        if constexpr (std::is_same_v<value_type, std::string>) {
            return VARIANT(val.c_str());
        } else {
            return VARIANT(val);
        }
    }

    [[nodiscard]] bool is_valid_index(size_t pos) const noexcept {
        std::shared_lock lock(mutex_);
        return pos < data_.size();
    }

public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    template <bool IsConst>
    class BasicProxy {
    public:
        using VectorType = std::conditional_t<IsConst, const ObservableVector, ObservableVector>;
        using original_type = T;
        using value_type = typename ObservableVector::value_type; // Убираем element_type, используем только value_type

    private:
        VectorType& vec_;
        size_t index_;
        std::conditional_t<ObservableVector::is_pointer && !IsConst,
                std::optional<value_type>,
                std::monostate> old_value_;

        pointer get_ptr() const noexcept {
            vec_.check_invariants();

            std::shared_lock lock(vec_.mutex_);
            //static_assert(ObservableVector::is_pointer, "call get_ptr() with non-pointer template");
            return (index_ < vec_.data_.size()) ? vec_.data_[index_] : nullptr;
        }

    public:
        BasicProxy(VectorType& vec, size_type index) : vec_(vec), index_(index) {
            vec_.check_invariants();

            if constexpr (!IsConst && ObservableVector::is_pointer) {
                if (auto ptr = get_ptr()) {
                    old_value_.emplace(*ptr);
                }
            }
        }

        ~BasicProxy() {
            vec_.check_invariants();

            if constexpr (!IsConst) {
                if constexpr (ObservableVector::is_pointer) {
                    if (old_value_) {
                        if (auto ptr = get_ptr(); ptr && *ptr != *old_value_) {
                            vec_.notify_change(index_, *old_value_, *ptr);
                        }
                    }
                } else {
                    // Для не-указателей уведомление отправляется в operator=
                }
            }
        }

        // Прозрачное преобразование к оригинальному типу T
        operator original_type() const { //NOLINT

            std::shared_lock lock(vec_.mutex_);
            if (index_ >= vec_.data_.size())  throw std::out_of_range("Index out of range");
            return vec_.data_[index_];
        }

        // Операторы сравнения с original_type
        bool operator==(const original_type& other) const {
            return static_cast<original_type>(*this) == other;
        }

        bool operator!=(const original_type& other) const {
            return !(*this == other); //NOLINT
        }

        // Присваивание
        BasicProxy& operator=(const original_type& value) {
            static_assert(!IsConst, "Cannot assign to const proxy");
            std::unique_lock lock(vec_.mutex_);

            if constexpr (ObservableVector::is_pointer) {
                pointer old_ptr = vec_.data_[index_];
                value_type old_val = old_ptr ? *old_ptr : value_type{};
                vec_.data_[index_] = value;
                if (!old_value_ && old_ptr) {
                    old_value_.emplace(old_val);
                }
                if (value && old_ptr && *old_ptr != *value) {
                    lock.unlock();
                    vec_.notify_change(index_, old_val, *value);
                }
            } else {
                value_type old_val = vec_.data_[index_];
                vec_.data_[index_] = value;
                if (old_val != value) {
                    lock.unlock();
                    vec_.notify_change(index_, old_val, value);
                }
            }
            return *this;
        }

        // Разыменование (только для pointer-типов)
        template <typename U = T>
        auto operator*() -> std::enable_if_t<std::is_pointer_v<U>, value_type&> {
            static_assert(!IsConst, "Cannot dereference const proxy");
            auto ptr = get_ptr();
            if (!ptr) throw std::runtime_error("Dereferencing nullptr");
            if (!old_value_) old_value_.emplace(*ptr);
            return *ptr;
        }

        template <typename U = T>
        auto operator*() const -> std::enable_if_t<std::is_pointer_v<U>, const value_type&> {
            auto ptr = get_ptr();
            if (!ptr) throw std::runtime_error("Dereferencing nullptr");
            return *ptr;
        }
    };

    using Proxy = BasicProxy<false>;
    using ConstProxy = BasicProxy<true>;

    ObservableVector() = default;
    explicit ObservableVector(std::shared_ptr<DataServer> server) : data_server_(std::move(server)) {}

    explicit ObservableVector(size_type count) : data_(count) {
        check_invariants();
        //std::cout << "Constructor, this=" << this << ", size=" << data_.size() << std::endl;
    }

    ObservableVector(size_type count, const T& value) : data_(count, value) {}
    ObservableVector(std::initializer_list<T> init) : data_(init) {}

    template<class InputIt>
    ObservableVector(InputIt first, InputIt last) : data_(first, last) {}

    // Копирование и перемещение
    ObservableVector(const ObservableVector& other) {
        std::shared_lock lock(other.mutex_);
        data_ = other.data_;
        data_server_ = other.data_server_;
        key_prefix_ = other.key_prefix_;
    }

//    ObservableVector(ObservableVector&& other) noexcept {
//        std::unique_lock lock(other.mutex_);
//        data_ = std::move(other.data_);
//        data_server_ = std::move(other.data_server_);
//        key_prefix_ = std::move(other.key_prefix_);
//    }

    ~ObservableVector() // = default;
    {
        std::cout << "Destructor, this=" << this << ", size=" << data_.size() << std::endl;
    }

    // Операторы присваивания
    ObservableVector& operator=(const ObservableVector& other) {
        if (this == &other) return *this;

        std::unique_lock lock1(mutex_, std::defer_lock);
        std::shared_lock lock2(other.mutex_, std::defer_lock);
        std::lock(lock1, lock2);

        data_ = other.data_;
        data_server_ = other.data_server_;
        key_prefix_ = other.key_prefix_;

        return *this;
    }

//    ObservableVector& operator=(ObservableVector&& other) noexcept {
//        if (this != &other) {
//            std::unique_lock lock1(mutex_, std::defer_lock);
//            std::unique_lock lock2(other.mutex_, std::defer_lock);
//            std::lock(lock1, lock2);
//
//            data_ = std::move(other.data_);
//            data_server_ = std::move(other.data_server_);
//            key_prefix_ = std::move(other.key_prefix_);
//        }
//        return *this;
//    }

    // Доступ к элементам
    Proxy operator[](size_type pos) {
        check_invariants();
        if (pos >= size())
            throw std::out_of_range("Index out of range");

        return Proxy(*this, pos);  // Явно используем тип Proxy вместо BasicProxy
    }

    ConstProxy operator[](size_type pos) const {
        check_invariants();
        if (pos >= size())
            throw std::out_of_range("Index out of range");

        return ConstProxy(*this, pos);  // Явно используем тип ConstProxy вместо BasicProxy
    }

    Proxy at(size_type pos) {
        if (pos >= size())
            throw std::out_of_range("Index out of range");

        return Proxy(*this, pos);  // Явно используем тип Proxy
    }

    ConstProxy at(size_type pos) const {
        if (pos >= size())
            throw std::out_of_range("Index out of range");
        return ConstProxy(*this, pos);  // Явно используем тип ConstProxy
    }

    // Основные методы
    value_type get(size_type pos) const {
        check_invariants();

        std::shared_lock lock(mutex_);
        if (pos >= data_.size())
            throw std::out_of_range("Index out of range");

        if constexpr (is_pointer) {
            if (!data_[pos]) throw std::runtime_error("Null pointer dereference");
            return *data_[pos];
        } else {
            return data_[pos];
        }
    }

    void set(size_type pos, const value_type& value, uint64_t bit_mask = 0) {
        check_invariants();

        std::unique_lock lock(mutex_);
        value_type old_value = get(pos);
        if (old_value == value) return;
        if constexpr (is_pointer) {
            if (!data_[pos]) throw std::runtime_error("Null pointer");
            *data_[pos] = value;
        } else {
            data_[pos] = value;
        }
        notify_change(pos, old_value, value, bit_mask);
    }

    // Модификация контейнера
    void push_back(const T& value) {
        std::unique_lock lock(mutex_);
        size_type index = data_.size();
        data_.push_back(value);

        value_type empty_val{};
        if constexpr (is_pointer) {
            empty_val = value_type{};
            if (!value) return;
            notify_change(index, empty_val, *value);
        } else {
            notify_change(index, empty_val, value);
        }
    }

    void resize(size_type count, const T& value = T{}) {
        std::unique_lock lock(mutex_);
        size_type old_size = data_.size();
        data_.resize(count, value);

        // Уведомления для новых элементов
        for (size_type i = old_size; i < count; ++i) {
            if constexpr (is_pointer) {
                if (data_[i]) {
                    notify_change(i, value_type{}, *data_[i]);
                }
            } else {
                notify_change(i, value_type{}, data_[i]);
            }
        }
    }

    void clear() {
        std::unique_lock lock(mutex_);
        for (size_type i = 0; i < data_.size(); ++i) {
            if constexpr (is_pointer) {
                if (data_[i]) {
                    notify_change(i, *data_[i], value_type{});
                }
            } else {
                notify_change(i, data_[i], value_type{});
            }
        }
        data_.clear();
    }

    // Привязка к DataServer
    void bindToDataServer(std::shared_ptr<DataServer> server, const std::string& prefix = "vec_") {
        std::unique_lock lock(mutex_);
        data_server_ = std::move(server);
        key_prefix_ = prefix;
    }

    // Информационные методы
    Proxy front() { if (empty())  throw std::out_of_range("Vector is empty"); return Proxy(*this, 0); }
    ConstProxy front() const { if (empty())  throw std::out_of_range("Vector is empty"); return ConstProxy(*this, 0); }
    Proxy back() { if (empty())  throw std::out_of_range("Vector is empty"); return Proxy(*this, size() - 1); }
    ConstProxy back() const { if (empty())  throw std::out_of_range("Vector is empty"); return ConstProxy(*this, size() - 1); }

//    pointer data() noexcept { std::shared_lock lock(mutex_); return data_.empty() ? nullptr : data_.data(); }
//    const_pointer data() const noexcept { std::shared_lock lock(mutex_); return data_.empty() ? nullptr : data_.data(); }

    bool      empty()    const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.empty();    }
    size_type size()     const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.size();     }
    size_type max_size() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.max_size(); }
    size_type capacity() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.capacity(); }

    void reserve(size_type new_cap) { std::unique_lock<std::shared_mutex> lock(mutex_); data_.reserve(new_cap); }
    void shrink_to_fit() { std::unique_lock<std::shared_mutex> lock(mutex_); data_.shrink_to_fit(); }

//    // Итераторы (базовые)
    iterator begin() noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.begin(); }
    const_iterator begin() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.begin(); }
    const_iterator cbegin() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.cbegin(); }
    iterator end() noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.end(); }
    const_iterator end() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.end(); }
    const_iterator cend() const noexcept { std::shared_lock<std::shared_mutex> lock(mutex_); return data_.cend(); }

private:
    value_type get_value_unsafe(size_t pos) const noexcept {
        if constexpr (is_pointer) {
            return data_[pos] ? *data_[pos] : value_type{};
        } else {
            return data_[pos];
        }
    }

    void set_value_unsafe(size_t pos, T value) noexcept {
        if constexpr (is_pointer) {
            *data_[pos] = *value;  // Предполагаем, что память управляется пользователем
        } else {
            data_[pos] = value;
        }
    }

    void check_invariants() const {
        if(data_.size() != 1024) {
            std::cerr << "Vector size corrupted! Expected: " << 1024 << ", actual: " << data_.size();
            std::terminate();
        }
    }
};


// Объявления явного инстанцирования
extern template class ObservableVector<IEC_UINT*>;
extern template class ObservableVector<IEC_UDINT*>;
extern template class ObservableVector<IEC_ULINT*>;

#endif // PROCONT_EX_RANGE_OBSERVABLE_VECTOR_H
