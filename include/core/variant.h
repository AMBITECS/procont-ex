//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_VARIANT_H
#define PROCONT_EX_VARIANT_H

#include <string>
#include <optional>
#include <stdexcept>
#include <cmath>
#include <mutex>
#include <algorithm>
#include <sstream>
#include <iomanip>

//-----------------------------------------------------------------------------
// Define types with exact width
//-----------------------------------------------------------------------------
using T_BOOL   = bool;
using T_SINT8  = int8_t;
using T_SINT16 = int16_t;
using T_SINT32 = int32_t;
using T_SINT64 = int64_t;
using T_UINT8  = uint8_t;
using T_UINT16 = uint16_t;
using T_UINT32 = uint32_t;
using T_UINT64 = uint64_t;
using T_REAL32 = float;
using T_REAL64 = double;
using T_STRING = std::string;

//-----------------------------------------------------------------------------
// Variant type codes
//-----------------------------------------------------------------------------
enum VAR_TYPE : uint8_t {
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

    VT_STRING  = 0x20
};

//-----------------------------------------------------------------------------
// IEC type codes (aliases)
//-----------------------------------------------------------------------------
constexpr VAR_TYPE PLC_NULL  = VAR_TYPE::VT_NULL  ;
constexpr VAR_TYPE PLC_BOOL  = VAR_TYPE::VT_BOOL  ;
constexpr VAR_TYPE PLC_SINT  = VAR_TYPE::VT_SINT8 ;
constexpr VAR_TYPE PLC_INT   = VAR_TYPE::VT_SINT16;
constexpr VAR_TYPE PLC_DINT  = VAR_TYPE::VT_SINT32;
constexpr VAR_TYPE PLC_LINT  = VAR_TYPE::VT_SINT64;
constexpr VAR_TYPE PLC_USINT = VAR_TYPE::VT_UINT8 ;
constexpr VAR_TYPE PLC_UINT  = VAR_TYPE::VT_UINT16;
constexpr VAR_TYPE PLC_UDINT = VAR_TYPE::VT_UINT32;
constexpr VAR_TYPE PLC_ULINT = VAR_TYPE::VT_UINT64;
constexpr VAR_TYPE PLC_REAL  = VAR_TYPE::VT_REAL32;
constexpr VAR_TYPE PLC_LREAL = VAR_TYPE::VT_REAL64;
constexpr VAR_TYPE PLC_STRING= VAR_TYPE::VT_STRING;

//-----------------------------------------------------------------------------
// Thread-safe string wrapper
//-----------------------------------------------------------------------------
struct TS_STRING {
    T_STRING str;
    mutable std::mutex mtx;

    TS_STRING() = default;
    explicit TS_STRING(const T_STRING& s) : str(s) {}
    explicit TS_STRING(T_STRING&& s) : str(std::move(s)) {}

    TS_STRING(const TS_STRING& other) {
        std::lock_guard lock(other.mtx);
        str = other.str;
    }

    TS_STRING& operator=(const TS_STRING& other) {
        if (this != &other) {
            std::scoped_lock lock(mtx, other.mtx);
            str = other.str;
        }
        return *this;
    }

    TS_STRING(TS_STRING&& other) noexcept {
        std::lock_guard lock(other.mtx);
        str = std::move(other.str);
    }

    TS_STRING& operator=(TS_STRING&& other) noexcept {
        if (this != &other) {
            std::scoped_lock lock(mtx, other.mtx);
            str = std::move(other.str);
        }
        return *this;
    }
};

//-----------------------------------------------------------------------------
// Variant value union with proper alignment
//-----------------------------------------------------------------------------
union VAR_VALUE {
    T_BOOL     _bool;
    T_SINT8    _sint8;
    T_SINT16   _sint16;
    T_SINT32   _sint32;

    alignas(8)
    T_SINT64   _sint64;  // Явное выравнивание
    T_UINT8    _uint8;
    T_UINT16   _uint16;
    T_UINT32   _uint32;

    alignas(8)
    T_UINT64   _uint64;  // Явное выравнивание
    T_REAL32   _real32;

    alignas(8)
    T_REAL64   _real64;  // Явное выравнивание
    alignas(alignof(void*))

    TS_STRING* _string;  // Для указателя

    VAR_VALUE() noexcept : _uint64(0) {}
    ~VAR_VALUE() noexcept = default;

    explicit VAR_VALUE(T_BOOL   v) noexcept : _bool  (v) {}
    explicit VAR_VALUE(T_SINT8  v) noexcept : _sint8 (v) {}
    explicit VAR_VALUE(T_SINT16 v) noexcept : _sint16(v) {}
    explicit VAR_VALUE(T_SINT32 v) noexcept : _sint32(v) {}
    explicit VAR_VALUE(T_SINT64 v) noexcept : _sint64(v) {}
    explicit VAR_VALUE(T_UINT8  v) noexcept : _uint8 (v) {}
    explicit VAR_VALUE(T_UINT16 v) noexcept : _uint16(v) {}
    explicit VAR_VALUE(T_UINT32 v) noexcept : _uint32(v) {}
    explicit VAR_VALUE(T_UINT64 v) noexcept : _uint64(v) {}
    explicit VAR_VALUE(T_REAL32 v) noexcept : _real32(v) {}
    explicit VAR_VALUE(T_REAL64 v) noexcept : _real64(v) {}

    explicit VAR_VALUE(const T_STRING& v) : _string(new TS_STRING(v)) {}
    explicit VAR_VALUE(T_STRING&& v) : _string(new TS_STRING(std::move(v))) {}

    VAR_VALUE(const VAR_VALUE& src) noexcept { _uint64 = src._uint64; }

    VAR_VALUE& operator=(const VAR_VALUE& val) noexcept { if (this != &val) { _uint64 = val._uint64; } return *this; }
    VAR_VALUE& operator=(VAR_VALUE&& val) noexcept { if (this != &val) { _uint64 = val._uint64; val._uint64 = 0; } return *this; }
};

//-----------------------------------------------------------------------------
// Variant typed value class
//-----------------------------------------------------------------------------
class VARIANT {
    VAR_TYPE  type_ = VT_NULL;
    VAR_VALUE value_{};

    void cleanup() noexcept {
        if (type_ == VT_STRING && value_._string != nullptr) {
            delete value_._string;
            value_._string = nullptr;
        }
    }

    void copy_from(const VARIANT& other) {
        if (other.type_ == VT_STRING) {
            value_._string = new TS_STRING(*other.value_._string);
        } else {
            value_ = other.value_;
        }
        type_ = other.type_;
    }

    void move_from(VARIANT&& other) noexcept {
        type_ = other.type_;
        value_ = other.value_;
        other.type_ = VT_NULL;
        other.value_._uint64 = 0;
    }

    template<typename T>
    void checkRange(T value, T min, T max) const {
        if (value < min || value > max) {
            throw std::overflow_error("Value out of range for target type");
        }
    }

public:
    //-----------------------------------------------------------------------------
    // Constructors & Destructor
    //-----------------------------------------------------------------------------
    VARIANT() noexcept : type_(VT_NULL), value_() { value_._uint64 = 0; }
    ~VARIANT() { cleanup(); }

    VARIANT(const VARIANT& other) : type_(VT_NULL) { copy_from(other); }
    VARIANT(VARIANT&& other) noexcept : type_(VT_NULL) { move_from(std::move(other)); }

    explicit VARIANT(VAR_TYPE type) noexcept : type_(type), value_() {
        value_._uint64 = 0;
        if (type_ == VT_STRING) { value_._string = new TS_STRING(); }
    }

    VARIANT(VAR_TYPE type, const void* value);

    explicit VARIANT(T_BOOL v)   noexcept  : type_(VT_BOOL),   value_(v) {}
    explicit VARIANT(T_SINT8 v)  noexcept  : type_(VT_SINT8),  value_(v) {}
    explicit VARIANT(T_SINT16 v) noexcept  : type_(VT_SINT16), value_(v) {}
    explicit VARIANT(T_SINT32 v) noexcept  : type_(VT_SINT32), value_(v) {}
    explicit VARIANT(T_SINT64 v) noexcept  : type_(VT_SINT64), value_(v) {}
    explicit VARIANT(T_UINT8 v)  noexcept  : type_(VT_UINT8),  value_(v) {}
    explicit VARIANT(T_UINT16 v) noexcept  : type_(VT_UINT16), value_(v) {}
    explicit VARIANT(T_UINT32 v) noexcept  : type_(VT_UINT32), value_(v) {}
    explicit VARIANT(T_UINT64 v) noexcept  : type_(VT_UINT64), value_(v) {}
    explicit VARIANT(T_REAL32 v) noexcept  : type_(VT_REAL32), value_(v) {}
    explicit VARIANT(T_REAL64 v) noexcept  : type_(VT_REAL64), value_(v) {}
    explicit VARIANT(const T_STRING& v) : type_(VT_STRING), value_(v) {}
    explicit VARIANT(const char* v) : type_(VT_STRING), value_(T_STRING(v)) {}
    explicit VARIANT(std::nullptr_t) noexcept : type_(VT_NULL), value_() {}

    [[nodiscard]] bool isInitialized() const noexcept {
        if (type_ == VT_STRING) return value_._string != nullptr;
        return type_ != VT_NULL;
    }

    //-----------------------------------------------------------------------------
    // Assignment operators
    //-----------------------------------------------------------------------------
    VARIANT& operator=(T_BOOL v)   noexcept { cleanup(); type_ = VT_BOOL  ; value_._bool   = v; return *this; }
    VARIANT& operator=(T_SINT8 v)  noexcept { cleanup(); type_ = VT_SINT8 ; value_._sint8  = v; return *this; }
    VARIANT& operator=(T_SINT16 v) noexcept { cleanup(); type_ = VT_SINT16; value_._sint16 = v; return *this; }
    VARIANT& operator=(T_SINT32 v) noexcept { cleanup(); type_ = VT_SINT32; value_._sint32 = v; return *this; }
    VARIANT& operator=(T_SINT64 v) noexcept { cleanup(); type_ = VT_SINT64; value_._sint64 = v; return *this; }
    VARIANT& operator=(T_UINT8 v)  noexcept { cleanup(); type_ = VT_UINT8 ; value_._uint8  = v; return *this; }
    VARIANT& operator=(T_UINT16 v) noexcept { cleanup(); type_ = VT_UINT16; value_._uint16 = v; return *this; }
    VARIANT& operator=(T_UINT32 v) noexcept { cleanup(); type_ = VT_UINT32; value_._uint32 = v; return *this; }
    VARIANT& operator=(T_UINT64 v) noexcept { cleanup(); type_ = VT_UINT64; value_._uint64 = v; return *this; }
    VARIANT& operator=(T_REAL32 v) noexcept { cleanup(); type_ = VT_REAL32; value_._real32 = v; return *this; }
    VARIANT& operator=(T_REAL64 v) noexcept { cleanup(); type_ = VT_REAL64; value_._real64 = v; return *this; }

    VARIANT& operator=(const VARIANT& other) { if (this != &other) { cleanup(); copy_from(other); } return *this; }
    VARIANT& operator=(VARIANT&& other) noexcept { if (this != &other) { cleanup(); move_from(std::move(other)); } return *this; }

    VARIANT& operator=(const T_STRING& v) { cleanup(); type_ = VT_STRING; value_._string = new TS_STRING(v); return *this; }
    VARIANT& operator=(const char* v) { cleanup(); type_ = VT_STRING; value_._string = new TS_STRING(v); return *this; }
    VARIANT& operator=(std::nullptr_t) noexcept { cleanup(); type_ = VT_NULL; value_._uint64 = 0; return *this; }

    //-----------------------------------------------------------------------------
    // Type information
    //-----------------------------------------------------------------------------
    [[nodiscard]] VAR_TYPE type()   const noexcept { return type_; }
    [[nodiscard]] bool isNull()     const noexcept { return type_ == VT_NULL; }
    [[nodiscard]] bool isBool()     const noexcept { return type_ == VT_BOOL; }
    [[nodiscard]] bool isInteger()  const noexcept { return (type_ >= VT_SINT8 && type_ <= VT_UINT64) || type_ == VT_BOOL; }
    [[nodiscard]] bool isSigned()   const noexcept { return type_ >= VT_SINT8 && type_ <= VT_SINT64; }
    [[nodiscard]] bool isUnsigned() const noexcept { return type_ >= VT_UINT8 && type_ <= VT_UINT64; }
    [[nodiscard]] bool isReal()     const noexcept { return type_ == VT_REAL32 || type_ == VT_REAL64; }
    [[nodiscard]] bool isString()   const noexcept { return type_ == VT_STRING; }
    [[nodiscard]] bool isNumeric()  const noexcept { return isInteger() || isReal(); }

    //-----------------------------------------------------------------------------
    // Safe value getters
    //-----------------------------------------------------------------------------
    template<typename T>
    [[nodiscard]] std::optional<T> tryGet() const noexcept {
        try {
            return get<T>();
        } catch (...) {
            return std::nullopt;
        }
    }

    template<typename T>
    [[nodiscard]] T get() const {
        if      constexpr (std::is_same_v<T, bool>)     { return getBOOL();   }
        else if constexpr (std::is_same_v<T, T_SINT8>)  { return getSINT8();  }
        else if constexpr (std::is_same_v<T, T_SINT16>) { return getSINT16(); }
        else if constexpr (std::is_same_v<T, T_SINT32>) { return getSINT32(); }
        else if constexpr (std::is_same_v<T, T_SINT64>) { return getSINT64(); }
        else if constexpr (std::is_same_v<T, T_UINT8>)  { return getUINT8();  }
        else if constexpr (std::is_same_v<T, T_UINT16>) { return getUINT16(); }
        else if constexpr (std::is_same_v<T, T_UINT32>) { return getUINT32(); }
        else if constexpr (std::is_same_v<T, T_UINT64>) { return getUINT64(); }
        else if constexpr (std::is_same_v<T, T_REAL32>) { return getREAL32(); }
        else if constexpr (std::is_same_v<T, T_REAL64>) { return getREAL64(); }
        else if constexpr (std::is_same_v<T, T_STRING>) { return getSTRING(); }
        else {
            static_assert(sizeof(T) == 0, "Unsupported type for VARIANT::get()");
        }
    }

    // Приведение к каждому типу в отдельности
    [[nodiscard]] T_BOOL    getBOOL()   const;
    [[nodiscard]] T_SINT8   getSINT8()  const;
    [[nodiscard]] T_SINT16  getSINT16() const;
    [[nodiscard]] T_SINT32  getSINT32() const;
    [[nodiscard]] T_SINT64  getSINT64() const;
    [[nodiscard]] T_UINT8   getUINT8()  const;
    [[nodiscard]] T_UINT16  getUINT16() const;
    [[nodiscard]] T_UINT32  getUINT32() const;
    [[nodiscard]] T_UINT64  getUINT64() const;
    [[nodiscard]] T_REAL32  getREAL32() const;
    [[nodiscard]] T_REAL64  getREAL64() const;
    [[nodiscard]] T_STRING  getSTRING() const;

    //-------------------------------------------------------------------------
    // Bitwise interpreters (reinterpret raw bits)
    //-------------------------------------------------------------------------
    template<VAR_TYPE TargetType>
    [[nodiscard]] VARIANT asType() const {
        if (!isInitialized()) {
            throw std::runtime_error("VARIANT not properly initialized");
        }
        if (type_ == VT_STRING) {
            throw std::runtime_error("Cannot interpret string as this type");
        }
        return VARIANT{TargetType, &value_};
    }

    [[nodiscard]] VARIANT asBOOL()   const { return asType<VT_BOOL>  (); }
    [[nodiscard]] VARIANT asSINT8()  const { return asType<VT_SINT8> (); }
    [[nodiscard]] VARIANT asSINT16() const { return asType<VT_SINT16>(); }
    [[nodiscard]] VARIANT asSINT32() const { return asType<VT_SINT32>(); }
    [[nodiscard]] VARIANT asSINT64() const { return asType<VT_SINT64>(); }
    [[nodiscard]] VARIANT asUINT8()  const { return asType<VT_UINT8> (); }
    [[nodiscard]] VARIANT asUINT16() const { return asType<VT_UINT16>(); }
    [[nodiscard]] VARIANT asUINT32() const { return asType<VT_UINT32>(); }
    [[nodiscard]] VARIANT asUINT64() const { return asType<VT_UINT64>(); }
    [[nodiscard]] VARIANT asREAL32() const { return asType<VT_REAL32>(); }
    [[nodiscard]] VARIANT asREAL64() const { return asType<VT_REAL64>(); }

    //-------------------------------------------------------------------------
    // Safe converters with special handling for real numbers
    //-------------------------------------------------------------------------
    [[nodiscard]] VARIANT toBOOL()   const { return VARIANT(getBOOL()); }
    [[nodiscard]] VARIANT toSINT8()  const { return isReal()  ? asSINT8()  : VARIANT(getSINT8());  }
    [[nodiscard]] VARIANT toSINT16() const { return isReal()  ? asSINT16() : VARIANT(getSINT16()); }
    [[nodiscard]] VARIANT toSINT32() const { return isReal()  ? asSINT32() : VARIANT(getSINT32()); }
    [[nodiscard]] VARIANT toSINT64() const { return isReal()  ? asSINT64() : VARIANT(getSINT64()); }
    [[nodiscard]] VARIANT toUINT8()  const { return isReal()  ? asUINT8()  : VARIANT(getUINT8());  }
    [[nodiscard]] VARIANT toUINT16() const { return isReal()  ? asUINT16() : VARIANT(getUINT16()); }
    [[nodiscard]] VARIANT toUINT32() const { return isReal()  ? asUINT32() : VARIANT(getUINT32()); }
    [[nodiscard]] VARIANT toUINT64() const { return isReal()  ? asUINT64() : VARIANT(getUINT64()); }
    [[nodiscard]] VARIANT toREAL32() const { return !isReal() ? asREAL32() : VARIANT(getREAL32()); }
    [[nodiscard]] VARIANT toREAL64() const { return !isReal() ? asREAL64() : VARIANT(getREAL64()); }

    //-----------------------------------------------------------------------------
    [[nodiscard]] VARIANT to(VAR_TYPE target_type) const {
        switch (target_type) {
            case VT_BOOL:   return toBOOL();
            case VT_SINT8:  return toSINT8();
            case VT_SINT16: return toSINT16();
            case VT_SINT32: return toSINT32();
            case VT_SINT64: return toSINT64();
            case VT_UINT8:  return toUINT8();
            case VT_UINT16: return toUINT16();
            case VT_UINT32: return toUINT32();
            case VT_UINT64: return toUINT64();
            case VT_REAL32: return toREAL32();
            case VT_REAL64: return toREAL64();
            case VT_STRING: return VARIANT(toString());
            case VT_NULL:   return {};
            default:       throw std::invalid_argument("Invalid target type");
        }
    }

    //-----------------------------------------------------------------------------
    // Comparison operators
    //-----------------------------------------------------------------------------
    static bool compareDoubles(double a, double b) noexcept {
        if (std::isnan(a)) return false;
        if (std::isnan(b)) return true;
        if (std::abs(a - b) <= std::numeric_limits<double>::min()) return true;
        return std::abs(a - b) <= std::numeric_limits<double>::epsilon() *
                                  std::max(std::abs(a), std::abs(b));
    }

    bool operator==(const VARIANT& other) const {
        if (type_ != other.type_) {
            if (isNumeric() && other.isNumeric()) {
                if (isReal() || other.isReal()) {
                    double this_val = isReal() ? getREAL64() : static_cast<double>(getSINT64());
                    double other_val = other.isReal() ? other.getREAL64() : static_cast<double>(other.getSINT64());
                    return compareDoubles(this_val, other_val);
                }
                return getSINT64() == other.getSINT64();
            }
            return false;
        }

        switch (type_) {
            case VT_NULL:   return true;
            case VT_BOOL:   return value_._bool   == other.value_._bool;
            case VT_SINT8:  return value_._sint8  == other.value_._sint8;
            case VT_SINT16: return value_._sint16 == other.value_._sint16;
            case VT_SINT32: return value_._sint32 == other.value_._sint32;
            case VT_SINT64: return value_._sint64 == other.value_._sint64;
            case VT_UINT8:  return value_._uint8  == other.value_._uint8;
            case VT_UINT16: return value_._uint16 == other.value_._uint16;
            case VT_UINT32: return value_._uint32 == other.value_._uint32;
            case VT_UINT64: return value_._uint64 == other.value_._uint64;
            case VT_REAL32: return compareDoubles(value_._real32, other.value_._real32);
            case VT_REAL64: return compareDoubles(value_._real64, other.value_._real64);
            case VT_STRING: {
                std::scoped_lock lock(value_._string->mtx, other.value_._string->mtx);
                return value_._string->str == other.value_._string->str;
            }
            default: return false;
        }
    }

    bool operator!=(const VARIANT& other) const {
        return !(*this == other);
    }

    static bool compareLess(double a, double b) noexcept {
        if (std::isnan(a)) return false;
        if (std::isnan(b)) return true;
        if (std::isinf(a) && std::isinf(b)) return a < b;
        if (std::isinf(a)) return a < 0;
        if (std::isinf(b)) return b > 0;

        double diff = a - b;
        double max_val = std::max(std::abs(a), std::abs(b));
        return diff < -std::numeric_limits<double>::epsilon() * max_val;
    }

    bool operator<(const VARIANT& other) const {
        if (type_ != other.type_) {
            if (isNumeric() && other.isNumeric()) {
                if (isReal() || other.isReal()) {
                    double this_val = isReal() ? getREAL64() : static_cast<double>(getSINT64());
                    double other_val = other.isReal() ? other.getREAL64() : static_cast<double>(other.getSINT64());
                    return compareLess(this_val, other_val);
                }
                return getSINT64() < other.getSINT64();
            }
            return type_ < other.type_;
        }

        switch (type_) {
            case VT_BOOL:   return value_._bool   < other.value_._bool;
            case VT_SINT8:  return value_._sint8  < other.value_._sint8;
            case VT_SINT16: return value_._sint16 < other.value_._sint16;
            case VT_SINT32: return value_._sint32 < other.value_._sint32;
            case VT_SINT64: return value_._sint64 < other.value_._sint64;
            case VT_UINT8:  return value_._uint8  < other.value_._uint8;
            case VT_UINT16: return value_._uint16 < other.value_._uint16;
            case VT_UINT32: return value_._uint32 < other.value_._uint32;
            case VT_UINT64: return value_._uint64 < other.value_._uint64;
            case VT_REAL32: return compareLess(value_._real32, other.value_._real32);
            case VT_REAL64: return compareLess(value_._real64, other.value_._real64);
            case VT_STRING: {
                std::scoped_lock lock(value_._string->mtx, other.value_._string->mtx);
                return value_._string->str < other.value_._string->str;
            }
            case VT_NULL: return false;  // NULL is not less than NULL
        }
        return false;
    }

    bool operator<=(const VARIANT& other) const { return !(other < *this); }
    bool operator>(const VARIANT& other)  const { return (other < *this);  }
    bool operator>=(const VARIANT& other) const { return !(*this < other); }

    //-----------------------------------------------------------------------------
    // Utility functions
    //-----------------------------------------------------------------------------
    [[nodiscard]] T_STRING toString() const { return getSTRING(); }

    [[nodiscard]] static VARIANT of(const T_STRING& str, VAR_TYPE type = VT_STRING) {
        if (type == VT_STRING) {
            return VARIANT(str);
        }

        try {
            switch (type) {
                case VT_BOOL: {
                    T_STRING lower;
                    std::transform(str.begin(), str.end(), std::back_inserter(lower), ::tolower);
                    return VARIANT(lower == "true" || lower == "1" || lower == "yes");
                }
                case VT_SINT8:  return VARIANT(static_cast<T_SINT8>(std::stoi(str)));
                case VT_SINT16: return VARIANT(static_cast<T_SINT16>(std::stoi(str)));
                case VT_SINT32: return VARIANT(static_cast<T_SINT32>(std::stol(str)));
                case VT_SINT64: return VARIANT(static_cast<T_SINT64>(std::stoll(str)));
                case VT_UINT8:  return VARIANT(static_cast<T_UINT8>(std::stoul(str)));
                case VT_UINT16: return VARIANT(static_cast<T_UINT16>(std::stoul(str)));
                case VT_UINT32: return VARIANT(static_cast<T_UINT32>(std::stoul(str)));
                case VT_UINT64: return VARIANT(static_cast<T_UINT64>(std::stoull(str)));
                case VT_REAL32: return VARIANT(std::stof(str));
                case VT_REAL64: return VARIANT(std::stod(str));
                default: throw std::invalid_argument("Unsupported conversion type");
            }
        } catch (...) {
            throw std::runtime_error("String conversion failed");
        }
    }

    [[nodiscard]] static constexpr VAR_TYPE typeFromInt(int code) noexcept {
        return (code >= VT_NULL && code <= VT_STRING) ? static_cast<VAR_TYPE>(code) : VT_NULL;
    }

    [[nodiscard]] static const char* typeToStr(VAR_TYPE type) noexcept {
        switch (type) {
            case VT_NULL:   return "NULL";
            case VT_BOOL:   return "BOOL";
            case VT_SINT8:  return "SINT8";
            case VT_SINT16: return "SINT16";
            case VT_SINT32: return "SINT32";
            case VT_SINT64: return "SINT64";
            case VT_UINT8:  return "UINT8";
            case VT_UINT16: return "UINT16";
            case VT_UINT32: return "UINT32";
            case VT_UINT64: return "UINT64";
            case VT_REAL32: return "REAL32";
            case VT_REAL64: return "REAL64";
            case VT_STRING: return "STRING";
            default:        return "UNKNOWN";
        }
    }

    [[nodiscard]] const char* typeStr() const noexcept {
        return typeToStr(type_);
    }

    void swap(VARIANT& other) noexcept {
        if (this != &other) {
            std::swap(type_, other.type_);
            std::swap(value_, other.value_);
        }
    }
};

//-----------------------------------------------------------------------------
// Non-member functions
//-----------------------------------------------------------------------------
inline void swap(VARIANT& lhs, VARIANT& rhs) noexcept {
    lhs.swap(rhs);
}

inline std::ostream& operator<<(std::ostream& os, const VARIANT& var) {
    os << var.toString();
    return os;
}

#endif //PROCONT_EX_VARIANT_H
