#ifndef COMPILIER_H
#define COMPILIER_H

#include <QProcess>

class Compilier : public QProcess
{
    Q_OBJECT
public:
    Compilier() : QProcess()
    {}
};

#endif
