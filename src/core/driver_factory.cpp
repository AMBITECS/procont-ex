//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "iec_factory.h"
#include "driver_factory.h"

#include <utility>

void IECFactory::register_iec(std::function<std::unique_ptr<IProModule>()> creator) {
    iec_creator_ = std::move(creator);
}

std::unique_ptr<IProModule> IECFactory::create_iec() {
    if (!iec_creator_) { throw std::runtime_error("IEC module not registered"); }
    return iec_creator_();
}

//-----------------------------------------------------------------------------
//void DriverFactory::register_driver(
//        //const std::string& name,
//        const char* name,  // Заменяем std::string& на const char*
//        const std::function<std::unique_ptr<IProModule>(IClientFactory*)>& creator
//) {
//    if (!name) { throw std::invalid_argument("Driver name cannot be null"); }
//    creators_[name] = [creator](const std::shared_ptr<IClientFactory>& shared_factory) {
//        return creator(shared_factory.get());
//    };
//}

//std::unique_ptr<IProModule> DriverFactory::create(
//        const std::string& name,
//        std::shared_ptr<IClientFactory> factory
//) {
//    auto it = creators_.find(name);
//    if (it == creators_.end()) {
//        throw std::runtime_error("Driver not registered: " + name);
//    }
//    return it->second(std::move(factory));
//}
