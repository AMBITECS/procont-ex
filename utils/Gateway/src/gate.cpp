//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "gate.h"
#include "dto.h"

#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std::chrono_literals;
namespace sft::dtm::gateway {

    Gate::Gate(const Props& props)
            : props_(props),
              context_(1),
              admSocket_(std::make_unique<zmq::socket_t>(context_, ZMQ_REQ)),
              subSocket_(std::make_unique<zmq::socket_t>(context_, ZMQ_SUB)),
              pubSocket_(std::make_unique<zmq::socket_t>(context_, ZMQ_PUB)) {

        // Configure sockets
        admSocket_->set(zmq::sockopt::rcvtimeo, props_.timeout);
        admSocket_->set(zmq::sockopt::sndtimeo, props_.timeout);
        subSocket_->set(zmq::sockopt::rcvtimeo, props_.timeout);

        std::cout << "Gate initialized for " << props_.host << ":" << props_.admPort << std::endl;
    }

    Gate::~Gate() {
        disconnect();
        std::cout << "Gate destroyed" << std::endl;
    }

    void Gate::send(std::shared_ptr<void> message) {
        if (!message) {
            throw std::invalid_argument("Message cannot be null");
        }

        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            if (outboundQueue_.size() >= props_.maxQueueSize) {
                throw std::runtime_error("Outbound queue is full");
            }
            outboundQueue_.push(message);
        }

        queueCV_.notify_one();
    }

    void Gate::setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        inboundHandler_ = handler;
    }

    bool Gate::connect() {
        if (state_ == State::CONNECTED) return true;

        changeState(State::CONNECTING);
        std::cout << "Connecting to gateway..." << std::endl;

        try {
            admSocket_->connect(getAddress(props_.host, props_.admPort));
            subSocket_->connect(getAddress(props_.host, props_.subPort));
            subSocket_->set(zmq::sockopt::subscribe, "");
            pubSocket_->bind(getAddress("*", props_.pubPort));

            running_ = true;
            receiverThread_ = std::thread(&Gate::recvLoop, this);
            senderThread_ = std::thread(&Gate::sendLoop, this);
            heartbeatThread_ = std::thread(&Gate::heartbeatLoop, this);

            changeState(State::CONNECTED);
            return true;
        } catch (const zmq::error_t& e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
            cleanupResources();
            changeState(State::FAILED);
            return false;
        }
    }

    void Gate::disconnect() {
        if (state_ == State::DISCONNECTED ||
            state_ == State::DISCONNECTING) {
            return;
        }

        changeState(State::DISCONNECTING);
        std::cout << "Disconnecting..." << std::endl;

        running_ = false;
        queueCV_.notify_all();

        if (receiverThread_.joinable()) receiverThread_.join();
        if (senderThread_.joinable()) senderThread_.join();
        if (heartbeatThread_.joinable()) heartbeatThread_.join();

        cleanupResources();
        changeState(State::DISCONNECTED);
    }

    bool Gate::isRunning() const {
        return state_ == State::CONNECTED;
    }

    Gate::State Gate::getState() const {
        return state_.load();
    }

    void Gate::addStateChangeListener(std::function<void(State, State)> listener) {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        stateListeners_.push_back(listener);
    }

    // Private methods implementation
    void Gate::recvLoop() {
        // Prepare poll items
        zmq::pollitem_t items[] = {
                {*admSocket_, 0, ZMQ_POLLIN, 0},
                {*subSocket_, 0, ZMQ_POLLIN, 0}
        };

        while (running_) {
            try {
                // Poll with 100-ms timeout
                zmq::poll(items, 2, 100ms);

                if (!running_) break;

                // Check admin socket
                if (items[0].revents & ZMQ_POLLIN) {
                    handleAdminMessage();
                }

                // Check subscription socket
                if (items[1].revents & ZMQ_POLLIN) {
                    handleSubscription();
                }
            } catch (const zmq::error_t& e) {
                if (e.num() != ETERM) { // Ignore termination errors
                    std::cerr << "Recv error: " << e.what() << std::endl;
                    notifyConnectionLost();
                }
                break;
            } catch (...) {
                if (running_) {
                    std::cerr << "Unexpected receive error" << std::endl;
                    notifyConnectionLost();
                }
                break;
            }
        }
    }

    void Gate::sendLoop() {
        while (running_) {
            std::shared_ptr<void> message;

            {
                std::unique_lock<std::mutex> lock(queueMutex_);
                queueCV_.wait_for(lock, 100ms, [this]() {
                    return !outboundQueue_.empty() || !running_;
                });

                if (!running_) break;
                if (outboundQueue_.empty()) continue;

                message = outboundQueue_.front();
                outboundQueue_.pop();
            }

            if (message) {
                try {
                    sendToSocket(message);
                } catch (const zmq::error_t& e) {
                    std::cerr << "Send error: " << e.what() << std::endl;
                    notifyConnectionLost();
                } catch (...) {
                    if (running_) {
                        std::cerr << "Unexpected send error" << std::endl;
                        notifyConnectionLost();
                    }
                }
            }
        }
    }

    void Gate::heartbeatLoop() {
        while (running_) {
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(props_.heartbeatInterval));

            if (!running_) break;

            if (!performHeartbeat()) {
                std::cerr << "Heartbeat failed, attempting reconnect..." << std::endl;
                attemptReconnect();
            }
        }
    }

    bool Gate::performHeartbeat() {
        try {
            zmq::message_t ping("PING", 4);
            if (!admSocket_->send(ping, zmq::send_flags::dontwait)) {
                return false;
            }

            zmq::message_t pong;
            if (!admSocket_->recv(pong, zmq::recv_flags::dontwait)) {
                return false;
            }

            return std::string_view(static_cast<char*>(pong.data()), pong.size()) == "PONG";
        } catch (...) {
            return false;
        }
    }

    void Gate::attemptReconnect() {
        if (state_ == State::DISCONNECTING ||
            state_ == State::DISCONNECTED) {
            return;
        }

        changeState(State::FAILED);

        for (int attempt = 1; attempt <= props_.maxRetries && running_; ++attempt) {
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(props_.reconnectDelay));

            if (connect()) {
                notifyConnectionRestored();
                return;
            }
        }

        if (running_) {
            disconnect();
        }
    }

    void Gate::changeState(State newState) {
        State oldState = state_.exchange(newState);
        if (oldState != newState) {
            notifyStateChanged(oldState, newState);
        }
    }

    void Gate::cleanupResources() {
        std::lock_guard<std::mutex> lock(zmqMutex_);

        try {
            if (admSocket_) admSocket_->close();
            if (subSocket_) subSocket_->close();
            if (pubSocket_) pubSocket_->close();
        } catch (...) {
            // Ignore errors during cleanup
        }

        admSocket_.reset();
        subSocket_.reset();
        pubSocket_.reset();

        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            std::queue<std::shared_ptr<void>> empty;
            std::swap(outboundQueue_, empty);
        }
    }

    void Gate::handleAdminMessage() {
        zmq::message_t msg;
        if (admSocket_->recv(msg)) {
            try {
                auto resp = Resp::fromJSON(
                        std::string(static_cast<char*>(msg.data()), msg.size()));

                std::lock_guard<std::mutex> lock(listenersMutex_);
                if (inboundHandler_) {
                    inboundHandler_(std::make_shared<Resp>(resp));
                }
            } catch (...) {
                std::cerr << "Failed to parse admin message" << std::endl;
            }
        }
    }

    void Gate::handleSubscription() {
        zmq::message_t msg;
        if (subSocket_->recv(msg)) {
            try {
                auto recv = Recv::fromJSON(
                        std::string(static_cast<char*>(msg.data()), msg.size()));

                std::lock_guard<std::mutex> lock(listenersMutex_);
                if (inboundHandler_) {
                    inboundHandler_(std::make_shared<Recv>(recv));
                }
            } catch (...) {
                std::cerr << "Failed to parse subscription message" << std::endl;
            }
        }
    }

    void Gate::sendToSocket(std::shared_ptr<void> msg) {
        std::string json;

        // Проверяем тип сообщения через dynamic_pointer_cast
        if (auto init = std::static_pointer_cast<Init>(msg)) {
            json = init->toJSON();
        } else if (auto exit = std::static_pointer_cast<Exit>(msg)) {
            json = exit->toJSON();
        } else if (auto subs = std::static_pointer_cast<Subs>(msg)) {
            json = subs->toJSON();
        } else if (auto send = std::static_pointer_cast<Send>(msg)) {
            json = send->toJSON();
        } else {
            throw std::invalid_argument("Unsupported message type");
        }

        zmq::message_t zmqMsg(json.begin(), json.end());
        if (std::static_pointer_cast<Send>(msg)) {
            pubSocket_->send(zmqMsg, zmq::send_flags::none);
        } else {
            admSocket_->send(zmqMsg, zmq::send_flags::none);
        }
    }

    void Gate::notifyStateChanged(State oldState, State newState) {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        for (auto& listener : stateListeners_) {
            try {
                listener(oldState, newState);
            } catch (...) {
                // Ignore listener exceptions
            }
        }
    }

    void Gate::notifyConnectionLost() {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        // Additional notification logic if needed
    }

    void Gate::notifyConnectionRestored() {
        std::lock_guard<std::mutex> lock(listenersMutex_);
        // Additional notification logic if needed
    }

    std::string Gate::getAddress(const std::string& host, int port) const {
        return "tcp://" + host + ":" + std::to_string(port);
    }

    std::string Gate::stateToString(State state) {
        switch (state) {
            case State::DISCONNECTED: return "DISCONNECTED";
            case State::CONNECTING: return "CONNECTING";
            case State::CONNECTED: return "CONNECTED";
            case State::DISCONNECTING: return "DISCONNECTING";
            case State::FAILED: return "FAILED";
            default: return "UNKNOWN";
        }
    }

} // namespace sft::dtm::gateway