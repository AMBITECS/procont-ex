//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "driver_factory.h"
#include <iostream>

// объявление функций IEC модуля
void config_init__();
void config_run__(unsigned long tick);

class IecWrapper : public IIecModule {
public:
    bool initialize(const json& config) override {
        try {
            if (running_) shutdown();

            // Парсинг конфигурации
            cycle_time_ = config.value("cycle_time", 50);
            debug_ = config.value("debug", false);

            // Инициализация IEC
            config_init__();
            //glueVars();

            running_ = true;
            return true;
        } catch (...) {
            running_ = false;
            return false;
        }
    }

    void run_cycle() override {
        if (running_) {
            config_run__(tick_++);
        }
    }

    [[nodiscard]] bool is_running() const override { return running_; }
    [[nodiscard]] std::string status() const override {return running_ ? "RUNNING" : "STOPPED";}

    void shutdown() override {
        if (running_) {
            // Корректное завершение работы ...
            running_ = false;
        }
    }

private:
    bool            debug_{};
    bool            running_{};
    int             cycle_time_{50};
    unsigned long   tick_ = {};
};

// Регистрация модуля
IEC_REGISTER(IecWrapper)