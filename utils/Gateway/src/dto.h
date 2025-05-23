//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "ikeyholder.h"
#include "quality.h"
#include "variant.h"
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace sft::dtm::gateway {

// Базовый класс для всех DTO с реализацией IKeyHolder
    class DtoBase : public IKeyHolder {
    public:
        virtual ~DtoBase() = default;
        [[nodiscard]] virtual std::string toJSON() const = 0;
    };

// Инициализация соединения
    struct Init : public DtoBase {
        struct Write {
            std::string topic;
            std::string url;
            Write(std::string t, std::string u) : topic(std::move(t)), url(std::move(u)) {}
        };

        struct Scada {
            std::string url;
            explicit Scada(std::string u) : url(std::move(u)) {}
        };

        struct Model {
            std::string url;
            explicit Model(std::string u) : url(std::move(u)) {}
        };

        struct Tag {
            std::string key = "unknown";
            std::string scadatag;
            std::string modeltag;
            VAR_TYPE type = VAR_TYPE::VT_SINT32;
            VARIANT value = VARIANT(0);

            bool isValid() const {
                return (key != "unknown" && (!scadatag.empty() || !modeltag.empty()));
            }
        };

        std::string key;
        Write write;
        Scada scada;
        Model model;
        std::vector<Tag> tags;

        Init(std::string k, std::string urlWrite, std::string urlScada, std::string urlModel)
                : key(std::move(k)),
                  write(key, std::move(urlWrite)),
                  scada(std::move(urlScada)),
                  model(std::move(urlModel)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] std::string toJSON() const override {
            json j;
            j["key"] = key;
            j["write"] = {{"topic", write.topic}, {"url", write.url}};
            j["scada"] = {{"url", scada.url}};
            j["model"] = {{"url", model.url}};

            if (!tags.empty()) {
                json tagsArray = json::array();
                for (const auto& tag : tags) {
                    json t;
                    t["key"] = tag.key;
                    t["scadatag"] = tag.scadatag;
                    t["modeltag"] = tag.modeltag;
                    t["type"] = static_cast<int>(tag.type);
                    t["value"] = tag.value.toString();
                    tagsArray.push_back(t);
                }
                j["tags"] = tagsArray;
            }

            return j.dump();
        }

        static Init fromJSON(const std::string& jsonStr) {
            auto j = json::parse(jsonStr);
            Init init(
                    j["key"].get<std::string>(),
                    j["write"]["url"].get<std::string>(),
                    j["scada"]["url"].get<std::string>(),
                    j["model"]["url"].get<std::string>()
            );

            if (j.contains("tags")) {
                for (const auto& tag : j["tags"]) {
                    Init::Tag t;
                    t.key = tag["key"].get<std::string>();
                    t.scadatag = tag["scadatag"].get<std::string>();
                    t.modeltag = tag["modeltag"].get<std::string>();
                    t.type = static_cast<VAR_TYPE>(tag["type"].get<int>());
                    t.value = VARIANT::fromString(tag["value"].get<std::string>(), t.type);
                    init.tags.push_back(t);
                }
            }

            return init;
        }

        bool addTag(const Tag& tag) {
            if (tag.isValid()) {
                tags.push_back(tag);
                return true;
            }
            return false;
        }
    };

// Завершение соединения
    struct Exit : public DtoBase {
        std::string key;

        explicit Exit(std::string k) : key(std::move(k)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] std::string toJSON() const override {
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

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] std::string toJSON() const override {
            json j;
            j["key"] = key;
            j["subscription"] = {
                    {"topic", key},
                    {"keys", keys}
            };
            return j.dump();
        }

        static Subs fromJSON(const std::string& jsonStr) {
            auto j = json::parse(jsonStr);
            return Subs{
                    j["key"].get<std::string>(),
                    j["subscription"]["keys"].get<std::vector<std::string>>()
            };
        }
    };

// Отправка данных
    struct Send : public DtoBase {
        struct Tag {
            std::string key = "key";
            VARIANT value = VARIANT(0);
            bool prior = true;
        };

        std::string key;
        std::vector<Tag> values;

        Send(std::string k, std::vector<Tag> v)
                : key(std::move(k)), values(std::move(v)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] std::string toJSON() const override {
            json j;
            j["key"] = key;

            json valuesArray = json::array();
            for (const auto& tag : values) {
                json item;
                item["key"] = tag.key;
                item["value"] = tag.value.toString();
                item["prior"] = tag.prior;
                valuesArray.push_back(item);
            }
            j["onchangevalues"] = valuesArray;

            return j.dump();
        }

        static Send fromJSON(const std::string& jsonStr) {
            auto j = json::parse(jsonStr);
            std::vector<Tag> values;

            for (const auto& item : j["onchangevalues"]) {
                Tag t;
                t.key = item["key"].get<std::string>();
                t.value = VARIANT::fromString(item["value"].get<std::string>());
                t.prior = item["prior"].get<bool>();
                values.push_back(t);
            }

            return Send{
                    j["key"].get<std::string>(),
                    std::move(values)
            };
        }
    };

// Получение данных
    struct Recv : public DtoBase {
        struct Tag {
            std::string key = "key";
            VARIANT value = VARIANT(0);
            Quality quality = Quality::GOOD;
            std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();

            Tag(std::string k, VARIANT v, Quality q, std::chrono::system_clock::time_point ts)
                    : key(std::move(k)), value(std::move(v)), quality(q), timestamp(ts) {}
        };

        std::string key;
        std::vector<Tag> data;

        Recv(std::string k, std::vector<Tag> d)
                : key(std::move(k)), data(std::move(d)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] std::string toJSON() const override {
            json j;
            j["key"] = key;

            json valuesArray = json::array();
            for (const auto& tag : data) {
                json item;
                item["key"] = tag.key;
                item["value"] = tag.value.toString();
                item["quality"] = static_cast<int>(tag.quality);

                auto time_t = std::chrono::system_clock::to_time_t(tag.timestamp);
                char timeStr[20];
                std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));
                item["timestamp"] = timeStr;

                valuesArray.push_back(item);
            }
            j["onchangevalues"] = valuesArray;

            return j.dump();
        }

        static Recv fromJSON(const std::string& jsonStr) {
            auto j = json::parse(jsonStr);
            std::vector<Tag> data;

            for (const auto& item : j["onchangevalues"]) {
                std::tm tm = {};
                std::istringstream ss(item["timestamp"].get<std::string>());
                ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                auto time_point = std::chrono::system_clock::from_time_t(std::mktime(&tm));

                data.emplace_back(
                        item["key"].get<std::string>(),
                        VARIANT::fromString(item["value"].get<std::string>()),
                        QualityUtils::fromInt(item["quality"].get<int>()),
                        time_point
                );
            }

            return Recv{
                    j["key"].get<std::string>(),
                    std::move(data)
            };
        }
    };

// Ответ на запрос
    struct Resp : public DtoBase {
        static constexpr int SUCCESS = 200;
        static constexpr int BAD_REQUEST = 400;
        static constexpr int NOT_JSON = 415;
        static constexpr int INTERNAL_ERROR = 500;
        static constexpr int REQUEST_HANDLE_ERROR = 502;

        std::string key;
        int result = SUCCESS;
        std::string message;

        Resp(std::string k, int r, std::string m)
                : key(std::move(k)), result(r), message(std::move(m)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] bool isSuccess() const { return result >= 200 && result < 300; }

        [[nodiscard]] std::string toJSON() const override {
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
                    j["result"].get<int>(),
                    j["message"].get<std::string>()
            };
        }

        static Resp success(std::string key, std::string message = "OK") {
            return Resp(std::move(key), SUCCESS, std::move(message));
        }

        static Resp error(std::string key, std::string message) {
            return Resp(std::move(key), INTERNAL_ERROR, std::move(message));
        }
    };

// Информация о соединении
    struct Info : public DtoBase {
        struct Connection {
            std::string channel;
            bool status;

            Connection(std::string c, bool s) : channel(std::move(c)), status(s) {}

            static Connection connected(std::string channel) {
                return Connection(std::move(channel), true);
            }

            static Connection disconnected(std::string channel) {
                return Connection(std::move(channel), false);
            }
        };

        std::string key;
        Connection connection;

        Info(std::string k, Connection c) : key(std::move(k)), connection(std::move(c)) {}

        // IKeyHolder implementation
        [[nodiscard]] std::string _key() const override { return key; }
        void _key(const std::string& k) override { key = k; }

        [[nodiscard]] bool isConnected() const { return connection.status; }
        [[nodiscard]] std::string channel() const { return connection.channel; }

        [[nodiscard]] std::string toJSON() const override {
            json j;
            j["key"] = key;
            j["connection"] = {
                    {"channel", connection.channel},
                    {"status", connection.status}
            };
            return j.dump();
        }

        static Info fromJSON(const std::string& jsonStr) {
            auto j = json::parse(jsonStr);
            return Info{
                    j["key"].get<std::string>(),
                    Connection{
                            j["connection"]["channel"].get<std::string>(),
                            j["connection"]["status"].get<bool>()
                    }
            };
        }

        static Info create(std::string key, std::string channel, bool status) {
            return Info(std::move(key), Connection(std::move(channel), status);
        }

        static Info connected(std::string key, std::string channel) {
            return Info(std::move(key), Connection::connected(std::move(channel)));
        }

        static Info disconnected(std::string key, std::string channel) {
            return Info(std::move(key), Connection::disconnected(std::move(channel)));
        }
    };

} // namespace sft::dtm::gateway
