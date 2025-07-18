//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "variant.h"

VARIANT::VARIANT(VAR_TYPE type, const void *value) : type_(type) {
    if (type_ == VT_STRING) {
        throw std::invalid_argument("Use string constructor for VT_STRING");
    }
    switch (type_) {
        case VT_BOOL:   value_ = VAR_VALUE(*static_cast<const T_BOOL*>(value));   break;
        case VT_SINT8:  value_ = VAR_VALUE(*static_cast<const T_SINT8*>(value));  break;
        case VT_SINT16: value_ = VAR_VALUE(*static_cast<const T_SINT16*>(value)); break;
        case VT_SINT32: value_ = VAR_VALUE(*static_cast<const T_SINT32*>(value)); break;
        case VT_SINT64: value_ = VAR_VALUE(*static_cast<const T_SINT64*>(value)); break;
        case VT_UINT8:  value_ = VAR_VALUE(*static_cast<const T_UINT8*>(value));  break;
        case VT_UINT16: value_ = VAR_VALUE(*static_cast<const T_UINT16*>(value)); break;
        case VT_UINT32: value_ = VAR_VALUE(*static_cast<const T_UINT32*>(value)); break;
        case VT_UINT64: value_ = VAR_VALUE(*static_cast<const T_UINT64*>(value)); break;
        case VT_REAL32: value_ = VAR_VALUE(*static_cast<const T_REAL32*>(value)); break;
        case VT_REAL64: value_ = VAR_VALUE(*static_cast<const T_REAL64*>(value)); break;
        default: type_ = VT_NULL; value_._uint64 = 0;
    }
}

T_BOOL VARIANT::getBOOL() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool;
        case VT_SINT8:  return value_._sint8  != 0;
        case VT_SINT16: return value_._sint16 != 0;
        case VT_SINT32: return value_._sint32 != 0;
        case VT_SINT64: return value_._sint64 != 0;
        case VT_UINT8:  return value_._uint8  != 0;
        case VT_UINT16: return value_._uint16 != 0;
        case VT_UINT32: return value_._uint32 != 0;
        case VT_UINT64: return value_._uint64 != 0;
        case VT_REAL32: return value_._real32 != 0.0f;
        case VT_REAL64: return value_._real64 != 0.0;
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            return !value_._string->str.empty() && value_._string->str != "0" &&
                   value_._string->str != "false" && value_._string->str != "FALSE";
        }
        case VT_NULL:
        default: return false;
    }
}

T_SINT8 VARIANT::getSINT8() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8:  return value_._sint8;
        case VT_SINT16: {
            checkRange(value_._sint16, static_cast<T_SINT16>(std::numeric_limits<T_SINT8>::min()),
                       static_cast<T_SINT16>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._sint16);
        }
        case VT_SINT32: {
            checkRange(value_._sint32, static_cast<T_SINT32>(std::numeric_limits<T_SINT8>::min()),
                       static_cast<T_SINT32>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._sint32);
        }
        case VT_SINT64: {
            checkRange(value_._sint64, static_cast<T_SINT64>(std::numeric_limits<T_SINT8>::min()),
                       static_cast<T_SINT64>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_SINT8>(value_._uint8);
        case VT_UINT16: {
            checkRange(value_._uint16, static_cast<T_UINT16>(0),
                       static_cast<T_UINT16>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._uint16);
        }
        case VT_UINT32: {
            checkRange(value_._uint32, static_cast<T_UINT32>(0),
                       static_cast<T_UINT32>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._uint32);
        }
        case VT_UINT64: {
            checkRange(value_._uint64, static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32, static_cast<T_REAL32>(std::numeric_limits<T_SINT8>::min()),
                       static_cast<T_REAL32>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64, static_cast<T_REAL64>(std::numeric_limits<T_SINT8>::min()),
                       static_cast<T_REAL64>(std::numeric_limits<T_SINT8>::max()));
            return static_cast<T_SINT8>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                int64_t val = std::stoll(value_._string->str);
                checkRange(val, static_cast<int64_t>(std::numeric_limits<T_SINT8>::min()),
                           static_cast<int64_t>(std::numeric_limits<T_SINT8>::max()));
                return static_cast<T_SINT8>(val);
            } catch (...) {
                throw std::runtime_error("String to SINT8 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to SINT8");
    }
}

T_SINT16 VARIANT::getSINT16() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8:  return static_cast<T_SINT16>(value_._sint8);
        case VT_SINT16: return value_._sint16;
        case VT_SINT32: {
            checkRange(value_._sint32,
                       static_cast<T_SINT32>(std::numeric_limits<T_SINT16>::min()),
                       static_cast<T_SINT32>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._sint32);
        }
        case VT_SINT64: {
            checkRange(value_._sint64,
                       static_cast<T_SINT64>(std::numeric_limits<T_SINT16>::min()),
                       static_cast<T_SINT64>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_SINT16>(value_._uint8);
        case VT_UINT16: {
            checkRange(value_._uint16,
                       static_cast<T_UINT16>(0),
                       static_cast<T_UINT16>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._uint16);
        }
        case VT_UINT32: {
            checkRange(value_._uint32,
                       static_cast<T_UINT32>(0),
                       static_cast<T_UINT32>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._uint32);
        }
        case VT_UINT64: {
            checkRange(value_._uint64,
                       static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32,
                       static_cast<T_REAL32>(std::numeric_limits<T_SINT16>::min()),
                       static_cast<T_REAL32>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64,
                       static_cast<T_REAL64>(std::numeric_limits<T_SINT16>::min()),
                       static_cast<T_REAL64>(std::numeric_limits<T_SINT16>::max()));
            return static_cast<T_SINT16>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                int64_t val = std::stoll(value_._string->str);
                checkRange(val,
                           static_cast<int64_t>(std::numeric_limits<T_SINT16>::min()),
                           static_cast<int64_t>(std::numeric_limits<T_SINT16>::max()));
                return static_cast<T_SINT16>(val);
            } catch (...) {
                throw std::runtime_error("String to SINT16 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to SINT16");
    }
}

T_SINT32 VARIANT::getSINT32() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8:  return static_cast<T_SINT32>(value_._sint8);
        case VT_SINT16: return static_cast<T_SINT32>(value_._sint16);
        case VT_SINT32: return value_._sint32;
        case VT_SINT64: {
            checkRange(value_._sint64,
                       static_cast<T_SINT64>(std::numeric_limits<T_SINT32>::min()),
                       static_cast<T_SINT64>(std::numeric_limits<T_SINT32>::max()));
            return static_cast<T_SINT32>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_SINT32>(value_._uint8);
        case VT_UINT16: return static_cast<T_SINT32>(value_._uint16);
        case VT_UINT32: {
            checkRange(value_._uint32,
                       static_cast<T_UINT32>(0),
                       static_cast<T_UINT32>(std::numeric_limits<T_SINT32>::max()));
            return static_cast<T_SINT32>(value_._uint32);
        }
        case VT_UINT64: {
            checkRange(value_._uint64,
                       static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_SINT32>::max()));
            return static_cast<T_SINT32>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32,
                       static_cast<T_REAL32>(std::numeric_limits<T_SINT32>::min()),
                       static_cast<T_REAL32>(std::numeric_limits<T_SINT32>::max()));
            return static_cast<T_SINT32>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64,
                       static_cast<T_REAL64>(std::numeric_limits<T_SINT32>::min()),
                       static_cast<T_REAL64>(std::numeric_limits<T_SINT32>::max()));
            return static_cast<T_SINT32>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                int64_t val = std::stoll(value_._string->str);
                checkRange(val,
                           static_cast<int64_t>(std::numeric_limits<T_SINT32>::min()),
                           static_cast<int64_t>(std::numeric_limits<T_SINT32>::max()));
                return static_cast<T_SINT32>(val);
            } catch (...) {
                throw std::runtime_error("String to SINT32 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to SINT32");
    }
}

T_SINT64 VARIANT::getSINT64() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8:  return static_cast<T_SINT64>(value_._sint8);
        case VT_SINT16: return static_cast<T_SINT64>(value_._sint16);
        case VT_SINT32: return static_cast<T_SINT64>(value_._sint32);
        case VT_SINT64: return value_._sint64;
        case VT_UINT8:  return static_cast<T_SINT64>(value_._uint8);
        case VT_UINT16: return static_cast<T_SINT64>(value_._uint16);
        case VT_UINT32: return static_cast<T_SINT64>(value_._uint32);
        case VT_UINT64: {
            if (value_._uint64 > static_cast<T_UINT64>(std::numeric_limits<T_SINT64>::max()))
                throw std::overflow_error("UINT64 value too large for SINT64");
            return static_cast<T_SINT64>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            if (value_._real32 < static_cast<T_REAL32>(std::numeric_limits<T_SINT64>::min()) ||
                value_._real32 > static_cast<T_REAL32>(std::numeric_limits<T_SINT64>::max()))
                throw std::overflow_error("REAL32 value out of range for SINT64");
            return static_cast<T_SINT64>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            if (value_._real64 < static_cast<T_REAL64>(std::numeric_limits<T_SINT64>::min()) ||
                value_._real64 > static_cast<T_REAL64>(std::numeric_limits<T_SINT64>::max()))
                throw std::overflow_error("REAL64 value out of range for SINT64");
            return static_cast<T_SINT64>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                return std::stoll(value_._string->str);
            } catch (...) {
                throw std::runtime_error("String to SINT64 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to SINT64");
    }
}

T_UINT8 VARIANT::getUINT8() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8: {
            if (value_._sint8 < 0) throw std::underflow_error("Negative SINT8 to UINT8 conversion");
            return static_cast<T_UINT8>(value_._sint8);
        }
        case VT_SINT16: {
            checkRange(value_._sint16,
                       static_cast<T_SINT16>(0),
                       static_cast<T_SINT16>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._sint16);
        }
        case VT_SINT32: {
            checkRange(value_._sint32,
                       static_cast<T_SINT32>(0),
                       static_cast<T_SINT32>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._sint32);
        }
        case VT_SINT64: {
            checkRange(value_._sint64,
                       static_cast<T_SINT64>(0),
                       static_cast<T_SINT64>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._sint64);
        }
        case VT_UINT8:  return value_._uint8;
        case VT_UINT16: {
            checkRange(value_._uint16,
                       static_cast<T_UINT16>(0),
                       static_cast<T_UINT16>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._uint16);
        }
        case VT_UINT32: {
            checkRange(value_._uint32,
                       static_cast<T_UINT32>(0),
                       static_cast<T_UINT32>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._uint32);
        }
        case VT_UINT64: {
            checkRange(value_._uint64,
                       static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32,
                       static_cast<T_REAL32>(0),
                       static_cast<T_REAL32>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64,
                       static_cast<T_REAL64>(0),
                       static_cast<T_REAL64>(std::numeric_limits<T_UINT8>::max()));
            return static_cast<T_UINT8>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                unsigned long val = std::stoul(value_._string->str);
                checkRange(val,
                           static_cast<unsigned long>(0),
                           static_cast<unsigned long>(std::numeric_limits<T_UINT8>::max()));
                return static_cast<T_UINT8>(val);
            } catch (...) {
                throw std::runtime_error("String to UINT8 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to UINT8");
    }
}

T_UINT16 VARIANT::getUINT16() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8: {
            if (value_._sint8 < 0) throw std::underflow_error("Negative SINT8 to UINT16 conversion");
            return static_cast<T_UINT16>(value_._sint8);
        }
        case VT_SINT16: {
            if (value_._sint16 < 0) throw std::underflow_error("Negative SINT16 to UINT16 conversion");
            return static_cast<T_UINT16>(value_._sint16);
        }
        case VT_SINT32: {
            checkRange(value_._sint32,
                       static_cast<T_SINT32>(0),
                       static_cast<T_SINT32>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._sint32);
        }
        case VT_SINT64: {
            checkRange(value_._sint64,
                       static_cast<T_SINT64>(0),
                       static_cast<T_SINT64>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_UINT16>(value_._uint8);
        case VT_UINT16: return value_._uint16;
        case VT_UINT32: {
            checkRange(value_._uint32,
                       static_cast<T_UINT32>(0),
                       static_cast<T_UINT32>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._uint32);
        }
        case VT_UINT64: {
            checkRange(value_._uint64,
                       static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32,
                       static_cast<T_REAL32>(0),
                       static_cast<T_REAL32>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64,
                       static_cast<T_REAL64>(0),
                       static_cast<T_REAL64>(std::numeric_limits<T_UINT16>::max()));
            return static_cast<T_UINT16>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                unsigned long val = std::stoul(value_._string->str);
                checkRange(val,
                           static_cast<unsigned long>(0),
                           static_cast<unsigned long>(std::numeric_limits<T_UINT16>::max()));
                return static_cast<T_UINT16>(val);
            } catch (...) {
                throw std::runtime_error("String to UINT16 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to UINT16");
    }
}

T_UINT32 VARIANT::getUINT32() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8: {
            if (value_._sint8 < 0) throw std::underflow_error("Negative SINT8 to UINT32 conversion");
            return static_cast<T_UINT32>(value_._sint8);
        }
        case VT_SINT16: {
            if (value_._sint16 < 0) throw std::underflow_error("Negative SINT16 to UINT32 conversion");
            return static_cast<T_UINT32>(value_._sint16);
        }
        case VT_SINT32: {
            if (value_._sint32 < 0) throw std::underflow_error("Negative SINT32 to UINT32 conversion");
            return static_cast<T_UINT32>(value_._sint32);
        }
        case VT_SINT64: {
            if (value_._sint64 < 0) throw std::underflow_error("Negative SINT64 to UINT32 conversion");
            if (value_._sint64 > static_cast<T_SINT64>(std::numeric_limits<T_UINT32>::max()))
                throw std::overflow_error("SINT64 value too large for UINT32");
            return static_cast<T_UINT32>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_UINT32>(value_._uint8);
        case VT_UINT16: return static_cast<T_UINT32>(value_._uint16);
        case VT_UINT32: return value_._uint32;
        case VT_UINT64: {
            checkRange(value_._uint64,
                       static_cast<T_UINT64>(0),
                       static_cast<T_UINT64>(std::numeric_limits<T_UINT32>::max()));
            return static_cast<T_UINT32>(value_._uint64);
        }
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            checkRange(value_._real32,
                       static_cast<T_REAL32>(0),
                       static_cast<T_REAL32>(std::numeric_limits<T_UINT32>::max()));
            return static_cast<T_UINT32>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            checkRange(value_._real64,
                       static_cast<T_REAL64>(0),
                       static_cast<T_REAL64>(std::numeric_limits<T_UINT32>::max()));
            return static_cast<T_UINT32>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                return std::stoul(value_._string->str);
            } catch (...) {
                throw std::runtime_error("String to UINT32 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to UINT32");
    }
}

T_UINT64 VARIANT::getUINT64() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1 : 0;
        case VT_SINT8: {
            if (value_._sint8 < 0) throw std::underflow_error("Negative SINT8 to UINT64 conversion");
            return static_cast<T_UINT64>(value_._sint8);
        }
        case VT_SINT16: {
            if (value_._sint16 < 0) throw std::underflow_error("Negative SINT16 to UINT64 conversion");
            return static_cast<T_UINT64>(value_._sint16);
        }
        case VT_SINT32: {
            if (value_._sint32 < 0) throw std::underflow_error("Negative SINT32 to UINT64 conversion");
            return static_cast<T_UINT64>(value_._sint32);
        }
        case VT_SINT64: {
            if (value_._sint64 < 0) throw std::underflow_error("Negative SINT64 to UINT64 conversion");
            return static_cast<T_UINT64>(value_._sint64);
        }
        case VT_UINT8:  return static_cast<T_UINT64>(value_._uint8);
        case VT_UINT16: return static_cast<T_UINT64>(value_._uint16);
        case VT_UINT32: return static_cast<T_UINT64>(value_._uint32);
        case VT_UINT64: return value_._uint64;
        case VT_REAL32: {
            if (std::isnan(value_._real32)) throw std::domain_error("NaN conversion");
            if (value_._real32 < 0.0f) throw std::underflow_error("Negative REAL32 to UINT64 conversion");
            if (value_._real32 > static_cast<T_REAL32>(std::numeric_limits<T_UINT64>::max()))
                throw std::overflow_error("REAL32 value too large for UINT64");
            return static_cast<T_UINT64>(value_._real32);
        }
        case VT_REAL64: {
            if (std::isnan(value_._real64)) throw std::domain_error("NaN conversion");
            if (value_._real64 < 0.0) throw std::underflow_error("Negative REAL64 to UINT64 conversion");
            if (value_._real64 > static_cast<T_REAL64>(std::numeric_limits<T_UINT64>::max()))
                throw std::overflow_error("REAL64 value too large for UINT64");
            return static_cast<T_UINT64>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                return std::stoull(value_._string->str);
            } catch (...) {
                throw std::runtime_error("String to UINT64 conversion failed");
            }
        }
        case VT_NULL:   return 0;
        default:        throw std::runtime_error("Invalid type conversion to UINT64");
    }
}

T_REAL32 VARIANT::getREAL32() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1.0f : 0.0f;
        case VT_SINT8:  return static_cast<T_REAL32>(value_._sint8);
        case VT_SINT16: return static_cast<T_REAL32>(value_._sint16);
        case VT_SINT32: return static_cast<T_REAL32>(value_._sint32);
        case VT_SINT64: return static_cast<T_REAL32>(value_._sint64);
        case VT_UINT8:  return static_cast<T_REAL32>(value_._uint8);
        case VT_UINT16: return static_cast<T_REAL32>(value_._uint16);
        case VT_UINT32: return static_cast<T_REAL32>(value_._uint32);
        case VT_UINT64: return static_cast<T_REAL32>(value_._uint64);
        case VT_REAL32: return value_._real32;
        case VT_REAL64: {
            if (value_._real64 < -std::numeric_limits<T_REAL32>::max() ||
                value_._real64 > std::numeric_limits<T_REAL32>::max()) {
                throw std::overflow_error("REAL64 value out of range for REAL32");
            }
            return static_cast<T_REAL32>(value_._real64);
        }
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                return std::stof(value_._string->str);
            } catch (...) {
                throw std::runtime_error("String to REAL32 conversion failed");
            }
        }
        case VT_NULL:   return 0.0f;
        default:        throw std::runtime_error("Invalid type conversion to REAL32");
    }
}

T_REAL64 VARIANT::getREAL64() const {
    switch (type_) {
        case VT_BOOL:   return value_._bool ? 1.0 : 0.0;
        case VT_SINT8:  return static_cast<T_REAL64>(value_._sint8);
        case VT_SINT16: return static_cast<T_REAL64>(value_._sint16);
        case VT_SINT32: return static_cast<T_REAL64>(value_._sint32);
        case VT_SINT64: return static_cast<T_REAL64>(value_._sint64);
        case VT_UINT8:  return static_cast<T_REAL64>(value_._uint8);
        case VT_UINT16: return static_cast<T_REAL64>(value_._uint16);
        case VT_UINT32: return static_cast<T_REAL64>(value_._uint32);
        case VT_UINT64: return static_cast<T_REAL64>(value_._uint64);
        case VT_REAL32: return static_cast<T_REAL64>(value_._real32);
        case VT_REAL64: return value_._real64;
        case VT_STRING: {
            std::lock_guard lock(value_._string->mtx);
            try {
                return std::stod(value_._string->str);
            } catch (...) {
                throw std::runtime_error("String to REAL64 conversion failed");
            }
        }
        case VT_NULL:   return 0.0;
        default:        throw std::runtime_error("Invalid type conversion to REAL64");
    }
}

T_STRING VARIANT::getSTRING() const {
    if (type_ == VT_STRING) {
        std::lock_guard lock(value_._string->mtx);
        return value_._string->str;
    }

    std::ostringstream oss;
    switch (type_) {
        case VT_BOOL:   oss << (value_._bool ? "true" : "false"); break;
        case VT_SINT8:  oss << static_cast<int>(value_._sint8); break;
        case VT_SINT16: oss << value_._sint16; break;
        case VT_SINT32: oss << value_._sint32; break;
        case VT_SINT64: oss << value_._sint64; break;
        case VT_UINT8:  oss << static_cast<unsigned>(value_._uint8); break;
        case VT_UINT16: oss << value_._uint16; break;
        case VT_UINT32: oss << value_._uint32; break;
        case VT_UINT64: oss << value_._uint64; break;
        case VT_REAL32: oss << std::setprecision(9) << value_._real32; break;
        case VT_REAL64: oss << std::setprecision(17) << value_._real64; break;
        case VT_NULL:   oss << "null"; break;
        default:        oss << "invalid";
    }
    return oss.str();
}
