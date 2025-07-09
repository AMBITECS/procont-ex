//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "pro_module.h"
#include "pro_driver.h"

#include <memory>
#include <vector>
#include <mutex>
#include <atomic>

class DriverManager {
public:
    static DriverManager& instance();

    // Основное API
    void initialize(const std::shared_ptr<IClientFactory>& client_factory);
    void initialize_iec();
    void shutdown();

    // Управление IEC модулем
    void start_iec();
    void stop_iec();
    void restart_iec();
    void run_iec_cycle();

    // Состояние
    bool is_iec_running() const;
    std::string iec_status() const;

    // Мьютекс для внешней синхронизации
    std::mutex& get_iec_mutex() { return iec_mutex_; }

    // Запрет копирования
    DriverManager(const DriverManager&) = delete;
    DriverManager& operator=(const DriverManager&) = delete;

private:
    DriverManager() = default;
    ~DriverManager() = default;

    std::vector<std::unique_ptr<IProModule>> drivers_;
    std::unique_ptr<IProModule> iec_module_;
    mutable std::mutex iec_mutex_;
    std::atomic<bool> iec_running_{false};
};
