// plc_control.h
//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>

enum class PlcState {
    STOPPED,    // Программа остановлена
    STARTING,   // Идет запуск
    RUNNING,    // Нормальное выполнение
    PAUSED,     // Пауза (выполнение приостановлено)
    STOPPING,   // Идет остановка
    ERROR       // Ошибка
};

class PlcControl {
public:
    // Запрещаем копирование и присваивание
    PlcControl(const PlcControl&) = delete;
    PlcControl& operator=(const PlcControl&) = delete;

    // Получение экземпляра синглтона
    static PlcControl& instance() {
        static PlcControl instance;
        return instance;
    }

    // Запуск PLC
    bool start() {
        std::lock_guard<std::mutex> lock(state_mutex_);
        if (state_ == PlcState::STOPPED || state_ == PlcState::ERROR) {
            state_ = PlcState::STARTING;
            state_cv_.notify_all();
            return true;
        }
        return false;
    }

    // Останов PLC
    bool stop() {
        std::lock_guard<std::mutex> lock(state_mutex_);
        if (state_ == PlcState::RUNNING || state_ == PlcState::STARTING) {
            state_ = PlcState::STOPPING;
            state_cv_.notify_all();
            return true;
        }
        return false;
    }

    bool pause() {
        std::lock_guard<std::mutex> lock(state_mutex_);
        if (state_ == PlcState::RUNNING) {
            state_ = PlcState::PAUSED;
            state_cv_.notify_all();
            return true;
        }
        return false;
    }

    bool resume() {
        std::lock_guard<std::mutex> lock(state_mutex_);
        if (state_ == PlcState::PAUSED) {
            state_ = PlcState::RUNNING;
            state_cv_.notify_all();
            return true;
        }
        return false;
    }

    // Получение текущего состояния
    PlcState state() const {
        std::lock_guard<std::mutex> lock(state_mutex_);
        return state_;
    }

    // Проверка состояния
    bool isRunning() const { return state() == PlcState::RUNNING; }
    bool isStopped() const { return state() == PlcState::STOPPED; }

    // Ожидание перехода в определенное состояние
    bool waitFor(PlcState target, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(state_mutex_);
        return state_cv_.wait_for(lock, timeout, [this, target] {
            return state_ == target || state_ == PlcState::ERROR;
        });
    }

    // Установка состояния (для использования внутри main цикла)
    void setState(PlcState new_state) {
        std::lock_guard<std::mutex> lock(state_mutex_);
        state_ = new_state;
        state_cv_.notify_all();
    }

    // Преобразование состояния в строку
    std::string toString() {
        switch(state_) {
            case PlcState::STOPPED:  return "STOPPED";
            case PlcState::STARTING: return "STARTING";
            case PlcState::RUNNING:  return "RUNNING";
            case PlcState::STOPPING: return "STOPPING";
            case PlcState::ERROR:    return "ERROR";
            default:                 return "UNKNOWN";
        }
    }

private:
    PlcControl() = default;
    ~PlcControl() = default;

    mutable std::mutex state_mutex_;
    std::condition_variable state_cv_;
    PlcState state_ = PlcState::STOPPED;
};

