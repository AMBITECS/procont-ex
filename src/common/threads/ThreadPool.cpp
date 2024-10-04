//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#include "ThreadPool.h"
#include "PoolThread.h"
#include "PoolClient.h"

const QString ThreadPool::THREADPOOL_DEF_NAME    = ("ThreadPool");

// ----------------------------------------------------------------------------
void ThreadPool::startPool(const int tCount) {
    //log().debug("Init ThreadPool {} ... ", this);

    // устанавливаем пул по умолчанию на себя
    if (PoolClient::defaultPool == nullptr) PoolClient::defaultPool = this;
    name        = THREADPOOL_DEF_NAME;              // Имя пула
    threadCount = tCount;                           // Количество потоков в пуле
    threadData  = new ThreadData[threadCount];      // массив структур ThreadData (@deletable)

    // создаём и запускаем потоки в пуле
    for (int tid = 0; tid < threadCount; tid++) {
        // Заполняем данные потока
        threadData[tid].threadId     = tid++;       // threadId = tid
        threadData[tid].threadPool   = this;        // pool = this;
        threadData[tid].activeClient = nullptr;     // no active client yet

        // Создаем новый поток
        threadData[tid].pThread = new PoolThread(&threadData[tid]);

        // Запускаем поток
        threadData[tid].pThread->start();
    }
}

// ----------------------------------------------------------------------------
void ThreadPool::stopPool() {
    // log().debug("Destroying ThreadPool ... ");

    // clear default pool
    if ( PoolClient::defaultPool == this ) PoolClient::defaultPool = nullptr;

    // remove all registered clients
    lock();
    for (auto* client: clientSet) client->pool = nullptr;
    clientSet.clear();
    unlock();

    // Generate "must die" event for all threads
    bDie = true;                    // time to die!
    mDoWork.wakeAll();              // broadcast signal to release threads
    QThread::yieldCurrentThread();  // QThread::msleep(10L);

    // Удаление потоков
    for (int tid = 0; tid < threadCount; tid++)
    {
        // Потоки должны финишировать т.к. bDie=TRUE + wakeAll()
        // Но мы их подождём (на всякий случай)
        if (threadData[tid].pThread->join()) {
            // join() should end with false
            throw TError(E_JOIN_THREAD, ("PoolThread"));
        }

        // Удаляем объект потока
        delete threadData[tid].pThread;
    }

    //log().debug("ThreadPool={} Terminated!", this);
}

//=--------------------------------------------------------------------------=
PoolClient* ThreadPool::getClientToWork()
{
    PoolClient* client = nullptr;
    TSClass<Mutex> locker(*this);
    if( !clientQue.isEmpty() ) {
        client = clientQue.front();
        // проверяем его наличие в реестре клиентов
        assert(clientSet.find(client)!=clientSet.end());
        clientQue.pop_front();
    }
    return client;  // возвращаем указатель на найденного клиента
}

//=--------------------------------------------------------------------------=
// Потоковая обработка
//=--------------------------------------------------------------------------=
void ThreadPool::ThreadFunc(ThreadData& data)
{
    OnThreadInit();				// Инициализация
    while( !bDie ) {			// пока живем ...
        mDoWork.wait();         // ждем синхронизирующее событие m_hDoWork
        if ( bDie ) break;      // если событие из деструктора - break
        PoolClient *pClient;

        lock();

        // определяем активного клиента
        while( !bDie && ((pClient = getClientToWork()) != nullptr) )
        {
            data.lock();                                    // захват данных
            data.activeClient = pClient;		            // установка активного клиента
            ++threadInUse;                                  // threads counter
            threadPeakUse = std::max(threadPeakUse, threadInUse);
            pClient->state = PoolClient::RUNNING;	        // устанавливаем статус "клиент в работе"

            unlock();

            pClient->Work();					            // client in work!!!
            PoolThread::msleep(0);				        // release some time for other threads

            lock();

            data.activeClient = nullptr;			        // сбрасываем указатель на клиента
            --threadInUse;                                  // threads counter

            const bool bAgain = (pClient->state == PoolClient::RUN_AGAIN);
            pClient->state = PoolClient::IDLE;              // состояние клиента = пассивен
            if (bAgain) pClient->DoWork();               // клиент ставит себя в очередь
            data.unlock();		                    // отпускаем мьютекс данных
        }

        unlock();
    }

    OnThreadExit();                 // деинициализация
    data.pThread = nullptr;
}

// ----------------------------------------------------------------------------
void ThreadPool::joinQueue(PoolClient* client) {
    if (!bDie) {
        {
            TSClass<Mutex> locker(*this);
            switch (client->state) {
            case PoolClient::IDLE:
                {
                    const TClientSet::iterator it = clientSet.find(client);
                    if (it != clientSet.end()) {              // если клиент зарегистрирован в наборе:
                        clientQue.push_back(client);          // ставим в очередь
                        client->state = PoolClient::QUEUED;   // состояние = 'клиент в очереди'
                        queuePeakUse = std::max(queuePeakUse,
                            static_cast<int>(clientQue.size()));
                        mDoWork.wakeOne();                    // событие = "есть работа!!!"
                    }
                }
                break;
            case PoolClient::RUNNING:
                client->state = PoolClient::RUN_AGAIN;        // уст состояние повторного запуска
                break;
            default: break;
            }
        }
        PoolThread::msleep(0);  // release some time for other threads
    }
}

// ----------------------------------------------------------------------------
void ThreadPool::leaveQueue(PoolClient* client) {
    int i;
    {
        TSClass<Mutex> locker(*this);
        if (clientSet.empty()) return;  // клиентов нет - нечего удалять
        unregClient(client);            // предотвращает установку в очередь

        // проверяем активность данного клиента
        for (i = 0; i < threadCount; i++) {
            if (threadData[i].activeClient == client) break;
        }
    }
    // ожидание, пока клиент освободится ...
    if ( i < threadCount ) {     // клиент активен (i - номер потока)
        //TRACEARG(_T("Client %Xh is stay active!\n"), &client );
        if ( threadData[i].tryLock(5000) ) {    // ждём освобождения мьютекса (5 сек)
            // TODO This is bad! There is something to think about!!!
            //TRACE(_T("TryLock() timed out in CThreadPool::Remove()\n"));
        } else {
            // клиент должен быть уже не активен
            assert(threadData[i].activeClient == nullptr);
            threadData[i].activeClient = nullptr;
            threadData[i].unlock();		           // освобождаем мьютекс
            //TRACEARG(_T("done TryLock() for client %Xh\n") , &client);
        }
    }
}

//=--------------------------------------------------------------------------=
// Регистрация клиента
//=--------------------------------------------------------------------------=
void ThreadPool::regClient(PoolClient* client ) {
    TSClass<Mutex> locker(*this);
    clientSet.insert(client);
}

//=--------------------------------------------------------------------------=
// Удаление клиента
//=--------------------------------------------------------------------------=
bool ThreadPool::unregClient(PoolClient* client ) {
    TSClass<Mutex> locker(*this);

    // Удаление из реестра
    TClientSet::iterator it = clientSet.find(client);
    if (it != clientSet.end()) {
        client->pool = nullptr;
        it = clientSet.erase(TClientSet::const_iterator(it));
    }

    // Удаление из очереди
    bool && bQueued = (client->state == PoolClient::QUEUED);
    if (bQueued) {
        TClientQue::iterator itQ = clientQue.begin();
        while (itQ != clientQue.end()) {
            if (*itQ != client) ++itQ;
            else {
                itQ = clientQue.erase(TClientQue::const_iterator(itQ));
                client->state = PoolClient::IDLE;
                //break;
            }
        }
    }
    return bQueued;
}

// ----------------------------------------------------------------------------
