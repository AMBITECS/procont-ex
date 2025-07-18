#pragma once

#include "reg_server.h"

#include <vector>
#include <memory>

class IRegClient;

class Binder {
private:
    static std::unique_ptr<Binder> _instance;

    struct Binding {
        Address  addr{};    // Address to bind
        void*    pvar{};    // Pointer-to-var
        VAR_TYPE type{};    // Variant type
    };

    std::vector<Binding>        binds;
    std::shared_ptr<IRegClient> _regClient;

public:
    static Binder& instance();

    Binder(const Binder&) = delete;
    Binder& operator=(const Binder&) = delete;

    void bind(const std::string& regNotation, void* iecVar, VAR_TYPE type);
    void updateToIec();
    void updateFromIec();

private:
    Binder(); //= default;
};
