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

////Bytes
//extern IEC_BYTE *_IB [BUFFER_SIZE];
//extern IEC_BYTE *_QB [BUFFER_SIZE];
//
////Analog I/O
//extern IEC_UINT *_IW [BUFFER_SIZE];
//extern IEC_UINT *_QW [BUFFER_SIZE];
//
////32bit I/O
//extern IEC_UDINT *_ID [BUFFER_SIZE];
//extern IEC_UDINT *_QD [BUFFER_SIZE];
//
////64bit I/O
//extern IEC_ULINT *_IL [BUFFER_SIZE];
//extern IEC_ULINT *_QL [BUFFER_SIZE];

////Memory
//extern IEC_UINT  *_MW [BUFFER_SIZE];
//extern IEC_UDINT *_MD [BUFFER_SIZE];
//extern IEC_ULINT *_ML [BUFFER_SIZE];

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
// Объявляем глобальные экземпляры прокси-объектов
extern Registry::IX IX;
extern Registry::QX QX;

extern Registry::IB IB;
extern Registry::QB QB;

extern Registry::IW IW;
extern Registry::QW QW;

extern Registry::ID ID;
extern Registry::QD QD;

extern Registry::IL IL;
extern Registry::QL QL;

extern Registry::MX MX;
extern Registry::MB MB;
extern Registry::MW MW;
extern Registry::MD MD;
extern Registry::ML ML;

#endif //PRO_GATEWAY_H
