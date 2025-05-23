//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <unordered_map>

namespace sft::dtm::gateway {

    class GateConfig {
    public:
        GateConfig(const std::string& configPath = "dtm-conf.properties");

        struct Props {
            std::string host{"127.0.0.1"};
            int admPort{5501};
            int subPort{5502};
            int pubPort{5503};
            int timeout{500};
            int maxRetries{3};
            int maxQueueSize{128};
            int heartbeatInterval{5000};
            int reconnectDelay{3000};
        };

        const Props& getProps() const { return props_; }

    private:
        void loadFromFile(const std::string& path);
        void parseConfig(const std::unordered_map<std::string, std::string>& configMap);

        Props props_;

    public:
//        std::string findConfigFile() {
//            const std::vector<std::string> locations = {
//                    "./dtm-conf.properties",
//                    "/etc/dtm/dtm-conf.properties",
//                    "/usr/local/etc/dtm/dtm-conf.properties"
//            };
//
//            for (const auto& path : locations) {
//                std::ifstream file(path);
//                if (file.good()) return path;
//            }
//
//            return ""; // не найден
//        }
    };

} // namespace sft::dtm::gateway