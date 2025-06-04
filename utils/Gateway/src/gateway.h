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
extern IEC_BOOL *IX [BUFFER_SIZE][8];
extern IEC_BOOL *QX [BUFFER_SIZE][8];

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
extern Registry::IX _IX;
extern Registry::QX _QX;
extern Registry::MX _MX;

extern Registry::IB _IB;
extern Registry::QB _QB;
extern Registry::MB _MB;

extern Registry::IW _IW;
extern Registry::QW _QW;
extern Registry::MW _MW;


//// ----------------------------------------------------------------------------
//// OLD Register Types
//// ----------------------------------------------------------------------------
//// Специализации для стандартных типов using VEC_BOOL  = BitwiseVector <IEC_BOOL*>;
//using VEC_BYTE  = ObservableVector <IEC_BYTE*>;
//using VEC_UINT  = ObservableVector <IEC_UINT*>;
//using VEC_UDINT = ObservableVector <IEC_UDINT*>;
//using VEC_ULINT = ObservableVector <IEC_ULINT*>;
//
//extern VEC_BYTE    IB;
//extern VEC_BYTE    QB;
//extern VEC_UINT    IW;
//extern VEC_UINT    QW;
//extern VEC_UDINT   ID;
//extern VEC_UDINT   QD;
//extern VEC_ULINT   IL;
//extern VEC_ULINT   QL;
//
//extern VEC_UINT    MW;
//extern VEC_UDINT   MD;
//extern VEC_ULINT   ML;
//
//// Объявления явного инстанцирования
//extern template class ObservableVector<IEC_BYTE*>;
//extern template class ObservableVector<IEC_UINT*>;
//extern template class ObservableVector<IEC_UDINT*>;
//extern template class ObservableVector<IEC_ULINT*>;

#endif //PRO_GATEWAY_H
