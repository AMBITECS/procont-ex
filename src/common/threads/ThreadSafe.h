//============================================================================
// ThreadSafe classes
//=--------------------------------------------------------------------------=
// Copyright (C) 2024 The Ambitecs Company Ltd. ALL RIGHTS RESERVED.
// Consult your license regarding permissions and restrictions.
//============================================================================
#ifndef A_DEXTER_THREADSAFE_H
#define A_DEXTER_THREADSAFE_H
#include "global.h"
#include <parallel/features.h>
#include <pthread.h>

//Platform specific
#if defined(__ANDROID__)
    #include <android/api-level.h>
#else
    #define __ANDROID_API__ 0
#endif

#ifndef __GLIBC_PREREQ
    #define __GLIBC_PREREQ(maj, min)	1
#endif

//// Begin with my own namespace "ars"
//ARS_BEGIN

//=--------------------------------------------------------------------------=
// TError - класс для генерации исключений по критическим ошибкам
//=--------------------------------------------------------------------------=
enum TErrCode {
    E_SUCCESS = 0,
    E_BadPtr,
    E_OPEN_SEMA,
    E_Deadlock,
    E_Timeout,
    E_INIT_ATTR,
    E_CREATE_THREAD,
    E_JOIN_THREAD,
    E_Unknown = 999
};

class TError final : public std::exception {
public:
    // Attributes
    TErrCode code;
    QString  desc;

    // Methods
    explicit TError(TErrCode eCode, const QString& ctx = (""));
};

//=--------------------------------------------------------------------------=
// Interlocked template class for atomic Increment & Decrement
//=--------------------------------------------------------------------------=
template <class T> class Interlocked {
public:
    static T Inc( T* ptr ) {
#if defined(__WINDOWS__)
        #if defined(_WIN64)
                return InterlockedIncrement64(ptr);
            #elif defined(_WIN32)
                return InterlockedIncrement(ptr);
            #else
                return InterlockedIncrement16(ptr);
            #endif
#else
        return __sync_add_and_fetch(ptr, 1);
#endif
    }
    static T Dec( T* ptr ) {
#if defined(__WINDOWS__)
        #if defined(_WIN64)
                return InterlockedDecrement64(ptr);
            #elif defined(_WIN32)
                return InterlockedDecrement(ptr);
            #else
                return InterlockedDecrement16(ptr);
            #endif
#else
        return __sync_sub_and_fetch(ptr, 1);
#endif
    }
};

//=--------------------------------------------------------------------------=
// SpinLock class
//=--------------------------------------------------------------------------=
class Spinlock {
protected:
    pthread_spinlock_t spin{};
public:
    explicit Spinlock(int iShared = PTHREAD_PROCESS_PRIVATE) { pthread_spin_init(&spin, iShared); }
    ~Spinlock()     { pthread_spin_destroy(&spin); }

    int lock()      { return pthread_spin_lock(&spin); }
    int trylock()   { return pthread_spin_trylock(&spin); }
    int unlock()    { return pthread_spin_unlock(&spin); }

    pthread_spinlock_t &ref()           { return spin; }
    pthread_spinlock_t& operator*()		{ return spin; }
    pthread_spinlock_t* operator->()    { return &spin; }
};

//=--------------------------------------------------------------------------=
// Mutex class
//=--------------------------------------------------------------------------=
class Mutex  {
protected:
    pthread_mutex_t	mutex;
public:
    explicit Mutex(bool isRecurs = true): mutex(PTHREAD_MUTEX_INITIALIZER) {
        pthread_mutexattr_t attrM;
        pthread_mutexattr_init(&attrM);
        if (isRecurs) pthread_mutexattr_settype(&attrM, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&mutex, &attrM);
        pthread_mutexattr_destroy(&attrM);
    }
    ~Mutex()        { pthread_mutex_destroy(&mutex); }

    int lock()      { return pthread_mutex_lock(&mutex); }
    int unlock()    { return pthread_mutex_unlock(&mutex); }
    int tryLock(unsigned short tm = 0);

    pthread_mutex_t& ref()  { return mutex; }
    pthread_mutex_t* ptr()  { return reinterpret_cast<pthread_mutex_t *>(this); }
};

//=--------------------------------------------------------------------------=
// TSValue template class
//=--------------------------------------------------------------------------=
template <class T> class TSValue: public Mutex {
private:
    T	m_t;
public:
    void	set( const T& src ) {lock(); m_t = src; unlock();};
    T		get() {lock(); T rtn = m_t; unlock(); return rtn; };
};

//=--------------------------------------------------------------------------=
// TSClass - threadSafe class template
//=--------------------------------------------------------------------------=
template <class T, class L = T> class TSClass
{
protected:
    const T&    m_ref;
    const L*    m_pLock;
public:
    explicit TSClass(const T& ref, L* pLocker = nullptr, bool bAutoLock = true): m_ref(ref) {
        m_pLock = (pLocker != nullptr) ? pLocker : &((L&)m_ref);
        if (bAutoLock) lock();
    }
    ~TSClass()    { unlock(); }

    int lock()    { return (m_pLock != nullptr) ? ((L*)m_pLock)->lock() : (-1); }
    int unlock()  { return (m_pLock != nullptr) ? ((L*)m_pLock)->unlock() : (-1); }

    explicit operator T* ()         { return &((T&)m_ref); }	// type cast (T*)
    explicit operator T* ()  const  { return &((T&)m_ref); }	// type cast (T*)

    T*      operator->()	        { return &((T&)m_ref); }	// member-selection operator (->)
    T*      operator->()	const   { return &((T&)m_ref); }	// member-selection operator (->)

    T&		operator* ()	    	{return (T&)m_ref;}
    T&		operator* ()	const 	{return (T&)m_ref;}
};

//=--------------------------------------------------------------------------=
// ThreadSafe -  threadSafe class template with inner spinlock protector
//=--------------------------------------------------------------------------=
template <class T> class ThreadSafe {
private:
    bool            m_bLocked;
    static Spinlock spin;
protected:
    const T&        m_ref;
public:
    explicit ThreadSafe(const T& ref, bool bL = true): m_ref(ref), m_bLocked(false) { if (bL) lock(); }
    ~ThreadSafe() { unlock(); }

    int lock() {
        TSClass<Spinlock> locker(spin);
        if (m_bLocked) return 0;                                // already locked
        int iRes = ((T&)m_ref).lock();                          // lock now
        if (iRes == 0) m_bLocked = true;                        // set locked flag
        return iRes;
    };
    int unlock() {
        TSClass<Spinlock> locker(spin);
        if (!m_bLocked) return 0;                               // already unlocked
        int iRes = ((T&)m_ref).unlock();                        // unlock now
        if (iRes == 0) m_bLocked = false;                       // unset locked flag
        return iRes;
    };

    explicit operator T* ()          { return &((T&)m_ref); }   // type cast (T*)
    explicit operator T* ()  const   { return &((T&)m_ref); }   // type cast (T*)

    T*      operator->()	        { return &((T&)m_ref); }	// member-selection operator (->)
    T*      operator->()	const   { return &((T&)m_ref); }	// member-selection operator (->)

    T&		operator* ()	    	{ return (T&)m_ref; }
    T&		operator* ()	const 	{ return (T&)m_ref; }
};

template<class T> Spinlock ThreadSafe<T>::spin;

//=--------------------------------------------------------------------------=
// POSIX Thread RW-Locker object
//=--------------------------------------------------------------------------=
class LockRW {
public:
    LockRW();
    ~LockRW();

    void lockR(unsigned short tm = 0 );	// Read lock, tm in milliseconds
    void lockW(unsigned short tm = 0 );	// Write lock, tm in milliseconds
    void lock(bool toWr, unsigned short tm = 0 ) { if (toWr) lockW(tm); else lockR(tm); }
    bool tryW();
    bool tryR();
    void unlock();

private:
    pthread_rwlock_t	rwlock;
    #if !__GLIBC_PREREQ(2,4)
        pthread_t		wThr;
    #endif
};

//=--------------------------------------------------------------------------=
// POSIX Thread Auto RW-lock object
//=--------------------------------------------------------------------------=
class AutoRW {
public:
    explicit AutoRW(LockRW &rid) : mId(rid), mLock(false) {};
    AutoRW(LockRW &rid, bool write, unsigned short tm = 0) : mId(rid), mLock(false) { lock(write, tm); }
    ~AutoRW() { unlock(); }
    void lock(bool write = false, unsigned short tm = 0);
    void unlock()  { if (mLock) {mId.unlock(); mLock = false;} }
private:
    LockRW	&mId;
    bool	mLock;
};

//=--------------------------------------------------------------------------=
// Conditional variable object, by mutex
//=--------------------------------------------------------------------------=
class ThreadCond {
private:
    bool            bNewMtx;
    Mutex           *pMtx;
    pthread_cond_t	cnd;

    void            init();
    void            exit();

public:
    explicit ThreadCond(Mutex* pMutex = nullptr): pMtx(pMutex), cnd() {
        if ((bNewMtx = (pMtx == nullptr))) { pMtx = new Mutex(); }
        init();
    }
    ~ThreadCond() { exit(); if (bNewMtx) delete pMtx; }

    int wait(unsigned short tm = 0);
    int wakeOne();
    int wakeAll();
};

//=--------------------------------------------------------------------------=

//ARS_END
#endif //A_DEXTER_THREADSAFE_H
