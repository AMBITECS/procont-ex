#pragma once

#include "reg_client.h"

#include <vector>
#include <memory>

class Binder {
private:
    static std::unique_ptr<Binder> _instance;

    struct Binding {
        Address addr{};
        void* pvar{};
        VAR_TYPE type{};
    };

    std::vector<Binding> binds;
    std::shared_ptr<IRegClient> _regClient;

public:
    static Binder& instance();

    Binder(const Binder&) = delete;
    Binder& operator=(const Binder&) = delete;

    void bind(const std::string& regNotation, void* iecVar, PLC_TYPE type);
    void updateToIec();
    void updateFromIec();

private:
    Binder();
};
