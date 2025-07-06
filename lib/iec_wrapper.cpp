//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "driver_factory.h"

// объявление фуш=нкций IEC модуля
void config_init__(void);
void config_run__(unsigned long tick);

class IecWrapper : public IIecModule {
public:
    void initialize() override {
        config_init__();
        //glueVars();
    }

    void run_cycle() override {
        config_run__(tick_++);
    }

    void shutdown() override {
        // При необходимости
    }

private:
    unsigned long tick_ = 0;
};

// Регистрация модуля
IEC_REGISTER(IecWrapper)