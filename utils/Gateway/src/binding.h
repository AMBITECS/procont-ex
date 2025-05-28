#ifndef BINDING_MANAGER_H
#define BINDING_MANAGER_H

#include "registry.h"
#include "address.h"
#include <vector>
#include <string>

class BindingManager {
private:
    Registry& _reg; // Ссылка на экземпляр Registry

    struct Binding {
        Address addr{};
        void* iecVar{};
        Binding(Address adr, void *dat);
    };

    std::vector<Binding> bindings_;

    template<Registry::Category CAT, typename T>
    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    template<Registry::Category CAT>
    void processWithCategory(const Address& addr, void* iecVar, bool toRegistry);

    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

public:
    explicit BindingManager(Registry& reg);
    static BindingManager& instance();

    void bind(const std::string& regNotation, void* iecVar);
    void updateToIec();
    void updateFromIec();
};

#endif // BINDING_MANAGER_H