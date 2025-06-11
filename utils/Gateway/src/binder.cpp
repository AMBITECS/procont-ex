#include "binder.h"

std::unique_ptr<Binder> Binder::_instance;

Binder& Binder::instance() {
    if (!_instance) {
        _instance = std::unique_ptr<Binder>(new Binder());
    }
    return *_instance;
}

void Binder::bind(const std::string& regNotation, void* iecVar) {
    Address addr = Address::of(regNotation);
    binds.emplace_back(Binding{addr, iecVar});
}

void Binder::updateToIec() {
    for (auto& bind : binds) {
        updateVariable(bind.addr, bind.pvar, false);
    }
}

void Binder::updateFromIec() {
    for (auto& bind : binds) {
        updateVariable(bind.addr, bind.pvar, true);
    }
}

void Binder::updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
    using Cat = Registry::Category;
    switch(addr.category()) {
        case Cat::INPUT:   processWithCategory<Cat::INPUT>  (addr, iecVar, toRegistry); break;
        case Cat::OUTPUT:  processWithCategory<Cat::OUTPUT> (addr, iecVar, toRegistry); break;
        case Cat::MEMORY:  processWithCategory<Cat::MEMORY> (addr, iecVar, toRegistry); break;
        case Cat::SPECIAL: processWithCategory<Cat::SPECIAL>(addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown register category");
    }
}

template<Registry::Category CAT>
void Binder::processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.type()) {
        case Address::TYPE_BIT:   handleType<bool    , CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_BYTE:  handleType<uint8_t , CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_WORD:  handleType<uint16_t, CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_DWORD: handleType<uint32_t, CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_LWORD: handleType<uint64_t, CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_REAL:  handleType<float   , CAT> (addr, iecVar, toRegistry); break;
        case Address::TYPE_LREAL: handleType<double  , CAT> (addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown data type");
    }
}

template<typename T, Registry::Category CAT>
void Binder::handleType(const Address& addr, void* iecVar, bool toRegistry) {
    auto& proxy = getProxy<T, CAT>();
    const size_t index = addr.index();
    if (toRegistry) {
        proxy[index] = *static_cast<T*>(iecVar);
    } else {
        *static_cast<T*>(iecVar) = proxy[index];
    }
}

template<typename T, Registry::Category CAT>
auto& Binder::getProxy() {
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
