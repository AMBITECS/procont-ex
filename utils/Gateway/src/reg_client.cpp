#include "reg_server.h"
#include "proxy.h"

RegClient::RegClient(std::string name): name_(std::move(name)) {}

RegClient::~RegClient() {
    subscriptions_.clear();
    RegServer::instance().removeClient(name_);
}

// Одиночные операции
uint64_t RegClient::read(const Address& addr) { return ::getProxyValue(addr); }
void RegClient::write(const Address& addr, uint64_t value) { ::setProxyValue(addr, value); }

// Массовые операции
void RegClient::read(std::vector<ItemData>& items) {
    for (auto& item : items) {
        item.data = ::getProxyValue(item.addr);
    }
}

void RegClient::write(const std::vector<ItemData>& items) {
    for (const auto& item : items) {
        ::setProxyValue(item.addr, item.data);
    }
}

// Операции с подпиской
void RegClient::setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) {
    data_handler_ = std::move(handler);
}

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

// Обновлнение по изменениям
void RegClient::update() {
    if (!data_handler_) return;

    std::vector<OnDataChange> changes;
    for (const auto& [addr, key] : subscriptions_) {
        if (::isProxyChanged(addr)) {
            changes.push_back({key, ::getProxyValue(addr)});
        }
    }

    if (!changes.empty()) {
        data_handler_(changes);
    }
}
