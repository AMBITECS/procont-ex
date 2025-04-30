//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_VECTOR_H
#define PROCONT_EX_VECTOR_H

#include <mutex>
#include <string>
#include <unordered_map>
#include <functional>

#include <shared_mutex>

using namespace std;

template<typename T>
class Vector : public vector<T>
{
private:
    mutable shared_mutex mtx;

public:
    Vector() = default;

    explicit Vector(int capacity) {
        this->reserve(capacity);
    }

    shared_mutex& mutex() { return mtx; }

    T* V() {return this->data();}

    void lock()   {mtx.lock();}
    void unlock() {mtx.unlock();}

    // Запись блокирует полностью
    void set(int index, const T& value) {
        unique_lock<shared_mutex> lock(mtx);
        (*this)[index] = value;
    }

    // Чтение допускает параллельный доступ
    bool get(int index, T& value) const {
        shared_lock<shared_mutex> lock(mtx);
        if (index < this->size()) {
            value = this->at(index);
            return true;
        }
        return false;
    }

    // Оптимизированное обновление
    void update(int index, function<void(T&)> updater) {
        unique_lock<shared_mutex> lock(mtx);
        updater((*this)[index]);
    }

    template <typename Function>
    void for_each(Function f) const {
        std::lock_guard lock(mtx);
        for (const auto& item : this->data) {
            f(item);
        }
    }
};

#endif //PROCONT_EX_VECTOR_H
