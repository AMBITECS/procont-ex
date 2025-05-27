#ifndef REGISTER_ADDRESS_H
#define REGISTER_ADDRESS_H

#include <cstdint>
#include <string>
#include <regex>
#include <stdexcept>

class RegisterAddress {
public:
    // Категории регистров (4 бита)
    enum Category : uint8_t {
        INPUT = 0, OUTPUT = 1, MEMORY = 2, SPECIAL = 3, EXT1 = 4, EXT2 = 5, EXT3 = 6, EXT4 = 7,
        EXT5 = 8, EXT6 = 9, EXT7 = 10, EXT8 = 11, EXT9 = 12, EXT10 = 13, EXT11 = 14, EXT12 = 15
    };

    // Типы данных (4 бита)
    enum DataType : uint8_t {
        TYPE_BIT = 0, TYPE_BYTE = 1, TYPE_WORD = 2, TYPE_DWORD = 3, TYPE_LWORD = 4,
        TYPE_REAL = 5, TYPE_LREAL = 6
    };

    // Битовые поля в 64-битном значении
    static constexpr uint64_t CATEGORY_SHIFT = 60;
    static constexpr uint64_t TYPE_SHIFT     = 56;
    static constexpr uint64_t BITPOS_SHIFT   = 48;

    static constexpr uint64_t CATEGORY_MASK  = 0xF000000000000000;
    static constexpr uint64_t TYPE_MASK      = 0x0F00000000000000;
    static constexpr uint64_t BITPOS_MASK    = 0x00FF000000000000;
    static constexpr uint64_t OFFSET_MASK    = 0x0000FFFFFFFFFFFF;

    // Конструкторы
    constexpr RegisterAddress() : packed_(0) {}

    constexpr RegisterAddress(Category cat, DataType type, uint64_t offset, uint8_t bitpos = 0xFF)
            : packed_((static_cast<uint64_t>(cat)  << CATEGORY_SHIFT) |
                      (static_cast<uint64_t>(type) << TYPE_SHIFT)     |
                      (static_cast<uint64_t>(bitpos) << BITPOS_SHIFT) |
                      (offset & OFFSET_MASK)) {}

    // Фабричные методы
    static RegisterAddress fromKey(const std::string& key);
    static constexpr RegisterAddress fromLong(uint64_t val) {
        return RegisterAddress(val);
    }

    // Преобразования
    constexpr uint64_t toLong() const { return packed_; }
    std::string toKey() const;

    // Методы доступа
    constexpr Category getCategory() const {
        return static_cast<Category>((packed_ & CATEGORY_MASK) >> CATEGORY_SHIFT);
    }

    constexpr DataType getDataType() const {
        return static_cast<DataType>((packed_ & TYPE_MASK) >> TYPE_SHIFT);
    }

    constexpr uint64_t getOffset() const {
        return packed_ & OFFSET_MASK;
    }

    constexpr uint8_t getBitPosition() const {
        uint8_t pos = (packed_ & BITPOS_MASK) >> BITPOS_SHIFT;
        return (getDataType() == TYPE_BIT) ? pos : 0xFF;
    }

private:
    constexpr explicit RegisterAddress(uint64_t packed) : packed_(packed) {}

    uint64_t packed_; // Все данные упакованы в 64 бита

    // Вспомогательные структуры для парсинга
    static const std::regex     key_regex_;
    static const char* const    category_prefixes_;
    static const char* const    type_prefixes_;
};

#endif // REGISTER_ADDRESS_H
