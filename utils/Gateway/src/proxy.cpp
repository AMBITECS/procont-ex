//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Proxy-objects for Registry memory.
//-----------------------------------------------------------------------------
#include "proxy.h"
#include <mutex>

std::mutex bufferLock;

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

// Реализация методов (без шаблонов!)
uint64_t getProxyValue(const Address& addr) {
    return getGlobalRegistry().getRawValue(addr); // Категория берётся из addr.category()
}

void setProxyValue(const Address& addr, uint64_t value) {
    getGlobalRegistry().setRawValue(addr, value); // Категория из addr.category()
}

bool isProxyChanged(const Address& addr) {
    return getGlobalRegistry().isChanged(addr); // Категория из addr.category()
}
