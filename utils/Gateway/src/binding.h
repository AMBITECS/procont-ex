#ifndef BINDING_MANAGER_H
#define BINDING_MANAGER_H

#include "registry.h"
#include "address.h"
#include <vector>
#include <string>
#include <memory>

class BindingManager {
private:
    struct Binding {
        Address addr;
        void*   pvar;
        Binding(Address adr, void* dat) : addr(adr), pvar(dat) {}
    };

    Registry&            _reg;
    std::vector<Binding> binds;

    static std::unique_ptr<BindingManager>  _instance;
    static inline std::unordered_map<
        Address::Category,
        std::function<size_t(size_t)>>      category_mappings_;


    template<Registry::Category CAT, typename T>
    void handleType(const Address& addr, void* iecVar, bool toRegistry);

    template<Registry::Category CAT>
    void processWithCategory(const Address& addr, void* iecVar, bool toRegistry);

    explicit BindingManager(Registry& reg);

public:
    static BindingManager& instance();

    void bind(const std::string& regNotation, void* iecVar);

    void updateToIec();
    void updateFromIec();

    void updateVariable(const Address& addr, void* iecVar, bool toRegistry);

    // Запрещаем копирование и присваивание
    BindingManager(const BindingManager&) = delete;
    BindingManager& operator=(const BindingManager&) = delete;

    // -----------------
    template<typename ProxyT>
    static void registerProxy(Address::Category cat, const ProxyT& proxy) {
        category_mappings_[cat] = [&proxy](size_t idx) {
            return proxy.base_offset() + idx * ProxyT::value_size;
        };
    }

    static size_t mapOffset(Address::Category cat, size_t index) {
        return category_mappings_.at(cat)(index);
    }
};

#endif // BINDING_MANAGER_H