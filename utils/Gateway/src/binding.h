#ifndef BINDING_MANAGER_H
#define BINDING_MANAGER_H

#include "registry.h"
#include "address.h"
#include <vector>
#include <string>
#include <memory>

class BindingManager {
private:
    Registry& _reg;
    static std::unique_ptr<BindingManager> _instance;

    struct Binding {
        Address addr;
        void*   pvar;
        Binding(Address adr, void* dat) : addr(adr), pvar(dat) {}
    };

    std::vector<Binding> binds;

    template<Registry::Category CAT, typename T>
    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    template<Registry::Category CAT>
    void processWithCategory(const Address& addr, void* iecVar, bool toRegistry);

    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

    explicit BindingManager(Registry& reg);

public:
    static BindingManager& instance();

    void bind(const std::string& regNotation, void* iecVar);

    void updateToIec();
    void updateFromIec();

    // Запрещаем копирование и присваивание
    BindingManager(const BindingManager&) = delete;
    BindingManager& operator=(const BindingManager&) = delete;
};

#endif // BINDING_MANAGER_H