//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#ifndef A_DEXTER_POOLTHREAD_H
#define A_DEXTER_POOLTHREAD_H
#include <ThreadSafe.h>

#include "global.h"

#define QTHREAD true
#ifdef QTHREAD
    #include <QThread>
#else
    #include <pthread.h>
#endif

#ifdef __WINDOWS__
    #include <conio.h>
    #include <Windows.h>
    #define Sleep(X) Sleep(X)           // аргумент - милисекунды!
#else
    #include <unistd.h>
    #define Sleep(X) usleep((X)*1000)   // аргумент - микросекунды!
#endif

class ThreadPool;
class PoolThread;
class PoolClient;

// ----------------------------------------------------------------------------
// ThreadData
// ----------------------------------------------------------------------------
struct ThreadData : Mutex {
    int         threadId      = (-1);
    PoolThread* pThread       = nullptr;
    ThreadPool* threadPool    = nullptr;
    PoolClient* activeClient  = nullptr;
};

// ----------------------------------------------------------------------------
// PoolThread
// ----------------------------------------------------------------------------
class PoolThread
{
#ifdef QTHREAD
    typedef QThread::Priority   TPriority;
    static  constexpr TPriority THREAD_MAX_PRIORITY = QThread::NormalPriority;
    QThread*                    pThread             = nullptr;
#else
    typedef int                 TPriority;
    static  constexpr TPriority THREAD_MAX_PRIORITY = 0;
    pthread_t                   hThread             = pthread_t{0};
#endif

private:
    static constexpr long       THREAD_DEF_STACKSIZE = 0; //(1024*1024*8);
    static const QString        POOLTHREAD_DEF_NAME;

    QString         name;               // имя потока   (для логгирования)
    ThreadData*     data;               // данные потока

    static void	threadStub(void* pD);	// потоковая процедура

public:
    EXP PoolThread(
            ThreadData*       data,
            const QString&    name      = POOLTHREAD_DEF_NAME,
            QThread::Priority prio      = THREAD_MAX_PRIORITY,
            long              stackSize = THREAD_DEF_STACKSIZE
    );
    ~PoolThread();

    static void msleep(long ms=0);      // sleep for ms (милисекунды)

    void        start() const;          // Start thread
    void        terminate() const;      // Terminate thread
    bool        join() const;           // NOLINT (to suppress nondiscard waqrning)
};

// ----------------------------------------------------------------------------
#endif //A_DEXTER_POOLTHREAD_H
