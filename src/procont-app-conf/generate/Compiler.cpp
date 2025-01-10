#include "Compiler.h"

#include "log/Logger.h"

#include <QFileInfo>

#include "main/MainWindow.h"

// ----------------------------------------------------------------------------
// *** Compiler ***
//
Compiler::Compiler() :
    _m_process(new QProcess)
{
    connect(&_m_process, &QProcess::readyReadStandardOutput, this, &Compiler::slot_readStandardOutput);
    connect(&_m_process, &QProcess::readyReadStandardError, this, &Compiler::slot_readStandardError);
    connect(&_m_process, &QProcess::finished, this, &Compiler::slot_finished);
}

int Compiler::compile()
{
    if(!QFileInfo::exists(_m_compiler))
    {
        QStringList lmess;
        lmess << QObject::tr("Compiler not found, build is aborted");
        lmess << QString(QObject::tr("not found file '%1'").arg(_m_compiler));
        lmess << QString(QObject::tr("enter correct compiler path in %1").arg(MainWindow::config_file()));
        m_warn(lmess);
        return 1;
    }

    b_command(CCmd::eCT_Clear);

    qDebug() << _m_compiler << _m_args;

    _m_process.start(_m_compiler, _m_args);

    m_info(QObject::tr("build started"));

    return 0;
}

void Compiler::slot_readStandardOutput()
{
    auto output = _m_process.readAllStandardOutput().split('\n');

    if(output.last().size() == 0)
        output.removeLast();

    for(const auto &i : output)
        b_info(i);
}

void Compiler::slot_readStandardError()
{
    auto error = _m_process.readAllStandardError().split('\n');

    if(error.last().size() == 0)
        error.removeLast();

    for(const auto &i : error)
        b_crit(i);
}

void Compiler::slot_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString message = QObject::tr("build finished");
    if(exitCode > 0)
    {
        m_warn(message);
        return;
    }

    m_info(message);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Compiler ***
//
Compiler_matiec::Compiler_matiec(const QString &st_file_, const QString &build_path_, const QString &compiler_path_)
{    
    _m_compiler = QString("%1/iec2c").arg(compiler_path_);

    _m_args << "-f" << "-l" << "-p"
         << "-I" << QString("%1/lib").arg(compiler_path_)
         << "-T" << QString("%1").arg(build_path_)
         << QString("%1/%2").arg(build_path_, st_file_);

}
// ----------------------------------------------------------------------------
