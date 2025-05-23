//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include <mutex>
#include <atomic>
#include <memory>
#include <functional>
#include <vector>
#include <stdexcept>

template<typename T>
class Reg {
public:
    struct Stats {
        std::atomic<int> registrations{0};
        std::atomic<int> unregistrations{0};
        std::atomic<int> lookups{0};
        std::atomic<int> misses{0};
        std::atomic<int> collisions{0};
        std::atomic<int> compactions{0};

        int getSize() const { return registrations - unregistrations; }
        double getHitRatio() const {
            return lookups > 0 ? 1.0 - static_cast<double>(misses) / lookups : 0.0;
        }
    };

    // Получение стабильного адреса объекта
    size_t addrOf(const T& obj) const {
        if (!obj) throw std::invalid_argument("Cannot get address of null object");
        stats.lookups++;
        return reinterpret_cast<size_t>(obj.get());
    }

    // Регистрация объекта и получение адреса
    size_t reg(const std::shared_ptr<T>& obj) {
        if (!obj) throw std::invalid_argument("Cannot register null object");

        std::lock_guard<std::mutex> lock(mutex_);
        size_t address = addrOf(obj);

        auto [it, inserted] = addressToObjectMap.try_emplace(address, obj);
        if (inserted) {
            stats.registrations++;
            return address;
        }

        if (it->second == obj) {
            stats.lookups++;
            return address;
        }

        stats.collisions++;
        throw std::runtime_error("Address collision for object");
    }

    // Удаление регистрации по адресу
    void unreg(size_t address) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (addressToObjectMap.erase(address) > 0) {
            stats.unregistrations++;
        } else {
            stats.misses++;
            throw std::invalid_argument("Address not found for unregister");
        }
    }

    // Получение объекта по адресу
    std::shared_ptr<T> get(size_t address) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = addressToObjectMap.find(address);
        if (it != addressToObjectMap.end()) {
            stats.lookups++;
            return it->second;
        }
        stats.misses++;
        return nullptr;
    }

    // Поиск адреса объекта
    size_t find(const std::shared_ptr<T>& obj) const {
        if (!obj) return 0;

        size_t address = addrOf(obj);
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = addressToObjectMap.find(address);
        if (it != addressToObjectMap.end() && it->second == obj) {
            return address;
        }
        stats.misses++;
        return 0;
    }

    bool contains(const std::shared_ptr<T>& obj) const {
        return find(obj) != 0;
    }

    void compact() {
        stats.compactions++;
        // В C++ нет необходимости в явной компактификации
    }

    std::shared_ptr<T> computeIfAbsent(size_t address, std::function<std::shared_ptr<T>(size_t)> mappingFunction) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = addressToObjectMap.find(address);
        if (it != addressToObjectMap.end()) {
            return it->second;
        }
        auto obj = mappingFunction(address);
        addressToObjectMap[address] = obj;
        return obj;
    }

    std::vector<size_t> getAllAddresses() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<size_t> addresses;
        addresses.reserve(addressToObjectMap.size());
        for (const auto& pair : addressToObjectMap) {
            addresses.push_back(pair.first);
        }
        return addresses;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return addressToObjectMap.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        addressToObjectMap.clear();
    }

    const Stats& getStats() const { return stats; }

private:
    mutable std::mutex mutex_;
    std::unordered_map<size_t, std::shared_ptr<T>> addressToObjectMap;
    mutable Stats stats;
};

