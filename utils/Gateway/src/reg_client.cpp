#include "reg_client.h"
#include "reg_server.h"

#include <iostream>

RegClient::RegClient(std::string name, IClientCallback* callback)
    : name_(std::move(name)), callback_(callback)
    , server_(RegServer::instance())
    {}

RegClient::~RegClient() {
//    subscriptions_.clear();
//    RegServer::instance().removeClient(name_);
    shutdown();
}

void RegClient::shutdown() {
    if (!active_.exchange(false)) return;

    if (callback_) {
        callback_->onExit();
        callback_ = nullptr;
    }

    server_.removeClient(name_);
}

// Одиночные операции
uint64_t RegClient::read(const Address& addr) { return RegServer::instance().getProxyValue(addr); }
void RegClient::write(const Address& addr, uint64_t value) { RegServer::instance().setProxyValue(addr, value); }

// Массовые операции
void RegClient::read(std::vector<ItemData>& items) {
    for (auto& item : items) {
        item.data = RegServer::instance().getProxyValue(item.addr);
    }
}

void RegClient::write(const std::vector<ItemData>& items) {
    for (const auto& item : items) {
        RegServer::instance().setProxyValue(item.addr, item.data);
    }
}

// Операции с подпиской
void RegClient::subscribe(const std::vector<RegItem>& items) {
    for (const auto& item : items) {
        subscriptions_[item.addr] = item.key;
    }
}

void RegClient::unsubscribe(const std::vector<Address>& addresses) {
    for (const auto& addr : addresses) {
        subscriptions_.erase(addr);
    }
}

void RegClient::unsubscribeAll() {
    subscriptions_.clear();
}

void RegClient::update() {
    if (!callback_) return;

    // Статическая переменная для отслеживания времени последнего вывода точки
    static auto last_dot_time = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();

    // Проверяем, прошло ли 5 секунд
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_dot_time).count() >= 5) {
        std::cout << "." << std::flush;
        last_dot_time = now;
    }

    if (subscriptions_.empty()) return;

    std::vector<OnDataChange> changes;
    size_t changed_count = 0;

    for (const auto& [addr, key] : subscriptions_) {
        if (RegServer::instance().isProxyChanged(addr)) {
            uint64_t new_value = RegServer::instance().getProxyValue(addr);
            changes.push_back({key, new_value});
            changed_count++;

            // Форматированный вывод с учетом типа данных
            std::cout << "\n[CLIENT] " << name_
                      << " | Register: " << addr.toString()
                      << " | Key: 0x" << std::hex << key << std::dec
                      << " | New value: ";

            switch(addr.type()) {
                case Address::TYPE_BIT:   std::cout << (new_value ? "TRUE" : "FALSE"); break;
                case Address::TYPE_BYTE:
                case Address::TYPE_WORD:  std::cout << static_cast<uint16_t>(new_value); break;
                case Address::TYPE_DWORD: std::cout << static_cast<uint32_t>(new_value); break;
                case Address::TYPE_LWORD: std::cout << new_value; break;
                case Address::TYPE_REAL: {
                    float val;
                    memcpy(&val, &new_value, sizeof(float));
                    std::cout << val;
                    break;
                }
                case Address::TYPE_LREAL: {
                    double val;
                    memcpy(&val, &new_value, sizeof(double));
                    std::cout << val;
                    break;
                }
                default:
                    std::cout << new_value;
            }

            if (addr.isBit()) {
                std::cout << " (bit " << static_cast<int>(addr.bitpos()) << ")";
            }
        }
    }

    if (!changes.empty()) {
        std::cout << "\n[CLIENT] " << name_
                  << " | Total changes: " << changed_count
                  << " | Notifying callback..." << std::endl;
        callback_->updateOutputs(changes);
    }
}

//void RegClient::update() {
//    if (!callback_) return;
//
//    std::vector<OnDataChange> changes;
//    for (const auto& [addr, key] : subscriptions_) {
//        if (RegServer::instance().isProxyChanged(addr)) {
//            changes.push_back({key, RegServer::instance().getProxyValue(addr)});
//        }
//    }
//
//    if (!changes.empty()) {
//        callback_->updateOutputs(changes);
//    }
//}
