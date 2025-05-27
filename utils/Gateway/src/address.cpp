#include "address.h"
#include <stdexcept>

const std::regex RegisterAddress::key_regex_("([IQMSE]\\d*)([XBWDLT]\\d*)(\\d+)(?:\\.(\\d+))?");
const char* const RegisterAddress::category_prefixes_ = "IQMSE";
const char* const RegisterAddress::type_prefixes_ = "XBWDLT";

RegisterAddress RegisterAddress::fromKey(const std::string& key) {
    std::smatch match;
    if (!std::regex_match(key, match, key_regex_)) {
        throw std::invalid_argument("Invalid register key format");
    }

    // Парсинг категории
    Category cat = INPUT;
    char cat_prefix = match[1].str()[0];
    switch(cat_prefix) {
        case 'I': cat = INPUT; break;
        case 'Q': cat = OUTPUT; break;
        case 'M': cat = MEMORY; break;
        case 'S': cat = SPECIAL; break;
        case 'E': cat = static_cast<Category>(3 + std::stoi(match[1].str().substr(1)));
        default: throw std::invalid_argument("Invalid category prefix");
    }

    // Парсинг типа данных
    DataType dtype = TYPE_BIT;
    char type_prefix = match[2].str()[0];
    switch(type_prefix) {
        case 'X': dtype = TYPE_BIT; break;
        case 'B': dtype = TYPE_BYTE; break;
        case 'W': dtype = TYPE_WORD; break;
        case 'D': dtype = TYPE_DWORD; break;
        case 'L': dtype = TYPE_LWORD; break;
        case 'T': dtype = static_cast<DataType>(4 + std::stoi(match[2].str().substr(1)));
        default: throw std::invalid_argument("Invalid type prefix");
    }

    // Парсинг смещения и битовой позиции
    uint64_t offset = std::stoull(match[3]);
    uint8_t bitpos = 0xFF;

    if (dtype == TYPE_BIT && match[4].matched) {
        bitpos = std::stoul(match[4]);
        if (bitpos > 63) throw std::out_of_range("Bit position must be 0-63");
    }

    return RegisterAddress(cat, dtype, offset, bitpos);
}

std::string RegisterAddress::toKey() const {
    std::ostringstream oss;

    // Категория
    uint8_t cat = getCategory();
    if (cat <= SPECIAL) {
        oss << category_prefixes_[cat];
    } else {
        oss << 'E' << (cat - 3);
    }

    // Тип данных
    uint8_t type = getDataType();
    if (type <= TYPE_LWORD) {
        oss << type_prefixes_[type];
    } else {
        oss << 'T' << (type - 4);
    }

    // Смещение
    uint64_t type_size = (type == TYPE_BIT) ? 1 : (1 << (type - 1));
    oss << (getOffset() / type_size);

    // Битовая позиция
    if (type == TYPE_BIT) {
        uint8_t bp = getBitPosition();
        if (bp != 0xFF) oss << '.' << static_cast<int>(bp);
    }

    return oss.str();
}
