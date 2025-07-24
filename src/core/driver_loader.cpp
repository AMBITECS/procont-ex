//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "driver_loader.h"

#include "mod_factory.h"
#include "driver_factory.h"

#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
constexpr const char* lib_prefix = "";
constexpr const char* lib_extension = ".dll";
#else
#include <dlfcn.h>
constexpr const char* lib_prefix = "lib";
constexpr const char* lib_extension = ".so";
#endif

DriverLoader& DriverLoader::instance() {
    static DriverLoader instance;
    return instance;
}

void DriverLoader::load_config(const std::string& config_path) {
    //std::lock_guard<std::mutex> lock(lib_mutex_);

    std::ifstream config_file(config_path);
    if (!config_file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + config_path);
    }

    nlohmann::json config;
    config_file >> config;

    load_config_from_json(config);
    last_config_path_ = config_path;
}

nlohmann::json DriverLoader::get_config() const {
    std::lock_guard<std::mutex> lock(lib_mutex_);
    return nlohmann::json{ {"iec", iec_config_},  {"drivers", drivers_config_} };
}

void DriverLoader::load_config_from_json(const nlohmann::json& config) {
    std::lock_guard<std::mutex> lock(lib_mutex_);

    // Парсинг IEC конфигурации
    if (config.contains("iec")) {
        iec_config_.library_path = config["iec"].value("library_path", "");
        iec_config_ = config["iec"].get<ModuleConfig>();
    }

    // Парсинг конфигурации драйверов
    drivers_config_.clear();
    for (const auto& item : config["drivers"]) {
        drivers_config_.push_back(item.get<ModuleConfig>());
    }
}

void DriverLoader::load_configured_drivers() {
    std::lock_guard<std::mutex> lock(lib_mutex_);

    // (1) Загрузка IEC модуля
    std::cout << "=== Загрузка IEC модуля ...\n";
    {
        auto &cfg = iec_config_;
        std::string iec_lib_path = cfg.library_path + lib_prefix + cfg.library_name + std::string(lib_extension);
        if (!iec_lib_path.empty()) {

            iec_handle_ = load_single_library(iec_lib_path);

            if (iec_handle_) {
                register_module_iec(iec_handle_);
            }
        }
    }

    // (2) Загрузка драйверов
    std::cout << "=== Загрузка драйверов ... \n";
    for (const auto& cfg : drivers_config_) {
        std::string lib_path = cfg.library_path + cfg.library_name;
        void* handle = load_single_library(lib_path);
        if (handle) {
            std::cout << "=== Регистрация драйвера: " << cfg.library_name << " \n";
            register_module_driver(handle);
        }
    }

}

void DriverLoader::register_module_driver(void* handle) {
#ifdef _WIN32
    auto register_func
                = (void(__cdecl *)(DriverFactory*))GetProcAddress(static_cast<HMODULE>(handle), "register_driver");
#else
    auto register_func
            = (void(*)(DriverFactory*))dlsym(handle, "register_driver");
#endif
    if (register_func) {
        register_func(& DriverFactory::instance());
        loaded_libraries_.push_back(handle);
    } else {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
    }
}

void DriverLoader::register_module_iec(void* handle) {
    // Унифицированное имя символа
    const char* symbol_name = "register_module_iec";

    // Получаем указатель на функцию
    auto register_func = reinterpret_cast<void(*)(IECFactory*)>(
#ifdef _WIN32
            GetProcAddress(static_cast<HMODULE>(handle), symbol_name)
#else
            dlsym(handle, symbol_name)
#endif
    );

    if (!register_func) {
        std::cerr << "Failed to find symbol: " << symbol_name << std::endl;
        return;
    }

    // Вызываем функцию
    std::cout << "=== 3\n";
    IECFactory* factory = &IECFactory::instance();
    if (!factory) {
        std::cerr << "ERROR: IECFactory::instance() returned nullptr!" << std::endl;
        return;
    }
    std::cout << "Factory pointer: " << factory << std::endl;  // Убедитесь, что не 0x0
    register_func(factory);

    std::cout << "=== 4 ===\n";
}

//void DriverLoader::register_module_iec(void* handle)
//{
//#ifdef _WIN32
//    auto register_func = (void(__cdecl *)(IECFactory*))GetProcAddress(
//        static_cast<HMODULE>(handle), "register_module_iec");
//#else
//    auto register_func = (void(*)(IECFactory*))dlsym(handle, "register_module_iec");
//
//
//#endif
//    if (register_func) {
//
//        register_func(& IECFactory::instance());
//
//    }
//}

void DriverLoader::unload_all() {
    std::lock_guard<std::mutex> lock(lib_mutex_);

// Вызов очистки в обратном порядке
//    for (auto it = loaded_libraries_.rbegin(); it != loaded_libraries_.rend(); ++it) {
//        //call_unload_function(*it);
//    }

    // !. Очищаем фабрики модулей
    std::cout << "=====  Очищаем фабрики модулей =====\n";
    DriverFactory::instance().unload_drivers();
    IECFactory::instance().unload_iec();

    // 2 Выгружаем библиотеки в обратном порядке
    std::cout << "=====  Выгружаем библиотеки =====\n";
    for (auto it = loaded_libraries_.rbegin(); it != loaded_libraries_.rend(); ++it) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(*it));
#else
        dlclose(*it);
#endif
        *it = nullptr;
    }

    loaded_libraries_.clear();

    // 3. Выгружаем IEC модуль отдельно
    std::cout << "=====  Выгружаем Выгружаем IEC модуль =====\n";
    if (iec_handle_) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(iec_handle_));
#else
        dlclose(iec_handle_);
#endif
        iec_handle_ = nullptr;
    }
}

//void DriverLoader::force_unload_all() {
//    std::lock_guard<std::mutex> lock(lib_mutex_);
//
//    // Агрессивная выгрузка без обработки ошибок
//    for (auto lib : loaded_libraries_) {
//        try {
//#ifdef _WIN32
//            FreeLibrary(static_cast<HMODULE>(lib));
//#else
//            dlclose(lib);
//#endif
//        } catch (...) {}
//    }
//    loaded_libraries_.clear();
//
//    if (iec_handle_) {
//        try {
//#ifdef _WIN32
//            FreeLibrary(static_cast<HMODULE>(iec_handle_));
//#else
//            dlclose(iec_handle_);
//#endif
//        } catch (...) {}
//        iec_handle_ = nullptr;
//    }
//}

//bool DriverLoader::reload_iec_library(const std::string& new_lib_path) {
//    std::lock_guard<std::mutex> lock(lib_mutex_);
//    void* old_handle = iec_handle_;
//
//    std::string path = new_lib_path.empty() ? iec_config_.library_path : new_lib_path;
//    iec_handle_ = load_single_library(path);
//
//    if (!iec_handle_) {
//        iec_handle_ = old_handle;
//        return false;
//    }
//
//    register_module_iec(iec_handle_);
//    update_loaded_libraries(old_handle, iec_handle_);
//    return true;
//}

void* DriverLoader::load_single_library(const std::string& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(path.c_str());
    if (!handle) {
        std::cerr << "LoadLibrary failed: " << GetLastError() << std::endl;
        return nullptr;
    }
#else
    void* handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
        std::cerr << "dlopen failed: " << dlerror() << std::endl;
        return nullptr;
    }
#endif
    return handle;
}

void DriverLoader::update_loaded_libraries(void* old_handle, void* new_handle) {
    auto it = std::find(loaded_libraries_.begin(), loaded_libraries_.end(), old_handle);
    if (it != loaded_libraries_.end()) {
        *it = new_handle;
    } else {
        loaded_libraries_.push_back(new_handle);
    }

    if (old_handle) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(old_handle));
#else
        dlclose(old_handle);
#endif
    }
}
