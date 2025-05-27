#ifndef CONTROLLER_REGISTERS_H
#define CONTROLLER_REGISTERS_H

#include "address.h"
#include "variant.h"

#include <vector>
#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <variant>
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

class ControllerRegisters {
public:
    using Category = RegisterAddress::Category;
    using DataType = RegisterAddress::DataType;

    explicit ControllerRegisters(size_t memory_size = 1024) {
        resize(memory_size);
    }

    void resize(size_t new_size) {
        input_registers_.resize(new_size);
        output_registers_.resize(new_size);
        memory_registers_.resize(new_size);
    }

    template<typename T, Category CAT>
    class RegisterAccessor {
        ControllerRegisters &parent_;
        uint64_t offset_;

        std::vector<uint8_t> &getStorage() { return parent_.getStorage(CAT); }

        const std::vector<uint8_t> &getStorage() const { return parent_.getStorage(CAT); }

        void checkBounds() const {
            if (offset_ + RegisterTraits<T>::size > getStorage().size()) {
                throw std::out_of_range("Register access out of range");
            }
        }

    public:
        RegisterAccessor(ControllerRegisters &parent, uint64_t offset) : parent_(parent), offset_(offset) {
            if (offset_ % RegisterTraits<T>::size != 0) {
                throw std::runtime_error("Unaligned register access");
            }
        }

        operator T() const {
            checkBounds();
            const auto &storage = getStorage();
            return *reinterpret_cast<const typename RegisterTraits<T>::storage_type *>(&storage[offset_]);
        }

        RegisterAccessor &operator=(T value) {
            checkBounds();
            auto &storage = getStorage();
            *reinterpret_cast<typename RegisterTraits<T>::storage_type *>(&storage[offset_]) = value;
            return *this;
        }

        class BitReference {
            RegisterAccessor &accessor_;
            uint8_t bit_pos_;
        public:
            BitReference(RegisterAccessor &accessor, uint8_t bit_pos)
                    : accessor_(accessor), bit_pos_(bit_pos) {
                if (bit_pos_ >= sizeof(T) * 8) {
                    throw std::out_of_range("Bit position out of range");
                }
            }

            operator bool() const { return (static_cast<T>(accessor_) >> bit_pos_) & 0x1; }

            BitReference &operator=(bool b) {
                T value = accessor_;
                T mask = static_cast<T>(1) << bit_pos_;
                accessor_ = b ? (value | mask) : (value & ~mask);
                return *this;
            }
        };

        BitReference operator[](uint8_t bit_pos) {
            static_assert(std::is_integral_v<T>, "Bit access only available for integral types");
            return BitReference(*this, bit_pos);
        }
    };

    // Псевдонимы типов для удобства
    template<typename T> using IRegister = RegisterAccessor<T, Category::INPUT>;
    template<typename T> using QRegister = RegisterAccessor<T, Category::OUTPUT>;
    template<typename T> using MRegister = RegisterAccessor<T, Category::MEMORY>;

    using IX = RegisterAccessor<bool, Category::INPUT>;
    using IB = RegisterAccessor<int8_t, Category::INPUT>;
    using IW = RegisterAccessor<int16_t, Category::INPUT>;
    using ID = RegisterAccessor<int32_t, Category::INPUT>;
    using IL = RegisterAccessor<int64_t, Category::INPUT>;

    using QX = RegisterAccessor<bool, Category::OUTPUT>;
    using QB = RegisterAccessor<int8_t, Category::OUTPUT>;
    using QW = RegisterAccessor<int16_t, Category::OUTPUT>;
    using QD = RegisterAccessor<int32_t, Category::OUTPUT>;
    using QL = RegisterAccessor<int64_t, Category::OUTPUT>;

    using MX = RegisterAccessor<bool, Category::MEMORY>;
    using MB = RegisterAccessor<int8_t, Category::MEMORY>;
    using MW = RegisterAccessor<int16_t, Category::MEMORY>;
    using MD = RegisterAccessor<int32_t, Category::MEMORY>;
    using ML = RegisterAccessor<int64_t, Category::MEMORY>;

    // Основные методы доступа
    template<Category CAT>
    auto get(uint64_t offset) {
        return RegisterAccessor<bool, CAT>(*this, offset);
    }

    template<typename T, Category CAT>
    auto get(uint64_t offset) {
        return RegisterAccessor<T, CAT>(*this, offset);
    }

// Универсальный доступ
    VARIANT getByAddress(const RegisterAddress& addr) {
        const auto type = addr.getDataType();
        const auto cat = addr.getCategory();
        const auto offset = addr.getOffset();
        const auto bit_pos = addr.getBitPosition();

        if (bit_pos != 0xFF) {
            // Битовая операция - возвращаем bool
            bool bit_value = false;
            switch(cat) {
                case Category::INPUT:  bit_value = get<bool, Category::INPUT>(offset)[bit_pos]; break;
                case Category::OUTPUT: bit_value = get<bool, Category::OUTPUT>(offset)[bit_pos]; break;
                case Category::MEMORY: bit_value = get<bool, Category::MEMORY>(offset)[bit_pos]; break;
                default: throw std::invalid_argument("Unsupported category for bit access");
            }
            return VARIANT(bit_value);
        } else {
            // Доступ к значению - возвращаем VARIANT с соответствующим типом
            switch(type) {
                case DataType::TYPE_BYTE: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(static_cast<T_SINT8>(get<uint8_t, Category::INPUT>(offset)));
                        case Category::OUTPUT: return VARIANT(static_cast<T_SINT8>(get<uint8_t, Category::OUTPUT>(offset)));
                        case Category::MEMORY: return VARIANT(static_cast<T_SINT8>(get<uint8_t, Category::MEMORY>(offset)));
                        default: throw std::invalid_argument("Unsupported category for byte access");
                    }
                }
                case DataType::TYPE_WORD: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(static_cast<T_SINT16>(get<uint16_t, Category::INPUT>(offset)));
                        case Category::OUTPUT: return VARIANT(static_cast<T_SINT16>(get<uint16_t, Category::OUTPUT>(offset)));
                        case Category::MEMORY: return VARIANT(static_cast<T_SINT16>(get<uint16_t, Category::MEMORY>(offset)));
                        default: throw std::invalid_argument("Unsupported category for word access");
                    }
                }
                case DataType::TYPE_DWORD: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(static_cast<T_SINT32>(get<uint32_t, Category::INPUT>(offset)));
                        case Category::OUTPUT: return VARIANT(static_cast<T_SINT32>(get<uint32_t, Category::OUTPUT>(offset)));
                        case Category::MEMORY: return VARIANT(static_cast<T_SINT32>(get<uint32_t, Category::MEMORY>(offset)));
                        default: throw std::invalid_argument("Unsupported category for dword access");
                    }
                }
                case DataType::TYPE_LWORD: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(static_cast<T_SINT64>(get<uint64_t, Category::INPUT>(offset)));
                        case Category::OUTPUT: return VARIANT(static_cast<T_SINT64>(get<uint64_t, Category::OUTPUT>(offset)));
                        case Category::MEMORY: return VARIANT(static_cast<T_SINT64>(get<uint64_t, Category::MEMORY>(offset)));
                        default: throw std::invalid_argument("Unsupported category for lword access");
                    }
                }
                case DataType::TYPE_REAL: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(get<float, Category::INPUT>(offset));
                        case Category::OUTPUT: return VARIANT(get<float, Category::OUTPUT>(offset));
                        case Category::MEMORY: return VARIANT(get<float, Category::MEMORY>(offset));
                        default: throw std::invalid_argument("Unsupported category for real access");
                    }
                }
                case DataType::TYPE_LREAL: {
                    switch(cat) {
                        case Category::INPUT:  return VARIANT(get<double, Category::INPUT>(offset));
                        case Category::OUTPUT: return VARIANT(get<double, Category::OUTPUT>(offset));
                        case Category::MEMORY: return VARIANT(get<double, Category::MEMORY>(offset));
                        default: throw std::invalid_argument("Unsupported category for lreal access");
                    }
                }
                default:
                    throw std::invalid_argument("Unsupported data type");
            }
        }
    }

    auto getByKey(const std::string& key) {
        return getByAddress(RegisterAddress::fromKey(key));
    }

    auto getByLong(uint64_t addr) {
        return getByAddress(RegisterAddress::fromLong(addr));
    }

private:
    std::vector<uint8_t> input_registers_;
    std::vector<uint8_t> output_registers_;
    std::vector<uint8_t> memory_registers_;

    std::vector<uint8_t>& getStorage(Category cat) {
        switch(cat) {
            case Category::INPUT:  return input_registers_;
            case Category::OUTPUT: return output_registers_;
            case Category::MEMORY: return memory_registers_;
            default: throw std::invalid_argument("Invalid register category");
        }
    }
};

#endif // CONTROLLER_REGISTERS_H
