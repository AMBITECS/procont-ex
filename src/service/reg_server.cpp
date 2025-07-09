#include "reg_server.h"
#include "reg_client.h"

RegServer &RegServer::instance() {
    static RegServer server;
    return server;
}

std::shared_ptr<IRegClient> RegServer::createClient(const std::string& name, IClientCallback* callback) {
    if (shutdown_.load()) return nullptr;

    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);

    // Очищаем "просросенных" клиентов
    for (auto it = clients_.begin(); it != clients_.end(); ) {
        if (it->second.expired()) {
            it = clients_.erase(it);
        } else {
            ++it;
        }
    }

    auto client = std::make_shared<RegClient>(name, callback);
    clients_[name] = client;
    return client;
}

void RegServer::removeClient(const std::string& name) {
    if (shutdown_.load()) return;

    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);
    clients_.erase(name);
}

void RegServer::clearAllClients() {
    //std::lock_guard<std::mutex> lock(clients_mutex_);
    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);
    clients_.clear();
}

void RegServer::notifyInit() {
    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);

    for (auto it = clients_.begin(); it != clients_.end(); ) {
        if (auto client = it->second.lock()) {  // Получаем shared_ptr из weak_ptr
            if (auto callback = client->getCallback()) {
                callback->onInit();
            }
            ++it;
        } else {
            // Удаляем expired клиенты
            it = clients_.erase(it);
        }
    }
}

void RegServer::notifyExit() {
    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);

    for (auto it = clients_.begin(); it != clients_.end(); ) {
        if (auto client = it->second.lock()) {
            if (auto callback = client->getCallback()) {
                callback->onExit();
            }
            ++it;
        } else {
            it = clients_.erase(it);
        }
    }
}

void RegServer::notifyDataRead() {
    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);

    for (auto it = clients_.begin(); it != clients_.end(); ) {
        if (auto client = it->second.lock()) {
            if (auto callback = client->getCallback()) {
                callback->updateInputs();
            }
            ++it;
        } else {
            it = clients_.erase(it);
        }
    }
}

void RegServer::notifyDataWrite() {
    std::lock_guard<std::recursive_mutex> lock(clients_mutex_);

    for (auto it = clients_.begin(); it != clients_.end(); ) {
        if (auto client = it->second.lock()) {
            client->update();
            ++it;
        } else {
            it = clients_.erase(it);
        }
    }
}

void RegServer::commit() {
    registry_.commit();
}


// ----------------------------------------------------------------------------
// Основные функции-обёртки
// ----------------------------------------------------------------------------
uint64_t RegServer::getProxyValue(const Address& addr) const {
    switch(addr.category()) {
        case Registry::Category::INPUT:   return getValueByCategory<Registry::Category::INPUT>(addr);
        case Registry::Category::OUTPUT:  return getValueByCategory<Registry::Category::OUTPUT>(addr);
        case Registry::Category::MEMORY:  return getValueByCategory<Registry::Category::MEMORY>(addr);
        case Registry::Category::SPECIAL: return getValueByCategory<Registry::Category::SPECIAL>(addr);
        default: throw std::runtime_error("Unknown register category");
    }
}

void RegServer::setProxyValue(const Address& addr, uint64_t value) {
    switch(addr.category()) {
        case Registry::Category::INPUT:   setValueByCategory<Registry::Category::INPUT>(addr, value); break;
        case Registry::Category::OUTPUT:  setValueByCategory<Registry::Category::OUTPUT>(addr, value); break;
        case Registry::Category::MEMORY:  setValueByCategory<Registry::Category::MEMORY>(addr, value); break;
        case Registry::Category::SPECIAL: setValueByCategory<Registry::Category::SPECIAL>(addr, value); break;
        default: throw std::runtime_error("Unknown register category");
    }
}

bool RegServer::isProxyChanged(const Address& addr) const {
    switch(addr.category()) {
        case Registry::Category::INPUT:   return isChangedByCategory<Registry::Category::INPUT>(addr);
        case Registry::Category::OUTPUT:  return isChangedByCategory<Registry::Category::OUTPUT>(addr);
        case Registry::Category::MEMORY:  return isChangedByCategory<Registry::Category::MEMORY>(addr);
        case Registry::Category::SPECIAL: return isChangedByCategory<Registry::Category::SPECIAL>(addr);
        default: return false;
    }
}

// ----------------------------------------------------------------------------
// Шаблонные вспомогательные методы
// ----------------------------------------------------------------------------
template<Registry::Category CAT>
uint64_t RegServer::getValueByCategory(const Address& addr) const {
    switch(addr.type()) {
        case Address::TYPE_BIT:   return getProxy<CAT, bool>()[addr.index()][addr.bitpos()] ? 1 : 0;
        case Address::TYPE_BYTE:  return getProxy<CAT, uint8_t>()[addr.index()];
        case Address::TYPE_WORD:  return getProxy<CAT, uint16_t>()[addr.index()];
        case Address::TYPE_DWORD: return getProxy<CAT, uint32_t>()[addr.index()];
        case Address::TYPE_LWORD: return getProxy<CAT, uint64_t>()[addr.index()];
        case Address::TYPE_REAL:
        {
            float val = getProxy<CAT, float>()[addr.index()];
            uint32_t tmp;
            memcpy(&tmp, &val, sizeof(float));
            return tmp;
        }
        case Address::TYPE_LREAL:
        {
            double val = getProxy<CAT, double>()[addr.index()];
            uint64_t tmp;
            memcpy(&tmp, &val, sizeof(double));
            return tmp;
        }
        default: throw std::runtime_error("Unsupported data type");
    }
}

template<Registry::Category CAT>
void RegServer::setValueByCategory(const Address& addr, uint64_t value) {
    switch(addr.type()) {
        case Address::TYPE_BIT:   getProxy<CAT, bool>()[addr.index()][addr.bitpos()] = (value != 0); break;
        case Address::TYPE_BYTE:  getProxy<CAT, uint8_t>()[addr.index()] = static_cast<uint8_t>(value); break;
        case Address::TYPE_WORD:  getProxy<CAT, uint16_t>()[addr.index()] = static_cast<uint16_t>(value); break;
        case Address::TYPE_DWORD: getProxy<CAT, uint32_t>()[addr.index()] = static_cast<uint32_t>(value); break;
        case Address::TYPE_LWORD: getProxy<CAT, uint64_t>()[addr.index()] = value; break;
        case Address::TYPE_REAL:
        {
            float val;
            auto tmp = static_cast<uint32_t>(value);
            memcpy(&val, &tmp, sizeof(float));
            getProxy<CAT, float>()[addr.index()] = val;
            break;
        }
        case Address::TYPE_LREAL:
        {
            double val;
            memcpy(&val, &value, sizeof(double));
            getProxy<CAT, double>()[addr.index()] = val;
            break;
        }
        default: throw std::runtime_error("Unsupported data type");
    }
}

template<Registry::Category CAT>
bool RegServer::isChangedByCategory(const Address& addr) const {
    switch(addr.type()) {
        case Address::TYPE_BIT:   return getProxy<CAT, bool>().isChanged(addr.index());
        case Address::TYPE_BYTE:  return getProxy<CAT, uint8_t>().isChanged(addr.index());
        case Address::TYPE_WORD:  return getProxy<CAT, uint16_t>().isChanged(addr.index());
        case Address::TYPE_DWORD: return getProxy<CAT, uint32_t>().isChanged(addr.index());
        case Address::TYPE_LWORD: return getProxy<CAT, uint64_t>().isChanged(addr.index());
        case Address::TYPE_REAL:  return getProxy<CAT, float>().isChanged(addr.index());
        case Address::TYPE_LREAL: return getProxy<CAT, double>().isChanged(addr.index());
        default: return false;
    }
}

// Вспомогательная структура для ошибок
template<typename T>
struct TypeNotSupported {
    static_assert(sizeof(T) == 0, "Type not supported for this category");
};

template<Registry::Category CAT, typename T>
auto& RegServer::getProxy() {
    static_assert(std::is_arithmetic_v<T>, "Only arithmetic types are supported");

    if constexpr (CAT == Registry::Category::INPUT) {
        if constexpr (std::is_same_v<T, bool>)          return IX();
        else if constexpr (std::is_same_v<T, uint8_t>)  return IB();
        else if constexpr (std::is_same_v<T, uint16_t>) return IW();
        else if constexpr (std::is_same_v<T, uint32_t>) return ID();
        else if constexpr (std::is_same_v<T, uint64_t>) return IL();
        else if constexpr (std::is_same_v<T, float>)    return IF();
        else if constexpr (std::is_same_v<T, double>)   return IE();
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::OUTPUT) {
        if constexpr (std::is_same_v<T, bool>)          return QX();
        else if constexpr (std::is_same_v<T, uint8_t>)  return QB();
        else if constexpr (std::is_same_v<T, uint16_t>) return QW();
        else if constexpr (std::is_same_v<T, uint32_t>) return QD();
        else if constexpr (std::is_same_v<T, uint64_t>) return QL();
        else if constexpr (std::is_same_v<T, float>)    return QF();
        else if constexpr (std::is_same_v<T, double>)   return QE();
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::MEMORY) {
        if constexpr (std::is_same_v<T, bool>) return MX();
        else if constexpr (std::is_same_v<T, uint8_t>)  return MB();
        else if constexpr (std::is_same_v<T, uint16_t>) return MW();
        else if constexpr (std::is_same_v<T, uint32_t>) return MD();
        else if constexpr (std::is_same_v<T, uint64_t>) return ML();
        else if constexpr (std::is_same_v<T, float>)    return MF();
        else if constexpr (std::is_same_v<T, double>)   return ME();
        else return TypeNotSupported<T>::value;
    }
    else if constexpr (CAT == Registry::Category::SPECIAL) {
        if constexpr (std::is_same_v<T, bool>) return SX();
        else if constexpr (std::is_same_v<T, uint8_t>) return SB();
        else if constexpr (std::is_same_v<T, uint16_t>) return SW();
        else if constexpr (std::is_same_v<T, uint32_t>) return SD();
        else if constexpr (std::is_same_v<T, uint64_t>) return SL();
        else if constexpr (std::is_same_v<T, float>) return SF();
        else if constexpr (std::is_same_v<T, double>) return SE();
        else return TypeNotSupported<T>::value;
    }
    else { return TypeNotSupported<T>::value; }
}

template<Registry::Category CAT, typename T>
const auto& RegServer::getProxy() const { return const_cast<RegServer*>(this)->getProxy<CAT, T>(); }

