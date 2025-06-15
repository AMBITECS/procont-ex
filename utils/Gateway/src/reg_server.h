#ifndef REG_SERVER_H
#define REG_SERVER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "reg_client.h"

class RegServer {
private:
    friend RegClient;

    // Карта именованных клиентов
    std::unordered_map<std::string, std::shared_ptr<RegClient>> clients_;

    RegServer() = default;
    void removeClient(const std::string& client_name);

public:
    // Применяется шаблон "singleton"
    static RegServer& instance();

    // Конструктов копий и оператор присваивания недоступны для singleton
    RegServer(const RegServer&) = delete;
    RegServer& operator=(const RegServer&) = delete;

    // Создание клиента
    std::shared_ptr<IRegClient> createClient(const std::string& client_name);

    // Обновление всех зарегистрированных клиентов
    void updateAll();
};

#endif // REG_SERVER_H
