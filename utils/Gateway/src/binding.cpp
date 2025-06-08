#include "binding.h"
#include <stdexcept>

//std::unique_ptr<BindingManager> BindingManager::_instance;

BindingManager::BindingManager(Registry& reg) : _reg(reg) {}

BindingManager& BindingManager::instance() {
    static Registry defaultRegistry;
    static BindingManager inst(defaultRegistry);
    return inst;
}

//void BindingManager::init(Registry& reg) {
//    if (!_instance) {
//        _instance = std::unique_ptr<BindingManager>(new BindingManager(reg));
//    }
//}
//
//BindingManager& BindingManager::instance() {
//    if (!_instance) {
//        throw std::runtime_error("BindingManager not initialized");
//    }
//    return *_instance;
//}

template<Registry::Category CAT, typename T>
void BindingManager::handleType(const Address& addr, void* iecVar, bool toRegistry) {
    if (addr.offset() % RegisterTraits<T>::size != 0) {
        throw std::runtime_error("Unaligned access for " + addr.toString());
    }

    auto accessor = _reg.get<T, CAT>(addr.offset());
    if (toRegistry) {
        accessor = *static_cast<T*>(iecVar);
    } else {
        *static_cast<T*>(iecVar) = static_cast<T>(accessor);
    }
}

template<Registry::Category CAT>
void BindingManager::processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.datatype()) {
        case Address::TYPE_BIT:    handleType<CAT, bool>(addr, iecVar, toRegistry); break;
        case Address::TYPE_BYTE:   handleType<CAT, uint8_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_WORD:   handleType<CAT, uint16_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_DWORD:  handleType<CAT, uint32_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_LWORD:  handleType<CAT, uint64_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_REAL:   handleType<CAT, float>(addr, iecVar, toRegistry); break;
        case Address::TYPE_LREAL:  handleType<CAT, double>(addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown data type");
    }
}

void BindingManager::updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   processWithCategory<Registry::Category::INPUT>(addr, iecVar, toRegistry); break;
        case Registry::Category::OUTPUT:  processWithCategory<Registry::Category::OUTPUT>(addr, iecVar, toRegistry); break;
        case Registry::Category::MEMORY:  processWithCategory<Registry::Category::MEMORY>(addr, iecVar, toRegistry); break;
        case Registry::Category::SPECIAL: processWithCategory<Registry::Category::SPECIAL>(addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown register category");
    }
}

void BindingManager::bind(const std::string& regNotation, void* iecVar) {
    Address addr = Address::fromString(regNotation);
    binds.emplace_back(addr, iecVar);
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

// Явная инстанциация шаблонов
//template void BindingManager::handleType<Registry::Category::INPUT, bool>(const Address&, void*, bool);
//template void BindingManager::handleType<Registry::Category::INPUT, uint8_t>(const Address&, void*, bool);
//// ... (добавьте остальные необходимые инстанциации)

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
