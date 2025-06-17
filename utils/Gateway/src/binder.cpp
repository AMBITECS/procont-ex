#include "binder.h"
#include "proxy.h"
#include "reg_server.h"

std::unique_ptr<Binder> Binder::_instance;

Binder& Binder::instance() {
    if (!_instance) {
        _instance = std::unique_ptr<Binder>(new Binder());
    }
    return *_instance;
}

// ----------------------------------------------------------------------------
Binder::Binder(): _regClient(RegServer::instance().createClient("Binder")) {}

void Binder::bind(const std::string& regNotation, void* iecVar, VAR_TYPE type) {
    Address addr = Address::of(regNotation);
    binds.emplace_back(Binding{addr, iecVar});
}

namespace detail {
    VARIANT raw2var(uint64_t rawValue, Address::Type addrType) {
        switch (addrType) {
            case Address::TYPE_BIT:     // return VARIANT(rawValue != 0);
            case Address::TYPE_BYTE:    // return VARIANT(static_cast<uint8_t>(rawValue));
            case Address::TYPE_WORD:    // return VARIANT(static_cast<uint16_t>(rawValue));
            case Address::TYPE_DWORD:   // return VARIANT(static_cast<uint32_t>(rawValue));

            // Единое преобразование для всех целочисленных типов
            case Address::TYPE_LWORD:   return VARIANT(rawValue);

            // Отдельное преобразование для всех REAL
            case Address::TYPE_REAL:
            {
                float fValue;
                memcpy(&fValue, &rawValue, sizeof(float));
                return VARIANT(fValue);
            }

            case Address::TYPE_LREAL:
            {
                double dValue;
                memcpy(&dValue, &rawValue, sizeof(double));
                return VARIANT(dValue);
            }
            default: throw std::runtime_error("Unsupported register type");
        }
    }

    uint64_t var2raw(const VARIANT& var, Address::Type addrType) {
        switch (addrType) {
            case Address::TYPE_BIT:    return var.getBOOL() ? 1 : 0;
            case Address::TYPE_BYTE:   return var.getUINT8();
            case Address::TYPE_WORD:   return var.getUINT16();
            case Address::TYPE_DWORD:  return var.getUINT32();
            case Address::TYPE_LWORD:  return var.getUINT64();

            // Отдельное преобразование для всех REAL
            case Address::TYPE_REAL:
            {
                float fValue = var.getREAL32();
                uint32_t tmp;
                memcpy(&tmp, &fValue, sizeof(float));
                return tmp;
            }

            case Address::TYPE_LREAL:
            {
                double dValue = var.getREAL64();
                uint64_t tmp;
                memcpy(&tmp, &dValue, sizeof(double));
                return tmp;
            }
            default: throw std::runtime_error("Unsupported register type");
        }
    }
} // detail

void Binder::updateToIec() {
    for (auto& [addr, pvar, type] : binds) {
        try {
            uint64_t rawValue = _regClient->read(addr);
            VARIANT regValue = detail::raw2var(rawValue, addr.type());

            switch (type) {
                case VT_BOOL:   *static_cast<bool*>(pvar)     = regValue.getBOOL();   break;
                case VT_SINT8:  *static_cast<int8_t*>(pvar)   = regValue.getSINT8();  break;
                case VT_SINT16: *static_cast<int16_t*>(pvar)  = regValue.getSINT16(); break;
                case VT_SINT32: *static_cast<int32_t*>(pvar)  = regValue.getSINT32(); break;
                case VT_SINT64: *static_cast<int64_t*>(pvar)  = regValue.getSINT64(); break;
                case VT_UINT8:  *static_cast<uint8_t*>(pvar)  = regValue.getUINT8();  break;
                case VT_UINT16: *static_cast<uint16_t*>(pvar) = regValue.getUINT16(); break;
                case VT_UINT32: *static_cast<uint32_t*>(pvar) = regValue.getUINT32(); break;
                case VT_UINT64: *static_cast<uint64_t*>(pvar) = regValue.getUINT64(); break;
                case VT_REAL32: *static_cast<float*>(pvar)    = regValue.getREAL32(); break;
                case VT_REAL64: *static_cast<double*>(pvar)   = regValue.getREAL64(); break;
                case VT_STRING: throw std::runtime_error("String type not supported in binding");
                case VT_NULL:   break;
                default:        throw std::runtime_error("Unsupported target type");
            }
        } catch (const std::exception& e) {
            // Логирование ошибки
            throw std::runtime_error(std::string("Failed to update from IEC: ") + e.what());
        }
    }
}

void Binder::updateFromIec() {
    for (auto& [addr, pvar, type] : binds) {
        try {
            VARIANT varValue;

            switch (type) {
                case VT_BOOL:   varValue = VARIANT(*static_cast<bool*>(pvar));     break;
                case VT_SINT8:  varValue = VARIANT(*static_cast<int8_t*>(pvar));   break;
                case VT_SINT16: varValue = VARIANT(*static_cast<int16_t*>(pvar));  break;
                case VT_SINT32: varValue = VARIANT(*static_cast<int32_t*>(pvar));  break;
                case VT_SINT64: varValue = VARIANT(*static_cast<int64_t*>(pvar));  break;
                case VT_UINT8:  varValue = VARIANT(*static_cast<uint8_t*>(pvar));  break;
                case VT_UINT16: varValue = VARIANT(*static_cast<uint16_t*>(pvar)); break;
                case VT_UINT32: varValue = VARIANT(*static_cast<uint32_t*>(pvar)); break;
                case VT_UINT64: varValue = VARIANT(*static_cast<uint64_t*>(pvar)); break;
                case VT_REAL32: varValue = VARIANT(*static_cast<float*>(pvar));    break;
                case VT_REAL64: varValue = VARIANT(*static_cast<double*>(pvar));   break;
                case VT_STRING: throw std::runtime_error("String type not supported in binding");
                case VT_NULL:   continue;
                default:       throw std::runtime_error("Unsupported target type");
            }

            uint64_t rawValue = detail::var2raw(varValue, addr.type());
            _regClient->write(addr, rawValue);

        } catch (const std::exception& e) {
            // Логирование ошибки
            throw std::runtime_error(std::string("Failed to update to IEC: ") + e.what());
        }
    }
}

//void Binder::updateToIec() {
//    for (auto& [addr, pvar, type] : binds) {
//        uint64_t rawValue = _regClient->read(addr);
//        VARIANT regValue;
//
//        // Сначала преобразуем rawValue в тип регистра
//        switch (addr.type()) {
//            case Address::TYPE_BIT:    regValue = VARIANT(rawValue != 0); break;
//            case Address::TYPE_BYTE:   regValue = VARIANT(static_cast<uint8_t>(rawValue)); break;
//            case Address::TYPE_WORD:   regValue = VARIANT(static_cast<uint16_t>(rawValue)); break;
//            case Address::TYPE_DWORD:  regValue = VARIANT(static_cast<uint32_t>(rawValue)); break;
//            case Address::TYPE_LWORD:  regValue = VARIANT(rawValue); break;
//            case Address::TYPE_REAL: {
//                float fValue;
//                memcpy(&fValue, &rawValue, sizeof(float));
//                regValue = VARIANT(fValue);
//                break;
//            }
//            case Address::TYPE_LREAL: {
//                double dValue;
//                memcpy(&dValue, &rawValue, sizeof(double));
//                regValue = VARIANT(dValue);
//                break;
//            }
//            default: throw std::runtime_error("Unsupported register type");
//        }
//
//        // Затем преобразуем к целевому типу и записываем
//        try {
//            switch (type) {
//                case VT_BOOL:   *static_cast<bool*>(pvar)     = regValue.getBOOL();   break;
//                case VT_SINT8:  *static_cast<int8_t*>(pvar)   = regValue.getSINT8();  break;
//                case VT_SINT16: *static_cast<int16_t*>(pvar)  = regValue.getSINT16(); break;
//                case VT_SINT32: *static_cast<int32_t*>(pvar)  = regValue.getSINT32(); break;
//                case VT_SINT64: *static_cast<int64_t*>(pvar)  = regValue.getSINT64(); break;
//                case VT_UINT8:  *static_cast<uint8_t*>(pvar)  = regValue.getUINT8();  break;
//                case VT_UINT16: *static_cast<uint16_t*>(pvar) = regValue.getUINT16(); break;
//                case VT_UINT32: *static_cast<uint32_t*>(pvar) = regValue.getUINT32(); break;
//                case VT_UINT64: *static_cast<uint64_t*>(pvar) = regValue.getUINT64(); break;
//                case VT_REAL32: *static_cast<float*>(pvar)    = regValue.getREAL32(); break;
//                case VT_REAL64: *static_cast<double*>(pvar)   = regValue.getREAL64(); break;
//                case VT_STRING: throw std::runtime_error("String type not supported in this binding");
//                case VT_NULL:   break; // Ничего не делаем для NULL типа
//                default:        throw std::runtime_error("Unsupported target type");
//            }
//        } catch (const std::exception& e) {
//            throw std::runtime_error(std::string("Conversion failed: ") + e.what());
//        }
//    }
//}
//
//void Binder::updateFromIec() {
//    for (auto& [addr, pvar, type] : binds) {
//        VARIANT varValue;
//
//        // Сначала читаем значение в VARIANT согласно целевому типу
//        try {
//            switch (type) {
//                case VT_BOOL:   varValue = VARIANT(*static_cast<bool*>(pvar)); break;
//                case VT_SINT8:  varValue = VARIANT(*static_cast<int8_t*>(pvar)); break;
//                case VT_SINT16: varValue = VARIANT(*static_cast<int16_t*>(pvar)); break;
//                case VT_SINT32: varValue = VARIANT(*static_cast<int32_t*>(pvar)); break;
//                case VT_SINT64: varValue = VARIANT(*static_cast<int64_t*>(pvar)); break;
//                case VT_UINT8:  varValue = VARIANT(*static_cast<uint8_t*>(pvar)); break;
//                case VT_UINT16: varValue = VARIANT(*static_cast<uint16_t*>(pvar)); break;
//                case VT_UINT32: varValue = VARIANT(*static_cast<uint32_t*>(pvar)); break;
//                case VT_UINT64: varValue = VARIANT(*static_cast<uint64_t*>(pvar)); break;
//                case VT_REAL32: varValue = VARIANT(*static_cast<float*>(pvar)); break;
//                case VT_REAL64: varValue = VARIANT(*static_cast<double*>(pvar)); break;
//                case VT_STRING: throw std::runtime_error("String type not supported in this binding");
//                case VT_NULL:   continue; // Пропускаем NULL тип
//                default:        throw std::runtime_error("Unsupported target type");
//            }
//        } catch (const std::exception& e) {
//            throw std::runtime_error(std::string("Value reading failed: ") + e.what());
//        }
//
//        // Затем преобразуем к типу регистра и записываем
//        uint64_t rawValue = 0;
//        switch (addr.type()) {
//            case Address::TYPE_BIT:   rawValue = varValue.getBOOL() ? 1 : 0; break;
//            case Address::TYPE_BYTE:  rawValue = varValue.getUINT8(); break;
//            case Address::TYPE_WORD:  rawValue = varValue.getUINT16(); break;
//            case Address::TYPE_DWORD: rawValue = varValue.getUINT32(); break;
//            case Address::TYPE_LWORD: rawValue = varValue.getUINT64(); break;
//            case Address::TYPE_REAL: {
//                float fValue = varValue.getREAL32();
//                memcpy(&rawValue, &fValue, sizeof(float));
//                break;
//            }
//            case Address::TYPE_LREAL: {
//                double dValue = varValue.getREAL64();
//                memcpy(&rawValue, &dValue, sizeof(double));
//                break;
//            }
//            default: throw std::runtime_error("Unsupported register type");
//        }
//
//        _regClient->write(addr, rawValue);
//    }
//}

//void Binder::updateToIec() {
//    for (auto& [addr, pvar, type] : binds) {
//        uint64_t rawValue = _regClient->read(addr);
//
//        switch (addr.type()) {
//            case Address::TYPE_BIT:    *static_cast<bool*>(pvar)   = rawValue != 0; break;
//            case Address::TYPE_BYTE:   *static_cast<uint8_t*>(pvar)  = static_cast<uint8_t>(rawValue); break;
//            case Address::TYPE_WORD:   *static_cast<uint16_t*>(pvar) = static_cast<uint16_t>(rawValue); break;
//            case Address::TYPE_DWORD:  *static_cast<uint32_t*>(pvar) = static_cast<uint32_t>(rawValue); break;
//            case Address::TYPE_LWORD:  *static_cast<uint64_t*>(pvar) = rawValue; break;
//            case Address::TYPE_REAL:   memcpy(pvar, &rawValue, sizeof(float)); break;
//            case Address::TYPE_LREAL:  memcpy(pvar, &rawValue, sizeof(double)); break;
//            default: throw std::runtime_error("Unsupported type");
//        }
//    }
//}
//
//void Binder::updateFromIec() {
//    for (auto& [addr, pvar, type] : binds) {
//        uint64_t rawValue = 0;
//
//        switch (addr.type()) {
//            case Address::TYPE_BIT:    rawValue = *static_cast<bool*>(pvar); break;
//            case Address::TYPE_BYTE:   rawValue = *static_cast<uint8_t*>(pvar); break;
//            case Address::TYPE_WORD:   rawValue = *static_cast<uint16_t*>(pvar); break;
//            case Address::TYPE_DWORD:  rawValue = *static_cast<uint32_t*>(pvar); break;
//            case Address::TYPE_LWORD:  rawValue = *static_cast<uint64_t*>(pvar); break;
//            case Address::TYPE_REAL:   memcpy(&rawValue, pvar, sizeof(float)); break;
//            case Address::TYPE_LREAL:  memcpy(&rawValue, pvar, sizeof(double)); break;
//            default: throw std::runtime_error("Unsupported type");
//        }
//
//        _regClient->write(addr, rawValue);
//    }
//}
