#include "reg_server.h"
#include "gateway.h"

RegClient::RegClient(Registry& registry, std::string name)
        : registry_(registry), name_(std::move(name)) {}

RegClient::~RegClient() {
    exit();
}

void RegClient::init(std::function<void(const std::vector<ItemData>&)> handler) {
    data_handler_ = std::move(handler);
}

void RegClient::subscribe(const std::vector<RegItem>& items) {
    for (const auto& item : items) {
        subscriptions_[item.addr] = item.key;
    }
}

void RegClient::activate() {
    if (!is_active_) {
        is_active_ = true;
        // Здесь будет логика активации в Registry
    }
}

void RegClient::deactivate() {
    if (is_active_) {
        is_active_ = false;
        // Здесь будет логика деактивации в Registry
    }
}

// Проверка изменений и уведомление клиента
void RegClient::update() {
    if (!is_active_ || !data_handler_) return;

    std::vector<ItemData> changes;

    for (const auto& [addr, key] : subscriptions_)
    {
        // проверка на изменение
        if ([this, &addr]() {
            switch(addr.category()) {
                case Registry::Category::INPUT:   return checkChanged<Registry::Category::INPUT>(addr);
                case Registry::Category::OUTPUT:  return checkChanged<Registry::Category::OUTPUT>(addr);
                case Registry::Category::MEMORY:  return checkChanged<Registry::Category::MEMORY>(addr);
                case Registry::Category::SPECIAL: return checkChanged<Registry::Category::SPECIAL>(addr);
                default: return false;
            }
        }()) {
            // если изменился - кладём в вектор
            changes.push_back({
                key,
                [this, &addr]() {
                    switch(addr.category()) {
                        case Registry::Category::INPUT:   return getValue<Registry::Category::INPUT>(addr);
                        case Registry::Category::OUTPUT:  return getValue<Registry::Category::OUTPUT>(addr);
                        case Registry::Category::MEMORY:  return getValue<Registry::Category::MEMORY>(addr);
                        case Registry::Category::SPECIAL: return getValue<Registry::Category::SPECIAL>(addr);
                        default: return uint64_t{0};
                    }
                }()
            });
        }
    }

    if (!changes.empty()) {
        data_handler_(changes);
    }
}

void RegClient::exit() {
    deactivate();
    subscriptions_.clear();
    RegServer::instance().removeClient(name_);
}

// Получение инстанцированного proxy-типа
template<typename T, Registry::Category CATEGORY>
auto& RegClient::getProxy() {
    if constexpr (CATEGORY == Registry::Category::INPUT) {
        if constexpr (std::is_same_v<T, bool>)          return ::IX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::IB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::IW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::ID;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::IL;
        else if constexpr (std::is_same_v<T, float>)    return ::IF;
        else if constexpr (std::is_same_v<T, double>)   return ::IE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for INPUT category");
        }
    } else if constexpr (CATEGORY == Registry::Category::OUTPUT) {
        if constexpr (std::is_same_v<T, bool>)          return ::QX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::QB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::QW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::QD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::QL;
        else if constexpr (std::is_same_v<T, float>)    return ::QF;
        else if constexpr (std::is_same_v<T, double>)   return ::QE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for OUTPUT category");
        }
    } else if constexpr (CATEGORY == Registry::Category::MEMORY) {
        if constexpr (std::is_same_v<T, bool>)          return ::MX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::MB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::MW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::MD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::ML;
        else if constexpr (std::is_same_v<T, float>)    return ::MF;
        else if constexpr (std::is_same_v<T, double>)   return ::ME;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for MEMORY category");
        }
    } else if constexpr (CATEGORY == Registry::Category::SPECIAL) {
        if constexpr (std::is_same_v<T, bool>) return ::SX;
        else if constexpr (std::is_same_v<T, uint8_t>)  return ::SB;
        else if constexpr (std::is_same_v<T, uint16_t>) return ::SW;
        else if constexpr (std::is_same_v<T, uint32_t>) return ::SD;
        else if constexpr (std::is_same_v<T, uint64_t>) return ::SL;
        else if constexpr (std::is_same_v<T, float>)    return ::SF;
        else if constexpr (std::is_same_v<T, double>)   return ::SE;
        else {
            static_assert(!std::is_same_v<T, T>, "Unsupported type for SPECIAL category");
        }
    } else {
        static_assert(sizeof(CATEGORY) == 0, "Unknown register category");
    }
}

template<Registry::Category CAT>
uint64_t RegClient::getValue(const Address& addr) {
    switch(addr.type()) {
        case Address::TYPE_BIT:    return getProxy<bool,     CAT>()[addr.index()] ? 1 : 0;
        case Address::TYPE_BYTE:   return getProxy<uint8_t,  CAT>()[addr.index()];
        case Address::TYPE_WORD:   return getProxy<uint16_t, CAT>()[addr.index()];
        case Address::TYPE_DWORD:  return getProxy<uint32_t, CAT>()[addr.index()];
        case Address::TYPE_LWORD:  return getProxy<uint64_t, CAT>()[addr.index()];
        case Address::TYPE_REAL:   {
            float val = getProxy<float, CAT>()[addr.index()];
            uint32_t tmp;
            memcpy(&tmp, &val, sizeof(float));
            return tmp;
        }
        case Address::TYPE_LREAL:  {
            double val = getProxy<double, CAT>()[addr.index()];
            uint64_t tmp;
            memcpy(&tmp, &val, sizeof(double));
            return tmp;
        }
        default: return 0;
    }
}

template<Registry::Category CAT>
bool RegClient::checkChanged(const Address& addr) {
    switch(addr.type()) {
        case Address::TYPE_BIT:    return getProxy<bool,     CAT>().isChanged(addr.index());
        case Address::TYPE_BYTE:   return getProxy<uint8_t,  CAT>().isChanged(addr.index());
        case Address::TYPE_WORD:   return getProxy<uint16_t, CAT>().isChanged(addr.index());
        case Address::TYPE_DWORD:  return getProxy<uint32_t, CAT>().isChanged(addr.index());
        case Address::TYPE_LWORD:  return getProxy<uint64_t, CAT>().isChanged(addr.index());
        case Address::TYPE_REAL:   return getProxy<float,    CAT>().isChanged(addr.index());
        case Address::TYPE_LREAL:  return getProxy<double,   CAT>().isChanged(addr.index());
        default: return false;
    }
}

