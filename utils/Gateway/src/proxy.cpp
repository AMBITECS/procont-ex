//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Proxy-objects for Registry memory.
//-----------------------------------------------------------------------------
#include "proxy.h"
#include <mutex>

Registry& getGlobalRegistry() {
    static Registry instance(REGISTRY_SIZE);
    return instance;
}

// Инициализация proxy-объектов
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

// Вспомогательная структура для ошибок
template<typename T>
struct TypeNotSupported {
    static_assert(sizeof(T) == 0, "Type not supported for this category");
};

template<typename T, Registry::Category CAT>
auto& _getProxy() {
    if constexpr (CAT == Registry::Category::INPUT) {
        if      constexpr (std::is_same_v<T, bool>)     return ::IX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::IB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::IW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::ID;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::IL;
        else if constexpr (std::is_same_v<T, float>)    return ::IF;
        else if constexpr (std::is_same_v<T, double>)   return ::IE;
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::OUTPUT) {
        if      constexpr (std::is_same_v<T, bool>)     return ::QX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::QB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::QW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::QD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::QL;
        else if constexpr (std::is_same_v<T, float>)    return ::QF;
        else if constexpr (std::is_same_v<T, double>)   return ::QE;
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::MEMORY) {
        if      constexpr (std::is_same_v<T, bool>)     return ::MX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::MB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::MW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::MD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::ML;
        else if constexpr (std::is_same_v<T, float>)    return ::MF;
        else if constexpr (std::is_same_v<T, double>)   return ::ME;
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::SPECIAL) {
        if      constexpr (std::is_same_v<T, bool>)     return ::SX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::SB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::SW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::SD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::SL;
        else if constexpr (std::is_same_v<T, float>)    return ::SF;
        else if constexpr (std::is_same_v<T, double>)   return ::SE;
        else return TypeNotSupported<T>::value;
    }
    else {
        return TypeNotSupported<T>::value;
    }
}

template<Registry::Category CAT, typename F>
auto _processWithCategory(const Address& addr, F&& func) {
    switch(addr.type()) {
        case Address::TYPE_BIT:     return func(_getProxy<bool, CAT>(), addr.index());
        case Address::TYPE_BYTE:    return func(_getProxy<uint8_t, CAT>(), addr.index());
        case Address::TYPE_WORD:    return func(_getProxy<uint16_t, CAT>(), addr.index());
        case Address::TYPE_DWORD:   return func(_getProxy<uint32_t, CAT>(), addr.index());
        case Address::TYPE_LWORD:   return func(_getProxy<uint64_t, CAT>(), addr.index());
        case Address::TYPE_REAL:    return func(_getProxy<float, CAT>(), addr.index());
        case Address::TYPE_LREAL:   return func(_getProxy<double, CAT>(), addr.index());
        default: throw std::runtime_error("Unsupported data type");
    }
}

//template<typename T, Registry::Category CAT>
//void _handleType(const Address& addr, void* iecVar, bool toRegistry) {
//    auto& proxy = _getProxy<T, CAT>();
//    const size_t index = addr.index();
//    if (toRegistry) {
//        proxy[index] = *static_cast<T*>(iecVar);
//    } else {
//        *static_cast<T*>(iecVar) = proxy[index];
//    }
//}

// Шаблонные вспомогательные функции
template<Registry::Category CAT>
uint64_t _getProxyValueByCategory(const Address& addr) {
    return _processWithCategory<CAT>(addr, [](auto& proxy, uint64_t index) -> uint64_t {
        using ValueType = typename std::remove_reference_t<decltype(proxy)>::value_type;

        if constexpr (std::is_same_v<ValueType, float>) {
            float val = proxy[index];
            uint32_t tmp;
            memcpy(&tmp, &val, sizeof(float));
            return tmp;
        }
        else if constexpr (std::is_same_v<ValueType, double>) {
            double val = proxy[index];
            uint64_t tmp;
            memcpy(&tmp, &val, sizeof(double));
            return tmp;
        }
        else {
            return static_cast<uint64_t>(proxy[index]);
        }
    });
}

template<Registry::Category CAT>
void _setProxyValueByCategory(const Address& addr, uint64_t value) {
    _processWithCategory<CAT>(addr, [value](auto& proxy, uint64_t index) {
        using ValueType = typename std::remove_reference_t<decltype(proxy)>::value_type;

        if constexpr (std::is_same_v<ValueType, float>) {
            float val;
            auto tmp = static_cast<uint32_t>(value);
            memcpy(&val, &tmp, sizeof(float));
            proxy[index] = val;
        }
        else if constexpr (std::is_same_v<ValueType, double>) {
            double val;
            memcpy(&val, &value, sizeof(double));
            proxy[index] = val;
        }
        else {
            proxy[index] = static_cast<ValueType>(value);
        }
    });
}

template<Registry::Category CAT>
bool _isProxyChangedByCategory(const Address& addr) {
    return _processWithCategory<CAT>(addr, [](auto& proxy, uint64_t index) {
        return proxy.isChanged(index);
    });
}

//template<Registry::Category CAT>
//uint64_t _getProxyValueByCategory(const Address& addr) {
//    return _processWithCategory<CAT>(addr, [](auto& proxy, uint64_t index) {
//        return static_cast<uint64_t>(proxy[index]);
//    });
//}
//
//template<Registry::Category CAT>
//void _setProxyValueByCategory(const Address& addr, uint64_t value) {
//    _processWithCategory<CAT>(addr, [value](auto& proxy, uint64_t index) {
//        proxy[index] = static_cast<typename std::remove_reference_t<decltype(proxy)>::value_type>(value);
//    });
//}
//
//template<Registry::Category CAT>
//bool _isProxyChangedByCategory(const Address& addr) {
//    return _processWithCategory<CAT>(addr, [](auto& proxy, uint64_t index) {
//        return proxy.isChanged(index);
//    });
//}


// Основные функции-обёртки
uint64_t getProxyValue(const Address& addr) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   return _getProxyValueByCategory<Registry::Category::INPUT>(addr);
        case Registry::Category::OUTPUT:  return _getProxyValueByCategory<Registry::Category::OUTPUT>(addr);
        case Registry::Category::MEMORY:  return _getProxyValueByCategory<Registry::Category::MEMORY>(addr);
        case Registry::Category::SPECIAL: return _getProxyValueByCategory<Registry::Category::SPECIAL>(addr);
        default: throw std::runtime_error("Unknown register category");
    }
}

void setProxyValue(const Address& addr, uint64_t value) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   _setProxyValueByCategory<Registry::Category::INPUT>(addr, value); break;
        case Registry::Category::OUTPUT:  _setProxyValueByCategory<Registry::Category::OUTPUT>(addr, value); break;
        case Registry::Category::MEMORY:  _setProxyValueByCategory<Registry::Category::MEMORY>(addr, value); break;
        case Registry::Category::SPECIAL: _setProxyValueByCategory<Registry::Category::SPECIAL>(addr, value); break;
        default: throw std::runtime_error("Unknown register category");
    }
}

bool isProxyChanged(const Address& addr) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   return _isProxyChangedByCategory<Registry::Category::INPUT>(addr);
        case Registry::Category::OUTPUT:  return _isProxyChangedByCategory<Registry::Category::OUTPUT>(addr);
        case Registry::Category::MEMORY:  return _isProxyChangedByCategory<Registry::Category::MEMORY>(addr);
        case Registry::Category::SPECIAL: return _isProxyChangedByCategory<Registry::Category::SPECIAL>(addr);
        default: return false;
    }
}

// Реализация методов (без шаблонов!)
//uint64_t getProxyValue(const Address& addr) {
//    return getGlobalRegistry().getRawValue(addr); // Категория берётся из addr.category()
//}
//
//void setProxyValue(const Address& addr, uint64_t value) {
//    getGlobalRegistry().setRawValue(addr, value); // Категория из addr.category()
//}
//
//bool isProxyChanged(const Address& addr) {
//    return getGlobalRegistry().isChanged(addr); // Категория из addr.category()
//}

