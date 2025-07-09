//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "driver_config.h"

#include <vector>
#include <mutex>
#include <unordered_map>
#include <memory>
#include <nlohmann/json.hpp>

class DriverLoader {
public:
    static DriverLoader& instance();

    // Основные методы
    void load_config(const std::string& config_path);
    void load_config_from_json(const nlohmann::json& config);
    void load_configured_drivers();
    void unload_all();
    void force_unload_all();

    bool reload_iec_library(const std::string& new_lib_path = "");

    // Доступ к конфигурации
    nlohmann::json get_config() const;

    const ModuleConfig& get_iec_config() const {
        std::lock_guard<std::mutex> lock(lib_mutex_);
        return iec_config_;
    }

    const std::vector<ModuleConfig>& get_drivers_config() const {
        std::lock_guard<std::mutex> lock(lib_mutex_);
        return drivers_config_;
    }

    std::string get_config_path() const {
        std::lock_guard<std::mutex> lock(lib_mutex_);
        return last_config_path_;
    }

    // Запрет копирования
    DriverLoader(const DriverLoader&) = delete;
    DriverLoader& operator=(const DriverLoader&) = delete;

private:
    DriverLoader() = default;
    ~DriverLoader() = default;

    static void* load_single_library(const std::string& path);
    void update_loaded_libraries(void* old_handle, void* new_handle);

    void register_module_iec(void* handle);
    void register_module_driver(void* handle);

    std::vector<ModuleConfig> drivers_config_;
    ModuleConfig              iec_config_;
    std::vector<void*>        loaded_libraries_;

    void*                 iec_handle_ = nullptr;
    std::string           last_config_path_;
    mutable std::mutex    lib_mutex_;
};
