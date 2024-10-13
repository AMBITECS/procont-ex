//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#ifndef A_DEXTER_POOLCLIENT_H
#define A_DEXTER_POOLCLIENT_H
#include "global.h"

class ThreadPool;

// ----------------------------------------------------------------------------
class PoolClient {
    friend ThreadPool;
    static ThreadPool* defaultPool; // потоковый пул по умолчанию

    // Состояние клиента
    enum state { IDLE, QUEUED, RUNNING, RUN_AGAIN };

    // Attributes
    ThreadPool*     pool;           // текущий потоковый накопитель
    state           state;          // состояние клиента

protected:
    virtual void Work() = 0;        // Must be defined in child class!
    
public:
    PoolClient();
    VRT ~PoolClient() { EndWork(); }

    [[nodiscard]] bool hasPool() const { return (pool != nullptr); }
    void SetPool(ThreadPool *newPool);

    void DoWork();
    void EndWork();
};

// ----------------------------------------------------------------------------
#endif //A_DEXTER_POOLCLIENT_H
