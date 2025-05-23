//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include <chrono>

/**
 * @struct ServerStats
 * @brief Статистика работы сервера
 */
struct ServerStats {
    bool active;                ///< Флаг активности сервера
    size_t clientsCount;        ///< Количество подключенных клиентов
    size_t pendingRequestsCount; ///< Количество ожидающих запросов
    std::chrono::system_clock::time_point startTime; ///< Время старта сервера

    // Конструктор по умолчанию
    ServerStats()
            : active(false),
              clientsCount(0),
              pendingRequestsCount(0),
              startTime(std::chrono::system_clock::now()) {}

    /**
     * @brief Получение времени работы сервера
     * @return Длительность в секундах
     */
    std::chrono::seconds uptime() const {
        return std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - startTime);
    }
};