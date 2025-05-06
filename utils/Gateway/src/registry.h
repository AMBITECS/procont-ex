//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_REGISTRY_H
#define PROCONT_EX_REGISTRY_H

#include "bitwise.h"
#include "iec_types.h"

constexpr size_t BUFFER_MAXSIZE = 65536;    // Standard PLC addressing space
constexpr size_t BUFFER_SIZE    = 1024;     // Current PLC addressing size

// ----------------------------------------------------------------------------
// PLC Register Types
// ----------------------------------------------------------------------------
typedef BitwiseVector<IEC_BOOL>  VEC_BOOL;
typedef BitwiseVector<IEC_BYTE>  VEC_BYTE;
typedef BitwiseVector<IEC_UINT>  VEC_UINT;
typedef BitwiseVector<IEC_UDINT> VEC_UDINT;
typedef BitwiseVector<IEC_ULINT> VEC_ULINT;

// ----------------------------------------------------------------------------
// PLC Register Map
// ----------------------------------------------------------------------------
struct Registry {
    // Digital Inputs (%IX)
    VEC_BOOL    IX = VEC_BOOL(BUFFER_SIZE);

    // Digital Outputs (%QX)
    VEC_BOOL    QX = VEC_BOOL(BUFFER_SIZE);

    // Byte Inputs (%IB)
    VEC_BYTE    IB = VEC_BYTE(BUFFER_SIZE);

    // Byte Outputs (%QB)
    VEC_BYTE    QB = VEC_BYTE(BUFFER_SIZE);

    // Word Inputs (%IW)
    VEC_UINT    IW = VEC_UINT(BUFFER_SIZE);

    // Word Outputs (%QW)
    VEC_UINT    QW = VEC_UINT(BUFFER_SIZE);

    // Double Word Inputs (%ID)
    VEC_UDINT   ID = VEC_UDINT(BUFFER_SIZE);

    // Double Word Outputs (%QD)
    VEC_UDINT   QD = VEC_UDINT(BUFFER_SIZE);

    // Long Word Inputs (%IL)
    VEC_ULINT   IL = VEC_ULINT(BUFFER_SIZE);

    // Long Word Outputs (%QL)
    VEC_ULINT   QL = VEC_ULINT(BUFFER_SIZE);

    // Memory Words (%MW)
    VEC_UINT    MW = VEC_UINT(BUFFER_SIZE);

    // Memory Double Words (%MD)
    VEC_UDINT   MD = VEC_UDINT(BUFFER_SIZE);

    // Local Data (%ML)
    VEC_ULINT   ML = VEC_ULINT(BUFFER_SIZE);

    Registry() = default;

    // Initialize all registers with default values
    void initialize() {
        IX.resize(BUFFER_SIZE, 0);
        QX.resize(BUFFER_SIZE, 0);
        IB.resize(BUFFER_SIZE, 0);
        QB.resize(BUFFER_SIZE, 0);
        IW.resize(BUFFER_SIZE, 0);
        QW.resize(BUFFER_SIZE, 0);
        ID.resize(BUFFER_SIZE, 0);
        QD.resize(BUFFER_SIZE, 0);
        IL.resize(BUFFER_SIZE, 0);
        QL.resize(BUFFER_SIZE, 0);
        MW.resize(BUFFER_SIZE, 0);
        MD.resize(BUFFER_SIZE, 0);
        ML.resize(BUFFER_SIZE, 0);
    }
};

// Global registry access
Registry& reg();

#endif //PROCONT_EX_REGISTRY_H
