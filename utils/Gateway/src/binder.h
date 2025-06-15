#pragma once

#include "registry.h"
#include <vector>
#include <memory>

#include "proxy.h"

class Binder {
private:
    static std::unique_ptr<Binder> _instance;

    struct Binding {
        Address addr;
        void* pvar{};
    };

    std::vector<Binding> binds;

    // Вспомогательная структура для ошибок
    template<typename T>
    struct TypeNotSupported {
        static_assert(sizeof(T) == 0, "Type not supported for this category");
    };

public:
    static Binder& instance();

    Binder(const Binder&) = delete;
    Binder& operator=(const Binder&) = delete;

    void bind(const std::string& regNotation, void* iecVar);
    void updateToIec();
    void updateFromIec();

    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

private:
    Binder() = default;

    template<Registry::Category CAT>
    void processWithCategory(const Address &addr, void *iecVar, bool toRegistry);

    template<typename T, Registry::Category CAT>
    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    template<typename T, Registry::Category CAT>
    auto& getProxy();
};
