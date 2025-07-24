#ifndef DRIVER_FACTORY_H
#define DRIVER_FACTORY_H

#define PROCONT_API
#ifndef PROCONT_API
#ifdef _WIN32
        #ifdef API_EXPORTS
            #define PROCONT_API __declspec(dllexport)
        #else
            #define PROCONT_API __declspec(dllimport)
        #endif
    #else
        #define PROCONT_API __attribute__((visibility("default")))
    #endif
#endif

#include "api_module.h"
#include "api_driver.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>

#pragma pack(push, 8)
class PROCONT_API DriverFactory {
private:
    // Creators для драйверов
    using DriverCreator = std::function<std::unique_ptr<IProModule>(IClientFactory*)>;
    std::unordered_map<std::string, DriverCreator>  creators_{};

    DriverFactory()  = default;    // Приватный конструктор
    ~DriverFactory() = default;    // Приватный деструктор

public:
    // Singleton access
    static DriverFactory& instance() { static DriverFactory instance; return instance; }

    // Запрещаем копирование
    DriverFactory(const DriverFactory&) = delete;
    DriverFactory& operator=(const DriverFactory&) = delete;

    // Регистрация драйвера
    void register_driver(const char* name, DriverCreator creator) {
        if (name) creators_[name] = std::move(creator);
    }

    void unload_drivers() {
        for (auto& [name, creator] : creators_) {
            creator = nullptr;
        }
        creators_.clear();
    }

    // Создание экземпляра драйвера
    std::unique_ptr<IProModule> create(const char* name, IClientFactory* factory) {
        auto it = creators_.find(name);
        if (it == creators_.end()) {
            throw std::runtime_error("Driver not registered: " + std::string(name));
        }
        return it->second(factory);
    }
};
#pragma pack(pop)

// Скрипт регистрации драйвера
#define DRIVER_REGISTER(driver_name, DriverClass) \
extern "C" void register_driver(DriverFactory* factory) { \
    factory->register_driver(driver_name, \
        [](IClientFactory* factory) { \
            return std::make_unique<DriverClass>(factory); \
        }); \
}

#endif // DRIVER_FACTORY_H
