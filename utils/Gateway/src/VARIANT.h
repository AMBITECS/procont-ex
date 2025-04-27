//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PRO_VARIANT_H
#define PRO_VARIANT_H

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cctype>
#include <cassert>

//-----------------------------------------------------------------------------
// Define types
//-----------------------------------------------------------------------------
typedef bool       T_BOOL;
typedef __int8_t   T_SINT8;
typedef __int16_t  T_SINT16;
typedef __int32_t  T_SINT32;
typedef __int64_t  T_SINT64;
typedef __uint8_t  T_UINT8;
typedef __uint16_t T_UINT16;
typedef __uint32_t T_UINT32;
typedef __uint64_t T_UINT64;
typedef float      T_REAL32;
typedef double     T_REAL64;

//-----------------------------------------------------------------------------
// Variant type codes
//-----------------------------------------------------------------------------
enum  VAR_TYPE {
    VT_NULL    = 0x00,
    VT_BOOL    = 0x01,
    VT_SINT8   = 0x02,
    VT_SINT16  = 0x03,
    VT_SINT32  = 0x04,
    VT_SINT64  = 0x15,
    VT_UINT8   = 0x05,
    VT_UINT16  = 0x06,
    VT_UINT32  = 0x07,
    VT_UINT64  = 0x1B,
    VT_REAL32  = 0x08,
    VT_REAL64  = 0x12,
};

//-----------------------------------------------------------------------------
// Variant value union
//-----------------------------------------------------------------------------
union VAR_VALUE {
    T_BOOL    _bool;    // 0x01     bool
    T_SINT8   _sint8;   // 0x02     int8_t
    T_SINT16  _sint16;  // 0x03     int16_t
    T_SINT32  _sint32;  // 0x04     int32_t
    T_SINT64  _sint64;  // 0x15     int64_t
    T_UINT8   _uint8;   // 0x05     uint8_t
    T_UINT16  _uint16;  // 0x06     uint16_t
    T_UINT32  _uint32;  // 0x07     uint32_t
    T_UINT64  _uint64;  // 0x1B     uint64_t
    T_REAL32  _real32;  // 0x08     float
    T_REAL64  _real64;  // 0x12     double

    VAR_VALUE() = default;
    VAR_VALUE(const VAR_VALUE & src) = default;

    explicit VAR_VALUE(T_BOOL   v) { _bool   = v;}
    explicit VAR_VALUE(T_SINT8  v) { _sint8  = v;}
    explicit VAR_VALUE(T_SINT16 v) { _sint16 = v;}
    explicit VAR_VALUE(T_SINT32 v) { _sint32 = v;}
    explicit VAR_VALUE(T_SINT64 v) { _sint64 = v;}
    explicit VAR_VALUE(T_UINT8  v) { _uint8  = v;}
    explicit VAR_VALUE(T_UINT16 v) { _uint16 = v;}
    explicit VAR_VALUE(T_UINT32 v) { _uint32 = v;}
    explicit VAR_VALUE(T_UINT64 v) { _uint64 = v;}
    explicit VAR_VALUE(T_REAL32 v) { _real32 = v;}
    explicit VAR_VALUE(T_REAL64 v) { _real64 = v;}

    VAR_VALUE& operator= (const VAR_VALUE& val) {
        _uint64 = val._uint64;
        return *this;
    }
};

//-----------------------------------------------------------------------------
// Variant typed value struct
//-----------------------------------------------------------------------------
struct VARIANT {
    // Data
    VAR_TYPE  type{};
    VAR_VALUE val{};

    [[nodiscard]] bool isReal() const { return (type == VT_REAL32 || type == VT_REAL64); }

    // Constructors
    VARIANT(const VARIANT & src) = default;
    VARIANT(): type(VT_SINT16), val(VAR_VALUE{}) {}
    VARIANT(VAR_TYPE code, VAR_VALUE value): type(code), val(value) {}

    explicit VARIANT(T_BOOL   v): type(VT_BOOL  ), val(v) {}
    explicit VARIANT(T_SINT8  v): type(VT_SINT8 ), val(v) {}
    explicit VARIANT(T_SINT16 v): type(VT_SINT16), val(v) {}
    explicit VARIANT(T_SINT32 v): type(VT_SINT32), val(v) {}
    explicit VARIANT(T_SINT64 v): type(VT_SINT64), val(v) {}
    explicit VARIANT(T_UINT8  v): type(VT_UINT8 ), val(v) {}
    explicit VARIANT(T_UINT16 v): type(VT_UINT16), val(v) {}
    explicit VARIANT(T_UINT32 v): type(VT_UINT32), val(v) {}
    explicit VARIANT(T_UINT64 v): type(VT_UINT64), val(v) {}
    explicit VARIANT(T_REAL32 v): type(VT_REAL32), val(v) {}
    explicit VARIANT(T_REAL64 v): type(VT_REAL64), val(v) {}

    VARIANT& operator= (const VARIANT& var) = default;

    VARIANT(VAR_TYPE type, const void *value): type(type)
    {
        switch (type) {
            case VT_BOOL  : val = VAR_VALUE (* (T_BOOL   *) value); break;
            case VT_SINT8 : val = VAR_VALUE (* (T_SINT8  *) value); break;
            case VT_SINT16: val = VAR_VALUE (* (T_SINT16 *) value); break;
            case VT_SINT32: val = VAR_VALUE (* (T_SINT32 *) value); break;
            case VT_SINT64: val = VAR_VALUE (* (T_SINT64 *) value); break;
            case VT_UINT8 : val = VAR_VALUE (* (T_UINT8  *) value); break;
            case VT_UINT16: val = VAR_VALUE (* (T_UINT16 *) value); break;
            case VT_UINT32: val = VAR_VALUE (* (T_UINT32 *) value); break;
            case VT_UINT64: val = VAR_VALUE (* (T_UINT64 *) value); break;
            case VT_REAL32: val = VAR_VALUE (* (T_REAL32 *) value); break;
            case VT_REAL64: val = VAR_VALUE (* (T_REAL64 *) value); break;
            default: val = VAR_VALUE(0);
        }
    }

    // Getters
    [[nodiscard]] T_BOOL getBOOL() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool);
            case VT_SINT8 :  return (val._sint8 ) != 0;
            case VT_SINT16:  return (val._sint16) != 0;
            case VT_SINT32:  return (val._sint32) != 0;
            case VT_SINT64:  return (val._sint64) != 0;
            case VT_UINT8 :  return (val._uint8 ) != 0;
            case VT_UINT16:  return (val._uint16) != 0;
            case VT_UINT32:  return (val._uint32) != 0;
            case VT_UINT64:  return (val._uint64) != 0;
            case VT_REAL32:  return (val._real32) != 0;
            case VT_REAL64:  return (val._real64) != 0;
            default: return(false);
        }
    }

    [[nodiscard]] T_SINT8 getSINT8() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0 ;
            case VT_SINT8 :  return T_SINT8(val._sint8 );
            case VT_SINT16:  return T_SINT8(val._sint16);
            case VT_SINT32:  return T_SINT8(val._sint32);
            case VT_SINT64:  return T_SINT8(val._sint64);
            case VT_UINT8 :  return T_SINT8(val._uint8 );
            case VT_UINT16:  return T_SINT8(val._uint16);
            case VT_UINT32:  return T_SINT8(val._uint32);
            case VT_UINT64:  return T_SINT8(val._uint64);
            case VT_REAL32:  return T_SINT8(val._real32);
            case VT_REAL64:  return T_SINT8(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_SINT16 getSINT16() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_SINT16(val._sint8 );
            case VT_SINT16:  return T_SINT16(val._sint16);
            case VT_SINT32:  return T_SINT16(val._sint32);
            case VT_SINT64:  return T_SINT16(val._sint64);
            case VT_UINT8 :  return T_SINT16(val._uint8 );
            case VT_UINT16:  return T_SINT16(val._uint16);
            case VT_UINT32:  return T_SINT16(val._uint32);
            case VT_UINT64:  return T_SINT16(val._uint64);
            case VT_REAL32:  return T_SINT16(val._real32);
            case VT_REAL64:  return T_SINT16(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_SINT32 getSINT32() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_SINT32(val._sint8 );
            case VT_SINT16:  return T_SINT32(val._sint16);
            case VT_SINT32:  return T_SINT32(val._sint32);
            case VT_SINT64:  return T_SINT32(val._sint64);
            case VT_UINT8 :  return T_SINT32(val._uint8 );
            case VT_UINT16:  return T_SINT32(val._uint16);
            case VT_UINT32:  return T_SINT32(val._uint32);
            case VT_UINT64:  return T_SINT32(val._uint64);
            case VT_REAL32:  return T_SINT32(val._real32);
            case VT_REAL64:  return T_SINT32(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_SINT64 getSINT64() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_SINT64(val._sint8 );
            case VT_SINT16:  return T_SINT64(val._sint16);
            case VT_SINT32:  return T_SINT64(val._sint32);
            case VT_SINT64:  return T_SINT64(val._sint64);
            case VT_UINT8 :  return T_SINT64(val._uint8 );
            case VT_UINT16:  return T_SINT64(val._uint16);
            case VT_UINT32:  return T_SINT64(val._uint32);
            case VT_UINT64:  return T_SINT64(val._uint64);
            case VT_REAL32:  return T_SINT64(val._real32);
            case VT_REAL64:  return T_SINT64(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_UINT8 getUINT8() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0 ;
            case VT_SINT8 :  return T_UINT8(val._sint8 );
            case VT_SINT16:  return T_UINT8(val._sint16);
            case VT_SINT32:  return T_UINT8(val._sint32);
            case VT_SINT64:  return T_UINT8(val._sint64);
            case VT_UINT8 :  return T_UINT8(val._uint8 );
            case VT_UINT16:  return T_UINT8(val._uint16);
            case VT_UINT32:  return T_UINT8(val._uint32);
            case VT_UINT64:  return T_UINT8(val._uint64);
            case VT_REAL32:  return T_UINT8(val._real32);
            case VT_REAL64:  return T_UINT8(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_UINT16 getUINT16() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_UINT16(val._sint8 );
            case VT_SINT16:  return T_UINT16(val._sint16);
            case VT_SINT32:  return T_UINT16(val._sint32);
            case VT_SINT64:  return T_UINT16(val._sint64);
            case VT_UINT8 :  return T_UINT16(val._uint8 );
            case VT_UINT16:  return T_UINT16(val._uint16);
            case VT_UINT32:  return T_UINT16(val._uint32);
            case VT_UINT64:  return T_UINT16(val._uint64);
            case VT_REAL32:  return T_UINT16(val._real32);
            case VT_REAL64:  return T_UINT16(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_UINT32 getUINT32() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_UINT32(val._sint8 );
            case VT_SINT16:  return T_UINT32(val._sint16);
            case VT_SINT32:  return T_UINT32(val._sint32);
            case VT_SINT64:  return T_UINT32(val._sint64);
            case VT_UINT8 :  return T_UINT32(val._uint8 );
            case VT_UINT16:  return T_UINT32(val._uint16);
            case VT_UINT32:  return T_UINT32(val._uint32);
            case VT_UINT64:  return T_UINT32(val._uint64);
            case VT_REAL32:  return T_UINT32(val._real32);
            case VT_REAL64:  return T_UINT32(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_UINT64 getUINT64() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_UINT64(val._sint8 );
            case VT_SINT16:  return T_UINT64(val._sint16);
            case VT_SINT32:  return T_UINT64(val._sint32);
            case VT_SINT64:  return T_UINT64(val._sint64);
            case VT_UINT8 :  return T_UINT64(val._uint8 );
            case VT_UINT16:  return T_UINT64(val._uint16);
            case VT_UINT32:  return T_UINT64(val._uint32);
            case VT_UINT64:  return T_UINT64(val._uint64);
            case VT_REAL32:  return T_UINT64(val._real32);
            case VT_REAL64:  return T_UINT64(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_REAL32 getREAL32() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_REAL32(val._sint8 );
            case VT_SINT16:  return T_REAL32(val._sint16);
            case VT_SINT32:  return T_REAL32(val._sint32);
            case VT_SINT64:  return T_REAL32(val._sint64);
            case VT_UINT8 :  return T_REAL32(val._uint8 );
            case VT_UINT16:  return T_REAL32(val._uint16);
            case VT_UINT32:  return T_REAL32(val._uint32);
            case VT_UINT64:  return T_REAL32(val._uint64);
            case VT_REAL32:  return T_REAL32(val._real32);
            case VT_REAL64:  return T_REAL32(val._real64);
            default: return(0);
        }
    }

    [[nodiscard]] T_REAL64 getREAL64() const {
        switch (type) {
            case VT_BOOL  :  return (val._bool) ? 1 : 0  ;
            case VT_SINT8 :  return T_REAL64(val._sint8 );
            case VT_SINT16:  return T_REAL64(val._sint16);
            case VT_SINT32:  return T_REAL64(val._sint32);
            case VT_SINT64:  return T_REAL64(val._sint64);
            case VT_UINT8 :  return T_REAL64(val._uint8 );
            case VT_UINT16:  return T_REAL64(val._uint16);
            case VT_UINT32:  return T_REAL64(val._uint32);
            case VT_UINT64:  return T_REAL64(val._uint64);
            case VT_REAL32:  return T_REAL64(val._real32);
            case VT_REAL64:  return T_REAL64(val._real64);
            default: return(0);
        }
    }

    // Interpreters
    [[nodiscard]] VARIANT asBOOL  () const { return VARIANT(val._bool  ); }
    [[nodiscard]] VARIANT asSINT8 () const { return VARIANT(val._sint8 ); }
    [[nodiscard]] VARIANT asSINT16() const { return VARIANT(val._sint16); }
    [[nodiscard]] VARIANT asSINT32() const { return VARIANT(val._sint32); }
    [[nodiscard]] VARIANT asSINT64() const { return VARIANT(val._sint64); }
    [[nodiscard]] VARIANT asUINT8 () const { return VARIANT(val._uint8 ); }
    [[nodiscard]] VARIANT asUINT16() const { return VARIANT(val._uint16); }
    [[nodiscard]] VARIANT asUINT32() const { return VARIANT(val._uint32); }
    [[nodiscard]] VARIANT asUINT64() const { return VARIANT(val._uint64); }
    [[nodiscard]] VARIANT asREAL32() const { return VARIANT(val._real32); }
    [[nodiscard]] VARIANT asREAL64() const { return VARIANT(val._real64); }

    // Converters
    [[nodiscard]] VARIANT toBOOL  () const { return VARIANT(getBOOL()); }
    [[nodiscard]] VARIANT toSINT8 () const { return isReal()  ? asSINT8 () : VARIANT(getSINT8 ()); }
    [[nodiscard]] VARIANT toSINT16() const { return isReal()  ? asSINT16() : VARIANT(getSINT16()); }
    [[nodiscard]] VARIANT toSINT32() const { return isReal()  ? asSINT32() : VARIANT(getSINT32()); }
    [[nodiscard]] VARIANT toSINT64() const { return isReal()  ? asSINT64() : VARIANT(getSINT64()); }
    [[nodiscard]] VARIANT toUINT8 () const { return isReal()  ? asUINT8 () : VARIANT(getUINT8 ()); }
    [[nodiscard]] VARIANT toUINT16() const { return isReal()  ? asUINT16() : VARIANT(getUINT16()); }
    [[nodiscard]] VARIANT toUINT32() const { return isReal()  ? asUINT32() : VARIANT(getUINT32()); }
    [[nodiscard]] VARIANT toUINT64() const { return isReal()  ? asUINT64() : VARIANT(getUINT64()); }
    [[nodiscard]] VARIANT toREAL32() const { return !isReal() ? asREAL32() : VARIANT(getREAL32()); }
    [[nodiscard]] VARIANT toREAL64() const { return !isReal() ? asREAL64() : VARIANT(getREAL64()); }

    [[nodiscard]] VARIANT to(VAR_TYPE dst_type) const {
        switch (dst_type) {
            case VT_BOOL:    return toBOOL  ();
            case VT_SINT8:   return toSINT8 ();
            case VT_SINT16:  return toSINT16();
            case VT_SINT32:  return toSINT32();
            case VT_SINT64:  return toSINT64();
            case VT_UINT8:   return toUINT8 ();
            case VT_UINT16:  return toUINT16();
            case VT_UINT32:  return toUINT32();
            case VT_UINT64:  return toUINT64();
            case VT_REAL32:  return toREAL32();
            case VT_REAL64:  return toREAL64();
            default: return VARIANT(0);
        }
    }

    static VAR_TYPE typeOf(int code) { return (VAR_TYPE) code; }
};

#endif //PRO_VARIANT_H
