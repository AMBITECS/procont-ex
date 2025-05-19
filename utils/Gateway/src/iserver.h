//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "client.h"
#include <memory>
#include <future>

class IServer {
public:
    virtual ~IServer() = default;
    virtual void registerClient(std::shared_ptr<Client> client) = 0;
    virtual void unregisterClient(std::shared_ptr<Client> client) = 0;

    virtual std::future<Response> sendRequest(
            std::shared_ptr<Client> client,
            std::shared_ptr<void> request,
            long timeoutMs) = 0;

    virtual void publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) = 0;
};

