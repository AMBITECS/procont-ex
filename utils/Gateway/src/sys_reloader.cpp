//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "sys_reloader.h"
#include "client_factory.h"
#include "driver_factory.h"
#include <iostream>

SystemReloader& SystemReloader::instance() {
    static SystemReloader instance;
    return instance;
}

SystemReloader::SystemReloader() {
    try {
        load_config_from_file();
    } catch (...) {
        std::cerr << "No valid backup config found" << std::endl;
    }
}

bool SystemReloader::full_reload(const std::string& config_path) {
    if (reloading_) return false;
    bool bResult = false;
    std::lock_guard<std::mutex> lock(reload_mutex_);
    reloading_.store(true);

    try {
        // 1. Загрузка новой конфигурации
        json new_config;
        std::string actual_path = config_path.empty() ? last_config_path_ : config_path;
        if (actual_path.empty()) { throw std::runtime_error("No config path specified"); }
        std::ifstream config_file(actual_path);
        config_file >> new_config;
        if (!validate_config(new_config)) { throw std::runtime_error("Config validation failed"); }

        // 2. Выполнение перезагрузки модулей (!)
        perform_reload(new_config);

        // 3. Обновление рабочей конфигурации
        {
            std::lock_guard<std::mutex> config_lock(config_mutex_);
            last_working_config_ = new_config;
            last_config_path_    = actual_path;
        }
        save_config_to_file();
        bResult = true;
    }
    catch (const std::exception& e) {
        std::cerr << "Reload failed: " << e.what() << std::endl;
    }
    reloading_.store(false);
    return bResult;
}

void SystemReloader::emergency_restore() {
    std::lock_guard<std::mutex> lock(reload_mutex_);
    reloading_.store(true);

    try {
        json backup_config;
        {
            std::lock_guard<std::mutex> config_lock(config_mutex_);
            if (last_working_config_.empty()) {
                throw std::runtime_error("No backup config available");
            }
            backup_config = last_working_config_;
        }

        std::cerr << "Attempting emergency restore..." << std::endl;
        perform_reload(backup_config);
        std::cerr << "Emergency restore completed successfully" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Fatal: Emergency restore failed - " << e.what() << std::endl;
        std::terminate();
    }

    reloading_.store(false);
}

void SystemReloader::save_config_to_file(const std::string& path) {
    std::lock_guard<std::mutex> lock(config_mutex_);
    std::ofstream f(path);
    if (!f) throw std::runtime_error("Can't open config file for writing");
    f << last_working_config_.dump(4);
}

void SystemReloader::load_config_from_file(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("Can't open config file");
    json config;
    f >> config;
    if (!validate_config(config)) { throw std::runtime_error("Invalid config in backup file"); }
    std::lock_guard<std::mutex> lock(config_mutex_);
    last_working_config_ = config;
}

const json& SystemReloader::get_last_working_config() const {
    std::lock_guard<std::mutex> lock(config_mutex_);
    return last_working_config_;
}

void SystemReloader::update_last_working_config() {
    std::lock_guard<std::mutex> lock(config_mutex_);
    last_working_config_ = DriverLoader::instance().get_config().dump();
    save_config_to_file();
}

//-----------------------------------------------------------------------------
// Приватные методы
//-----------------------------------------------------------------------------
void SystemReloader::perform_reload(const json& config) {
    // 1. Остановка системы
    DriverManager::instance().shutdown();
    DriverLoader::instance().unload_all();

    // 2. Загрузка новой конфигурации
    DriverLoader::instance().load_config_from_json(config);
    DriverLoader::instance().load_configured_drivers();

    // 3. Инициализация
    auto client_factory = std::make_shared<ClientFactoryImpl>(RegServer::instance());
    DriverManager::instance().initialize_iec();             // Инициализация iec
    DriverManager::instance().initialize(client_factory);   // Инициализация драйверов
}

bool SystemReloader::validate_config(const json& config) {
    // Базовые проверки
    if (!config.contains("drivers") || !config["drivers"].is_array()) return false;
    if (!config.contains("iec") || !config["iec"].is_object()) return false;

    // Дополнительные проверки по необходимости ...
    return true;
}
