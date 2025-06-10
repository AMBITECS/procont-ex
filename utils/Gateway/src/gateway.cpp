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

// ----------------------------------------------------------------------------
// Специализации шаблонной функции getGlobalProxy
// ----------------------------------------------------------------------------
template<> Registry::IX& getGlobalProxy<Registry::IX>() { return IX; }
template<> Registry::QX& getGlobalProxy<Registry::QX>() { return QX; }
template<> Registry::MX& getGlobalProxy<Registry::MX>() { return MX; }
template<> Registry::SX& getGlobalProxy<Registry::SX>() { return SX; }

// Для байтовых типов (B)
template<> Registry::IB& getGlobalProxy<Registry::IB>() { return IB; }
template<> Registry::QB& getGlobalProxy<Registry::QB>() { return QB; }
template<> Registry::MB& getGlobalProxy<Registry::MB>() { return MB; }
template<> Registry::SB& getGlobalProxy<Registry::SB>() { return SB; }

// Для словных типов (W)
template<> Registry::IW& getGlobalProxy<Registry::IW>() { return IW; }
template<> Registry::QW& getGlobalProxy<Registry::QW>() { return QW; }
template<> Registry::MW& getGlobalProxy<Registry::MW>() { return MW; }
template<> Registry::SW& getGlobalProxy<Registry::SW>() { return SW; }

// Для словных типов (D)
template<> Registry::ID& getGlobalProxy<Registry::ID>() { return ID; }
template<> Registry::QD& getGlobalProxy<Registry::QD>() { return QD; }
template<> Registry::MD& getGlobalProxy<Registry::MD>() { return MD; }
template<> Registry::SD& getGlobalProxy<Registry::SD>() { return SD; }

// Для словных типов (L)
template<> Registry::IL& getGlobalProxy<Registry::IL>() { return IL; }
template<> Registry::QL& getGlobalProxy<Registry::QL>() { return QL; }
template<> Registry::ML& getGlobalProxy<Registry::ML>() { return ML; }
template<> Registry::SL& getGlobalProxy<Registry::SL>() { return SL; }

// Для словных типов (R)
template<> Registry::IF& getGlobalProxy<Registry::IF>() { return IF; }
template<> Registry::QF& getGlobalProxy<Registry::QF>() { return QF; }
template<> Registry::MF& getGlobalProxy<Registry::MF>() { return MF; }
template<> Registry::SF& getGlobalProxy<Registry::SF>() { return SF; }

// Для словных типов (F)
template<> Registry::IE& getGlobalProxy<Registry::IE>() { return IE; }
template<> Registry::QE& getGlobalProxy<Registry::QE>() { return QE; }
template<> Registry::ME& getGlobalProxy<Registry::ME>() { return ME; }
template<> Registry::SE& getGlobalProxy<Registry::SE>() { return SE; }

//-----------------------------------------------------------------------------
