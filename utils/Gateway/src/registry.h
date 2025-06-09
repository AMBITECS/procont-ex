//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef REGISTRY_H
#define REGISTRY_H

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

#include "address.h"
#include "variant.h"

constexpr unsigned int   REGISTRY_SIZE    = 65536;   // Размер категорий регистров

//-----------------------------------------------------------------------------
// Registry (улучшенная версия)
//-----------------------------------------------------------------------------
class Registry {
public:
    using Storage  = std::vector<uint8_t>;  // тип хранилища реестра
    using Category = Address::Category;     // тип категории реестра
    using DataType = Address::DataType;     // тип данных в реестре

// Внутренний метод для получения хранилища по категориям IEC
std::vector<uint8_t>& getStorage(Category cat) { return categories_[cat].A; }

private:
    // Регистры контроллера по категориям IEC
    struct RegStorage {
        Storage A;  // A - текущий слой
        Storage B;  // B - предыдущий слой
    };

    using  CategoriesMap  = std::unordered_map<Category, RegStorage>;
    using  SubscribersMap = std::unordered_map<Address, std::vector<std::function<void()>>>;

    CategoriesMap  categories_;
    SubscribersMap subscribers_;

    const std::vector<uint8_t>& getStorage(Category cat) const { return categories_.at(cat).A; }

public:
    explicit Registry(size_t memory_size = REGISTRY_SIZE) {
        // Инициализируем все категории по умолчанию
        categories_[Category::INPUT]   = RegStorage{};
        categories_[Category::OUTPUT]  = RegStorage{};
        categories_[Category::MEMORY]  = RegStorage{};
        categories_[Category::SPECIAL] = RegStorage{};
        resize(memory_size);
    }

    void resize(size_t new_size) {
        for (auto& [cat, reg] : categories_) {
            reg.A.resize(new_size);
            reg.B.resize(new_size);
        }
    }

    bool isChanged(const Address& addr) const {
        const auto& cat = categories_.at(addr.category());
        const size_t offset = addr.offset();
        size_t size = 0;

        // Определяем размер через switch вместо шаблонного параметра
        switch(addr.datatype()) {
            case Address::TYPE_BIT:   size = addr.hasBit() ? 1 : RegisterTraits<bool>::size; break;
            case Address::TYPE_BYTE:  size = RegisterTraits<uint8_t>::size; break;
            case Address::TYPE_WORD:  size = RegisterTraits<uint16_t>::size; break;
            case Address::TYPE_DWORD: size = RegisterTraits<uint32_t>::size; break;
            case Address::TYPE_LWORD: size = RegisterTraits<uint64_t>::size; break;
            case Address::TYPE_REAL:  size = RegisterTraits<float>::size; break;
            case Address::TYPE_LREAL: size = RegisterTraits<double>::size; break;
            default: throw std::invalid_argument("Unknown data type");
        }

        return memcmp(&cat.A[offset], &cat.B[offset], size) != 0;
    }

    void subscribe(const Address& addr, const std::function<void()>& callback) {
        subscribers_[addr].push_back(callback);
    }

    void commitChanges() {
        // Уведомление подписчиков
        for (const auto& [addr, callbacks] : subscribers_) {
            if (isChanged(addr)) {
                for (const auto& cb : callbacks) {
                    cb();
                }
            }
        }

        // Синхронизация слоёв
        for (auto& [cat, reg] : categories_) { reg.B = reg.A; }
    }

    //-------------------------------------------------------------------------
    // Accessor - шаблон доступа к типу T в категории CAT по смещению offset_
    //-------------------------------------------------------------------------
    template<typename T, Category CAT>
    class Accessor
    {
    private:
        Registry &parent_;
        uint64_t offset_;

        Storage &                       getStorage()        { return parent_.categories_[CAT].A; }
        [[nodiscard]] const Storage &   getStorage() const  { return parent_.categories_[CAT].A; }

        void checkBounds(size_t additional = 0) const {
            if (offset_ + additional + RegisterTraits<T>::size > getStorage().size()) {
                throw std::out_of_range("Register access out of range");
            }
        }

    public:
        Accessor(Registry &parent, uint64_t offset) : parent_(parent), offset_(offset) {
            if (offset_ % RegisterTraits<T>::size != 0) {
                throw std::runtime_error("Unaligned register access");
            }
        }

        // Безопасное приведение типов (извлечение значения)
        operator T() const { //NOLINT - неявное преобразование типа
            checkBounds();
            if constexpr (sizeof(T) == 1) {
                return getStorage()[offset_];
            } else {
                T value;
                std::memcpy(&value, &getStorage()[offset_], sizeof(T));
                return value;
            }
        }

        // Запись с защитой от aliasing (запись значения)
        Accessor &operator=(T value) {
            checkBounds();
            std::memcpy(&getStorage()[offset_], &value, sizeof(T));
            return *this;
        }

        Accessor& operator=(const Accessor& other) {
            if (this != &other) {
                parent_ = other.parent_;
                offset_ = other.offset_;
            }
            return *this;
        }

        Accessor& operator&=(T value) {
            checkBounds();
            T current;
            std::memcpy(&current, &getStorage()[offset_], sizeof(T));
            current &= value;
            std::memcpy(&getStorage()[offset_], &current, sizeof(T));
            return *this;
        }

        Accessor& operator|=(T value) {
            checkBounds();
            T current;
            std::memcpy(&current, &getStorage()[offset_], sizeof(T));
            current |= value;
            std::memcpy(&getStorage()[offset_], &current, sizeof(T));
            return *this;
        }

        Accessor& operator^=(T value) {
            checkBounds();
            T current;
            std::memcpy(&current, &getStorage()[offset_], sizeof(T));
            current ^= value;
            std::memcpy(&getStorage()[offset_], &current, sizeof(T));
            return *this;
        }

        Accessor& operator+=(T value) {
            checkBounds();
            T current;
            std::memcpy(&current, &getStorage()[offset_], sizeof(T));
            current += value;
            std::memcpy(&getStorage()[offset_], &current, sizeof(T));
            return *this;
        }

        Accessor& operator-=(T value) {
            checkBounds();
            T current;
            std::memcpy(&current, &getStorage()[offset_], sizeof(T));
            current -= value;
            std::memcpy(&getStorage()[offset_], &current, sizeof(T));
            return *this;
        }

        Accessor& operator&=(const Accessor& other) {
            return *this &= static_cast<T>(other);
        }

        Accessor& operator|=(const Accessor& other) {
            return *this |= static_cast<T>(other);
        }

        //---------------------------------------------------------------------
        // BitReference - побитовый доступ через Accessor
        //---------------------------------------------------------------------
        class BitReference {
            Accessor &accessor_;
            uint8_t bit_pos_;

        public:
            BitReference(Accessor &accessor, uint8_t bit_pos): accessor_(accessor), bit_pos_(bit_pos)
            {
                if (bit_pos_ >= sizeof(T) * 8) {
                    throw std::out_of_range("Bit position out of range");
                }
            }

            // Неявное приведение к bool (чтение бита)
            operator bool() const { //NOLINT - неявное преобразование типа
                return (static_cast<T>(accessor_) >> bit_pos_) & 0x01;
            }

            // Безопасная запись бита (установка или сброс)
            BitReference &operator=(bool b) {
                T value = static_cast<T>(accessor_);
                T mask = static_cast<T>(1) << bit_pos_;
                accessor_ = b ? (value | mask) : (value & ~mask);
                return *this;
            }

            BitReference& operator&=(bool b) {
                bool current = static_cast<bool>(*this);
                *this = current & b;
                return *this;
            }

            BitReference& operator|=(bool b) {
                bool current = static_cast<bool>(*this);
                *this = current | b;
                return *this;
            }

            BitReference& operator^=(bool b) {
                bool current = static_cast<bool>(*this);
                *this = current ^ b;
                return *this;
            }

        };

        BitReference operator[](uint8_t bit_pos) {
            static_assert(std::is_integral_v<T>, "Bit access only available for integral types");
            return BitReference(*this, bit_pos);
        }

        //---------------------------------------------------------------------
        // IndexProxy - выдача Accessor через operator[]
        //---------------------------------------------------------------------
        class IndexProxy {
            Registry& parent_;
            uint64_t base_offset_;  // Базовое смещение
            uint64_t count_;        // Количество элементов

        public:
            explicit IndexProxy(Registry& parent, uint64_t base_offset = 0, uint64_t count = 0)
                    : parent_(parent),
                      base_offset_(base_offset),
                      count_(count == 0 ? calculateCount(parent, base_offset) : count)
            {
                // Дополнительная проверка, если count задан явно
                if (count != 0) {
                    const auto& storage = parent.getStorage(CAT);
                    uint64_t required_size = base_offset_ + count * RegisterTraits<T>::size;
                    if (required_size > storage.size()) {
                        throw std::out_of_range(
                                "Requested count " + std::to_string(count) +
                                " exceeds available storage for type size " +
                                std::to_string(RegisterTraits<T>::size)
                        );
                    }
                }
            }

        private:
            // Вычисляет максимальное количество элементов
            uint64_t calculateCount(Registry& parent, uint64_t offset) const {
                const auto& storage = parent.getStorage(CAT);
                if (storage.size() <= offset) return 0;
                return (storage.size() - offset) / RegisterTraits<T>::size;
            }

        public:
            // Итератор для range-based for
            class Iterator {
                Registry* parent_;
                uint64_t base_offset_;
                uint64_t index_;
                uint64_t count_;

                // Храним кэшированный Accessor как член класса
                // (для конструкций типа for (auto & i : MW) checksum ^= i;)
                //Accessor current_accessor_;

            public:
                Iterator(Registry* parent, uint64_t offset, uint64_t index, uint64_t count):
                    parent_(parent),
                    base_offset_(offset),
                    index_(index),
                    count_(count)
                    //,current_accessor_(*parent, offset + index * RegisterTraits<T>::size)
                    {}

                //Accessor operator*() {
                //    return Accessor(*parent_, base_offset_ + index_ * RegisterTraits<T>::size);
                //}

                Accessor operator*() const {
                    return Accessor(*parent_, base_offset_ + index_ * RegisterTraits<T>::size);
                    //return (*parent_).get<T, CAT>(base_offset_ + index_ * RegisterTraits<T>::size);
                }

                //Accessor& operator*() {
                //    // Обновляем позицию current_accessor_
                //    current_accessor_ = Accessor(*parent_, base_offset_ + index_ * RegisterTraits<T>::size);
                //    return current_accessor_;
                //}

                Iterator& operator++() { ++index_; return *this; }
                bool operator!=(const Iterator& other) const { return index_ != other.index_; }
            };

            Iterator begin() { return Iterator(&parent_, base_offset_, 0, count_); }
            Iterator end()   { return Iterator(&parent_, base_offset_, count_, count_); }

            Accessor operator[](uint64_t index) {
                if (index >= count_) {
                    throw std::out_of_range("Register index out of range");
                }
                uint64_t offset = base_offset_ + index * RegisterTraits<T>::size;
                return Accessor(parent_, offset);
            }

            [[nodiscard]] uint64_t size() const { return count_; } // Добавляем метод size()
        };

    }; // Accessor

    template<typename T, Category CAT>
    Accessor<T, CAT> get(uint64_t offset) { return Accessor<T, CAT>(*this, offset); }

    // Базовые аксессоры по категориям
    template<typename T> using IRegister = Accessor<T, Category::INPUT>;
    template<typename T> using QRegister = Accessor<T, Category::OUTPUT>;
    template<typename T> using MRegister = Accessor<T, Category::MEMORY>;
    template<typename T> using SRegister = Accessor<T, Category::SPECIAL>;

    // Proxy-типы для входных регистров (I)
    using IX = IRegister<T_BOOL>::IndexProxy;
    using IB = IRegister<T_UINT8>::IndexProxy;
    using IW = IRegister<T_UINT16>::IndexProxy;
    using ID = IRegister<T_UINT32>::IndexProxy;
    using IL = IRegister<T_UINT64>::IndexProxy;
    using IR = IRegister<T_REAL32>::IndexProxy;  // для float
    using IF = IRegister<T_REAL64>::IndexProxy;  // для double

    // Proxy-типы для выходных регистров (Q)
    using QX = QRegister<T_BOOL>::IndexProxy;
    using QB = QRegister<T_UINT8>::IndexProxy;
    using QW = QRegister<T_UINT16>::IndexProxy;
    using QD = QRegister<T_UINT32>::IndexProxy;
    using QL = QRegister<T_UINT64>::IndexProxy;
    using QR = QRegister<T_REAL32>::IndexProxy;
    using QF = QRegister<T_REAL64>::IndexProxy;

    // Proxy-типы для регистров памяти (M)
    using MX = MRegister<T_BOOL>::IndexProxy;
    using MB = MRegister<T_UINT8>::IndexProxy;
    using MW = MRegister<T_UINT16>::IndexProxy;
    using MD = MRegister<T_UINT32>::IndexProxy;
    using ML = MRegister<T_UINT64>::IndexProxy;
    using MR = MRegister<T_REAL32>::IndexProxy;
    using MF = MRegister<T_REAL64>::IndexProxy;

    // Proxy-типы для специальных регистров (S)
    using SX = SRegister<T_BOOL>::IndexProxy;
    using SB = SRegister<T_UINT8>::IndexProxy;
    using SW = SRegister<T_UINT16>::IndexProxy;
    using SD = SRegister<T_UINT32>::IndexProxy;
    using SL = SRegister<T_UINT64>::IndexProxy;
    using SR = SRegister<T_REAL32>::IndexProxy;
    using SF = SRegister<T_REAL64>::IndexProxy;

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
            case Category::INPUT:   return access<Category::INPUT> ( datatype, offset, bitpos);
            case Category::OUTPUT:  return access<Category::OUTPUT>( datatype, offset, bitpos);
            case Category::MEMORY:  return access<Category::MEMORY>( datatype, offset, bitpos);
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
            case DataType::TYPE_BYTE:  return VARIANT(static_cast<uint8_t>  (get<uint8_t,  CAT>(offset)));
            case DataType::TYPE_WORD:  return VARIANT(static_cast<uint16_t> (get<uint16_t, CAT>(offset)));
            case DataType::TYPE_DWORD: return VARIANT(static_cast<uint32_t> (get<uint32_t, CAT>(offset)));
            case DataType::TYPE_LWORD: return VARIANT(static_cast<uint64_t> (get<uint64_t, CAT>(offset)));
            case DataType::TYPE_REAL:  return VARIANT(static_cast<float>    (get<float,    CAT>(offset)));
            case DataType::TYPE_LREAL: return VARIANT(static_cast<double>   (get<double,   CAT>(offset)));
            default: throw std::invalid_argument("Invalid data type");
        }
    }

};

#endif // REGISTRY_H
