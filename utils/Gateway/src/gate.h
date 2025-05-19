//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "dto.h"
#include "zmq.h"

#include "../../cppzmq/zmq.hpp"

#include <atomic>
#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unordered_map>

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
        std::string host = "127.0.0.1";
        int admPort = 5501;
        int subPort = 5502;
        int pubPort = 5503;
        int timeout = 500;
        int maxRetries = 3;
        int maxQueueSize = 128;
        int heartbeatInterval = 5000;
    };

    enum class State { DISCONNECTED, CONNECTING, CONNECTED, DISCONNECTING, FAILED };

    explicit Gate(const Props& props);
    ~Gate() override;

    // IGate implementation
    void send(std::shared_ptr<void> message) override;
    void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) override;
    bool connect() override;
    void disconnect() override;

    // State management
    [[nodiscard]] State getState() const;
    void addStateChangeListener(std::function<void(State, State)> listener);

private:
    void recvLoop();
    void sendLoop();
    void startHeartbeat();
    bool checkConnection();
    void reconnect();
    void changeState(State newState);

    Props props_;
    std::atomic<State> state_{State::DISCONNECTED};
    zmq::context_t context_;
    zmq::socket_t admSocket_;
    zmq::socket_t subSocket_;
    zmq::socket_t pubSocket_;

    std::mutex                                  queueMutex_;
    std::condition_variable                     queueCV_;
    std::queue<std::shared_ptr<void>>           outboundQueue_;
    std::function<void(std::shared_ptr<void>)>  inboundHandler_;

    std::thread receiverThread_;
    std::thread senderThread_;
    std::thread heartbeatThread_;
    std::vector<std::function<void(State, State)>> stateListeners_;
    std::mutex listenersMutex_;
};