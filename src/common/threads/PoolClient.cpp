//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#include "PoolClient.h"
#include "ThreadPool.h"

ThreadPool* PoolClient::defaultPool = nullptr;

//=--------------------------------------------------------------------------=
// PoolClient object
//=--------------------------------------------------------------------------=
PoolClient::PoolClient() : state(IDLE), pool(defaultPool) {
    if (hasPool()) pool->regClient( this );
}

//=--------------------------------------------------------------------------=
void PoolClient::SetPool(ThreadPool *newPool) {
    if (pool != newPool) {
        bool bQueued = false;
        if (pool != nullptr) bQueued = pool->unregClient( this );
        if (((pool = newPool) != nullptr)) {
            pool->regClient( this );
            if (bQueued) {
                DoWork();
            }
        } else {
            EndWork();
        }
    }
}

//=--------------------------------------------------------------------------=
void PoolClient::DoWork()    { if (hasPool()) pool->joinQueue ( this ); }
void PoolClient::EndWork()   { if (hasPool()) pool->leaveQueue( this ); }

//=--------------------------------------------------------------------------=
