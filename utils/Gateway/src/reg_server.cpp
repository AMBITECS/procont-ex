#include "reg_server.h"
#include "reg_client.h"
#include "registry.h"

RegServer& RegServer::instance() {
    static RegServer instance;
    return instance;
}

std::shared_ptr<IRegClient> RegServer::createClient(const std::string& client_name/*, Registry& registry*/) {
    if (clients_.find(client_name) != clients_.end()) {
        throw std::runtime_error("Client with name " + client_name + " already exists");
    }

    auto client = std::make_shared<RegClient>(client_name);
    clients_[client_name] = client;
    return client;
}

void RegServer::removeClient(const std::string& client_name) {
    clients_.erase(client_name);
}

void RegServer::updateAll() {
    for (auto& [name, client] : clients_) {
        client->update();
    }
}