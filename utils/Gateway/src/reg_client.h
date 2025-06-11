#ifndef REG_CLIENT_H
#define REG_CLIENT_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "address.h"

// Для одписки на изменения Registry
struct RegItem {
    Address addr;  // Адрес в реестре
    uint64_t key;  // Дескриптор элемента подписчика
};

// Для передачи подписчику
struct ItemData {
    uint64_t key;  // Дескриптор элемента
    uint64_t data; // Сырое значение
};

class Registry; // Forward declaration

class IRegClient {
public:
    virtual ~IRegClient() = default;
    virtual void init(std::function<void(const std::vector<ItemData>&)> handler) = 0;
    virtual void subscribe(const std::vector<RegItem>& items) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void exit() = 0;
};

class RegClient : public IRegClient {
private:
    Registry& registry_;
    std::string name_;
    std::function<void(const std::vector<ItemData>&)> data_handler_;
    std::unordered_map<Address, uint64_t> subscriptions_; // addr -> key
    bool is_active_ = false;

public:
    RegClient(Registry& registry, std::string name);
    ~RegClient() override;

    void init(std::function<void(const std::vector<ItemData>&)> handler) override;
    void subscribe(const std::vector<RegItem>& items) override;
    void activate() override;
    void deactivate() override;
    void exit() override;

    const std::string& getName() const { return name_; }

    bool hasSubscription(const Address& addr) const {
        return subscriptions_.count(addr) > 0;
    }

    uint64_t getKeyForAddress(const Address& addr) const {
        auto it = subscriptions_.find(addr);
        return it != subscriptions_.end() ? it->second : 0;
    }

    void update();

//    void notify(const std::vector<ItemData>& changes) {
//        if (data_handler_ && is_active_) {
//            data_handler_(changes);
//        }
//    }
};

#endif // REG_CLIENT_H
