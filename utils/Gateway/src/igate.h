//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <functional>
#include <memory>

class IGate {
public:
    virtual ~IGate() = default;

    virtual void send(std::shared_ptr<void> message) = 0;
    virtual void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) = 0;
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
};
