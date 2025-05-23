//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "dto.h"
#include "gate_config.h"

#include <zmq.hpp>
#include <zmq_addon.hpp>

#include <atomic>
#include <memory>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <string>

namespace sft::dtm::gateway {

    class IGate {
    public:
        virtual ~IGate() = default;
        virtual void send(std::shared_ptr<void> message) = 0;
        virtual void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) = 0;
        virtual bool connect() = 0;
        virtual void disconnect() = 0;
        [[nodiscard]] virtual bool isRunning() const = 0;
    };

    class Gate final : public IGate
    {
    public:
//        struct Props {
//            std::string host{"127.0.0.1"};
//            int admPort             {5501};     // Порт администрирования
//            int subPort             {5502};     // Порт подписки
//            int pubPort             {5503};     // Порт публикации
//
//            int timeout             {500};
//            int maxRetries          {3};
//            int maxQueueSize        {128};
//            int heartbeatInterval   {5000};
//            int reconnectDelay      {3000};
//        };

        enum class State {
            DISCONNECTED,
            CONNECTING,
            CONNECTED,
            DISCONNECTING,
            FAILED
        };

    private:
        // Member variables
        GateConfig::Props props_;
        std::atomic<State> state_{State::DISCONNECTED};
        std::atomic<bool> running_{false};

        // ZMQ resources
        zmq::context_t context_;
        std::unique_ptr<zmq::socket_t> admSocket_;
        std::unique_ptr<zmq::socket_t> subSocket_;
        std::unique_ptr<zmq::socket_t> pubSocket_;
        std::mutex zmqMutex_;

        // Message queue
        std::queue<std::shared_ptr<void>> outboundQueue_;
        std::mutex queueMutex_;
        std::condition_variable queueCV_;

        // Handlers and listeners
        std::function<void(std::shared_ptr<void>)>      inboundHandler_;
        std::vector<std::function<void(State, State)>>  stateListeners_;
        std::mutex listenersMutex_;

        // Worker threads
        std::thread receiverThread_;
        std::thread senderThread_;
        std::thread heartbeatThread_;

    public:
        explicit Gate(const GateConfig& config): Gate(config.getProps()) {}
        explicit Gate(const GateConfig::Props& props);
        ~Gate() override;

        // IGate interface implementation
        void send(std::shared_ptr<void> message) override;
        void setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) override;
        bool connect() override;
        void disconnect() override;
        [[nodiscard]] bool isRunning() const override;

        // Additional functionality
        [[nodiscard]] State getState() const;
        void addStateChangeListener(std::function<void(State, State)> listener);

    private:
        // Internal methods
        void recvLoop();
        void sendLoop();

        void heartbeatLoop();
        bool performHeartbeat();

        void attemptReconnect();

        void changeState(State newState);
        void cleanupResources();

        void handleAdminMessage();
        void handleSubscription();

        void sendToSocket(std::shared_ptr<void> msg);

        void notifyStateChanged(State oldState, State newState);
        void notifyConnectionLost();
        void notifyConnectionRestored();

        // Helper methods
        [[nodiscard]] std::string getAddress(const std::string& host, int port) const;
        static std::string stateToString(State state);
    };

} // namespace sft::dtm::gateway