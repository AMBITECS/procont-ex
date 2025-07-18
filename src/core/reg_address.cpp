#include "reg_address.h"

#include <stdexcept>
#include <cctype>
#include <sstream>
#include <regex>

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

    // Разбираем тип данных
    Type type = TYPE_BIT;
    if (matches[2].length() > 0) {
        char type_char = static_cast<char>(toupper(static_cast<unsigned char>(matches[2].str()[0])));
        switch (type_char) {
            case 'X': type = TYPE_BIT;    break;
            case 'B': type = TYPE_BYTE;   break;
            case 'W': type = TYPE_WORD;   break;
            case 'D': type = TYPE_DWORD;  break;
            case 'L': type = TYPE_LWORD;  break;
            case 'R': type = TYPE_REAL;   break;
            case 'F': type = TYPE_LREAL;  break;
            default: throw std::invalid_argument("Unknown data type: " + matches[2].str());
        }
    }

    // Разбираем индекс (сохраняем как есть)
    uint64_t index = 0;
    if (matches[3].length() > 0) {
        try {
            index = std::stoull(matches[3].str());
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

    return Address{cat, type, index, bitpos};
}

std::string Address::toString() const {
    static const char* const category_prefixes = "IQMS";
    static const char* const type_prefixes = "XBWDLRF";
    std::ostringstream oss;
    // Категория (I/Q/M/S)
    if (category() <= SPECIAL)  { oss << category_prefixes[category()]; } else { oss << '?'; }
    // Тип данных (X/B/W/D/L/R/F)
    if (type() <= TYPE_LREAL)   { oss << type_prefixes[type()]; } else { oss << '?'; }
    // Выводим индекс (без преобразования)
    oss << index();
    // Позиция бита (если есть)
    if (isBit()) { oss << '.' << static_cast<int>(bitpos()); }
    return oss.str();
}

