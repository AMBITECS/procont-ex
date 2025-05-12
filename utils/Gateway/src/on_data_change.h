//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_ON_DATA_CHANGE_H
#define PROCONT_EX_ON_DATA_CHANGE_H

#include <chrono>
#include <limits>
#include "variant.h"

// Событие изменения данных
struct OnDataChange {
    using TimeStamp = std::chrono::system_clock::time_point;

    std::string key;    // Идентификатор из addItems
    uint64_t bit_mask;  // Маска измененных битов
    VARIANT old_value;
    VARIANT new_value;
    std::chrono::system_clock::time_point timestamp;

    OnDataChange(std::string k, uint64_t mask, VARIANT old_val, VARIANT new_val,
                 TimeStamp time_ = std::chrono::system_clock::now())
            : key(std::move(k)), bit_mask(mask),
              old_value(std::move(old_val)),
              new_value(std::move(new_val)),
              timestamp(time_) {}

    [[nodiscard]] bool is_bit_change() const noexcept {
        return bit_mask != 0;
    }
};

#endif //PROCONT_EX_ON_DATA_CHANGE_H