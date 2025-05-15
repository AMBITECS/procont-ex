//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <string>
#include <stdexcept>
#include "../$install/zmq/include/zmq.h"
#include "../$install/zmq/include/zmq_utils.h"
//#include <zmq.h>

class IGate {
public:
    virtual ~IGate() = default;

    virtual void send(std::shared_ptr<void> message) = 0;
    virtual void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) = 0;
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
};

class Gate : public IGate {
public:
    struct Props {
        std::string gateIP = "127.0.0.1";
        int admPort = 5501;
        int subPort = 5502;
        int pubPort = 5503;
        int timeout = 5000;
        int maxcount = 128;
        int maxRetries = 3;
    };

    explicit Gate(const Props& props);
    ~Gate() override;

    // IGate implementation
    void send(std::shared_ptr<void> message) override;
    void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) override;
    bool connect() override;
    void disconnect() override;

private:
    void recvLoop();
    void sendLoop();
    void handleAdminMessage();
    void handleSubscription();
    void sendToSocket(std::shared_ptr<void> msg);

    Props props_;
    zmq::context_t context_;
    zmq::socket_t admSocket_;
    zmq::socket_t subSocket_;
    zmq::socket_t pubSocket_;

    std::function<void(std::shared_ptr<void>)> inboundHandler_;
    std::queue<std::shared_ptr<void>> outboundQueue_;
    std::mutex queueMutex_;
    std::condition_variable queueCV_;
    std::atomic<bool> running_{false};

    std::thread recvThread_;
    std::thread sendThread_;
    std::mutex handlerMutex_;
};
