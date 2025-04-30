//-----------------------------------------------------------------------------
// Copyright 2025 Ambitecs
//-----------------------------------------------------------------------------
// Internal buffers for I/O and memory.
// These buffers are defined in the auto-generated glueVars.cpp file
//-----------------------------------------------------------------------------
#ifndef PRO_GATEWAY_H
#define PRO_GATEWAY_H

#include "registry.h"
#include "VARIANT.h"

//Booleans
extern IEC_BOOL *bool_input [BUFFER_SIZE][8];
extern IEC_BOOL *bool_output[BUFFER_SIZE][8];

//Bytes
extern IEC_BYTE *byte_input [BUFFER_SIZE];
extern IEC_BYTE *byte_output[BUFFER_SIZE];

//Analog I/O
extern IEC_UINT *int_input [BUFFER_SIZE];
extern IEC_UINT *int_output[BUFFER_SIZE];

//32bit I/O
extern IEC_UDINT *dint_input [BUFFER_SIZE];
extern IEC_UDINT *dint_output[BUFFER_SIZE];

//64bit I/O
extern IEC_ULINT *lint_input [BUFFER_SIZE];
extern IEC_ULINT *lint_output[BUFFER_SIZE];

//Memory
extern IEC_UINT  *int_memory [BUFFER_SIZE];
extern IEC_UDINT *dint_memory[BUFFER_SIZE];
extern IEC_ULINT *lint_memory[BUFFER_SIZE];

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
