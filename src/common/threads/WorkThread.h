//=============================================================================
// Copyright (C) 2024 The Ambitecs Company Ltd.
//=============================================================================
#ifndef A_DEXTER_WORKTHREAD_H
#define A_DEXTER_WORKTHREAD_H
#include "global.h"
#include <QThread>
#include <iostream>

// ----------------------------------------------------------------------------
// Класс "рабочего потока"
// ----------------------------------------------------------------------------
class Worker: public QThread
{
Q_OBJECT
private:
    bool bRun = false;

public:
    EXP Worker(QObject *parent = nullptr);
    ~Worker()  OVR;

    void start();
    void stop();
    void run() OVR;

Q_SIGNALS:
    void started();
    void stopped(bool);

// виртуальные функции (реализуются наследниками)
public:
    virtual void onStart() {}
    virtual void onStop() {}
    virtual void doWork() {}
};

// ----------------------------------------------------------------------------
#endif //A_DEXTER_WORKTHREAD_H
