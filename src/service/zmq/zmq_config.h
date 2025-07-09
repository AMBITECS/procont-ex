//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once
#include "cfg_utils.h"
#include <string>
#include <unordered_map>

using namespace utils;

namespace cfg {

/**
 * @brief Конфигурация ZMQ сервера
 *
 * Содержит все необходимые параметры для настройки серверной части ZMQ соединения
 */
    struct ZmqServerConfig {
        // Основные параметры
        int admPort{5551};                      // Порт административного канала (ROUTER)
        int pubPort{5552};                      // Порт публикации (PUB)
        int workerThreads{2};                   // Количество рабочих потоков I/O

        // Ограничения
        int maxClients{100};                    // Максимальное количество клиентов
        int maxQueueSize{1024};                 // Максимальный размер очереди сообщений
        int maxMessageSize{65536};              // Максимальный размер сообщения (байт)
        int operationTimeout{1000};             // Таймаут операций (мс)

        // heartbeat
        int heartbeatInterval{30000};           // Интервал проверки активности клиентов (мс)
        int clientTimeout{60000};               // Время неактивности до отключения клиента (мс)
        bool debugMode{true};                   // Режим отладочной печати

        // Параметры передачи файлов
        std::string programsDir{"programs"};       // Базовый каталог для сохранения программ
        uint64_t maxFileSize{100 * 1024 * 1024};   // Максимальный размер файла (100 MB)
        uint64_t maxChunkSize{64 * 1024};          // Максимальный размер блока (64 KB)

        /**
         * @brief Загрузка конфигурации из key-value map
         * @param configMap Карта с параметрами конфигурации
         */
        void configure(const std::unordered_map<std::string, std::string>& configMap) {
            using namespace cfg; // Предполагается существование пространства имен с getConfig* функциями

            // Основные параметры
            admPort = getConfigInt(configMap, "zmq.server.adminPort", admPort);
            pubPort = getConfigInt(configMap, "zmq.server.pubPort", pubPort);
            workerThreads = getConfigInt(configMap, "zmq.server.workerThreads", workerThreads);

            // Ограничения
            maxClients = getConfigInt(configMap, "zmq.server.maxClients", maxClients);
            maxQueueSize = getConfigInt(configMap, "zmq.server.maxQueueSize", maxQueueSize);
            maxMessageSize = getConfigInt(configMap, "zmq.server.maxMessageSize", maxMessageSize);
            operationTimeout = getConfigInt(configMap, "zmq.server.timeout", operationTimeout);

            // Таймауты
            heartbeatInterval = getConfigInt(configMap, "zmq.server.heartbeatInterval", heartbeatInterval);
            clientTimeout = getConfigInt(configMap, "zmq.server.clientTimeout", clientTimeout);

            // Добавляем загрузку debugMode
            debugMode = getConfigBool(configMap, "zmq.server.debugMode", debugMode);

            // Параметры передачи файлов
            programsDir = getConfigStr(configMap, "zmq.server.programsDir", programsDir);
            maxFileSize = getConfigUInt64(configMap, "zmq.server.maxFileSize", maxFileSize);
            maxChunkSize = getConfigUInt64(configMap, "zmq.server.maxChunkSize", maxChunkSize);
        }

        /**
         * @brief Проверка валидности конфигурации
         * @throw std::invalid_argument При невалидных значениях
         */
        void validate() const {
            if (workerThreads <= 0) throw std::invalid_argument("workerThreads must be positive");
            if (admPort <= 0 || pubPort <= 0 /*|| subPort <= 0*/) {
                throw std::invalid_argument("Ports must be positive");
            }
            if (operationTimeout <= 0 || heartbeatInterval <= 0 || clientTimeout <= 0) {
                throw std::invalid_argument("Timeouts must be positive");
            }
            if (maxClients <= 0 || maxQueueSize <= 0 || maxMessageSize <= 0) {
                throw std::invalid_argument("Limits must be positive");
            }

            if (maxFileSize <= 0 || maxChunkSize <= 0) {
                throw std::invalid_argument("File size limits must be positive");
            }
            if (maxChunkSize > maxFileSize) {
                throw std::invalid_argument("Chunk size cannot be larger than max file size");
            }
        }
    };

    using Config = cfg::ConfigLoader<ZmqServerConfig>;

} // namespace cfg