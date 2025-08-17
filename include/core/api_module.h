//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Интерфейс жизненного цикла Procont-модуля
class IProModule {
public:
    virtual ~IProModule() = default;
    virtual bool initialize(const json& config) = 0;
    virtual void do_work()  = 0;
    virtual void shutdown() = 0;

    // Состояние модуля
//    virtual bool is_running() const = 0;
//    [[nodiscard]] virtual std::string status() const = 0;

    [[nodiscard]] virtual std::string name() const = 0;
};
