//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct ModuleConfig {
    std::string name;           // имя модуля
    std::string library_name;   // имя библиотеки
    std::string library_path;   // путь библиотеки
    json        config;         // конфигурация модуля

    // Сериализация в JSON (to_json)
    friend void to_json(json& j, const ModuleConfig& cfg) {
        j = json{
                {"name",            cfg.name},
                {"library_name",    cfg.library_name},
                {"library_path",    cfg.library_path},
                {"config",          cfg.config}
        };
    }

    // Десериализация из JSON (from_json)
    friend void from_json(const json& j, ModuleConfig& cfg) {
        j.at("name").get_to(cfg.name);
        j.at("library_name").get_to(cfg.library_name);
        j.at("library_path").get_to(cfg.library_path);
        j.at("config").get_to(cfg.config);
    }
};
