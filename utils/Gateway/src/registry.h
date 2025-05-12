//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "iec_types.h"
#include "bitwise.h"

constexpr unsigned short BUFFER_SIZE =  1024;     // Current PLC registers size

// ----------------------------------------------------------------------------
// PLC Register Types
// ----------------------------------------------------------------------------
//using VEC_BOOL  = BitwiseVector<IEC_BOOL*>;
using VEC_BYTE  = ObservableVector<IEC_BYTE*>;
using VEC_UINT  = ObservableVector<IEC_UINT*>;
using VEC_UDINT = ObservableVector<IEC_UDINT*>;
using VEC_ULINT = ObservableVector<IEC_ULINT*>;

class Registry {
public:
    // Digital Inputs/Outputs
//    static VEC_BOOL&  IX() { static VEC_BOOL instance(BUFFER_SIZE); return instance; }
//    static VEC_BOOL&  QX() { static VEC_BOOL instance(BUFFER_SIZE); return instance; }

    // Byte Inputs/Outputs
    static VEC_BYTE&  IB() { static VEC_BYTE  instance(BUFFER_SIZE); return instance; }
    static VEC_BYTE&  QB() { static VEC_BYTE  instance(BUFFER_SIZE); return instance; }

    // Word Inputs/Outputs
    static VEC_UINT&  IW() { static VEC_UINT  instance(BUFFER_SIZE); return instance; }
    static VEC_UINT&  QW() { static VEC_UINT  instance(BUFFER_SIZE); return instance; }

    // Double Word Inputs/Outputs
    static VEC_UDINT& ID() { static VEC_UDINT instance(BUFFER_SIZE); return instance; }
    static VEC_UDINT& QD() { static VEC_UDINT instance(BUFFER_SIZE); return instance; }

    // Long Word Inputs/Outputs
    static VEC_ULINT& IL() { static VEC_ULINT instance(BUFFER_SIZE); return instance; }
    static VEC_ULINT& QL() { static VEC_ULINT instance(BUFFER_SIZE); return instance; }

    // Memory Registers
    static VEC_UINT&  MW() { static VEC_UINT  instance(BUFFER_SIZE); return instance; }
    static VEC_UDINT& MD() { static VEC_UDINT instance(BUFFER_SIZE); return instance; }
    static VEC_ULINT& ML() { static VEC_ULINT instance(BUFFER_SIZE); return instance; }

    Registry() = delete;
    ~Registry() = delete;
};

// ----------------------------------------------------------------------------
// Shortcut Accessors (optional)
// ----------------------------------------------------------------------------
//inline VEC_BOOL & IX() { return Registry::IX(); }
//inline VEC_BOOL & QX() { return Registry::QX(); }
//inline VEC_BYTE & IB() { return Registry::IB(); }
//inline VEC_BYTE & QB() { return Registry::QB(); }
//inline VEC_UINT & IW() { return Registry::IW(); }
//inline VEC_UINT & QW() { return Registry::QW(); }
//inline VEC_UDINT& ID() { return Registry::ID(); }
//inline VEC_UDINT& QD() { return Registry::QD(); }
//inline VEC_ULINT& IL() { return Registry::IL(); }
//inline VEC_ULINT& QL() { return Registry::QL(); }
//inline VEC_UINT & MW() { return Registry::MW(); }
//inline VEC_UDINT& MD() { return Registry::MD(); }
//inline VEC_ULINT& ML() { return Registry::ML(); }

// ----------------------------------------------------------------------------
// Глобальные ссылки на регистры
// ----------------------------------------------------------------------------
//extern VEC_BOOL& IX;
//extern VEC_BOOL& QX;
extern VEC_BYTE&  IB;
extern VEC_BYTE&  QB;
extern VEC_UINT&  IW;
extern VEC_UINT&  QW;
extern VEC_UDINT& ID;
extern VEC_UDINT& QD;
extern VEC_ULINT& IL;
extern VEC_ULINT& QL;
extern VEC_UINT&  MW;
extern VEC_UDINT& MD;
extern VEC_ULINT& ML;
