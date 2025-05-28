#ifndef REGISTER_ADDRESS_H
#define REGISTER_ADDRESS_H

#include <string>
#include <cstdint>
#include <stdexcept>

class Address {
public:
    // Категории регистров (4 бита)
    enum Category : uint8_t {
        INPUT   = 0,        // 'I' - входные регистры
        OUTPUT  = 1,        // 'Q' - выходные регистры
        MEMORY  = 2,        // 'M' - регистры памяти
        SPECIAL = 3         // 'S' - специальные регистры
    };

    // Типы данных (4 бита)
    enum DataType : uint8_t {
        TYPE_BIT    = 0,    // 'X' - бит
        TYPE_BYTE   = 1,    // 'B' - байт
        TYPE_WORD   = 2,    // 'W' - слово
        TYPE_DWORD  = 3,    // 'D' - двойное слово
        TYPE_LWORD  = 4,    // 'L' - длинное слово
        TYPE_REAL   = 5,    // 'R' - вещественное (float)
        TYPE_LREAL  = 6     // 'F' - длинное вещественное (double)
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
    constexpr Address() : packed_(0) {}
    constexpr Address(Category cat, DataType type, uint64_t offset, uint8_t bitpos = 0xFF)
            : packed_((static_cast<uint64_t>(cat)    << CATEGORY_SHIFT) |
                      (static_cast<uint64_t>(type)   << TYPE_SHIFT)     |
                      (static_cast<uint64_t>(bitpos) << BITPOS_SHIFT)   |
                      (offset & OFFSET_MASK)) {}

    // Фабричные методы
    static Address Of(const std::string& key);
    static constexpr Address Of(uint64_t val) { return Address(val); }

    // Преобразования
    [[nodiscard]] constexpr uint64_t value() const { return packed_; }
    constexpr operator uint64_t() const { return packed_; }

    [[nodiscard]] std::string toString() const;

    // Методы доступа
    [[nodiscard]] constexpr Category category() const {
        return static_cast<Category>((packed_ & CATEGORY_MASK) >> CATEGORY_SHIFT);
    }

    [[nodiscard]] constexpr DataType datatype() const {
        return static_cast<DataType>((packed_ & TYPE_MASK) >> TYPE_SHIFT);
    }

    [[nodiscard]] constexpr uint64_t offset() const { return packed_ & OFFSET_MASK; }

    [[nodiscard]] constexpr uint8_t bitpos() const {
        uint8_t pos = (packed_ & BITPOS_MASK) >> BITPOS_SHIFT;
        return (datatype() == TYPE_BIT) ? pos : 0xFF;
    }

    [[nodiscard]] constexpr bool isBitAccess() const {
        return datatype() == TYPE_BIT && ((packed_ & BITPOS_MASK) >> BITPOS_SHIFT) != 0xFF;
    }

private:
    constexpr explicit Address(uint64_t packed) : packed_(packed) {}

    uint64_t packed_; // Все данные упакованы в 64 бита
};

#endif // REGISTER_ADDRESS_H
