//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#include "PoolThread.h"
#include "ThreadPool.h"

const QString PoolThread::POOLTHREAD_DEF_NAME    = ("PoolThread");

// ----------------------------------------------------------------------------
// PoolThread thread func
// ----------------------------------------------------------------------------
void PoolThread::threadStub(void* pD)
{
    const auto pData = static_cast<ThreadData*>(pD);
    return pData->threadPool->ThreadFunc(*pData);
}

// ----------------------------------------------------------------------------
void PoolThread::msleep(long ms)
{
    #ifdef QTHREAD
        if (ms==0)  QThread::yieldCurrentThread();
        else        QThread::msleep(ms);
    #else
        Sleep(ms);
    #endif
}

// ----------------------------------------------------------------------------
// PoolThread create & start
// ----------------------------------------------------------------------------
PoolThread::PoolThread(
        ThreadData *    data,
        const QString & name,
        TPriority       prio,
        long            stackSize
    )
{
    this->data = data;
    #ifdef QTHREAD
        pThread = QThread::create(threadStub, data);
        pThread->setStackSize(THREAD_DEF_STACKSIZE);
        pThread->setPriority (THREAD_MAX_PRIORITY);
    #else
        //// See start() func
    #endif
}

// ----------------------------------------------------------------------------
PoolThread::~PoolThread() {
    terminate();    // Убиваем поток (на всякий случай)
    #ifdef QTHREAD
        delete pThread;
    #else

    #endif
}

// ----------------------------------------------------------------------------
void PoolThread::start() const
{
    #ifdef QTHREAD
        pThread->start();
    #else
        // Create thread attribute object
        pthread_attr_t attr;
        if (pthread_attr_init(&attr)) throw TError(E_INIT_ATTR, _T("PoolThread"));

        // Create & start thread
        if ( pthread_create( &hThread, &attr, ThreadStub, data) )
        {
            throw TError(E_CREATE_THREAD, ("PoolThread"));
        }

        // Cleanup pthread_attr_t object, we don't need it anymore
        pthread_attr_destroy(&attr);
    #endif
}

// ----------------------------------------------------------------------------
void PoolThread::terminate() const
{
    // Убиваем поток (на всякий случай)
    #ifdef QTHREAD
        if (pThread!=nullptr) pThread->terminate();
    #else
        pthread_cancel(hThread);
        //pthread_join(m_pThreadData[tid].hThread, &status));
    #endif
}

// ----------------------------------------------------------------------------
bool PoolThread::join() const
{
    bool bRet = false;
    #ifdef QTHREAD
        bRet = pThread->wait();
    #else
        bRet = (pthread_join(hThread, nullptr)==0);
    #endif
    return bRet;
}

// ----------------------------------------------------------------------------
