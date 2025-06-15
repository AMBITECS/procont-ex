#include "gateway.h"
#include "reg_server.h"

RegClient::RegClient(std::string name): name_(std::move(name)) {}

RegClient::~RegClient() {
    subscriptions_.clear();
    RegServer::instance().removeClient(name_);
}

void RegClient::setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) {
    data_handler_ = std::move(handler);
}

void RegClient::subscribe(const std::vector<RegItem>& items) {
    for (const auto& item : items) {
        subscriptions_[item.addr] = item.key;
    }
}

// Проверка изменений и уведомление клиента
void RegClient::update() {
    if (!data_handler_) return;

    std::vector<OnDataChange> changes;

    for (const auto& subscription : subscriptions_) {
        const auto& addr = subscription.first;      // Address
        const auto& key = subscription.second;  // uint64_t

        // Проверка на изменение значения по адресу
        bool changed = [this, &addr]() {
            switch(addr.category()) {
                case Registry::Category::INPUT:   return checkChanged<Registry::Category::INPUT>  (addr);
                case Registry::Category::OUTPUT:  return checkChanged<Registry::Category::OUTPUT> (addr);
                case Registry::Category::MEMORY:  return checkChanged<Registry::Category::MEMORY> (addr);
                case Registry::Category::SPECIAL: return checkChanged<Registry::Category::SPECIAL>(addr);
                default: return false;
            }
        }();

        // Если регистр изменился ->
        if (changed) {
            // Получаем сырое значение
            uint64_t value = [this, &addr]() {
                switch(addr.category()) {
                    case Registry::Category::INPUT:   return getValue<Registry::Category::INPUT>  (addr);
                    case Registry::Category::OUTPUT:  return getValue<Registry::Category::OUTPUT> (addr);
                    case Registry::Category::MEMORY:  return getValue<Registry::Category::MEMORY> (addr);
                    case Registry::Category::SPECIAL: return getValue<Registry::Category::SPECIAL>(addr);
                    default: return uint64_t{0};
                }
            }();

            // Кладём в список изменений
            changes.push_back({key, value});
        }
    }

    if (!changes.empty()) {
        data_handler_(changes);
    }
}

void RegClient::read(std::vector<ItemData>& items) {
    for (auto& item : items) {
        const auto& addr = item.addr;
        uint64_t value = [this, &addr]() {
            switch(addr.category()) {
                case Registry::Category::INPUT:   return getValue<Registry::Category::INPUT>(addr);
                case Registry::Category::OUTPUT:  return getValue<Registry::Category::OUTPUT>(addr);
                case Registry::Category::MEMORY:  return getValue<Registry::Category::MEMORY>(addr);
                case Registry::Category::SPECIAL: return getValue<Registry::Category::SPECIAL>(addr);
                default: return uint64_t{0};
            }
        }();

        // Приводим к не-const ссылке для модификации данных
        item.data = value;
    }
}

void RegClient::write(const std::vector<ItemData>& items) {
    for (const auto& item : items) {
        const auto& addr = item.addr;
        switch(addr.category()) {
            case Registry::Category::INPUT:
                setValue<Registry::Category::INPUT>(addr, item.data);
                break;
            case Registry::Category::OUTPUT:
                setValue<Registry::Category::OUTPUT>(addr, item.data);
                break;
            case Registry::Category::MEMORY:
                setValue<Registry::Category::MEMORY>(addr, item.data);
                break;
            case Registry::Category::SPECIAL:
                setValue<Registry::Category::SPECIAL>(addr, item.data);
                break;
            default:
                throw std::runtime_error("Unknown register category");
        }
    }
}

//void RegClient::write(const std::vector<ItemData>& items) {
//    for (const auto& item : items) {
//        const auto& addr = item.addr;
//
//        // Сырое значение
//        const uint64_t value = item.data;
//
//        switch(addr.type()) {
//            case Address::TYPE_BIT:   { bool v = value != 0; updateVariable(addr, &v, true); break; }
//            case Address::TYPE_BYTE:  { auto v = static_cast<uint8_t>(value); updateVariable(addr, &v, true); break;  }
//            case Address::TYPE_WORD:  { auto v = static_cast<uint16_t>(value); updateVariable(addr, &v, true); break; }
//            case Address::TYPE_DWORD: { auto v = static_cast<uint32_t>(value); updateVariable(addr, &v, true); break; }
//            case Address::TYPE_LWORD: { auto v = static_cast<uint64_t>(value); updateVariable(addr, &v, true); break; }
//            case Address::TYPE_REAL:  {
//                float v;
//                auto tmp = static_cast<uint32_t>(value);
//                memcpy(&v, &tmp, sizeof(float));
//                updateVariable(addr, &v, true);
//                break;
//            }
//            case Address::TYPE_LREAL: {
//                double v;
//                auto tmp = static_cast<uint64_t>(value);
//                memcpy(&v, &tmp, sizeof(double));
//                updateVariable(addr, &v, true);
//                break;
//            }
//            default: throw std::runtime_error("Unknown data type");
//        }
//    }
//}

// ------------------------------------------
template<Registry::Category CAT>
uint64_t RegClient::getValue(const Address& addr) { return ::getProxyValue<CAT>(addr); }

template<Registry::Category CAT>
void RegClient::setValue(const Address& addr, uint64_t value) { ::setProxyValue<CAT>(addr, value); }

template<Registry::Category CAT>
bool RegClient::checkChanged(const Address& addr) { return ::isProxyChanged<CAT>(addr); }

//// ------------------------------------------
//void RegClient::updateVariable(const Address& addr, void* iecVar, bool toRegistry) {
//    using Cat = Registry::Category;
//    switch(addr.category()) {
//        case Cat::INPUT:   processWithCategory<Cat::INPUT>  (addr, iecVar, toRegistry); break;
//        case Cat::OUTPUT:  processWithCategory<Cat::OUTPUT> (addr, iecVar, toRegistry); break;
//        case Cat::MEMORY:  processWithCategory<Cat::MEMORY> (addr, iecVar, toRegistry); break;
//        case Cat::SPECIAL: processWithCategory<Cat::SPECIAL>(addr, iecVar, toRegistry); break;
//        default: throw std::runtime_error("Unknown register category");
//    }
//}

//template<Registry::Category CAT>
//void RegClient::processWithCategory(const Address& addr, void* iecVar, bool toRegistry) {
//    switch(addr.type()) {
//        case Address::TYPE_BIT:   handleType<bool    , CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_BYTE:  handleType<uint8_t , CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_WORD:  handleType<uint16_t, CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_DWORD: handleType<uint32_t, CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_LWORD: handleType<uint64_t, CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_REAL:  handleType<float   , CAT> (addr, iecVar, toRegistry); break;
//        case Address::TYPE_LREAL: handleType<double  , CAT> (addr, iecVar, toRegistry); break;
//        default: throw std::runtime_error("Unknown data type");
//    }
//}

//template<typename T, Registry::Category CAT>
//void RegClient::handleType(const Address &addr, void *iecVar, bool toRegistry) {
//    auto& proxy = getProxy<T, CAT>();
//    const size_t index = addr.index();
//    if (toRegistry) {
//        proxy[index] = *static_cast<T*>(iecVar);
//    } else {
//        *static_cast<T*>(iecVar) = proxy[index];
//    }
//}

//// Вспомогательная структура выявления ошибок компиляции
//template<typename T>
//struct TypeNotSupported {
//    static_assert(sizeof(T) == 0, "Type not supported for this category");
//};
//
//template<typename T, Registry::Category CAT>
//auto& RegClient::getProxy() {
//    if constexpr (CAT == Registry::Category::INPUT) {
//        if      constexpr (std::is_same_v<T, bool>)     return ::IX;
//        else if constexpr (std::is_same_v<T, uint8_t>)  return ::IB;
//        else if constexpr (std::is_same_v<T, uint16_t>) return ::IW;
//        else if constexpr (std::is_same_v<T, uint32_t>) return ::ID;
//        else if constexpr (std::is_same_v<T, uint64_t>) return ::IL;
//        else if constexpr (std::is_same_v<T, float>)    return ::IF;
//        else if constexpr (std::is_same_v<T, double>)   return ::IE;
//        else return TypeNotSupported<T>::value;
//    }
//    else if constexpr (CAT == Registry::Category::OUTPUT) {
//        if      constexpr (std::is_same_v<T, bool>)     return ::QX;
//        else if constexpr (std::is_same_v<T, uint8_t>)  return ::QB;
//        else if constexpr (std::is_same_v<T, uint16_t>) return ::QW;
//        else if constexpr (std::is_same_v<T, uint32_t>) return ::QD;
//        else if constexpr (std::is_same_v<T, uint64_t>) return ::QL;
//        else if constexpr (std::is_same_v<T, float>)    return ::QF;
//        else if constexpr (std::is_same_v<T, double>)   return ::QE;
//        else return TypeNotSupported<T>::value;
//    }
//    else if constexpr (CAT == Registry::Category::MEMORY) {
//        if      constexpr (std::is_same_v<T, bool>)     return ::MX;
//        else if constexpr (std::is_same_v<T, uint8_t>)  return ::MB;
//        else if constexpr (std::is_same_v<T, uint16_t>) return ::MW;
//        else if constexpr (std::is_same_v<T, uint32_t>) return ::MD;
//        else if constexpr (std::is_same_v<T, uint64_t>) return ::ML;
//        else if constexpr (std::is_same_v<T, float>)    return ::MF;
//        else if constexpr (std::is_same_v<T, double>)   return ::ME;
//        else return TypeNotSupported<T>::value;
//    }
//    else if constexpr (CAT == Registry::Category::SPECIAL) {
//        if      constexpr (std::is_same_v<T, bool>)     return ::SX;
//        else if constexpr (std::is_same_v<T, uint8_t>)  return ::SB;
//        else if constexpr (std::is_same_v<T, uint16_t>) return ::SW;
//        else if constexpr (std::is_same_v<T, uint32_t>) return ::SD;
//        else if constexpr (std::is_same_v<T, uint64_t>) return ::SL;
//        else if constexpr (std::is_same_v<T, float>)    return ::SF;
//        else if constexpr (std::is_same_v<T, double>)   return ::SE;
//        else return TypeNotSupported<T>::value;
//    }
//    else {
//        return TypeNotSupported<T>::value;
//    }
//}
