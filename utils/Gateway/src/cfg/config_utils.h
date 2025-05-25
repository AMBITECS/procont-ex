//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "config_loader.h"
#include <string>
#include <unordered_map>
#include <iostream>

namespace sft::dtm::utils {

    inline int getConfigInt(const std::unordered_map<std::string, std::string>& configMap,
                            const std::string& key,
                            int defaultValue) {
        auto it = configMap.find(key);
        if (it != configMap.end()) {
            try {
                return std::stoi(it->second);
            } catch (...) {
                std::cerr << "Invalid integer value for '" << key
                          << "', using default: " << defaultValue << std::endl;
            }
        }
        return defaultValue;
    }

    inline std::string getConfigStr(const std::unordered_map<std::string, std::string>& configMap,
                                    const std::string& key,
                                    const std::string& defaultValue) {
        auto it = configMap.find(key);
        return (it != configMap.end()) ? it->second : defaultValue;
    }

    template<typename T>
    inline T getConfigEnum(const std::unordered_map<std::string, std::string>& configMap,
                           const std::string& key,
                           T defaultValue,
                           const std::unordered_map<std::string, T>& enumMap) {
        auto it = configMap.find(key);
        if (it != configMap.end()) {
            auto enumIt = enumMap.find(it->second);
            if (enumIt != enumMap.end()) {
                return enumIt->second;
            }
            std::cerr << "Invalid enum value for '" << key
                      << "', using default" << std::endl;
        }
        return defaultValue;
    }

} // namespace sft::dtm::utils