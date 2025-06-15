//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Proxy-objects for Registry memory.
//-----------------------------------------------------------------------------
#include "proxy.h"
pthread_mutex_t bufferLock; //mutex for the internal buffers

Registry& getGlobalRegistry() {
    static Registry instance(REGISTRY_SIZE);
    return instance;
}

// Инициализируем глобальные прокси-объекты
Registry::IX IX{getGlobalRegistry()};
Registry::QX QX{getGlobalRegistry()};
Registry::MX MX{getGlobalRegistry(),   0,      2048 };
Registry::SX SX{getGlobalRegistry()};

Registry::IB IB{getGlobalRegistry()};
Registry::QB QB{getGlobalRegistry()};
Registry::MB MB{getGlobalRegistry(),   0,      2048 };
Registry::SB SB{getGlobalRegistry()};

Registry::IW IW{getGlobalRegistry()};
Registry::QW QW{getGlobalRegistry()};
Registry::MW MW{getGlobalRegistry(),   2048,   1024 };
Registry::SW SW{getGlobalRegistry()};

Registry::ID ID{getGlobalRegistry()};
Registry::QD QD{getGlobalRegistry()};
Registry::MD MD{getGlobalRegistry(),   4096,   1024 };
Registry::SD SD{getGlobalRegistry()};

Registry::IL IL{getGlobalRegistry()};
Registry::QL QL{getGlobalRegistry()};
Registry::ML ML{getGlobalRegistry(),   8192,   1024 };
Registry::SL SL{getGlobalRegistry()};

Registry::IF IF{getGlobalRegistry()};
Registry::QF QF{getGlobalRegistry()};
Registry::MF MF{getGlobalRegistry()};
Registry::SF SF{getGlobalRegistry()};

Registry::IE IE{getGlobalRegistry()};
Registry::QE QE{getGlobalRegistry()};
Registry::ME ME{getGlobalRegistry()};
Registry::SE SE{getGlobalRegistry()};

// Получение инстанцированного proxy-типа
template<typename T, Registry::Category CATEGORY>
auto& getProxy() {
    if constexpr (CATEGORY == Registry::Category::INPUT) {
        if constexpr (std::is_same_v<T, bool>)          return ::IX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::IB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::IW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::ID;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::IL;
        else if constexpr (std::is_same_v<T, float>)    return ::IF;
        else if constexpr (std::is_same_v<T, double>)   return ::IE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for INPUT category");
        }
    } else if constexpr (CATEGORY == Registry::Category::OUTPUT) {
        if constexpr (std::is_same_v<T, bool>)          return ::QX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::QB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::QW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::QD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::QL;
        else if constexpr (std::is_same_v<T, float>)    return ::QF;
        else if constexpr (std::is_same_v<T, double>)   return ::QE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for OUTPUT category");
        }
    } else if constexpr (CATEGORY == Registry::Category::MEMORY) {
        if constexpr (std::is_same_v<T, bool>)          return ::MX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::MB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::MW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::MD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::ML;
        else if constexpr (std::is_same_v<T, float>)    return ::MF;
        else if constexpr (std::is_same_v<T, double>)   return ::ME;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for MEMORY category");
        }
    } else if constexpr (CATEGORY == Registry::Category::SPECIAL) {
        if constexpr (std::is_same_v<T, bool>) return ::SX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::SB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::SW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::SD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::SL;
        else if constexpr (std::is_same_v<T, float>)    return ::SF;
        else if constexpr (std::is_same_v<T, double>)   return ::SE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for SPECIAL category");
        }
    } else {
        static_assert(sizeof(CATEGORY) == 0, "Unknown register category");
    }
}

template<Registry::Category CAT>
uint64_t getProxyValue(const Address& addr) {
    switch(addr.type()) {
        case Address::TYPE_BIT:    return getProxy<bool,     CAT>()[addr.index()] ? 1 : 0;
        case Address::TYPE_BYTE:   return getProxy<uint8_t,  CAT>()[addr.index()];
        case Address::TYPE_WORD:   return getProxy<uint16_t, CAT>()[addr.index()];
        case Address::TYPE_DWORD:  return getProxy<uint32_t, CAT>()[addr.index()];
        case Address::TYPE_LWORD:  return getProxy<uint64_t, CAT>()[addr.index()];
        case Address::TYPE_REAL:   {
            float val = getProxy<float, CAT>()[addr.index()];
            uint32_t tmp;
            memcpy(&tmp, &val, sizeof(float));
            return tmp;
        }
        case Address::TYPE_LREAL:  {
            double val = getProxy<double, CAT>()[addr.index()];
            uint64_t tmp;
            memcpy(&tmp, &val, sizeof(double));
            return tmp;
        }
        default: return 0;
    }
}

template<Registry::Category CAT>
void setProxyValue(const Address& addr, uint64_t value) {
    switch(addr.type()) {
        case Address::TYPE_BIT:   { getProxy<bool, CAT>()[addr.index()] = value != 0; break; }
        case Address::TYPE_BYTE:  { getProxy<uint8_t, CAT>()[addr.index()] = static_cast<uint8_t>(value); break; }
        case Address::TYPE_WORD:  { getProxy<uint16_t, CAT>()[addr.index()] = static_cast<uint16_t>(value); break; }
        case Address::TYPE_DWORD: { getProxy<uint32_t, CAT>()[addr.index()] = static_cast<uint32_t>(value); break; }
        case Address::TYPE_LWORD: { getProxy<uint64_t, CAT>()[addr.index()] = value; break; }
        case Address::TYPE_REAL: {
            float val;
            auto tmp = static_cast<uint32_t>(value);
            memcpy(&val, &tmp, sizeof(float));
            getProxy<float, CAT>()[addr.index()] = val;
            break;
        }
        case Address::TYPE_LREAL: {
            double val;
            memcpy(&val, &value, sizeof(double));
            getProxy<double, CAT>()[addr.index()] = val;
            break;
        }
        default:
            throw std::runtime_error("Unknown data type");
    }
}

template<Registry::Category CAT>
bool isProxyChanged(const Address& addr) {
    switch(addr.type()) {
        case Address::TYPE_BIT:    return getProxy<bool,     CAT>().isChanged(addr.index());
        case Address::TYPE_BYTE:   return getProxy<uint8_t,  CAT>().isChanged(addr.index());
        case Address::TYPE_WORD:   return getProxy<uint16_t, CAT>().isChanged(addr.index());
        case Address::TYPE_DWORD:  return getProxy<uint32_t, CAT>().isChanged(addr.index());
        case Address::TYPE_LWORD:  return getProxy<uint64_t, CAT>().isChanged(addr.index());
        case Address::TYPE_REAL:   return getProxy<float,    CAT>().isChanged(addr.index());
        case Address::TYPE_LREAL:  return getProxy<double,   CAT>().isChanged(addr.index());
        default: return false;
    }
}

//// Явные инстанциации для всех поддерживаемых комбинаций
template auto& getProxy<bool,     Registry::Category::INPUT>();
template auto& getProxy<uint8_t,  Registry::Category::INPUT>();
template auto& getProxy<uint16_t, Registry::Category::INPUT>();
template auto& getProxy<uint32_t, Registry::Category::INPUT>();
template auto& getProxy<uint64_t, Registry::Category::INPUT>();
template auto& getProxy<float,    Registry::Category::INPUT>();
template auto& getProxy<double,   Registry::Category::INPUT>();

template auto& getProxy<bool,     Registry::Category::OUTPUT>();
template auto& getProxy<uint8_t,  Registry::Category::OUTPUT>();
template auto& getProxy<uint16_t, Registry::Category::OUTPUT>();
template auto& getProxy<uint32_t, Registry::Category::OUTPUT>();
template auto& getProxy<uint64_t, Registry::Category::OUTPUT>();
template auto& getProxy<float,    Registry::Category::OUTPUT>();
template auto& getProxy<double,   Registry::Category::OUTPUT>();

template auto& getProxy<bool,     Registry::Category::MEMORY>();
template auto& getProxy<uint8_t,  Registry::Category::MEMORY>();
template auto& getProxy<uint16_t, Registry::Category::MEMORY>();
template auto& getProxy<uint32_t, Registry::Category::MEMORY>();
template auto& getProxy<uint64_t, Registry::Category::MEMORY>();
template auto& getProxy<float,    Registry::Category::MEMORY>();
template auto& getProxy<double,   Registry::Category::MEMORY>();

template auto& getProxy<bool,     Registry::Category::SPECIAL>();
template auto& getProxy<uint8_t,  Registry::Category::SPECIAL>();
template auto& getProxy<uint16_t, Registry::Category::SPECIAL>();
template auto& getProxy<uint32_t, Registry::Category::SPECIAL>();
template auto& getProxy<uint64_t, Registry::Category::SPECIAL>();
template auto& getProxy<float,    Registry::Category::SPECIAL>();
template auto& getProxy<double,   Registry::Category::SPECIAL>();

template bool isProxyChanged<Registry::Category::INPUT>  (const Address& addr);
template bool isProxyChanged<Registry::Category::OUTPUT> (const Address& addr);
template bool isProxyChanged<Registry::Category::MEMORY> (const Address& addr);
template bool isProxyChanged<Registry::Category::SPECIAL>(const Address& addr);

template uint64_t getProxyValue<Registry::Category::INPUT>  (const Address& addr);
template uint64_t getProxyValue<Registry::Category::OUTPUT> (const Address& addr);
template uint64_t getProxyValue<Registry::Category::MEMORY> (const Address& addr);
template uint64_t getProxyValue<Registry::Category::SPECIAL>(const Address& addr);

// Явные инстанциации для всех категорий
template void setProxyValue<Registry::Category::INPUT>(const Address&, uint64_t);
template void setProxyValue<Registry::Category::OUTPUT>(const Address&, uint64_t);
template void setProxyValue<Registry::Category::MEMORY>(const Address&, uint64_t);
template void setProxyValue<Registry::Category::SPECIAL>(const Address&, uint64_t);