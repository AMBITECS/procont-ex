#include "binding.h"
#include <stdexcept>

BindingManager::Binding::Binding(Address adr, void *dat): addr(adr), iecVar(dat) {}

BindingManager::BindingManager(Registry& reg) : _reg(reg) {}

BindingManager& BindingManager::instance() {
    static Registry defaultRegistry;
    static BindingManager inst(defaultRegistry);
    return inst;
}

void BindingManager::bind(const std::string& regNotation, void* iecVar) {
    Address addr = Address::fromString(regNotation);
    bindings_.emplace_back(addr, iecVar);
}

void BindingManager::updateToIec() {
    for (auto& binding : bindings_) { updateVariable(binding.addr, binding.iecVar, false); }
}

void BindingManager::updateFromIec() {
    for (auto& binding : bindings_) { updateVariable(binding.addr, binding.iecVar,  true); }
}

void BindingManager::updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
    using Cat = Registry::Category;
    switch(addr.category()) {
        case Address::INPUT:   processWithCategory<Cat::INPUT  > (addr, iecVar, toRegistry); break;
        case Address::OUTPUT:  processWithCategory<Cat::OUTPUT > (addr, iecVar, toRegistry); break;
        case Address::MEMORY:  processWithCategory<Cat::MEMORY > (addr, iecVar, toRegistry); break;
        case Address::SPECIAL: processWithCategory<Cat::SPECIAL> (addr, iecVar, toRegistry); break;
        default: throw std::invalid_argument("Unknown register category");
    }
}

template<Registry::Category CAT>
void BindingManager::processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.datatype()) {
        case Address::TYPE_BIT:
            if (toRegistry) {
                _reg.get<bool, CAT>(addr.offset())[addr.bitpos()] = *static_cast<bool*>(iecVar);
            } else {
                *static_cast<bool*>(iecVar) = _reg.get<bool, CAT>(addr.offset())[addr.bitpos()];
            }
            break;
        case Address::TYPE_BYTE:  handleType<CAT, uint8_t > (addr, iecVar, toRegistry); break;
        case Address::TYPE_WORD:  handleType<CAT, uint16_t> (addr, iecVar, toRegistry); break;
        case Address::TYPE_DWORD: handleType<CAT, uint32_t> (addr, iecVar, toRegistry); break;
        case Address::TYPE_LWORD: handleType<CAT, uint64_t> (addr, iecVar, toRegistry); break;
        case Address::TYPE_REAL:  handleType<CAT, float   > (addr, iecVar, toRegistry); break;
        case Address::TYPE_LREAL: handleType<CAT, double  > (addr, iecVar, toRegistry); break;
        default: throw std::invalid_argument("Unknown data type");
    }
}

template<Registry::Category CAT, typename T>
void BindingManager::handleType(const Address& addr, void* iecVar, bool toRegistry) {
    if (toRegistry) {
        _reg.get<T, CAT>(addr.offset()) = *static_cast<T*>(iecVar);
    } else {
        *static_cast<T*>(iecVar) = _reg.get<T, CAT>(addr.offset());
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
template void BindingManager::handleType< Registry::Category::INPUT,   float    > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::INPUT,   double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::OUTPUT,  uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  uint64_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  float    > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::OUTPUT,  double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::MEMORY,  uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  uint64_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  float    > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::MEMORY,  double   > (const Address&, void*, bool);

template void BindingManager::handleType< Registry::Category::SPECIAL, uint8_t  > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint16_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint32_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, uint64_t > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, float    > (const Address&, void*, bool);
template void BindingManager::handleType< Registry::Category::SPECIAL, double   > (const Address&, void*, bool);
