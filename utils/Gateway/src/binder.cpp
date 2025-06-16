#include "binder.h"
#include "proxy.h"
#include "reg_server.h"

std::unique_ptr<Binder> Binder::_instance;

Binder& Binder::instance() {
    if (!_instance) {
        _instance = std::unique_ptr<Binder>(new Binder());
    }
    return *_instance;
}

// ----------------------------------------------------------------------------
Binder::Binder(): _regClient(RegServer::instance().createClient("Binder")) {}

void Binder::bind(const std::string& regNotation, void* iecVar) {
    Address addr = Address::of(regNotation);
    binds.emplace_back(Binding{addr, iecVar});
}

void Binder::updateToIec() {
    for (auto& [addr, var] : binds) {
        uint64_t rawValue = _regClient->read(addr);

        switch (addr.type()) {
            case Address::TYPE_BIT:    *static_cast<bool*>(var)   = rawValue != 0; break;
            case Address::TYPE_BYTE:   *static_cast<uint8_t*>(var)  = static_cast<uint8_t>(rawValue); break;
            case Address::TYPE_WORD:   *static_cast<uint16_t*>(var) = static_cast<uint16_t>(rawValue); break;
            case Address::TYPE_DWORD:  *static_cast<uint32_t*>(var) = static_cast<uint32_t>(rawValue); break;
            case Address::TYPE_LWORD:  *static_cast<uint64_t*>(var) = rawValue; break;
            case Address::TYPE_REAL:   memcpy(var, &rawValue, sizeof(float)); break;
            case Address::TYPE_LREAL:  memcpy(var, &rawValue, sizeof(double)); break;
            default: throw std::runtime_error("Unsupported type");
        }
    }
}

void Binder::updateFromIec() {
    for (auto& [addr, var] : binds) {
        uint64_t rawValue = 0;

        switch (addr.type()) {
            case Address::TYPE_BIT:    rawValue = *static_cast<bool*>(var); break;
            case Address::TYPE_BYTE:   rawValue = *static_cast<uint8_t*>(var); break;
            case Address::TYPE_WORD:   rawValue = *static_cast<uint16_t*>(var); break;
            case Address::TYPE_DWORD:  rawValue = *static_cast<uint32_t*>(var); break;
            case Address::TYPE_LWORD:  rawValue = *static_cast<uint64_t*>(var); break;
            case Address::TYPE_REAL:   memcpy(&rawValue, var, sizeof(float)); break;
            case Address::TYPE_LREAL:  memcpy(&rawValue, var, sizeof(double)); break;
            default: throw std::runtime_error("Unsupported type");
        }

        _regClient->write(addr, rawValue);
    }
}
