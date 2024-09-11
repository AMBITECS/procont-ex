//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#include "WorkThread.h"

// ----------------------------------------------------------------------------
Worker::Worker(QObject *parent) : QThread(parent) {
    connect(this, &Worker::started,
            [=](){std::cout<<objectName().toStdString() << " launched " << std::endl;});
    connect(this, &Worker::stopped,
            [=](){std::cout<<objectName().toStdString() << " stopped  " << std::endl;});
}

// ----------------------------------------------------------------------------
Worker::~Worker() {
    stop();
}

// ----------------------------------------------------------------------------
void Worker::start() {
    if (!isRunning()) {
        QThread::start();
    }
}

// ----------------------------------------------------------------------------
void Worker::stop() {
    if (isRunning())  {
        bRun=false;
        wait();
    }
}

// ----------------------------------------------------------------------------
void Worker::run() {
    emit started();
    onStart();
    for(bRun=true; bRun;) {
        doWork();               // выполнение работы в потоке
        yieldCurrentThread();   // немного времени для других потоков (аналог msleep(0L);)
    }
    onStop();
    emit stopped(true);
}

// ----------------------------------------------------------------------------
