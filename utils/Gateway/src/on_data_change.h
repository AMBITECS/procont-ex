//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#ifndef PROCONT_EX_ON_DATA_CHANGE_H
#define PROCONT_EX_ON_DATA_CHANGE_H

#include <chrono>
#include <limits>
#include "variant.h"

struct OnDataChange {
    size_t   index;        // Индекс элемента
    uint64_t bit_mask;     // Маска затронутых битов (0 для небитовых изменений)
    VARIANT  old_value;
    VARIANT  new_value;
    std::chrono::system_clock::time_point timestamp;

    // Единый конструктор
    OnDataChange(size_t idx, uint8_t mask, VARIANT old_val, VARIANT new_val)
            : index(idx),
              bit_mask(mask),
              old_value(std::move(old_val)),
              new_value(std::move(new_val)),
              timestamp(std::chrono::system_clock::now()) {}

    bool is_bit_change() const { return bit_mask != 0; }
};

#endif //PROCONT_EX_ON_DATA_CHANGE_H