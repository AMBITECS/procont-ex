//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <string>

namespace sft::dtm::gateway {

/**
 * @brief Интерфейс для объектов, содержащих ключ
 *
 * Аналог Java-интерфейса IKeyHolder из пакета sft.dtm.gateway.api
 */
    class IKeyHolder {
    public:
        virtual ~IKeyHolder() = default;

        /**
         * @brief Получить текущий ключ
         * @return Текущее значение ключа
         */
        [[nodiscard]] virtual std::string _key() const = 0;
        //virtual std::string getKey() const = 0;

        /**
         * @brief Установить новый ключ
         * @param key Новое значение ключа
         */
        virtual void _key(const std::string& key) = 0;
        //virtual void setKey(const std::string& key) = 0;
    };

} // namespace sft::dtm::gateway