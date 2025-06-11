#include "reg_client.h"
#include "reg_server.h"
#include "registry.h"

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

// Проверка изменений
void RegClient::update() {
    if (!is_active_ || !data_handler_) return;
    std::vector<ItemData> changes;
    for (const auto& [addr, key] : subscriptions_) {
        if (registry_.isChanged(addr)) {
            changes.push_back({
                key,
                registry_.getRawValue(addr)
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
