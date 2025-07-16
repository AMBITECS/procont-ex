#ifndef DRIVER_FACTORY_H
#define DRIVER_FACTORY_H

#include "pro_module.h"
#include "pro_driver.h"

#ifdef _WIN32
#ifdef DRIVER_API_EXPORTS
        #define DRIVER_API __declspec(dllexport)
    #else
        #define DRIVER_API __declspec(dllimport)
    #endif
#else
#define DRIVER_API __attribute__((visibility("default")))
#endif

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>

class
DRIVER_API
DriverFactory {
private:
    // Creators для драйверов
    using DriverCreator = std::function<std::unique_ptr<IProModule>(std::shared_ptr<IClientFactory>)>;
    std::unordered_map<std::string, DriverCreator>  creators_{};

    DriverFactory()  = default;    // Приватный конструктор
    ~DriverFactory() = default;    // Приватный деструктор

public:
    // Singleton access
    static DriverFactory& instance();

    // Запрещаем копирование
    DriverFactory(const DriverFactory&) = delete;
    DriverFactory& operator=(const DriverFactory&) = delete;

    // Регистрация драйвера (из IDriverRegistrar)
    void register_driver(
            const std::string& name,
            std::function<std::unique_ptr<IProModule>(IClientFactory*)> creator
    );

    // Создание экземпляра драйвера
    std::unique_ptr<IProModule>
    create( const std::string& name,std::shared_ptr<IClientFactory> factory );
};

// Упрощенный C-интерфейс для регистрации
extern "C" DRIVER_API void register_driver(const char* name);

//// Скрипт регистрации драйвера
#define DRIVER_REGISTER(driver_name, DriverClass) \
extern "C" DRIVER_API void register_driver(const char* name) { \
    auto& factory = DriverFactory::instance(); \
    factory.register_driver(name, [](IClientFactory* f) { \
        auto sf = std::shared_ptr<IClientFactory>(f, [](auto*){}); \
        return std::make_unique<DriverClass>(sf); \
    });}

#endif // DRIVER_FACTORY_H
