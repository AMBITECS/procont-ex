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

    // Для работы с одиночными значениями
    virtual uint64_t read(const Address& addr) = 0;
    virtual void write(const Address& addr, uint64_t value) = 0;

    // Для работы с массивами
    virtual void read(std::vector<ItemData>& items) = 0;
    virtual void write(const std::vector<ItemData>& items) = 0;

    // Для работы с подпиской
    virtual void subscribe(const std::vector<RegItem>& items) = 0;
    virtual void setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) = 0;};

class RegClient : public IRegClient
{
private:
    std::string name_;
    std::function<void(const std::vector<OnDataChange>&)> data_handler_{};
    std::unordered_map<Address, uint64_t> subscriptions_; // addr -> key

public:
    explicit RegClient(std::string name);
    ~RegClient() override;

    const std::string& getName() const { return name_; }

    // Одиночные операции
    uint64_t read(const Address& addr) override;
    void write(const Address& addr, uint64_t value) override;

    // Массовые операции
    void read(std::vector<ItemData>& items) override;
    void write(const std::vector<ItemData>& items) override;

    // Подписка
    void subscribe(const std::vector<RegItem>& items) override;
    void setCallback(std::function<void(const std::vector<OnDataChange>&)> handler) override;

    // Обновление по изменениям
    void update();
};

#endif // REG_CLIENT_H
