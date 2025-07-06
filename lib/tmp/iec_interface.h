//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
class IIecModule {
public:
    virtual ~IIecModule() = default;
    virtual void initialize() = 0;
    virtual void run_cycle() = 0;
    virtual void shutdown() = 0;
};
