//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "driver_manager.h"
#include "mod_factory.h"
#include "driver_factory.h"
#include "driver_loader.h"
#include <iostream>

DriverManager& DriverManager::instance() {
    static DriverManager instance;
    return instance;
}

void DriverManager::initialize(const std::shared_ptr<IClientFactory>& client_factory)
{
    const auto& modules_config = DriverLoader::instance().get_drivers_config();
    for (const auto& driver_cfg : modules_config) {
        try {
            // Создание драйвера
            auto driver = DriverFactory::instance().create(
                    driver_cfg.name.data(),
                    client_factory.get()
            );

            // Инициализация драйвера
            driver->initialize(driver_cfg.config);
            // Сохранение драйвера
            drivers_.push_back(std::move(driver));
        } catch (const std::exception& e) {
            std::cerr << "Driver initialization failed: " << driver_cfg.name << " - " << e.what() << std::endl;
        }
    }
}

void DriverManager::initialize_iec() {
    std::lock_guard<std::mutex> lock(iec_mutex_);

    // Создание модуля
    if (!iec_module_) { iec_module_ = IECFactory::instance().create_iec(); }

    // Инициализация модуля
    if (iec_module_) {
        json config = DriverLoader::instance().get_iec_config().config;
        iec_module_->initialize(config);
        iec_running_ = true;
    }
}

void DriverManager::shutdown() {
    // Остановка IEC модуля
    stop_iec();

    // Остановка драйверов в обратном порядке
    for (auto it = drivers_.rbegin(); it != drivers_.rend(); ++it) {
        try {
            (*it)->shutdown();
        } catch (const std::exception& e) {
            std::cerr << "Driver shutdown error: " << e.what() << std::endl;
        }
    }
    drivers_.clear();
}

// IEC управление
void DriverManager::start_iec() {
    std::lock_guard<std::mutex> lock(iec_mutex_);
    if (iec_module_ && !iec_running_) {
        iec_module_->initialize( DriverLoader::instance().get_iec_config().config );
        iec_running_ = true;
    }
}

void DriverManager::stop_iec() {
    std::lock_guard<std::mutex> lock(iec_mutex_);
    if (iec_module_ && iec_running_) {
        iec_module_->shutdown();
        iec_running_ = false;
    }
}

void DriverManager::restart_iec() {
    std::lock_guard<std::mutex> lock(iec_mutex_);
    if (iec_module_) {
        iec_module_->shutdown();
        iec_module_->initialize( DriverLoader::instance().get_iec_config().config );
        iec_running_ = true;
    }
}

void DriverManager::run_iec_cycle() {
    std::lock_guard<std::mutex> lock(iec_mutex_);
    if (iec_module_ && iec_running_) {
        try {
            iec_module_->do_work();
        } catch (const std::exception& e) {
            std::cerr << "IEC cycle error: " << e.what() << std::endl;
            iec_running_ = false;
        }
    }
}

// Состояние
bool DriverManager::is_iec_running() const { return iec_running_.load(); }
std::string DriverManager::iec_status() const {
    std::lock_guard<std::mutex> lock(iec_mutex_);
    return iec_module_ ? (iec_running_ ? "RUNNING" : "STOPPED") : "NOT_LOADED";
}
