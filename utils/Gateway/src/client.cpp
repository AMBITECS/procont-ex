//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "client.h"
#include <iostream>
#include <stdexcept>

// Конструктор клиента
Client::Client(const std::string& key, size_t maxQueueSize)
        : key_(key),
          maxQueueSize_(maxQueueSize) {
    // Проверка валидности ключа
    if (key.empty()) {
        throw std::invalid_argument("Client key cannot be empty");
    }

    // Запускаем рабочий поток для обработки данных
    workerThread_ = std::thread(&Client::processData, this);
}

// Деструктор клиента
Client::~Client() {
    shutdown(); // Гарантированное завершение работы
}

// Получение ключа клиента
std::string Client::getKey() const {
    return key_;
}

// Установка обработчика входящих данных
void Client::setDataHandler(DataHandler handler) {
    dataHandler_ = std::move(handler);
}

// Обработка полученных данных (вызывается извне)
void Client::onDataReceived(std::shared_ptr<Receive> data) {
    if (!data) {
        std::cerr << "Warning: Received null data in client " << key_ << std::endl;
        return;
    }

    std::unique_lock<std::mutex> lock(queueMutex_);

    // Проверяем переполнение очереди
    if (dataQueue_.size() >= maxQueueSize_) {
        std::cerr << "Warning: Queue overflow in client " << key_
                  << ", discarding data" << std::endl;
        return;
    }

    // Добавляем данные в очередь
    dataQueue_.push(data);
    lock.unlock();

    // Уведомляем рабочий поток о новых данных
    queueCV_.notify_one();
}

// Завершение работы клиента
void Client::shutdown() {
    if (!running_.exchange(false)) {
        return; // Уже завершён
    }

    // Уведомляем рабочий поток
    queueCV_.notify_all();

    // Дожидаемся завершения потока
    if (workerThread_.joinable()) {
        workerThread_.join();
    }

    // Очищаем очередь
    std::lock_guard<std::mutex> lock(queueMutex_);
    while (!dataQueue_.empty()) {
        dataQueue_.pop();
    }
}

// Получение текущего размера очереди
size_t Client::getQueueSize() const {
    std::lock_guard<std::mutex> lock(queueMutex_);
    return dataQueue_.size();
}

// Основной цикл обработки данных (работает в отдельном потоке)
void Client::processData() {
    while (running_) {
        std::shared_ptr<Receive> data;

        {
            std::unique_lock<std::mutex> lock(queueMutex_);

            // Ждём данных или команды завершения
            queueCV_.wait(lock, [this]() {
                return !dataQueue_.empty() || !running_;
            });

            // Проверяем завершение работы
            if (!running_) {
                break;
            }

            // Извлекаем данные из очереди
            if (!dataQueue_.empty()) {
                data = dataQueue_.front();
                dataQueue_.pop();
            }
        }

        // Обрабатываем данные, если они есть
        if (data && dataHandler_) {
            processing_ = true;
            try {
                dataHandler_(data);
            } catch (const std::exception& e) {
                std::cerr << "Error in client " << key_
                          << " data handler: " << e.what() << std::endl;
            }
            processing_ = false;
        }
    }
}
