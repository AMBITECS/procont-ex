#ifndef REG_CLIENT_H
#define REG_CLIENT_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "registry.h"

// Для чтения/записи значения
struct ItemData {
    Address  addr{};    // Адрес в реестре
    uint64_t data{};    // Сырое значение
};

// Для оформления подписки на изменения
struct RegItem {
    Address  addr{};    // Адрес в реестре
    uint64_t key{};     // Дескриптор подписчика
};

// Для передачи подписчику
struct OnDataChange {
    uint64_t key{};     // Дескриптор подписчика
    uint64_t data{};    // Сырое значение
};

class IRegClient {
public:
    virtual ~IRegClient() = default;

    virtual void read(std::vector<ItemData>& items) = 0;
    virtual void write(const std::vector<ItemData>& items) = 0;
    virtual void subscribe(const std::vector<RegItem>& items) = 0;
    virtual void setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) = 0;
};

class RegClient : public IRegClient
{
private:
    std::string name_;
    std::function<void(const std::vector<OnDataChange>&)> data_handler_{};

    std::unordered_map<Address, uint64_t> subscriptions_; // addr -> key

    // ------------------------------------------
    // получение сырого значения
    template<Registry::Category CAT>
    uint64_t getValue(const Address& addr);

    template<Registry::Category CAT>
    void setValue(const Address& addr, uint64_t value);

    // проверка изменения значения по адресу
    template<Registry::Category CAT>
    bool checkChanged(const Address& addr);

//    template<typename T, Registry::Category CAT>
//    auto& getProxy();

//    template<Registry::Category CAT>
//    void processWithCategory(const Address &addr, void *iecVar, bool toRegistry);

//    template<typename T, Registry::Category CAT>
//    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    // ------------------------------------------
//    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

public:
    explicit RegClient(std::string name);
    ~RegClient() override;

    void setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) override;
    void subscribe(const std::vector<RegItem>& items) override;
    void read(std::vector<ItemData>& items) override;
    void write(const std::vector<ItemData>& items) override;

    const std::string& getName() const { return name_; }

    void update();
};

#endif // REG_CLIENT_H
