//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Internal buffers for I/O and memory.
// These buffers are defined in the auto-generated glueVars.cpp file
//-----------------------------------------------------------------------------
#ifndef PRO_GATEWAY_H
#define PRO_GATEWAY_H

#include "iec_types.h"
#include "variant.h"
#include "address.h"
#include "registry.h"
#include "binding.h"

#define BUFFER_MAXSIZE 65536;    // Standard PLC addressing space
constexpr unsigned short BUFFER_SIZE  =  1024;     // Current PLC registers size

//lock for the buffers
extern pthread_mutex_t bufferLock;

// ----------------------------------------------------------------------------
// OLD ARRAYS
// ----------------------------------------------------------------------------

//Booleans
//extern IEC_BOOL *_IX [BUFFER_SIZE][8];
//extern IEC_BOOL *_QX [BUFFER_SIZE][8];

//Bytes
extern IEC_BYTE *IB [BUFFER_SIZE];
extern IEC_BYTE *QB [BUFFER_SIZE];

//Analog I/O
extern IEC_UINT *IW [BUFFER_SIZE];
extern IEC_UINT *QW [BUFFER_SIZE];

//32bit I/O
extern IEC_UDINT *ID [BUFFER_SIZE];
extern IEC_UDINT *QD [BUFFER_SIZE];

//64bit I/O
extern IEC_ULINT *IL [BUFFER_SIZE];
extern IEC_ULINT *QL [BUFFER_SIZE];

//Memory
extern IEC_UINT  *MW [BUFFER_SIZE];
extern IEC_UDINT *MD [BUFFER_SIZE];
extern IEC_ULINT *ML [BUFFER_SIZE];

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
// Объявляем глобальные экземпляры прокси-объектов
extern Registry::IX IX;
extern Registry::QX QX;

extern Registry::IB __IB;
extern Registry::QB __QB;

extern Registry::IW __IW;
extern Registry::QW __QW;

extern Registry::ID __ID;
extern Registry::QD __QD;

extern Registry::IL __IL;
extern Registry::QL __QL;

extern Registry::MX __MX;
extern Registry::MB __MB;
extern Registry::MW __MW;
extern Registry::MD __MD;
extern Registry::ML __ML;

#endif //PRO_GATEWAY_H
