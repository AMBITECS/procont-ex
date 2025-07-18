//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "driver_loader.h"
#include "driver_manager.h"
#include <mutex>
#include <atomic>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SystemReloader {
private:
    mutable std::mutex  config_mutex_;
    mutable std::mutex  reload_mutex_;

    std::atomic<bool>   reloading_{false};
    std::string         last_config_path_;
    json                last_working_config_;

    static void perform_reload(const json& config);
    static bool validate_config(const json& config) ;

    SystemReloader();
public:
    static SystemReloader& instance();

    // Основной API
    bool full_reload(const std::string& config_path = "");
    void emergency_restore();

    // Состояние системы
    bool is_reloading() const { return reloading_.load(); }

    // Управление конфигурацией
    void save_config_to_file  (const std::string& path = "last_working_config.json");
    void load_config_from_file(const std::string& path = "last_working_config.json");

    const json& get_last_working_config() const;
    void update_last_working_config();

    // Запрет копирования
    SystemReloader(const SystemReloader&) = delete;
    SystemReloader& operator=(const SystemReloader&) = delete;
};
