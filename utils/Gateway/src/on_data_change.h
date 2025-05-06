//
// Created by master on 06.05.2025.
//

#ifndef PROCONT_EX_ON_DATA_CHANGE_H
#define PROCONT_EX_ON_DATA_CHANGE_H

#include <chrono>
#include "variant.h"

/**
 * @brief Structure representing a data change notification
 */
struct OnDataChange {
    size_t index{};                 ///< Index of changed element
    VARIANT old_value{};            ///< Previous value
    VARIANT new_value{};            ///< New value
    std::chrono::system_clock::time_point timestamp; ///< Time of change
};

#endif //PROCONT_EX_ON_DATA_CHANGE_H
