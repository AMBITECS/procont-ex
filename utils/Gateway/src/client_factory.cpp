//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "client_factory.h"
#include "reg_server.h"

ClientFactoryImpl::ClientFactoryImpl(RegServer& server): server_(server) {}

std::shared_ptr<IRegClient> ClientFactoryImpl::createClient(
        const std::string& name,
        IClientCallback* callback
) {
    return server_.createClient(name, callback);
}