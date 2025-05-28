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
#include "vector.h"
#include "address.h"
#include "registry.h"

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

////Bytes
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
extern Registry registry;
/*
class BindingManager {
private:
    Registry& _reg; // Ссылка на экземпляр Registry

    struct Binding {
        Address addr{};
        void* iecVar{};
        Binding(Address adr, void *dat): addr(adr), iecVar(dat) {}
    };

    std::vector<Binding> bindings_;

public:
    explicit BindingManager(Registry& reg) : _reg(reg) {}

    static BindingManager& instance() {
        static Registry defaultRegistry;
        static BindingManager inst(defaultRegistry);
        return inst;
    }

    void bind(const std::string& regNotation, void* iecVar) {
        Address addr = Address::fromString(regNotation);
        bindings_.emplace_back(addr, iecVar);
    }

    void updateToIec() {
        for (auto& binding : bindings_) {
            updateVariable(binding.addr, binding.iecVar, false);
        }
    }

    void updateFromIec() {
        for (auto& binding : bindings_) {
            updateVariable(binding.addr, binding.iecVar, true);
        }
    }

private:
    template<Registry::Category CAT, typename T>
    void handleType(const Address& addr, void* iecVar, bool toRegistry) {
        if (toRegistry) {
            _reg.get<T, CAT>(addr.offset()) = *static_cast<T*>(iecVar);
        } else {
            *static_cast<T*>(iecVar) = _reg.get<T, CAT>(addr.offset());
        }
    }

    void updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
        using Cat = Registry::Category;

        switch(addr.category()) {
            case Address::INPUT:
                processWithCategory<Cat::INPUT>(addr, iecVar, toRegistry);
                break;
            case Address::OUTPUT:
                processWithCategory<Cat::OUTPUT>(addr, iecVar, toRegistry);
                break;
            case Address::MEMORY:
                processWithCategory<Cat::MEMORY>(addr, iecVar, toRegistry);
                break;
            case Address::SPECIAL:
                processWithCategory<Cat::SPECIAL>(addr, iecVar, toRegistry);
                break;
        }
    }

    template<Registry::Category CAT>
    void processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
        switch(addr.datatype()) {
            case Address::TYPE_BIT:
                if (toRegistry) {
                    _reg.get<bool, CAT>(addr.offset())[addr.bitpos()] = *static_cast<bool*>(iecVar);
                } else {
                    *static_cast<bool*>(iecVar) = _reg.get<bool, CAT>(addr.offset())[addr.bitpos()];
                }
                break;
            case Address::TYPE_BYTE:
                handleType<CAT, uint8_t>(addr, iecVar, toRegistry);
                break;
            case Address::TYPE_WORD:
                handleType<CAT, uint16_t>(addr, iecVar, toRegistry);
                break;
            case Address::TYPE_DWORD:
                handleType<CAT, uint32_t>(addr, iecVar, toRegistry);
                break;
            case Address::TYPE_LWORD:
                handleType<CAT, uint64_t>(addr, iecVar, toRegistry);
                break;
            case Address::TYPE_REAL:
                handleType<CAT, float>(addr, iecVar, toRegistry);
                break;
            case Address::TYPE_LREAL:
                handleType<CAT, double>(addr, iecVar, toRegistry);
                break;
        }
    }
};
*/
//=============================================
//class BindingManager {
//public:
//    static BindingManager& instance() {
//        static BindingManager inst;
//        return inst;
//    }
//
//    void bind(const string& regNotation, void* iecVar) {
//        Address addr = Address::fromString(regNotation);
//        bindings_.emplace_back(addr, iecVar);
//    }
//
//    void updateToIec() {
//        for (auto& binding : bindings_) {
//            updateVariable(binding.addr, binding.iecVar, false);
//        }
//    }
//
//    void updateFromIec() {
//        for (auto& binding : bindings_) {
//            updateVariable(binding.addr, binding.iecVar, true);
//        }
//    }
//
//private:
//    struct Binding {
//        Address addr;
//        void* iecVar;
//    };
//
//    vector<Binding> bindings_;
//
//    void updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
//        switch(addr.datatype()) {
//            case Address::TYPE_BIT:
//                handleBit(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_BYTE:
//                handleType<uint8_t>(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_WORD:
//                handleType<uint16_t>(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_DWORD:
//                handleType<uint32_t>(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_LWORD:
//                handleType<uint64_t>(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_REAL:
//                handleType<float>(addr, iecVar, toRegistry);
//                break;
//            case Address::TYPE_LREAL:
//                handleType<double>(addr, iecVar, toRegistry);
//                break;
//        }
//    }
//
//    void handleBit(const Address& addr, void* iecVar, bool toRegistry) {
//        bool value = global_registry.get<bool>(addr)[addr.bitpos()];
//        *static_cast<bool*>(iecVar) = value;
//    }
//
//    template<typename T>
//    void handleType(const Address& addr, void* iecVar, bool toRegistry) {
//        if (toRegistry) {
//            global_registry.get<T>(addr) = *static_cast<T*>(iecVar);
//        } else {
//            *static_cast<T*>(iecVar) = global_registry.get<T>(addr);
//        }
//    }
//};

//
//// Алиасы для удобства
//using Category = Address::Category;
//using DataType = Address::DataType;
//
//extern Registry _reg;
//
//// Общий прокси-класс для регистров
//template<typename T, Category CAT>
//class RegisterProxy {
//public:
//    class BitReference {
//        uint64_t offset_;
//        uint8_t bit_;
//    public:
//        BitReference(uint64_t offset, uint8_t bit) : offset_(offset), bit_(bit) {}
//        operator bool() const { return _reg.template get<T, CAT>(offset_)[bit_];}
//
//        BitReference& operator=(bool value) {
//            _reg.template get<T, CAT>(offset_)[bit_] = value;
//            return *this;
//        }
//    };
//
//    RegisterProxy() = default;
//
//    typename Registry::template Accessor<T, CAT> operator[](uint64_t offset) {
//        return _reg.template get<T, CAT>(offset);
//    }
//
//    BitReference operator()(uint64_t offset, uint8_t bit) {
//        return BitReference(offset, bit);
//    }
//};
//
//// Специализации для конкретных типов регистров
//using _IX = RegisterProxy<bool, Category::INPUT>;
//using _QX = RegisterProxy<bool, Category::OUTPUT>;
//using _MX = RegisterProxy<bool, Category::MEMORY>;
//
//using _IW = RegisterProxy<uint16_t, Category::INPUT>;
//using _QW = RegisterProxy<uint16_t, Category::OUTPUT>;
//using _MW = RegisterProxy<uint16_t, Category::MEMORY>;
//
//using _ID = RegisterProxy<uint32_t, Category::INPUT>;
//using _QD = RegisterProxy<uint32_t, Category::OUTPUT>;
//using _MD = RegisterProxy<uint32_t, Category::MEMORY>;
////...

// Глобальные экземпляры
//inline _IX IX;
//inline _QX QX;
//inline _MX MX;
//inline _IW IW;
//inline _QW QW;
//inline _MW MW;
//inline _ID ID;
//inline _QD QD;
//inline _MD MD;

//// ----------------------------------------------------------------------------
//// PLC Register Types
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
