//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "quality.h"
#include "variant.h"
#include <chrono>
#include <string>
#include <memory>

/**
 * Item - Данные (значение) тега
 * Содержит текущее значение, качество и метку времени тега
 */
class Item {
public:
    std::string key     = "key";            // Уникальный ключ элемента
    bool        prior   = true;             // Приоритет обновления
    Quality     quality = Quality::GOOD;    // Качество данных

    // Текущее значение тега
    VARIANT     value   = VARIANT(VAR_TYPE::VT_SINT32);

    std::chrono::system_clock::time_point time = // Метка времени
            std::chrono::system_clock::now();

    // Конструкторы
    Item() = default;

    Item(std::string key, bool prior, VARIANT value,
         Quality quality = Quality::GOOD)
            : key(std::move(key)), prior(prior),
              value(std::move(value)), quality(quality) {}

    // Сериализация в JSON (заглушка - реализация зависит от библиотеки)
    std::string toJSON() const {
        // Здесь должна быть реализация сериализации
        return "{}";
    }

    // Оператор вывода для логирования
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        auto time_t = std::chrono::system_clock::to_time_t(item.time);
        os << "Item(key=" << item.key
           << ", prior=" << (item.prior ? "true" : "false")
           << ", value=" << item.value.toString()
           << ", quality=" << QualityUtils::toString(item.quality)
           << ", time=" << std::ctime(&time_t) << ")";
        return os;
    }

    // Геттеры
    const std::string& getKey() const { return key; }
    bool getPrior() const { return prior; }
    const VARIANT& getValue() const { return value; }
    Quality getQuality() const { return quality; }
    auto getTime() const { return time; }

    // Сеттеры
    void setKey(const std::string& newKey) { key = newKey; }
    void setPrior(bool newPrior) { prior = newPrior; }
    void setValue(const VARIANT& newValue) { value = newValue; }
    void setQuality(Quality newQuality) { quality = newQuality; }
    void setTime(const std::chrono::system_clock::time_point& newTime) {
        time = newTime;
    }
};