//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef REGISTRY_H
#define REGISTRY_H

#include "address.h"
#include "variant.h"
#include <vector>
#include <cstdint>
#include <type_traits>
#include <stdexcept>

template<typename T>
struct RegisterTraits {
    static_assert(sizeof(T) == 0, "Unsupported register type");
};

template<> struct RegisterTraits<bool>     { using storage_type = uint8_t;  static constexpr size_t size = 1; };
template<> struct RegisterTraits<int8_t>   { using storage_type = int8_t;   static constexpr size_t size = 1; };
template<> struct RegisterTraits<uint8_t>  { using storage_type = uint8_t;  static constexpr size_t size = 1; };
template<> struct RegisterTraits<int16_t>  { using storage_type = int16_t;  static constexpr size_t size = 2; };
template<> struct RegisterTraits<uint16_t> { using storage_type = uint16_t; static constexpr size_t size = 2; };
template<> struct RegisterTraits<int32_t>  { using storage_type = int32_t;  static constexpr size_t size = 4; };
template<> struct RegisterTraits<uint32_t> { using storage_type = uint32_t; static constexpr size_t size = 4; };
template<> struct RegisterTraits<float>    { using storage_type = float;    static constexpr size_t size = 4; };
template<> struct RegisterTraits<int64_t>  { using storage_type = int64_t;  static constexpr size_t size = 8; };
template<> struct RegisterTraits<uint64_t> { using storage_type = uint64_t; static constexpr size_t size = 8; };
template<> struct RegisterTraits<double>   { using storage_type = double;   static constexpr size_t size = 8; };

//-----------------------------------------------------------------------------
// Registry
//-----------------------------------------------------------------------------
class Registry {
private:
    // Регистры контроллера по категориям IEC
    std::vector<uint8_t> input_registers_;
    std::vector<uint8_t> output_registers_;
    std::vector<uint8_t> memory_registers_;
    std::vector<uint8_t> special_registers_;

public:
    using Category = Address::Category;
    using DataType = Address::DataType;

    explicit Registry(size_t memory_size = 1024) {resize(memory_size);}

    void resize(size_t new_size) {
        input_registers_.resize  (new_size);
        output_registers_.resize (new_size);
        memory_registers_.resize (new_size);
        special_registers_.resize(new_size);
    }

    //-------------------------------------------------------------------------
    // RegisterAccessor
    //-------------------------------------------------------------------------
    template<typename T, Category CAT>
    class Accessor {
        Registry &parent_;
        uint64_t offset_;

        std::vector<uint8_t> &getStorage() { return parent_.getStorage(CAT); }
        [[nodiscard]] const std::vector<uint8_t> &getStorage() const { return parent_.getStorage(CAT); }

        void checkBounds() const {
            if (offset_ + RegisterTraits<T>::size > getStorage().size()) {
                throw std::out_of_range("Register access out of range");
            }
        }

    public:
        Accessor(Registry &parent, uint64_t offset) : parent_(parent), offset_(offset) {
            if (offset_ % RegisterTraits<T>::size != 0) {
                throw std::runtime_error("Unaligned register access");
            }
        }

        operator T() const { //NOLINT
            checkBounds();
            const auto &storage = getStorage();
            return *reinterpret_cast<const typename RegisterTraits<T>::storage_type *>(&storage[offset_]);
        }

        Accessor &operator=(T value) {
            checkBounds();
            auto &storage = getStorage();
            *reinterpret_cast<typename RegisterTraits<T>::storage_type *>(&storage[offset_]) = value;
            return *this;
        }

        // Метод для создания нового RegisterAccessor с другим смещением
        Accessor operator()(uint64_t offset) const {
            return Accessor(parent_, offset);
        }

        //---------------------------------------------------------------------
        // BitReference
        //---------------------------------------------------------------------
        class BitReference {
            Accessor &accessor_;
            uint8_t bit_pos_;

        public:
            BitReference(Accessor &accessor, uint8_t bit_pos)
                    : accessor_(accessor), bit_pos_(bit_pos) {
                if (bit_pos_ >= sizeof(T) * 8) {
                    throw std::out_of_range("Bit position out of range");
                }
            }

            // Получаем значение
            operator bool() const { //NOLINT
                return (static_cast<T>(accessor_) >> bit_pos_) & 0x1;
            }

            // Устанавливаем значение
            BitReference &operator=(bool b) {
                T value = accessor_;
                T mask = static_cast<T>(1) << bit_pos_;
                accessor_ = b ? (value | mask) : (value & ~mask);
                return *this;
            }
        };  // BitReference

        BitReference operator[](uint8_t bit_pos) {
            static_assert(std::is_integral_v<T>, "Bit access only available for integral types");
            return BitReference(*this, bit_pos);
        }

        //---------------------------------------------------------------------
        // IndexProxy - класс для поддержки синтаксиса [index]
        //---------------------------------------------------------------------
        class IndexProxy {
            Registry& parent_;
            uint64_t base_offset_;
        public:
            IndexProxy(Registry& parent, uint64_t base_offset)
                    : parent_(parent), base_offset_(base_offset) {}

            Accessor operator[](uint64_t index) {
                uint64_t offset = base_offset_ + index * RegisterTraits<T>::size;
                return Accessor(parent_, offset);
            }
        };


    }; // Accessor

    template<typename T, Category CAT>
    Accessor<T, CAT> get(uint64_t offset) { return Accessor<T, CAT>(*this, offset); }

    // Псевдонимы типов
    template<typename T> using IRegister = typename Accessor<T, Category::INPUT>::IndexProxy;
    template<typename T> using QRegister = typename Accessor<T, Category::OUTPUT>::IndexProxy;
    template<typename T> using MRegister = typename Accessor<T, Category::MEMORY>::IndexProxy;
    template<typename T> using SRegister = typename Accessor<T, Category::SPECIAL>::IndexProxy;

    using IX = IRegister<T_BOOL  >;
    using IB = IRegister<T_UINT8 >;
    using IW = IRegister<T_UINT16>;
    using ID = IRegister<T_UINT32>;
    using IL = IRegister<T_UINT64>;

    using QX = QRegister<T_BOOL  >;
    using QB = QRegister<T_UINT8 >;
    using QW = QRegister<T_UINT16>;
    using QD = QRegister<T_UINT32>;
    using QL = QRegister<T_UINT64>;

    using MX = MRegister<T_BOOL  >;
    using MB = MRegister<T_UINT8 >;
    using MW = MRegister<T_UINT16>;
    using MD = MRegister<T_UINT32>;
    using ML = MRegister<T_UINT64>;

    //VARIANT getByAddress(const Address& addr);

// Оператор [] для доступа по Address
    VARIANT operator[](const Address& addr) {
        return getByAddress(addr);
    }

    // Метод getByAddress с поддержкой битового доступа
    VARIANT getByAddress(const Address& addr) {
        const uint64_t offset = addr.offset();
        const uint8_t bitpos = addr.bitpos();
        const DataType datatype = addr.datatype();
        switch(addr.category()) {
            case Category::INPUT:   return access<Category::INPUT>(datatype, offset, bitpos);
            case Category::OUTPUT:  return access<Category::OUTPUT>(datatype, offset, bitpos);
            case Category::MEMORY:  return access<Category::MEMORY>(datatype, offset, bitpos);
            case Category::SPECIAL: return access<Category::SPECIAL>(datatype, offset, bitpos);
            default: throw std::invalid_argument("Invalid register category");
        }
    }

private:
    // Шаблонный метод для доступа к регистрам
    template<Category CAT>
    VARIANT access(DataType type, uint64_t offset, uint8_t bitpos) {
        switch(type) {
            case DataType::TYPE_BIT:
                return (bitpos != 0xFF)
                ? VARIANT(static_cast<bool>(get<bool, CAT>(offset)[bitpos]))
                : VARIANT(static_cast<bool>(get<bool, CAT>(offset)));
            case DataType::TYPE_BYTE : return VARIANT(static_cast<uint8_t>(get<uint8_t, CAT>(offset)));
            case DataType::TYPE_WORD : return VARIANT(static_cast<uint16_t>(get<uint16_t, CAT>(offset)));
            case DataType::TYPE_DWORD: return VARIANT(static_cast<uint32_t>(get<uint32_t, CAT>(offset)));
            case DataType::TYPE_LWORD: return VARIANT(static_cast<uint64_t>(get<uint64_t, CAT>(offset)));
            case DataType::TYPE_REAL : return VARIANT(static_cast<float>(get<float, CAT>(offset)));
            case DataType::TYPE_LREAL: return VARIANT(static_cast<double>(get<double, CAT>(offset)));
            default: throw std::invalid_argument("Invalid data type");
        }
    }

private:
    std::vector<uint8_t>& getStorage(Category cat) {
        switch(cat) {
            case Category::INPUT:   return input_registers_;
            case Category::OUTPUT:  return output_registers_;
            case Category::MEMORY:  return memory_registers_;
            case Category::SPECIAL: return special_registers_;
            default: throw std::invalid_argument("Invalid register category");
        }
    }
};

#endif // REGISTRY_H
