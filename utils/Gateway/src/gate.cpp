//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "gate.h"
//#include "zmq.h"
#include <iostream>
#include <chrono>
#include <utility>

Gate::Gate(const Props& props)
        : props_(props),
          context_(1),
          admSocket_(context_, ZMQ_REQ),
          subSocket_(context_, ZMQ_SUB),
          pubSocket_(context_, ZMQ_PUB) {
    // Configure sockets
    admSocket_.set(zmq::sockopt::rcvtimeo, props_.timeout);
    admSocket_.set(zmq::sockopt::sndtimeo, props_.timeout);
    subSocket_.set(zmq::sockopt::rcvtimeo, props_.timeout);
}

Gate::~Gate() {
    disconnect();
}

bool Gate::connect() {
    try {
        admSocket_.connect("tcp://" + props_.gateIP + ":" + std::to_string(props_.admPort));
        subSocket_.connect("tcp://" + props_.gateIP + ":" + std::to_string(props_.subPort));
        subSocket_.set(zmq::sockopt::subscribe, "");
        pubSocket_.bind("tcp://*:" + std::to_string(props_.pubPort));

        running_ = true;
        recvThread_ = std::thread(&Gate::recvLoop, this);
        sendThread_ = std::thread(&Gate::sendLoop, this);

        return true;
    } catch (const zmq::error_t& e) {
        std::cerr << "ZMQ connection failed: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return false;
    }
}

void Gate::disconnect() {
    running_ = false;
    queueCV_.notify_all();

    if (recvThread_.joinable()) {
        recvThread_.join();
    }
    if (sendThread_.joinable()) {
        sendThread_.join();
    }

    try {
        context_.close();
    } catch (const zmq::error_t& e) {
        std::cerr << "ZMQ context close error: " << e.what() << std::endl;
    }
}

void Gate::send(std::shared_ptr<void> message) {
    if (!message) {
        throw std::invalid_argument("Message cannot be null");
    }

    std::unique_lock<std::mutex> lock(queueMutex_);
    if (outboundQueue_.size() >= static_cast<size_t>(props_.maxcount)) {
        throw std::runtime_error("Outbound queue is full");
    }

    outboundQueue_.push(std::move(message));
    lock.unlock();
    queueCV_.notify_one();
}

void Gate::setInboundHandler(std::function<void(std::shared_ptr<void>)> handler) {
    std::lock_guard<std::mutex> lock(handlerMutex_);
    inboundHandler_ = std::move(handler);
}

void Gate::recvLoop() {
    zmq::pollitem_t items[] = {
            {static_cast<void*>(admSocket_), 0, ZMQ_POLLIN, 0},
            {static_cast<void*>(subSocket_), 0, ZMQ_POLLIN, 0}
    };

    while (running_) {
        try {
            zmq::poll(items, 2, props_.timeout);

            if (items[0].revents & ZMQ_POLLIN) {
                handleAdminMessage();
            }
            if (items[1].revents & ZMQ_POLLIN) {
                handleSubscription();
            }
        } catch (const zmq::error_t& e) {
            if (running_) {
                std::cerr << "ZMQ poll error: " << e.what() << std::endl;
            }
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Receive error: " << e.what() << std::endl;
            }
        }
    }
}

void Gate::handleAdminMessage() {
    zmq::message_t message;
    if (admSocket_.recv(message, zmq::recv_flags::none)) {
        std::string msgStr(static_cast<char*>(message.data()), message.size());

        std::lock_guard<std::mutex> lock(handlerMutex_);
        if (inboundHandler_) {
            try {
                // Здесь нужно преобразование из JSON в соответствующий DTO объект
                // Например: auto resp = Resp::fromJSON(msgStr);
                inboundHandler_(std::make_shared<std::string>(std::move(msgStr)));
            } catch (const std::exception& e) {
                std::cerr << "Error processing admin message: " << e.what() << std::endl;
            }
        }
    }
}

void Gate::handleSubscription() {
    zmq::message_t message;
    if (subSocket_.recv(message, zmq::recv_flags::none)) {
        std::string msgStr(static_cast<char*>(message.data()), message.size());

        std::lock_guard<std::mutex> lock(handlerMutex_);
        if (inboundHandler_) {
            try {
                // Здесь нужно преобразование из JSON в соответствующий DTO объект
                // Например: auto recv = Recv::fromJSON(msgStr);
                inboundHandler_(std::make_shared<std::string>(std::move(msgStr)));
            } catch (const std::exception& e) {
                std::cerr << "Error processing subscription message: " << e.what() << std::endl;
            }
        }
    }
}

void Gate::sendLoop() {
    while (running_) {
        std::shared_ptr<void> msg;

        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            queueCV_.wait_for(lock, std::chrono::milliseconds(100),
                              [this]() { return !outboundQueue_.empty() || !running_; });

            if (!running_) break;

            if (!outboundQueue_.empty()) {
                msg = outboundQueue_.front();
                outboundQueue_.pop();
            }
        }

        if (msg) {
            try {
                sendToSocket(msg);
            } catch (const std::exception& e) {
                std::cerr << "Error sending message: " << e.what() << std::endl;
            }
        }
    }
}

void Gate::sendToSocket(std::shared_ptr<void> msg) {
    // В реальной реализации здесь должно быть преобразование в JSON
    std::string jsonStr;

    if (auto initPtr = std::static_pointer_cast<Init>(msg)) {
        jsonStr = initPtr->toJSON();
    }
        // else if (другие типы сообщений)...
    else {
        throw std::invalid_argument("Unsupported message type");
    }

    zmq::message_t message(jsonStr.begin(), jsonStr.end());

    if (dynamic_cast<Send*>(static_cast<void*>(msg.get()))) {
        pubSocket_.send(message, zmq::send_flags::none);
    } else {
        admSocket_.send(message, zmq::send_flags::none);
    }
}
