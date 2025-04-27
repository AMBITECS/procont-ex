//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PRO_GATEWAY_H
#define PRO_GATEWAY_H

#include "VARIANT.h"

// Internal buffers for I/O and memory.
// These buffers are defined in the auto-generated glueVars.cpp file
#define BUFFER_SIZE		1024

/*********************/
/*  IEC Types defs   */
/*********************/
typedef __uint8_t   IEC_BOOL;

typedef __int8_t    IEC_SINT;
typedef __int16_t   IEC_INT;
typedef __int32_t   IEC_DINT;
typedef __int64_t   IEC_LINT;

typedef __uint8_t   IEC_USINT;
typedef __uint16_t  IEC_UINT;
typedef __uint32_t  IEC_UDINT;
typedef __uint64_t  IEC_ULINT;

typedef __uint8_t   IEC_BYTE;
typedef __uint16_t  IEC_WORD;
typedef __uint32_t  IEC_DWORD;
typedef __uint64_t  IEC_LWORD;

typedef float       IEC_REAL;
typedef double      IEC_LREAL;

//Booleans
extern IEC_BOOL *bool_input[BUFFER_SIZE][8];
extern IEC_BOOL *bool_output[BUFFER_SIZE][8];

//Bytes
extern IEC_BYTE *byte_input[BUFFER_SIZE];
extern IEC_BYTE *byte_output[BUFFER_SIZE];

//Analog I/O
extern IEC_UINT *int_input[BUFFER_SIZE];
extern IEC_UINT *int_output[BUFFER_SIZE];

//32bit I/O
extern IEC_UDINT *dint_input[BUFFER_SIZE];
extern IEC_UDINT *dint_output[BUFFER_SIZE];

//64bit I/O
extern IEC_ULINT *lint_input[BUFFER_SIZE];
extern IEC_ULINT *lint_output[BUFFER_SIZE];

//Memory
extern IEC_UINT  *int_memory[BUFFER_SIZE];
extern IEC_UDINT *dint_memory[BUFFER_SIZE];
extern IEC_ULINT *lint_memory[BUFFER_SIZE];

//Special Functions
extern IEC_ULINT *special_functions[BUFFER_SIZE];

//lock for the buffers
extern pthread_mutex_t bufferLock;

/// parseAddressIEC
bool parseAddressIEC(char *pSrc, char *code1, char *code2, int *index1, int *index2);

struct ITEM_DEF {
    char    addr[16]{};
    VARIANT value;
};

struct ITEM_DATA {
    ushort  quality;
    ulong   time;
    VARIANT value;
};



#endif //PRO_GATEWAY_H
