//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "config_utils.h"
#include <string>
#include <unordered_map>

namespace sft::dtm::gateway {

    struct GateProps {
        std::string host{"127.0.0.1"};
        int admPort{5501};
        int subPort{5502};
        int pubPort{5503};
        int timeout{500};
        int maxRetries{3};
        int maxQueueSize{128};
        int heartbeatInterval{5000};
        int reconnectDelay{3000};

        void configure(const std::unordered_map<std::string, std::string>& configMap) {
            using namespace sft::dtm::utils;

            host = getConfigStr(configMap, "gate.host", host);
            admPort = getConfigInt(configMap, "gate.admPort", admPort);
            subPort = getConfigInt(configMap, "gate.subPort", subPort);
            pubPort = getConfigInt(configMap, "gate.pubPort", pubPort);
            timeout = getConfigInt(configMap, "gate.timeout", timeout);
            maxRetries = getConfigInt(configMap, "gate.maxRetries", maxRetries);
            maxQueueSize = getConfigInt(configMap, "gate.maxQueueSize", maxQueueSize);
            heartbeatInterval = getConfigInt(configMap, "gate.heartbeatInterval", heartbeatInterval);
            reconnectDelay = getConfigInt(configMap, "gate.reconnectDelay", reconnectDelay);
        }
    };

    using GateConfig = utils::ConfigLoader<GateProps>;

} // namespace sft::dtm::gateway