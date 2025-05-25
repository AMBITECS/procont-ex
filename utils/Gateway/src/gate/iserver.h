//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include "dto.h"
#include "server_stat.h"

#include <memory>
#include <future>
#include <vector>
#include <mutex>

namespace sft::dtm::gateway {

// Предварительное объявление класса Client
    class Client;

/**
 * @brief Интерфейс сервера для взаимодействия с клиентами
 *
 * Определяет основные операции, которые должен поддерживать сервер:
 * - Регистрация/удаление клиентов
 * - Отправка запросов с таймаутами
 * - Публикация данных
 * - Мониторинг состояния
 */
    class IServer {
    public:
        virtual ~IServer() = default;

        /**
         * @brief Регистрирует клиента на сервере
         * @param client Указатель на клиента для регистрации
         */
        virtual void registerClient(std::shared_ptr<Client> client) = 0;

        /**
         * @brief Отменяет регистрацию клиента
         * @param client Указатель на клиента для удаления
         */
        virtual void unregisterClient(std::shared_ptr<Client> client) = 0;

        /**
         * @brief Отправляет запрос через сервер
         * @param client Клиент-инициатор запроса
         * @param request Данные запроса
         * @param timeoutMs Таймаут выполнения в миллисекундах
         * @return std::future<Resp> Future с результатом выполнения
         */
        virtual std::future<Resp> sendRequest(
                std::shared_ptr<Client> client,
                std::shared_ptr<DtoBase> request,
                long timeoutMs) = 0;

        /**
         * @brief Публикует данные для всех клиентов
         * @param client Клиент-источник данных
         * @param data Данные для публикации
         */
        virtual void publish(std::shared_ptr<Client> client, std::shared_ptr<Send> data) = 0;

        /**
         * @brief Получает список подключенных клиентов
         * @return Вектор weak_ptr на активных клиентов
         */
        virtual std::vector<std::weak_ptr<Client>> getConnectedClients() const = 0;

        /**
         * @brief Получает текущую статистику сервера
         * @return Stats Структура с показателями
         */
        virtual ServerStats getStats() const = 0;

        /**
         * @brief Проверяет подключение клиента
         * @param client Клиент для проверки
         * @return bool true если клиент подключен
         */
        virtual bool isClientConnected(std::shared_ptr<Client> client) const = 0;

        /**
         * @brief Получает версию сервера
         * @return std::string Строка версии (например "1.0.0")
         */
        virtual std::string getVersion() const = 0;
    };

} // namespace sft::dtm::gateway