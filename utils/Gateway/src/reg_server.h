#ifndef REG_SERVER_H
#define REG_SERVER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "reg_client.h"

class Registry; // Forward declaration

class RegServer {
private:
    RegServer() = default;
    std::unordered_map<std::string, std::shared_ptr<RegClient>> clients_;

public:
    static RegServer& instance();

    RegServer(const RegServer&) = delete;
    RegServer& operator=(const RegServer&) = delete;

    std::shared_ptr<IRegClient> createClient(const std::string& client_name, Registry& registry);
    void removeClient(const std::string& client_name);

    // Для внутреннего использования Registry
    void updateAll();
};

#endif // REG_SERVER_H
