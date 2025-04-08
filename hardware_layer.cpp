//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cctype>
#include <cassert>
#include "ladder.h"

#include "OD.h"
#include "CIA405.h"
#include "CO_error.h"
#include "CO_epoll_interface.h"
#include "CO_storageLinux.h"

//-----------------------------------------------------------------------------
// Define types
//-----------------------------------------------------------------------------
typedef bool        T_BOOL;
typedef int8_t      T_SINT8;
typedef int16_t     T_SINT16;
typedef int32_t     T_SINT32;
typedef int64_t     T_SINT64;
typedef uint8_t     T_UINT8;
typedef uint16_t    T_UINT16;
typedef uint32_t    T_UINT32;
typedef uint64_t    T_UINT64;
typedef float       T_REAL32;
typedef double      T_REAL64;

//-----------------------------------------------------------------------------
// Variant type codes
//-----------------------------------------------------------------------------
typedef enum {
    E_BOOL    = 0x01,
    E_SINT8   = 0x02,
    E_SINT16  = 0x03,
    E_SINT32  = 0x04,
    E_SINT64  = 0x15,
    E_UINT8   = 0x05,
    E_UINT16  = 0x06,
    E_UINT32  = 0x07,
    E_UINT64  = 0x1B,
    E_REAL32  = 0x08,
    E_REAL64  = 0x12,
} VAR_TYPE;

//-----------------------------------------------------------------------------
// Variant value union
//-----------------------------------------------------------------------------
typedef union VAR_VALUE_t {
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

    VAR_VALUE_t() = default;
    VAR_VALUE_t(const VAR_VALUE_t & src) = default;

    explicit VAR_VALUE_t(T_BOOL   v) { _bool   = v;}
    explicit VAR_VALUE_t(T_SINT8  v) { _sint8  = v;}
    explicit VAR_VALUE_t(T_SINT16 v) { _sint16 = v;}
    explicit VAR_VALUE_t(T_SINT32 v) { _sint32 = v;}
    explicit VAR_VALUE_t(T_SINT64 v) { _sint64 = v;}
    explicit VAR_VALUE_t(T_UINT8  v) { _uint8  = v;}
    explicit VAR_VALUE_t(T_UINT16 v) { _uint16 = v;}
    explicit VAR_VALUE_t(T_UINT32 v) { _uint32 = v;}
    explicit VAR_VALUE_t(T_UINT64 v) { _uint64 = v;}
    explicit VAR_VALUE_t(T_REAL32 v) { _real32 = v;}
    explicit VAR_VALUE_t(T_REAL64 v) { _real64 = v;}

    VAR_VALUE_t(VAR_TYPE code, const void *value)
    {
        switch (code) {
            case E_BOOL  : _bool     = * (T_BOOL   *) value; break;
            case E_SINT8 : _sint8    = * (T_SINT8  *) value; break;
            case E_SINT16: _sint16   = * (T_SINT16 *) value; break;
            case E_SINT32: _sint32   = * (T_SINT32 *) value; break;
            case E_SINT64: _sint64   = * (T_SINT64 *) value; break;
            case E_UINT8 : _uint8    = * (T_UINT8  *) value; break;
            case E_UINT16: _uint16   = * (T_UINT16 *) value; break;
            case E_UINT32: _uint32   = * (T_UINT32 *) value; break;
            case E_UINT64: _uint64   = * (T_UINT64 *) value; break;
            case E_REAL32: _real32   = * (T_REAL32 *) value; break;
            case E_REAL64: _real64   = * (T_REAL64 *) value; break;
        }
    }

    VAR_VALUE_t& operator= (const VAR_VALUE_t& val) { _uint64 = val._uint64; return *this; }

} VAR_VALUE;

//-----------------------------------------------------------------------------
// Variant typed value struct
//-----------------------------------------------------------------------------
struct VARIANT {
    // Data
    VAR_TYPE  type{};
    VAR_VALUE val{};

    [[nodiscard]] bool isReal() const { return (type==E_REAL32 || type==E_REAL64); }

    // Constructors
    VARIANT(const VARIANT & src) = default;
    VARIANT(): type(E_SINT16), val(VAR_VALUE{}) {}
    VARIANT(VAR_TYPE code, VAR_VALUE value): type(code), val(value) {}

    explicit VARIANT(T_BOOL   v): type(E_BOOL  ), val(v) {}
    explicit VARIANT(T_SINT8  v): type(E_SINT8 ), val(v) {}
    explicit VARIANT(T_SINT16 v): type(E_SINT16), val(v) {}
    explicit VARIANT(T_SINT32 v): type(E_SINT32), val(v) {}
    explicit VARIANT(T_SINT64 v): type(E_SINT64), val(v) {}
    explicit VARIANT(T_UINT8  v): type(E_UINT8 ), val(v) {}
    explicit VARIANT(T_UINT16 v): type(E_UINT16), val(v) {}
    explicit VARIANT(T_UINT32 v): type(E_UINT32), val(v) {}
    explicit VARIANT(T_UINT64 v): type(E_UINT64), val(v) {}
    explicit VARIANT(T_REAL32 v): type(E_REAL32), val(v) {}
    explicit VARIANT(T_REAL64 v): type(E_REAL64), val(v) {}

    VARIANT(VAR_TYPE code, const void *value): type(code), val(VAR_VALUE_t(code, value)) {}

    VARIANT& operator= (const VARIANT& var) {
        this->type = var.type;
        this->val  = var.val;
        return *this;
    }

    // Getters
    [[nodiscard]] T_BOOL getBOOL() const {
        switch (type) {
            case E_BOOL  :  return (val._bool)       ;
            case E_SINT8 :  return (val._sint8 ) != 0;
            case E_SINT16:  return (val._sint16) != 0;
            case E_SINT32:  return (val._sint32) != 0;
            case E_SINT64:  return (val._sint64) != 0;
            case E_UINT8 :  return (val._uint8 ) != 0;
            case E_UINT16:  return (val._uint16) != 0;
            case E_UINT32:  return (val._uint32) != 0;
            case E_UINT64:  return (val._uint64) != 0;
            case E_REAL32:  return (val._real32) != 0;
            case E_REAL64:  return (val._real64) != 0;
        }
    }

    [[nodiscard]] T_SINT8 getSINT8() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0 ;
            case E_SINT8 :  return T_SINT8(val._sint8 );
            case E_SINT16:  return T_SINT8(val._sint16);
            case E_SINT32:  return T_SINT8(val._sint32);
            case E_SINT64:  return T_SINT8(val._sint64);
            case E_UINT8 :  return T_SINT8(val._uint8 );
            case E_UINT16:  return T_SINT8(val._uint16);
            case E_UINT32:  return T_SINT8(val._uint32);
            case E_UINT64:  return T_SINT8(val._uint64);
            case E_REAL32:  return T_SINT8(val._real32);
            case E_REAL64:  return T_SINT8(val._real64);
        }
    }
    
    [[nodiscard]] T_SINT16 getSINT16() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_SINT16(val._sint8 );
            case E_SINT16:  return T_SINT16(val._sint16);
            case E_SINT32:  return T_SINT16(val._sint32);
            case E_SINT64:  return T_SINT16(val._sint64);
            case E_UINT8 :  return T_SINT16(val._uint8 );
            case E_UINT16:  return T_SINT16(val._uint16);
            case E_UINT32:  return T_SINT16(val._uint32);
            case E_UINT64:  return T_SINT16(val._uint64);
            case E_REAL32:  return T_SINT16(val._real32);
            case E_REAL64:  return T_SINT16(val._real64);
        }
    }

    [[nodiscard]] T_SINT32 getSINT32() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_SINT32(val._sint8 );
            case E_SINT16:  return T_SINT32(val._sint16);
            case E_SINT32:  return T_SINT32(val._sint32);
            case E_SINT64:  return T_SINT32(val._sint64);
            case E_UINT8 :  return T_SINT32(val._uint8 );
            case E_UINT16:  return T_SINT32(val._uint16);
            case E_UINT32:  return T_SINT32(val._uint32);
            case E_UINT64:  return T_SINT32(val._uint64);
            case E_REAL32:  return T_SINT32(val._real32);
            case E_REAL64:  return T_SINT32(val._real64);
        }
    }

    [[nodiscard]] T_SINT64 getSINT64() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_SINT64(val._sint8 );
            case E_SINT16:  return T_SINT64(val._sint16);
            case E_SINT32:  return T_SINT64(val._sint32);
            case E_SINT64:  return T_SINT64(val._sint64);
            case E_UINT8 :  return T_SINT64(val._uint8 );
            case E_UINT16:  return T_SINT64(val._uint16);
            case E_UINT32:  return T_SINT64(val._uint32);
            case E_UINT64:  return T_SINT64(val._uint64);
            case E_REAL32:  return T_SINT64(val._real32);
            case E_REAL64:  return T_SINT64(val._real64);
        }
    }

    [[nodiscard]] T_UINT8 getUINT8() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0 ;
            case E_SINT8 :  return T_UINT8(val._sint8 );
            case E_SINT16:  return T_UINT8(val._sint16);
            case E_SINT32:  return T_UINT8(val._sint32);
            case E_SINT64:  return T_UINT8(val._sint64);
            case E_UINT8 :  return T_UINT8(val._uint8 );
            case E_UINT16:  return T_UINT8(val._uint16);
            case E_UINT32:  return T_UINT8(val._uint32);
            case E_UINT64:  return T_UINT8(val._uint64);
            case E_REAL32:  return T_UINT8(val._real32);
            case E_REAL64:  return T_UINT8(val._real64);
        }
    }

    [[nodiscard]] T_UINT16 getUINT16() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_UINT16(val._sint8 );
            case E_SINT16:  return T_UINT16(val._sint16);
            case E_SINT32:  return T_UINT16(val._sint32);
            case E_SINT64:  return T_UINT16(val._sint64);
            case E_UINT8 :  return T_UINT16(val._uint8 );
            case E_UINT16:  return T_UINT16(val._uint16);
            case E_UINT32:  return T_UINT16(val._uint32);
            case E_UINT64:  return T_UINT16(val._uint64);
            case E_REAL32:  return T_UINT16(val._real32);
            case E_REAL64:  return T_UINT16(val._real64);
        }
    }

    [[nodiscard]] T_UINT32 getUINT32() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_UINT32(val._sint8 );
            case E_SINT16:  return T_UINT32(val._sint16);
            case E_SINT32:  return T_UINT32(val._sint32);
            case E_SINT64:  return T_UINT32(val._sint64);
            case E_UINT8 :  return T_UINT32(val._uint8 );
            case E_UINT16:  return T_UINT32(val._uint16);
            case E_UINT32:  return T_UINT32(val._uint32);
            case E_UINT64:  return T_UINT32(val._uint64);
            case E_REAL32:  return T_UINT32(val._real32);
            case E_REAL64:  return T_UINT32(val._real64);
        }
    }

    [[nodiscard]] T_UINT64 getUINT64() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_UINT64(val._sint8 );
            case E_SINT16:  return T_UINT64(val._sint16);
            case E_SINT32:  return T_UINT64(val._sint32);
            case E_SINT64:  return T_UINT64(val._sint64);
            case E_UINT8 :  return T_UINT64(val._uint8 );
            case E_UINT16:  return T_UINT64(val._uint16);
            case E_UINT32:  return T_UINT64(val._uint32);
            case E_UINT64:  return T_UINT64(val._uint64);
            case E_REAL32:  return T_UINT64(val._real32);
            case E_REAL64:  return T_UINT64(val._real64);
        }
    }

    [[nodiscard]] T_REAL32 getREAL32() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_REAL32(val._sint8 );
            case E_SINT16:  return T_REAL32(val._sint16);
            case E_SINT32:  return T_REAL32(val._sint32);
            case E_SINT64:  return T_REAL32(val._sint64);
            case E_UINT8 :  return T_REAL32(val._uint8 );
            case E_UINT16:  return T_REAL32(val._uint16);
            case E_UINT32:  return T_REAL32(val._uint32);
            case E_UINT64:  return T_REAL32(val._uint64);
            case E_REAL32:  return T_REAL32(val._real32);
            case E_REAL64:  return T_REAL32(val._real64);
        }
    }

    [[nodiscard]] T_REAL64 getREAL64() const {
        switch (type) {
            case E_BOOL  :  return (val._bool) ? 1 : 0  ;
            case E_SINT8 :  return T_REAL64(val._sint8 );
            case E_SINT16:  return T_REAL64(val._sint16);
            case E_SINT32:  return T_REAL64(val._sint32);
            case E_SINT64:  return T_REAL64(val._sint64);
            case E_UINT8 :  return T_REAL64(val._uint8 );
            case E_UINT16:  return T_REAL64(val._uint16);
            case E_UINT32:  return T_REAL64(val._uint32);
            case E_UINT64:  return T_REAL64(val._uint64);
            case E_REAL32:  return T_REAL64(val._real32);
            case E_REAL64:  return T_REAL64(val._real64);
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
            case E_BOOL:    return toBOOL  ();
            case E_SINT8:   return toSINT8 ();
            case E_SINT16:  return toSINT16();
            case E_SINT32:  return toSINT32();
            case E_SINT64:  return toSINT64();
            case E_UINT8:   return toUINT8 ();
            case E_UINT16:  return toUINT16();
            case E_UINT32:  return toUINT32();
            case E_UINT64:  return toUINT64();
            case E_REAL32:  return toREAL32();
            case E_REAL64:  return toREAL64();
        }
    }

    static VAR_TYPE typeFrom(int code) { return (VAR_TYPE) code; }

//    static VARIANT convert(const void *val, VAR_TYPE src_type, VAR_TYPE dst_type) {
//        return VARIANT(src_type, val).to(dst_type);
//    }
//
//    typedef union convert_t {
//        T_UINT32 uint32; T_REAL32 real32;
//        T_UINT64 uint64; T_REAL64 real64;
//
//        explicit convert_t(T_UINT32 x) {uint32 = x;}
//        explicit convert_t(T_UINT64 x) {uint64 = x;}
//        explicit convert_t(T_REAL32 x) {real32 = x;}
//        explicit convert_t(T_REAL64 x) {real64 = x;}
//    } CONVERT;
//
//    static T_REAL32 INT2REAL32(T_UINT32 src) { return CONVERT{src}.real32; }
//    static T_REAL64 INT2REAL64(T_UINT64 src) { return CONVERT{src}.real64; }
//
//    static T_UINT32 REAL2INT32(T_REAL32 src) { return CONVERT{src}.uint32; }
//    static T_UINT64 REAL2INT64(T_REAL64 src) { return CONVERT{src}.uint64; }

};

//-----------------------------------------------------------------------------
bool parseReg(char *pSrc, char *code1, char *code2, int *index1, int *index2) {
    int i=0;
    bool bOK  = false;
    (*code1)  = (*code1)  = 0;
    (*index1) = (*index2) = 0;
    char buffer[8] = {};

    if (pSrc!=nullptr && (*pSrc++)=='%')
    {
        // Считываем код регистра
        for (i = 0; isalpha(*pSrc) && *pSrc!='\0' && i < 2; i++) buffer[i] = *pSrc++;

        // Должно быть ровно два символа
        if (i == 2 && *pSrc!='\0') {
            (*code1) = buffer[0];
            (*code2) = buffer[1];

            // Первый символ - обозначает вход|выход|память
            if ((*code1) == 'I' || (*code1) == 'Q' || (*code1) == 'M') {

                // Второй символ - обозначает тип регистра
                if ((*code2) == 'X' || (*code2) == 'B' || (*code2) == 'W' || (*code2) == 'D' || (*code2) == 'L')
                {
                    // считываем индекс pos1
                    for (i = 0; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
                    if (i > 0) {
                        buffer[i] = '\0';
                        *index1 = atoi(buffer);
                    }

                    // считываем индекс pos2 (только для типа 'X')
                    if ((*code2) == 'X') {
                        if (*pSrc != '\0') {
                            for (i = 0, pSrc++; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
                            if (i > 0) {
                                buffer[i] = '\0';
                                *index2 = atoi(buffer);
                                if ((*index2) < 8) {
                                    bOK = true;
                                }
                            }
                        }

                    } else {
                        bOK = true;
                    }
                }

            }
        }
    }
    return bOK;
}

//-----------------------------------------------------------------------------
// User callback function for receive CANopen network variable
//-----------------------------------------------------------------------------
// Modules:
// * PRO100_DI_321_V23.eds
// * PRO100_AI_161_V33.eds
// * PRO100_TI_101_V13.eds
// * PRO100_AO_041_V42.eds
//-----------------------------------------------------------------------------
//void cb_work_func(std::vector<T_NETWORK_VARIABLE> _data)
void cb_work_func(std::map<uint8_t, T_CIA405_SLAVE_NODE> _node, std::vector<T_NETWORK_VARIABLE> _data)
{
    // _data[i]._var_name   - имя переменной (из EDS файла + Node_Id)
    // _data[i]._value      - значение переменной (указатель на void)
    // _data[i]._var_type   - тип переменной (не все, пока только основные)(взято из CANopen спецификации)
    // BOOL    = 0x01, SIGN8   = 0x02, SIGN16  = 0x03, SIGN32  = 0x04,
    // USIGN8  = 0x05, USIGN16 = 0x06, USIGN32 = 0x07, REAL32  = 0x08,
    // _data[i]._mem_link   - ссылка на память (типа "%ID3", "%IB12" и т.д.)
    //                      - если "%Ixx" - то это "входная" переменная данные от удаленного узла в Master
    //                      - если "%Qxx" - то это "выходная" переменная (данные Master в удаленный узел)
    //                      - пока не понятно, т.к., например, и "REAL", и "UDINT" кодирует как "%IDx"
    //                      (различать их по _data[i]._var_type)

    static timespec time_now = {0};
    static timespec time_prev = {0};
    static bool flag_1 = false;
    static bool flag_2 = false;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);

    //-------------------------------------------------------------------------
    // Симуляция двух параметров (Евгений)
    //-------------------------------------------------------------------------
    if (time_prev.tv_sec != 0) {
        if((time_now.tv_sec - time_prev.tv_sec) > 5) {
            time_prev.tv_sec = time_now.tv_sec;
            for (auto & item : _data) {
                if (strcmp("Analogue_Output_1_4", item._var_name) == 0) {
                    if (flag_1) { flag_1 = false; *(float32_t *)(item._value) = 10.0; }
                    else         { flag_1 = true; *(float32_t *)(item._value) = 0.0;  }
                }
                if (strcmp("Analogue_Output_2_4", item._var_name) == 0) {
                    if (flag_2) { flag_2 = false; *(float32_t *)(item._value) = 0.0;  }
                    else         { flag_2 = true; *(float32_t *)(item._value) = 15.0; }
                }
            }
        }
    } else { time_prev.tv_sec = time_now.tv_sec; }

    //-------------------------------------------------------------------------
    // Раскладка данных в буферы (Peter)
    //-------------------------------------------------------------------------
    pthread_mutex_lock(&bufferLock);

    char dataScope=0, dataSize=0;
    int index1=0, index2=0;
    for (auto & item : _data)
    {
        // Извлекаем данные из _mem_link
        if (parseReg(item._mem_link, &dataScope, &dataSize, &index1, &index2 ))
        {
            if (dataScope == 'I') {         // INPUT
                // Значение CAN
                VARIANT var(VARIANT::typeFrom(item._var_type), item._value);

                switch (dataSize) {
                        case 'X': *bool_input[index1][index2] = (var.toBOOL().getBOOL() ? 1 : 0); break;
                        case 'B': *byte_input[index1] = var.toUINT8 ().getUINT8 (); break;
                        case 'W': *int_input [index1] = var.toUINT16().getUINT16(); break;
                        case 'D': *dint_input[index1] = var.toUINT32().getUINT32(); break;
                        case 'L': *lint_input[index1] = var.toUINT64().getUINT64(); break;
                        default:;
                }

            } else if (dataScope == 'Q') {  //OUTPUT
                VARIANT var;
                switch (dataSize) {
                    case 'X': var = VARIANT(*bool_input[index1][index2]);   break;
                    case 'B': var = VARIANT(*byte_input[index1]);           break;
                    case 'W': var = VARIANT(*int_input [index1]);           break;
                    case 'D': var = VARIANT(*dint_input[index1]);           break;
                    case 'L': var = VARIANT(*lint_input[index1]);           break;
                    default:;
                }

                // Запись значения
                switch (VARIANT::typeFrom(item._var_type)) {
                    case E_BOOL  :  (* (T_BOOL   *) item._value) = var.toBOOL().getBOOL();
                    case E_SINT8 :  (* (T_SINT8  *) item._value) = var.toBOOL().getSINT8();
                    case E_SINT16:  (* (T_SINT16 *) item._value) = var.toBOOL().getSINT16();
                    case E_SINT32:  (* (T_SINT32 *) item._value) = var.toBOOL().getSINT32();
                    case E_SINT64:  (* (T_SINT64 *) item._value) = var.toBOOL().getSINT64();
                    case E_UINT8 :  (* (T_UINT8  *) item._value) = var.toBOOL().getUINT8();
                    case E_UINT16:  (* (T_UINT16 *) item._value) = var.toBOOL().getUINT16();
                    case E_UINT32:  (* (T_UINT32 *) item._value) = var.toBOOL().getUINT32();
                    case E_UINT64:  (* (T_UINT64 *) item._value) = var.toBOOL().getUINT64();
                    case E_REAL32:  (* (T_REAL32 *) item._value) = var.toBOOL().getREAL32();
                    case E_REAL64:  (* (T_REAL64 *) item._value) = var.toBOOL().getREAL64();
                }

            } else if (dataScope == 'M') {
                // MEMORY
                // (не применяется)

            } else {
                //assert(false);
            }
        }
    }

    pthread_mutex_unlock(&bufferLock);
}


//-----------------------------------------------------------------------------
// This function is called by the main OpenPLC routine when it is initializing.
// Hardware initialization procedures should be here.
//-----------------------------------------------------------------------------
void initializeHardware()
{
    auto* _cia405 = new CIA405();

    bool _res = _cia405->configuration();
    if (_res) {
        // регистрация callback-функции для обработки сетевых переменных
        _cia405->set_callback_work_func(cb_work_func);

        // запуск основного потока CANopen
        _cia405->start();
    }


}

//-----------------------------------------------------------------------------
// This function is called by the main OpenPLC routine when it is finalizing.
// Resource clearing procedures should be here.
//-----------------------------------------------------------------------------
void finalizeHardware()
{
}

//-----------------------------------------------------------------------------
// This function is called by the OpenPLC in a loop. Here the internal buffers
// must be updated to reflect the actual Input state. The mutex bufferLock
// must be used to protect access to the buffers on a threaded environment.
//-----------------------------------------------------------------------------
void updateBuffersIn()
{
    pthread_mutex_lock(&bufferLock); //lock mutex

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

    pthread_mutex_unlock(&bufferLock); //unlock mutex
}

//-----------------------------------------------------------------------------
// This function is called by the OpenPLC in a loop. Here the internal buffers
// must be updated to reflect the actual Output state. The mutex bufferLock
// must be used to protect access to the buffers on a threaded environment.
//-----------------------------------------------------------------------------
void updateBuffersOut()
{
    pthread_mutex_lock(&bufferLock); //lock mutex

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

    pthread_mutex_unlock(&bufferLock); //unlock mutex
}

//-----------------------------------------------------------------------------
