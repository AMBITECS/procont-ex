//============================================================================
// ThreadSafe.cpp: Thread sync objects implementation
//=--------------------------------------------------------------------------=
// Copyright (c) 2023 by A. Korobeynikov.  ALL RIGHTS RESERVED.
// Consult your license regarding permissions and restrictions.
//============================================================================
#include "ThreadSafe.h"
#include <sys/types.h>
#include <cstdio>
#include <pthread.h>

//using namespace ars;

//=--------------------------------------------------------------------------=
TError::TError(TErrCode eCode, const QString& ctx): code(eCode) {
    switch (code) {
        case E_SUCCESS:     desc = ("");                                                break;
        case E_OPEN_SEMA:   desc = ("Error opening the semaphore");                     break;
        case E_Deadlock:    desc = ("The resource tries to tightly block the thread!"); break;
        case E_Timeout:     desc = ("Resource is timed out!");                          break;
        case E_BadPtr:      desc = ("The pointer is not defined");                      break;
        case E_Unknown:
        default:            desc = ("Undefined error");
    }
    desc = (ctx + desc);
}

//=--------------------------------------------------------------------------=
// Mutex object
//=--------------------------------------------------------------------------=
int Mutex::tryLock(unsigned short tm) {
    if (tm) {
        timespec wtm = {0};
#if __GLIBC_PREREQ(2, 4) && (__ANDROID_API__ == 0 || __ANDROID_API__ > 19)
        //clock_gettime(pSYS->clockRT() ? CLOCK_REALTIME : CLOCK_MONOTONIC, &wtm);
        clock_gettime(CLOCK_REALTIME, &wtm);
#else
        clock_gettime(CLOCK_REALTIME, &wtm);
#endif
        wtm.tv_nsec += 1000000 * (tm % 1000);
        wtm.tv_sec += tm / 1000 + wtm.tv_nsec / 1000000000;
        wtm.tv_nsec = wtm.tv_nsec % 1000000000;
        return pthread_mutex_timedlock(&mutex, &wtm);
    }
    return pthread_mutex_trylock(&mutex);
}

//=--------------------------------------------------------------------------=
// POSIX Thread RW-Locker object
//=--------------------------------------------------------------------------=
LockRW::LockRW(): rwlock() {
#if !__GLIBC_PREREQ(2,4)
    wThr = 0;
#endif
    if (pthread_rwlock_init(&rwlock, nullptr))
        throw TError(E_OPEN_SEMA, "LockRW");
}

//=--------------------------------------------------------------------------=
LockRW::~LockRW() {
    pthread_rwlock_wrlock(&rwlock);
    pthread_rwlock_destroy(&rwlock);
}

//=--------------------------------------------------------------------------=
void LockRW::lockW(unsigned short tm) {
    int rez = 0;
#if !__GLIBC_PREREQ(2,4)
    // EDEADLK test
    if (wThr && wThr == pthread_self()) rez == EDEADLK;
    else
#endif
    if (!tm) rez = pthread_rwlock_wrlock(&rwlock);
    else {
        timespec wtm = {0};
        //clock_gettime(pSYS->clockRT()?CLOCK_REALTIME:CLOCK_MONOTONIC, &wtm);
        clock_gettime(CLOCK_REALTIME, &wtm); // for pthread_rwlock the clock source changing unallowed!
        wtm.tv_nsec += 1000000*(tm%1000);
        wtm.tv_sec += tm/1000 + wtm.tv_nsec/1000000000;
        wtm.tv_nsec = wtm.tv_nsec%1000000000;
        rez = pthread_rwlock_timedwrlock(&rwlock, &wtm);
    }
    if (rez == EDEADLK) throw TError(E_Deadlock, ("LockRW"));
    else if (tm && rez == ETIMEDOUT) throw TError(E_Timeout, ("LockRW"));

#if !__GLIBC_PREREQ(2,4)
    wThr = pthread_self();
#endif
}

//=--------------------------------------------------------------------------=
void LockRW::lockR(unsigned short tm) {
    int rez = 0;
#if !__GLIBC_PREREQ(2,4)
    // EDEADLK imitation
    if (wThr && wThr == pthread_self()) rez == EDEADLK;
    else
#endif
    if (!tm) rez = pthread_rwlock_rdlock(&rwlock);
    else {
        timespec wtm = {0};
        //clock_gettime(pSYS->clockRT()?CLOCK_REALTIME:CLOCK_MONOTONIC, &wtm);
        clock_gettime(CLOCK_REALTIME, &wtm); // for pthread_rwlock the clock source changing unallowed!
        wtm.tv_nsec += 1000000*(tm%1000);
        wtm.tv_sec += tm/1000 + wtm.tv_nsec/1000000000; wtm.tv_nsec = wtm.tv_nsec%1000000000;
        rez = pthread_rwlock_timedrdlock(&rwlock, &wtm);
    }
    if (rez == EDEADLK) throw TError(E_Deadlock, ("LockRW"));
    else if (tm && rez == ETIMEDOUT) throw TError(E_Timeout, ("LockRW"));
}

//=--------------------------------------------------------------------------=
bool LockRW::tryR() {
    int rez = pthread_rwlock_tryrdlock(&rwlock);
    if (rez == EBUSY) return false;
    else if (rez == EDEADLK) throw TError(E_Deadlock, ("LockRW"));
    return true;
}

//=--------------------------------------------------------------------------=
bool LockRW::tryW() {
    int rez = pthread_rwlock_trywrlock(&rwlock);
    if (rez == EBUSY) return false;
    else if (rez == EDEADLK) throw TError(E_Deadlock, ("LockRW"));
    return true;
}

//=--------------------------------------------------------------------------=
void LockRW::unlock() {
    pthread_rwlock_unlock(&rwlock);
#if !__GLIBC_PREREQ(2,4)
    if (wThr == pthread_self()) wThr = 0;
#endif
}

//=--------------------------------------------------------------------------=
// Thread Auto RW-lock object
//=--------------------------------------------------------------------------=
void AutoRW::lock(bool write, unsigned short tm )
{
    if (mLock) unlock();
    mLock = false;
    try {
        if (write) mId.lockW(tm); else mId.lockR(tm);
        mLock = true;
    } catch (TError &err) {
        if (err.code != E_Deadlock) throw;
    }
}

//=--------------------------------------------------------------------------=
// Conditional variable object, by mutex
//=--------------------------------------------------------------------------=
void ThreadCond::init() {
    pthread_condattr_t attr;
    pthread_condattr_init(&attr);
#if __GLIBC_PREREQ(2,4) && (__ANDROID_API__ == 0 || __ANDROID_API__ > 19)
    //pthread_condattr_setclock(&attr, pSYS->clockRT() ? CLOCK_REALTIME : CLOCK_MONOTONIC);
    pthread_condattr_setclock(&attr, CLOCK_REALTIME);
#else
    pthread_condattr_setclock(&attr, CLOCK_REALTIME);
#endif
    pthread_cond_init(&cnd, &attr);
    pthread_condattr_destroy(&attr);
}

//=--------------------------------------------------------------------------=
void ThreadCond::exit() {
    pthread_cond_destroy(&cnd);
}

//=--------------------------------------------------------------------------=
int ThreadCond::wait( unsigned short tm ) {
    int rc = 0;
    TSClass<Mutex> locker(*pMtx);
    if (tm) {
        timespec wtm = {0};
#if __GLIBC_PREREQ(2,4) && (__ANDROID_API__ == 0 || __ANDROID_API__ > 19)
        //clock_gettime(pSYS->clockRT() ? CLOCK_REALTIME : CLOCK_MONOTONIC, &wtm);
        clock_gettime(CLOCK_REALTIME, &wtm);
#else
        clock_gettime(CLOCK_REALTIME, &wtm);
#endif
        wtm.tv_nsec += 1000000*(tm%1000);
        wtm.tv_sec += tm/1000 + wtm.tv_nsec/1000000000;
        wtm.tv_nsec = wtm.tv_nsec%1000000000;
        rc = pthread_cond_timedwait(&cnd, pMtx->ptr(), &wtm);
    }
    rc = pthread_cond_wait(&cnd, pMtx->ptr());
    return rc;
}

int ThreadCond::wakeOne( )	{ return pthread_cond_signal(&cnd); }
int ThreadCond::wakeAll( )	{ return pthread_cond_broadcast(&cnd); }

//=--------------------------------------------------------------------------=
