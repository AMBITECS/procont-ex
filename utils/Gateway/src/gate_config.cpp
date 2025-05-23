//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "gate_config.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace sft::dtm::gateway {

    namespace {
        void trim(std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        }
    }

    GateConfig::GateConfig(const std::string& configPath) {
        try {
            loadFromFile(configPath);
        } catch (const std::exception& e) {
            std::cerr << "Failed to load config: " << e.what()
                      << ". Using default settings." << std::endl;
        }
    }

    void GateConfig::loadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open config file: " + path);
        }

        std::unordered_map<std::string, std::string> configMap;
        std::string line;

        while (std::getline(file, line)) {
            // Пропускаем комментарии и пустые строки
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

    void GateConfig::parseConfig(const std::unordered_map<std::string, std::string>& configMap) {
        auto getInt = [&](const std::string& key, int defaultValue) {
            auto it = configMap.find(key);
            if (it != configMap.end()) {
                try {
                    return std::stoi(it->second);
                } catch (...) {
                    std::cerr << "Invalid value for " << key << ", using default" << std::endl;
                }
            }
            return defaultValue;
        };

        auto getStr = [&](const std::string& key, const std::string& defaultValue) {
            auto it = configMap.find(key);
            return (it != configMap.end()) ? it->second : defaultValue;
        };

        props_.host = getStr("gate.host", props_.host);
        props_.admPort = getInt("gate.admPort", props_.admPort);
        props_.subPort = getInt("gate.subPort", props_.subPort);
        props_.pubPort = getInt("gate.pubPort", props_.pubPort);
        props_.timeout = getInt("gate.timeout", props_.timeout);
        props_.maxRetries = getInt("gate.maxRetries", props_.maxRetries);
        props_.maxQueueSize = getInt("gate.maxQueueSize", props_.maxQueueSize);
        props_.heartbeatInterval = getInt("gate.heartbeatInterval", props_.heartbeatInterval);
        props_.reconnectDelay = getInt("gate.reconnectDelay", props_.reconnectDelay);
    }

} // namespace sft::dtm::gateway

