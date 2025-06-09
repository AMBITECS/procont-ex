#include "gateway.h"
#include <stdexcept>
#include <iostream>
#include <cassert>

std::unique_ptr<BindingManager> BindingManager::_instance;
BindingManager::BindingManager(Registry& reg) : _reg(reg) {}

BindingManager& BindingManager::instance() {
    if (!_instance) {
        _instance = std::unique_ptr<BindingManager>(
                new BindingManager(::getGlobalRegistry())
        );
    }
    return *_instance;
}

template<Registry::Category CAT, typename T>
void BindingManager::handleType(const Address& addr, void* iecVar, bool toRegistry) {
    // Проверка выравнивания
    constexpr size_t required_alignment = RegisterTraits<T>::size;
    if (addr.offset() % required_alignment != 0) {
        throw std::runtime_error(
                "Unaligned access for " + addr.toString() +
                ". Type requires " + std::to_string(required_alignment) +
                "-byte alignment, but offset is " + std::to_string(addr.offset())
        );
    }

    // Проверка границ
    const auto& storage = _reg.getStorage(CAT);
    if (addr.offset() + RegisterTraits<T>::size > storage.size()) {
        throw std::out_of_range(
                "Register access out of range for " + addr.toString() +
                ". Storage size: " + std::to_string(storage.size())
        );
    }

    try {
        auto accessor = _reg.get<T, CAT>(addr.offset()); // Получаем accessor

        if (toRegistry) {
            // Запись из переменной в регистр
            accessor = *static_cast<T*>(iecVar); // Используем operator= accessor'а
            assert(accessor == *static_cast<T*>(iecVar));
        } else {
            // Чтение из регистра в переменную
            T registry_value = static_cast<T>(accessor); // Явное преобразование
            T& iec_value = *static_cast<T*>(iecVar);

            if (registry_value != iec_value) {
                std::cerr << "WARNING: Overwriting at " << addr.toString()
                          << "\n  Old: " << iec_value
                          << "\n  New: " << registry_value << "\n";
                iec_value = registry_value;
            }
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to access register " + addr.toString() + ": " + e.what());
    }
}

//template<Registry::Category CAT, typename T>
//void BindingManager::handleType(const Address& addr, void* iecVar, bool toRegistry) {
//    if (addr.offset() % RegisterTraits<T>::size != 0) {
//        throw std::runtime_error("Unaligned access for " + addr.toString());
//    }
//    auto accessor = _reg.get<T, CAT>(addr.offset());
//    if (toRegistry) {
//        accessor = *static_cast<T*>(iecVar);
//    } else {
//        *static_cast<T*>(iecVar) = static_cast<T>(accessor);
//    }
//}

template<Registry::Category CAT>
void BindingManager::processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.datatype()) {
        case Address::TYPE_BIT:    handleType<CAT, bool>    (addr, iecVar, toRegistry); break;
        case Address::TYPE_BYTE:   handleType<CAT, uint8_t> (addr, iecVar, toRegistry); break;
        case Address::TYPE_WORD:   handleType<CAT, uint16_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_DWORD:  handleType<CAT, uint32_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_LWORD:  handleType<CAT, uint64_t>(addr, iecVar, toRegistry); break;
        case Address::TYPE_REAL:   handleType<CAT, float>   (addr, iecVar, toRegistry); break;
        case Address::TYPE_LREAL:  handleType<CAT, double>  (addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown data type");
    }
}

void BindingManager::updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   processWithCategory<Registry::Category::INPUT>  (addr, iecVar, toRegistry); break;
        case Registry::Category::OUTPUT:  processWithCategory<Registry::Category::OUTPUT> (addr, iecVar, toRegistry); break;
        case Registry::Category::MEMORY:  processWithCategory<Registry::Category::MEMORY> (addr, iecVar, toRegistry); break;
        case Registry::Category::SPECIAL: processWithCategory<Registry::Category::SPECIAL>(addr, iecVar, toRegistry); break;
        default: throw std::runtime_error("Unknown register category");
    }
}

//void BindingManager::bind(const std::string& regNotation, void* iecVar) {
//    Address addr = Address::fromString(regNotation);
//    binds.emplace_back(addr, iecVar);
//}

void BindingManager::bind(const std::string& regNotation, void* iecVar) {
    Address addr = Address::fromString(regNotation);

    if (!addr.isAlignedFor(addr.datatype())) {
        size_t required_alignment = 1;
        const char* typeName = "unknown";

        switch(addr.datatype()) {
            case Address::TYPE_BIT:   required_alignment = RegisterTraits<bool>::size;     typeName = "BIT";   break;
            case Address::TYPE_BYTE:  required_alignment = RegisterTraits<uint8_t>::size;  typeName = "BYTE";  break;
            case Address::TYPE_WORD:  required_alignment = RegisterTraits<uint16_t>::size; typeName = "WORD";  break;
            case Address::TYPE_DWORD: required_alignment = RegisterTraits<uint32_t>::size; typeName = "DWORD"; break;
            case Address::TYPE_LWORD: required_alignment = RegisterTraits<uint64_t>::size; typeName = "LWORD"; break;
            case Address::TYPE_REAL:  required_alignment = RegisterTraits<float>::size;    typeName = "REAL";  break;
            case Address::TYPE_LREAL: required_alignment = RegisterTraits<double>::size;   typeName = "LREAL"; break;
            default:
                throw std::runtime_error("Unknown data type in binding");
        }

        throw std::runtime_error(
                "Unaligned binding for " + addr.toString() +
                " (type: " + typeName + "). " +
                "Required alignment: " + std::to_string(required_alignment) +
                ", but offset is " + std::to_string(addr.offset())
        );
    }

    // Проверка на то, что переменная имеет достаточное выравнивание
    size_t varAlignment = 0;
    switch(addr.datatype()) {
        case Address::TYPE_BIT:   varAlignment = alignof(bool);     break;
        case Address::TYPE_BYTE:  varAlignment = alignof(uint8_t);  break;
        case Address::TYPE_WORD:  varAlignment = alignof(uint16_t); break;
        case Address::TYPE_DWORD: varAlignment = alignof(uint32_t); break;
        case Address::TYPE_LWORD: varAlignment = alignof(uint64_t); break;
        case Address::TYPE_REAL:  varAlignment = alignof(float);    break;
        case Address::TYPE_LREAL: varAlignment = alignof(double);   break;
        default: break;
    }

    if (reinterpret_cast<uintptr_t>(iecVar) % varAlignment != 0) {
        throw std::runtime_error("Variable is not properly aligned for type");
    }

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
