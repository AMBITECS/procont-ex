//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "reg_address.h"

#include <memory>
#include <vector>
#include <string>

//-----------------------------------------------------------------------------
// Структуры данных
//-----------------------------------------------------------------------------
// Для группового чтения/записи значения
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

//-----------------------------------------------------------------------------
// Интерфейсы
//-----------------------------------------------------------------------------
// Интерфейс клиентского доступа
class IRegClient {
public:
    virtual ~IRegClient() = default;

    // Базовые операции
    virtual uint64_t read(const Address& addr) = 0;
    virtual void     write(const Address& addr, uint64_t value) = 0;

    // Пакетные операции
    virtual void    read(std::vector<ItemData>& items) = 0;
    virtual void    write(const std::vector<ItemData>& items) = 0;

    // Подписка на изменения
    virtual void    subscribe(const std::vector<RegItem>& items) = 0;
    virtual void    unsubscribe(const std::vector<Address>& addresses) = 0;
    virtual void    unsubscribeAll() = 0;
};

// Интерфейс обратного вызова
class IClientCallback {
public:
    virtual ~IClientCallback() = default;

    virtual void onInit() = 0;
    virtual void onExit() = 0;
    virtual void updateInputs() = 0;
    virtual void updateOutputs(const std::vector<OnDataChange>&) = 0;
};

// Интерфейс фабрики клиентов (createClient)
class IClientFactory {
public:
    virtual ~IClientFactory() = default;
    virtual std::shared_ptr<IRegClient>
    createClient( const std::string& name, IClientCallback* callback ) = 0;
};
