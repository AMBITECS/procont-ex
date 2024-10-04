#ifndef COMPILER_H
#define COMPILER_H

#include <QProcess>

class Compiler : public QProcess
{
    Q_OBJECT
public:
    Compiler();

    virtual int compile();

protected slots:
    void slot_readStandardOutput();
    void slot_readStandardError();

protected:
    QString _m_compiler;
    QStringList _m_args;

private:
    QProcess * _m_process = nullptr;
};

class Compiler_matiec : public Compiler
{
public:
    Compiler_matiec(const QString &st_file_, const QString &build_path_, const QString &compiler_path_);
};

#endif
