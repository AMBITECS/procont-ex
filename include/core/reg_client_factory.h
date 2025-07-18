//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#ifndef CLIENT_FACTORY_IMPL_H
#define CLIENT_FACTORY_IMPL_H

#include "api_driver.h"
#include "reg_server.h"

class ClientFactoryImpl : public IClientFactory {
public:
    explicit ClientFactoryImpl(RegServer& server);

    std::shared_ptr<IRegClient> createClient(
            const std::string& name,
            IClientCallback* callback
    ) override;

private:
    RegServer& server_;
};

#endif // CLIENT_FACTORY_IMPL_H