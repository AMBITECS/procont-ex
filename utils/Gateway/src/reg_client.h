#ifndef REG_CLIENT_H
#define REG_CLIENT_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "registry.h"

// Для чтения/записи значения
struct ItemData {
    Address  addr;      // Адрес в реестре
    uint64_t data{};    // Сырое значение
};

// Для оформления подписки на изменения
struct RegItem {
    Address  addr;      // Адрес в реестре
    uint64_t key{};     // Дескриптор подписчика
};

// Для передачи подписчику
struct OnDataChange {
    uint64_t key;       // Дескриптор подписчика
    uint64_t data;      // Сырое значение
};

class IRegClient {
public:
    virtual ~IRegClient() = default;
    virtual void init(std::function<void(const std::vector<OnDataChange>&)> handler) = 0;
    virtual void subscribe(const std::vector<RegItem>& items) = 0;

    virtual void readTo(std::vector<ItemData>& items) = 0;
    virtual void writeFrom(const std::vector<ItemData>& items) = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void exit() = 0;
};

class RegClient : public IRegClient {
private:
    //Registry& registry_;

    std::string name_;
    std::function<void(const std::vector<OnDataChange>&)> data_handler_;
    std::unordered_map<Address, uint64_t> subscriptions_; // addr -> key
    bool is_active_ = false;

    // ------------------------------------------
    // получение сырого значения
    template<Registry::Category CAT>
    uint64_t getValue(const Address& addr);

    // проверка изменения значения по адресу
    template<Registry::Category CAT>
    bool checkChanged(const Address& addr);

    template<typename T, Registry::Category CAT>
    auto& getProxy();

    template<Registry::Category CAT>
    void processWithCategory(const Address &addr, void *iecVar, bool toRegistry);

    template<typename T, Registry::Category CAT>
    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    // ------------------------------------------
    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

public:
    RegClient(Registry& registry, std::string name);
    ~RegClient() override;

    void init(std::function<void(const std::vector<OnDataChange>&)> handler) override;
    void subscribe(const std::vector<RegItem>& items) override;
    void activate() override;
    void deactivate() override;
    void readTo(std::vector<ItemData>& items) override;
    void writeFrom(const std::vector<ItemData>& items) override;
    void exit() override;

    const std::string& getName() const { return name_; }

//    bool hasSubscription(const Address& addr) const {
//        return subscriptions_.count(addr) > 0;
//    }
//
//    uint64_t getKeyForAddress(const Address& addr) const {
//        auto it = subscriptions_.find(addr);
//        return it != subscriptions_.end() ? it->second : 0;
//    }

    void update();
};

#endif // REG_CLIENT_H
