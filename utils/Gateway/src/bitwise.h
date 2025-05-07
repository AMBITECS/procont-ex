//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_BITWISE_H
#define PROCONT_EX_BITWISE_H

#include "vector.h"

template<typename T>
struct BitwiseTraits
{
    static uint64_t get_bit_mask(size_t bit_pos) {
        if (bit_pos >= 64) throw std::out_of_range("Bit position out of 64-bit range");
        return static_cast<uint64_t>(1ULL << bit_pos);
    }

    static bool get_bit(T value, size_t bit_pos) {
        return (value >> bit_pos) & 0x01;
    }

    static T set_bit(T value, size_t bit_pos, bool bit_value) {
        const auto mask = static_cast<T>(1 << bit_pos);
        return bit_value ? (value | mask) : (value & ~mask);
    }
};

template<typename T>
class BitwiseVector : public ObservableVector<T> {
public:
    using size_type = size_t;
    using Base = ObservableVector<T>;
    using Base::Base;
    using value_type = typename Base::value_type;

    // Прокси для доступа к целым элементам
    class ElementProxy {
        Base& vec;
        size_t elem_idx;
    public:
        ElementProxy(Base& v, size_t idx) : vec(v), elem_idx(idx) {}

        operator value_type() const {
            return vec.get_at_index(elem_idx);
        }

        // Универсальный оператор присваивания
        ElementProxy& operator=(const value_type& value) {
            vec.set(elem_idx, value);
            return *this;
        }

        // Оператор присваивания для указателей
        template<typename U = T>
        ElementProxy& operator=(U* ptr) {
                if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
                vec.set_pointer(elem_idx, ptr);
                return *this;
        }

        // Универсальный оператор сравнения
        bool operator==(const value_type& other) const {
            return vec.get_at_index(elem_idx) == other;
        }

        // Специальная перегрузка для nullptr
        bool operator==(std::nullptr_t) const {
                if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
                return vec.get_pointer(elem_idx) == nullptr;
        }
    };

    // Const-версия прокси
    class ConstElementProxy {
        const Base& vec;
        size_t elem_idx;
    public:
        ConstElementProxy(const Base& v, size_t idx) : vec(v), elem_idx(idx) {}

        operator value_type() const {
            return vec.get_at_index(elem_idx);
        }

        bool operator==(const value_type& other) const {
            return vec.get_at_index(elem_idx) == other;
        }

        bool operator==(std::nullptr_t) const {
                if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
                return vec.get_pointer(elem_idx) == nullptr;
        }
    };

    // Прокси для битового доступа
    class BitReference {
        Base& vec;
        size_t elem_idx;
        size_t bit_idx;

    public:
        BitReference(Base& v, size_t e_idx, size_t b_idx)
                : vec(v), elem_idx(e_idx), bit_idx(b_idx)
        {
            if (bit_idx >= BitwiseTraits<T>::bit_size)
                throw std::out_of_range("Bit index out of range");
        }

        operator bool() const { //NOLINT
            if constexpr (Base::is_pointer) {
                auto ptr = vec.get_pointer(elem_idx);
                if (!ptr) throw std::runtime_error("Null pointer dereference");
                return BitwiseTraits<T>::get_bit(*ptr, bit_idx);
            } else {
                auto value = vec.get_at_index(elem_idx);
                return BitwiseTraits<T>::get_bit(value, bit_idx);
            }
        }

        BitReference& operator=(bool value) {
            if constexpr (Base::is_pointer) {
                auto ptr = vec.get_pointer(elem_idx);
                if (!ptr) throw std::runtime_error("Cannot assign to nullptr");

                T old_val = *ptr;
                T new_val = BitwiseTraits<T>::set_bit(old_val, bit_idx, value);

                if (old_val != new_val) {
                    uint64_t mask = BitwiseTraits<T>::get_bit_mask(bit_idx);
                    *ptr = new_val;
                    vec.notify_change(elem_idx, old_val, new_val, mask);
                }
            } else {
                T old_val = vec.get_at_index(elem_idx);
                T new_val = BitwiseTraits<T>::set_bit(old_val, bit_idx, value);

                if (old_val != new_val) {
                    uint64_t mask = BitwiseTraits<T>::get_bit_mask(bit_idx);
                    vec.set(elem_idx, new_val, mask);
                }
            }
            return *this;
        }
    };

    class ConstBitReference {
        const Base& vec;
        size_t elem_idx;
        size_t bit_idx;

    public:
        ConstBitReference(const Base& v, size_t e_idx, size_t b_idx)
                : vec(v), elem_idx(e_idx), bit_idx(b_idx)
        {
            if (bit_idx >= BitwiseTraits<T>::bit_size)
                throw std::out_of_range("Bit index out of range");
        }

        operator bool() const { //NOLINT
            if constexpr (Base::is_pointer) {
                const auto ptr = vec.get_pointer(elem_idx);
                if (!ptr) throw std::runtime_error("Null pointer dereference");
                return BitwiseTraits<T>::get_bit(*ptr, bit_idx);
            } else {
                const auto value = vec.get_at_index(elem_idx);
                return BitwiseTraits<T>::get_bit(value, bit_idx);
            }
        }
    };

    // Основной Accessor с универсальными операторами
    class Accessor {
        Base& vec;
        size_t elem_idx;
    public:
        Accessor(Base& v, size_t idx) : vec(v), elem_idx(idx) {}

        // Доступ к битам
        BitReference operator[](size_t bit_idx) {
            return BitReference(vec, elem_idx, bit_idx);
        }

        // Доступ к целому элементу
        ElementProxy operator*() {
            return ElementProxy(vec, elem_idx);
        }

//        // Оператор разыменования
//        value_type& operator*() {
//            if constexpr (Base::is_pointer) {
//                auto ptr = vec.get_pointer(elem_idx);
//                if (!ptr) throw std::runtime_error("Dereferencing nullptr");
//                return *ptr;
//            }
//            return vec.get_at_index(elem_idx);
//        }

//        const value_type& operator*() const {
//            if constexpr (Base::is_pointer) {
//                auto ptr = vec.get_pointer(elem_idx);
//                if (!ptr) throw std::runtime_error("Dereferencing nullptr");
//                return *ptr;
//            }
//            return vec.get_at_index(elem_idx);
//        }

        // Операторы сравнения
        bool operator!=(const value_type& other) const {
            return (*this != other);
        }

        // Специальная перегрузка для nullptr
        bool operator!=(std::nullptr_t) const {
            if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
            return (*this != nullptr);
        }

        // Универсальный оператор сравнения
        bool operator==(const value_type& other) const {
            return vec.get_at_index(elem_idx) == other;
        }

        // Специальная перегрузка для nullptr
        bool operator==(std::nullptr_t) const  {
            if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
            return vec.get_pointer(elem_idx) == nullptr;
        }

        // Универсальный оператор присваивания
            Accessor& operator=(const value_type& value) {
            vec.set(elem_idx, value);
            return *this;
        }

        // Специальная перегрузка для указателей
        template<typename U>
        Accessor& operator=(U* ptr) {
                if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot accept the pointer");
                vec.set_pointer(elem_idx, ptr);
                return *this;
        }

    };

    // Const-версия Accessor
    class ConstAccessor {
        const Base& vec;
        size_t elem_idx;
    public:
        ConstAccessor(const Base& v, size_t idx) : vec(v), elem_idx(idx) {}

        ConstElementProxy operator*() const {
            return ConstElementProxy(vec, elem_idx);
        }

        ConstBitReference operator[](size_t bit_idx) const {
            return ConstBitReference(vec, elem_idx, bit_idx);
        }

        bool operator==(const value_type& other) const {
            return vec.get_at_index(elem_idx) == other;
        }

        bool operator==(std::nullptr_t) const {
                if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot compare with pointer");
                return vec.get_pointer(elem_idx) == nullptr;
        }
    };

    // Операторы доступа
    Accessor operator[](size_t index) {
        return {*this, index};
    }

    ConstAccessor operator[](size_t index) const {
        return {*this, index};
    }

    // Дополнительные методы для работы с указателями
    template<typename U = T>
    void set_pointer(size_type pos, U* ptr) {
        if constexpr (!Base::is_pointer) throw std::runtime_error("Cannot accept the pointer");
        Base::set_raw(pos, ptr);
    }
};

#endif //PROCONT_EX_BITWISE_H
