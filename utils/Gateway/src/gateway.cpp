//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#define GATEWAY_EXPORTS
#include "gateway.h"

#include <cstdlib>
#include <cctype>

pthread_mutex_t bufferLock; //mutex for the internal buffers

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
