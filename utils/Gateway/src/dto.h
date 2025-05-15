//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Базовый класс для всех DTO
class DtoBase {
public:
    virtual ~DtoBase() = default;
    virtual std::string toJSON() const = 0;
};

// Инициализация соединения
struct Init : public DtoBase {
    std::string key;
    std::string urlWrite;
    std::string urlScada;
    std::string urlModel;

    Init(std::string k, std::string uw, std::string us, std::string um)
            : key(std::move(k)), urlWrite(std::move(uw)),
              urlScada(std::move(us)), urlModel(std::move(um)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;
        j["urlWrite"] = urlWrite;
        j["urlScada"] = urlScada;
        j["urlModel"] = urlModel;
        return j.dump();
    }

    static Init fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        return Init{
                j["key"].get<std::string>(),
                j["urlWrite"].get<std::string>(),
                j["urlScada"].get<std::string>(),
                j["urlModel"].get<std::string>()
        };
    }
};

// Завершение соединения
struct Exit : public DtoBase {
    std::string key;

    explicit Exit(std::string k) : key(std::move(k)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;
        return j.dump();
    }

    static Exit fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        return Exit{j["key"].get<std::string>()};
    }
};

// Подписка на данные
struct Subs : public DtoBase {
    std::string key;
    std::vector<std::string> keys;

    Subs(std::string k, std::vector<std::string> ks)
            : key(std::move(k)), keys(std::move(ks)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;
        j["keys"] = keys;
        return j.dump();
    }

    static Subs fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        return Subs{
                j["key"].get<std::string>(),
                j["keys"].get<std::vector<std::string>>()
        };
    }
};

// Отправка данных
struct Send : public DtoBase {
    std::string key;
    std::vector<std::pair<std::string, double>> values;

    Send(std::string k, std::vector<std::pair<std::string, double>> v)
            : key(std::move(k)), values(std::move(v)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;

        json valuesArray = json::array();
        for (const auto& [name, value] : values) {
            json item;
            item["name"] = name;
            item["value"] = value;
            valuesArray.push_back(item);
        }
        j["values"] = valuesArray;

        return j.dump();
    }

    static Send fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        std::vector<std::pair<std::string, double>> values;

        for (const auto& item : j["values"]) {
            values.emplace_back(
                    item["name"].get<std::string>(),
                    item["value"].get<double>()
            );
        }

        return Send{
                j["key"].get<std::string>(),
                std::move(values)
        };
    }
};

// Получение данных
struct Recv : public DtoBase {
    std::string key;
    std::vector<std::pair<std::string, double>> values;

    Recv(std::string k, std::vector<std::pair<std::string, double>> v)
            : key(std::move(k)), values(std::move(v)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;

        json valuesArray = json::array();
        for (const auto& [name, value] : values) {
            json item;
            item["name"] = name;
            item["value"] = value;
            valuesArray.push_back(item);
        }
        j["values"] = valuesArray;

        return j.dump();
    }

    static Recv fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        std::vector<std::pair<std::string, double>> values;

        for (const auto& item : j["values"]) {
            values.emplace_back(
                    item["name"].get<std::string>(),
                    item["value"].get<double>()
            );
        }

        return Recv{
                j["key"].get<std::string>(),
                std::move(values)
        };
    }
};

// Ответ на запрос
struct Resp : public DtoBase {
    std::string key;
    bool result;
    std::string message;

    Resp(std::string k, bool res, std::string msg)
            : key(std::move(k)), result(res), message(std::move(msg)) {}

    std::string toJSON() const override {
        json j;
        j["key"] = key;
        j["result"] = result;
        j["message"] = message;
        return j.dump();
    }

    static Resp fromJSON(const std::string& jsonStr) {
        auto j = json::parse(jsonStr);
        return Resp{
                j["key"].get<std::string>(),
                j["result"].get<bool>(),
                j["message"].get<std::string>()
        };
    }
};
