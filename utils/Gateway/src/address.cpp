#include "address.h"
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <regex>

std::string Address::toString() const {
    static const char* const category_prefixes = "IQMS";
    static const char* const type_prefixes = "XBWDLRF";

    std::ostringstream oss;

    // Категория (I/Q/M/S)
    if (category() <= SPECIAL) { oss << category_prefixes[category()]; } else { oss << '?'; }

    // Тип данных (X/B/W/D/L/R/F)
    if (type() <= TYPE_LREAL) { oss << type_prefixes[type()]; } else { oss << '?'; }

    // Вычисляем индекс в зависимости от типа данных
    size_t index = offset();
    switch(type()) {
        case TYPE_WORD:   index /= 2; break;    // WORD  - 2 байта
        case TYPE_DWORD:  index /= 4; break;    // DWORD - 4 байта
        case TYPE_LWORD:  index /= 8; break;    // LWORD - 8 байт
        case TYPE_REAL:   index /= 4; break;    // REAL  - 4 байта
        case TYPE_LREAL:  index /= 8; break;    // LREAL - 8 байт
        default: break;                         // BIT и BYTE - 1 байт (index = offset)
    }
    oss << index;

    // Позиция бита (если есть)
    if (isBit()) { oss << '.' << static_cast<int>(bitpos());}

    return oss.str();
}

Address Address::of(const std::string& key) {
    std::smatch matches;
    std::string normalized_key = key;
    const std::regex key_regex_(
            R"(^%?([IQMS])([XBWDRLF]?)(?:(\d+)(?:\.(\d+))?)?$)",
            std::regex_constants::icase);

    // Удаляем начальный '%' если присутствует
    if (!normalized_key.empty() && normalized_key[0] == '%') {
        normalized_key.erase(0, 1);
    }

    if (!std::regex_match(normalized_key, matches, key_regex_)) {
        throw std::invalid_argument("Invalid register address format: " + key);
    }

    // Разбираем категорию
    char cat_char = static_cast<char>(toupper(static_cast<unsigned char>(matches[1].str()[0])));
    Category cat;
    switch (cat_char) {
        case 'I': cat = Category::INPUT;   break;
        case 'Q': cat = Category::OUTPUT;  break;
        case 'M': cat = Category::MEMORY;  break;
        case 'S': cat = Category::SPECIAL; break;
        default: throw std::invalid_argument("Unknown register category: " + matches[1].str());
    }

    // Разбираем тип данных и определяем размер
    DataType type = TYPE_BIT;
    size_t type_size = 1;
    if (matches[2].length() > 0) {
        char type_char = static_cast<char>(toupper(static_cast<unsigned char>(matches[2].str()[0])));
        switch (type_char) {
            case 'X':   type = TYPE_BIT;    type_size = 1; break;
            case 'B':   type = TYPE_BYTE;   type_size = 1; break;
            case 'W':   type = TYPE_WORD;   type_size = 2; break;
            case 'D':   type = TYPE_DWORD;  type_size = 4; break;
            case 'L':   type = TYPE_LWORD;  type_size = 8; break;
            case 'R':   type = TYPE_REAL;   type_size = 4; break;
            case 'F':   type = TYPE_LREAL;  type_size = 8; break;
            default: throw std::invalid_argument("Unknown data type: " + matches[2].str());
        }
    }

    // Разбираем индекс и вычисляем смещение
    uint64_t index = 0;
    uint64_t offset = 0;
    if (matches[3].length() > 0) {
        try {
            index = std::stoull(matches[3].str());
            offset = index * type_size; // Преобразуем индекс в смещение в байтах
        } catch (...) {
            throw std::invalid_argument("Invalid index value: " + matches[3].str());
        }
    }

    // Разбираем позицию бита (если есть)
    uint8_t bitpos = 0xFF;
    if (matches[4].length() > 0) {
        try {
            int pos = std::stoi(matches[4].str());
            if (pos < 0 || pos > 63) {
                throw std::invalid_argument("Bit position out of range (0-63): " + matches[4].str());
            }
            bitpos = static_cast<uint8_t>(pos);
        } catch (...) {
            throw std::invalid_argument("Invalid bit position: " + matches[4].str());
        }
    }

    // Проверяем корректность комбинации типа и позиции бита
    if (bitpos != 0xFF && type != TYPE_BIT) {
        throw std::invalid_argument("Bit position can only be specified for bit type (X)");
    }

    return Address{cat, type, offset, bitpos};
}
