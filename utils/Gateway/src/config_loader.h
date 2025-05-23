//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <unordered_map>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>

namespace sft::dtm::utils {

    template <typename T>
    class ConfigLoader {
    public:
        ConfigLoader(const std::string& configPath) {
            loadFromFile(configPath);
        }

        const T& getConfig() const { return config_; }

    private:
        void loadFromFile(const std::string& path) {
            std::ifstream file(path);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open config file: " + path);
            }

            std::unordered_map<std::string, std::string> configMap;
            std::string line;

            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;

                size_t delimiterPos = line.find('=');
                if (delimiterPos == std::string::npos) continue;

                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);

                trim(key);
                trim(value);

                if (!key.empty() && !value.empty()) {
                    configMap[key] = value;
                }
            }

            parseConfig(configMap);
        }

        void trim(std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        }

        void parseConfig(const std::unordered_map<std::string, std::string>& configMap) {
            if constexpr (std::is_member_function_pointer_v<decltype(&T::configure)>) {
                config_.configure(configMap);
            } else {
                static_assert(std::is_member_function_pointer_v<decltype(&T::configure)>,
                              "Config struct must provide configure() method");
            }
        }

        T config_;
    };

} // namespace sft::dtm::utils
