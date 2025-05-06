//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_REGISTRY_H
#define PROCONT_EX_REGISTRY_H

#include "vector.h"
#include "iec_types.h"

#define BUFFER_SIZE		1024

//typedef std::array<unsigned char, 8> BITS8;

typedef RangeObservableVector<IEC_ULINT>   VEC_BOOL;
typedef RangeObservableVector<IEC_BYTE>    VEC_BYTE;
typedef RangeObservableVector<IEC_UINT>    VEC_UINT;
typedef RangeObservableVector<IEC_UDINT>   VEC_UDINT;
typedef RangeObservableVector<IEC_ULINT>   VEC_ULINT;

struct Registry {
    //Booleans
    VEC_BOOL    IX = VEC_BOOL(BUFFER_SIZE);
    VEC_BOOL    QX = VEC_BOOL(BUFFER_SIZE);

    //Bytes
    VEC_BYTE    IB = VEC_BYTE(BUFFER_SIZE);
    VEC_BYTE    QB = VEC_BYTE(BUFFER_SIZE);

    //Analog I/O
    VEC_UINT    IW = VEC_UINT(BUFFER_SIZE);
    VEC_UINT    QW = VEC_UINT(BUFFER_SIZE);

    //32bit I/O
    VEC_UDINT   ID = VEC_UDINT(BUFFER_SIZE);
    VEC_UDINT   QD = VEC_UDINT(BUFFER_SIZE);

    //64bit I/O
    VEC_ULINT   IL = VEC_ULINT(BUFFER_SIZE);
    VEC_ULINT   QL = VEC_ULINT(BUFFER_SIZE);

    //Memory
    VEC_UINT    MW = VEC_UINT (BUFFER_SIZE);
    VEC_UDINT   MD = VEC_UDINT(BUFFER_SIZE);
    VEC_ULINT   LD = VEC_ULINT(BUFFER_SIZE);

    Registry() = default;
};

//extern Registry reg;
const Registry& reg();

#endif //PROCONT_EX_REGISTRY_H
