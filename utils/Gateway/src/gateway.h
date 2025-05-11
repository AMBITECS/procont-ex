//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Internal buffers for I/O and memory.
// These buffers are defined in the auto-generated glueVars.cpp file
//-----------------------------------------------------------------------------
#ifndef PRO_GATEWAY_H
#define PRO_GATEWAY_H

//#include "registry.h"
#include "variant.h"

#include "bitwise.h"
#include "iec_types.h"

#define BUFFER_MAXSIZE 65536;    // Standard PLC addressing space
#define BUFFER_SIZE    1024     // Current PLC registers size

// ----------------------------------------------------------------------------
// PLC Register Types
// ----------------------------------------------------------------------------
// Специализации для стандартных типов
//using VEC_BOOL  = BitwiseVector <IEC_BOOL*>;
using VEC_BYTE  = ObservableVector <IEC_BYTE*>;
using VEC_UINT  = ObservableVector <IEC_UINT*>;
using VEC_UDINT = ObservableVector <IEC_UDINT*>;
using VEC_ULINT = ObservableVector <IEC_ULINT*>;

//// ----------------------------------------------------------------------------
//// PLC Register Map
//// ----------------------------------------------------------------------------
//struct Registry {
//    VEC_BOOL    IX = VEC_BOOL(BUFFER_SIZE);     // Digital Inputs (%IX)
//    VEC_BOOL    QX = VEC_BOOL(BUFFER_SIZE);     // Digital Outputs (%QX)
//    VEC_BYTE    IB = VEC_BYTE(BUFFER_SIZE);     // Byte Inputs (%IB)
//    VEC_BYTE    QB = VEC_BYTE(BUFFER_SIZE);     // Byte Outputs (%QB)
//    VEC_UINT    IW = VEC_UINT(BUFFER_SIZE);     // Word Inputs (%IW)
//    VEC_UINT    QW = VEC_UINT(BUFFER_SIZE);     // Word Outputs (%QW)
//    VEC_UDINT   ID = VEC_UDINT(BUFFER_SIZE);    // Double Word Inputs (%ID)
//    VEC_UDINT   QD = VEC_UDINT(BUFFER_SIZE);    // Double Word Outputs (%QD)
//    VEC_ULINT   IL = VEC_ULINT(BUFFER_SIZE);    // Long Word Inputs (%IL)
//    VEC_ULINT   QL = VEC_ULINT(BUFFER_SIZE);    // Long Word Outputs (%QL)
//    VEC_UINT    MW = VEC_UINT(BUFFER_SIZE);     // Memory Words (%MW)
//    VEC_UDINT   MD = VEC_UDINT(BUFFER_SIZE);    // Memory Double Words (%MD)
//    VEC_ULINT   ML = VEC_ULINT(BUFFER_SIZE);    // Local Data (%ML)
//
//    Registry() = default;
//
//    // Initialize all registers with default values
//    void initialize() {
//        IX.resize(BUFFER_SIZE, 0);
//        QX.resize(BUFFER_SIZE, 0);
//        IB.resize(BUFFER_SIZE, 0);
//        QB.resize(BUFFER_SIZE, 0);
//        IW.resize(BUFFER_SIZE, 0);
//        QW.resize(BUFFER_SIZE, 0);
//        ID.resize(BUFFER_SIZE, 0);
//        QD.resize(BUFFER_SIZE, 0);
//        IL.resize(BUFFER_SIZE, 0);
//        QL.resize(BUFFER_SIZE, 0);
//        MW.resize(BUFFER_SIZE, 0);
//        MD.resize(BUFFER_SIZE, 0);
//        ML.resize(BUFFER_SIZE, 0);
//    }
//};
//
//// Global registry access
//Registry& reg();

//Booleans
extern IEC_BOOL *IX [BUFFER_SIZE][8];
extern IEC_BOOL *QX [BUFFER_SIZE][8];

//////Bytes
//extern IEC_BYTE *IB [BUFFER_SIZE];
//extern IEC_BYTE *QB [BUFFER_SIZE];
//
////Analog I/O
//extern IEC_UINT *IW [BUFFER_SIZE];
//extern IEC_UINT *QW [BUFFER_SIZE];
//
////32bit I/O
//extern IEC_UDINT *ID [BUFFER_SIZE];
//extern IEC_UDINT *QD [BUFFER_SIZE];
//
////64bit I/O
//extern IEC_ULINT *IL [BUFFER_SIZE];
//extern IEC_ULINT *QL [BUFFER_SIZE];
//
////Memory
//extern IEC_UINT  *MW [BUFFER_SIZE];
//extern IEC_UDINT *MD [BUFFER_SIZE];
//extern IEC_ULINT *ML [BUFFER_SIZE];

extern VEC_BYTE    IB;
extern VEC_BYTE    QB;
extern VEC_UINT    IW;
extern VEC_UINT    QW;
extern VEC_UDINT   ID;
extern VEC_UDINT   QD;
extern VEC_ULINT   IL;
extern VEC_ULINT   QL;
extern VEC_UINT    MW;
extern VEC_UDINT   MD;
extern VEC_ULINT   ML;

//lock for the buffers
extern pthread_mutex_t bufferLock;

///// parseAddressIEC
//bool parseAddressIEC(char *pSrc, char *code1, char *code2, int *index1, int *index2);
//
//struct ITEM_DEF {
//    char    addr[16]{};
//    VARIANT value;
//};
//
//struct ITEM_DATA {
//    ushort  quality;
//    ulong   time;
//    VARIANT value;
//};

#endif //PRO_GATEWAY_H
