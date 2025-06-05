#include "binding.h"
#include <stdexcept>

BindingManager::BindingManager(Registry& reg) : _reg(reg) {}

BindingManager& BindingManager::instance() {
    static Registry defaultRegistry;
    static BindingManager inst(defaultRegistry);
    return inst;
}

void BindingManager::bind(const std::string& regNotation, void* pvar) {
    Address addr = Address::fromString(regNotation);
    binds.emplace_back(addr, pvar);
}

void BindingManager::updateToIec() {
    for (auto& bind : binds) {
        updateVariable(bind.addr, bind.pvar, false);
    }
}

void BindingManager::updateFromIec() {
    for (auto& bind : binds) {
        updateVariable(bind.addr, bind.pvar, true);
    }
}

void BindingManager::updateVariable(const Address& addr, void* pvar, bool toRegistry) {
    using Cat = Registry::Category;
    switch(addr.category()) {
        case Address::INPUT:   processWithCategory<Cat::INPUT  > (addr, pvar, toRegistry); break;
        case Address::OUTPUT:  processWithCategory<Cat::OUTPUT > (addr, pvar, toRegistry); break;
        case Address::MEMORY:  processWithCategory<Cat::MEMORY > (addr, pvar, toRegistry); break;
        case Address::SPECIAL: processWithCategory<Cat::SPECIAL> (addr, pvar, toRegistry); break;
        default: throw std::invalid_argument("Unknown register category");
    }
}

template<Registry::Category CAT>
void BindingManager::processWithCategory(const Address& addr, void* pvar, bool toRegistry) {
    switch(addr.datatype()) {
        case Address::TYPE_BIT:
            if (toRegistry) {
                _reg.get<bool, CAT>(addr.offset())[addr.bitpos()] = *static_cast<bool*>(pvar);
            } else {
                *static_cast<bool*>(pvar) = _reg.get<bool, CAT>(addr.offset())[addr.bitpos()];
            }
            break;
        case Address::TYPE_BYTE:  handleType<CAT, uint8_t > (addr, pvar, toRegistry); break;
        case Address::TYPE_WORD:  handleType<CAT, uint16_t> (addr, pvar, toRegistry); break;
        case Address::TYPE_DWORD: handleType<CAT, uint32_t> (addr, pvar, toRegistry); break;
        case Address::TYPE_LWORD: handleType<CAT, uint64_t> (addr, pvar, toRegistry); break;
//        case Address::TYPE_REAL:  handleType<CAT, float   > (addr, pvar, toRegistry); break;
//        case Address::TYPE_LREAL: handleType<CAT, double  > (addr, pvar, toRegistry); break;
        default: throw std::invalid_argument("Unknown data type");
    }
}

template<Registry::Category CAT, typename T>
void BindingManager::handleType(const Address& addr, void* pvar, bool toRegistry) {
    if (toRegistry) {
        _reg.get<T, CAT>(addr.offset()) = *static_cast<T*>(pvar);
    } else {
        *static_cast<T*>(pvar) = _reg.get<T, CAT>(addr.offset());
    }
}

// Явные инстанциации шаблонных методов для всех поддерживаемых комбинаций
template void BindingManager::processWithCategory<Registry::Category::INPUT>      (const Address&, void*, bool);
template void BindingManager::processWithCategory<Registry::Category::OUTPUT>     (const Address&, void*, bool);
template void BindingManager::processWithCategory<Registry::Category::MEMORY>     (const Address&, void*, bool);
template void BindingManager::processWithCategory<Registry::Category::SPECIAL>    (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::INPUT,   uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::INPUT,   uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::INPUT,   uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::INPUT,   uint64_t > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::INPUT,   float    > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::INPUT,   double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::OUTPUT,  uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint64_t > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::OUTPUT,  float    > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::OUTPUT,  double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::MEMORY,  uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint64_t > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::MEMORY,  float    > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::MEMORY,  double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::SPECIAL, uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint64_t > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::SPECIAL, float    > (const Address&, void*, bool);
//template void BindingManager::handleType< Registry::Category::SPECIAL, double   > (const Address&, void*, bool);
