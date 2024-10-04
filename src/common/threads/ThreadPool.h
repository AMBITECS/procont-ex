//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#ifndef A_DEXTER_THREADPOOL_H
#define A_DEXTER_THREADPOOL_H
#include "global.h"
#include "PoolThread.h"
#include "ThreadSafe.h"

#include <QSet>
#include <QQueue>
#include <QString>

typedef QQueue<PoolClient *> TClientQue;
typedef QSet  <PoolClient *> TClientSet;

// ----------------------------------------------------------------------------
class ThreadPool final
    : Mutex     // Mutex для защиты собственных данных
{
    friend PoolThread;
    friend PoolClient;

    static constexpr int    THREAD_DEF_COUNT = 5;
    static const QString    THREADPOOL_DEF_NAME;

    QString     name        = QString{};        // Имя пула
    ThreadData* threadData  = nullptr;          // Массив данных для потоков

    int threadCount         = 0;                // количество потоков накопителя
    int threadInUse         = 0;                // количество задействованных потоков
    int threadPeakUse       = 0;                // пиковая загрузка потоков
    int queuePeakUse        = 0;                // пиковая загрузка очереди

    TClientQue  clientQue{};                    // Очередь клиентов данного накопителя
    TClientSet  clientSet{};                    // Реестр клиентов

    bool		bDie = false;                   // флаг завершения работы
    ThreadCond  mDoWork{};		                // синхронизирующей мьютех типа "есть работа!"

    void        startPool(int tCount);          // Запуск пула
    void        stopPool();                     // Останов пула

    PoolClient* getClientToWork();              // Выбор клиента для работы

    void    ThreadFunc(ThreadData& data);       // Потоковая процедура

    void    OnThreadInit() {}                   // Вызов при входе в поток      (NOLINT)
    void    OnThreadExit() {}                   // Вызов при выходе из потока   (NOLINT)

    void    joinQueue (PoolClient* client);     // Клиент ставится в очередь
    void    leaveQueue(PoolClient* client);     // Клиент извлекается из очереди

    void    regClient  (PoolClient* client);    // Регистрация клиента
    bool    unregClient(PoolClient* client);	// Удаление клиента (TRUE= клиент был в очереди)

public:
    // Конструкторы пула
    ThreadPool()                    { startPool(THREAD_DEF_COUNT); }
    EXP ThreadPool(const int count) { startPool(std::max(1, count)); }
    ~ThreadPool()                   { stopPool(); }

};

// ----------------------------------------------------------------------------
#endif //A_DEXTER_THREADPOOL_H
