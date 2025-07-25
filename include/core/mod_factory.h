//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "api_module.h"

#pragma pack(push, 8)
class IECFactory {
private:
    using IecCreator    = std::function<std::unique_ptr<IProModule>()>;

    IecCreator iec_creator_{};  // Creator для IEC модуля

    IECFactory()  = default;    // Приватный конструктор
    ~IECFactory() = default;    // Приватный деструктор

public:
    // Singleton access
    static IECFactory& instance() { static IECFactory instance; return instance; }

    // Запрещаем копирование
    IECFactory(const IECFactory&) = delete;
    IECFactory& operator=(const IECFactory&) = delete;

    // Регистрация и создание IEC модуля
    void register_iec( std::function<std::unique_ptr<IProModule>()> creator );

    void unload_iec() {
        iec_creator_ = nullptr;  // Явно освобождаем лямбду
    }

    std::unique_ptr<IProModule> create_iec();

};
#pragma pack(pop)

// Скрипт регистрации IEC модуля
#define IEC_REGISTER(ModuleClass) \
extern "C" void register_module_iec(IECFactory* factory) { \
    factory->register_iec([](){return std::make_unique<ModuleClass>();}); \
}
