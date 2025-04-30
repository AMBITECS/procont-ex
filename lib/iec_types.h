#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"

#ifndef IEC_TYPES_H
#define IEC_TYPES_H

#include <climits>
#include <cfloat>
#include <cstdint>

// ----------------------------------------------------------------------------
//  IEC Types defs
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// WARNING: When editing the definition of IEC_TIMESPEC, take note that
//          if the order of the two elements 'tv_sec' and 'tv_nsec' is changed,
//          then the macros __time_to_timespec() and __tod_to_timespec()
//          will need to be changed accordingly (iec_std_lib.h)
// ----------------------------------------------------------------------------
typedef uint32_t ts_time_t;
typedef struct {
    ts_time_t tv_sec;            // Seconds
    ts_time_t tv_nsec;           // Nanoseconds
} /* __attribute__((packed)) */ IEC_TIMESPEC;  // packed is gcc specific!

// ----------------------------------------------------------------------------
#ifndef STR_MAX_LEN
#define STR_MAX_LEN 126
#endif

#ifndef STR_LEN_TYPE
#define STR_LEN_TYPE int8_t
#endif

typedef IEC_TIMESPEC IEC_TIME;
typedef IEC_TIMESPEC IEC_DATE;
typedef IEC_TIMESPEC IEC_DT;
typedef IEC_TIMESPEC IEC_TOD;

#define __INIT_REAL     0
#define __INIT_LREAL    0
#define __INIT_SINT     0
#define __INIT_INT      0
#define __INIT_DINT     0
#define __INIT_LINT     0
#define __INIT_USINT    0
#define __INIT_UINT     0
#define __INIT_UDINT    0
#define __INIT_ULINT    0
#define __INIT_TIME     (TIME){0,0}
#define __INIT_BOOL     0
#define __INIT_BYTE     0
#define __INIT_WORD     0
#define __INIT_DWORD    0
#define __INIT_LWORD    0
#define __INIT_STRING   (STRING){0,""}
//#define __INIT_WSTRING

#define __INIT_DATE     (DATE){0,0}
#define __INIT_TOD      (TOD){0,0}
#define __INIT_DT       (DT){0,0}

typedef STR_LEN_TYPE    __strlen_t;
typedef struct {
    __strlen_t  len;
    uint8_t     body[STR_MAX_LEN];
}  IEC_STRING;

#endif /*IEC_TYPES_H*/

#pragma clang diagnostic pop
