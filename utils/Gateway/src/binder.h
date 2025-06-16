#pragma once

#include "registry.h"
#include <vector>
#include <memory>

#include "proxy.h"
#include "reg_client.h"

class Binder {
private:
    static std::unique_ptr<Binder> _instance;

    struct Binding {
        Address addr;
        void* pvar{};
    };

    std::vector<Binding> binds;
    std::shared_ptr<IRegClient> _regClient;

public:
    static Binder& instance();

    Binder(const Binder&) = delete;
    Binder& operator=(const Binder&) = delete;

    void bind(const std::string& regNotation, void* iecVar);
    void updateToIec();
    void updateFromIec();

private:
    Binder();
};
