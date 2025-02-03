#include "Cmd.h"

#include "log/Logger.h"

#include <QFileInfo>

// #include "main/MainWindow.h"

// ----------------------------------------------------------------------------
// *** Cmd ***
//
// Cmd::Cmd()
// {
// }

int Cmd::execute()
{
    if(!_m_procs.size())
        return 1;

    _m_current_proc = _m_procs.at(_m_current_index);

    connect(_m_current_proc.get(), &QProcess::readyReadStandardOutput, this, &Cmd::slot_readStandardOutput);
    connect(_m_current_proc.get(), &QProcess::readyReadStandardError, this, &Cmd::slot_readStandardError);
    connect(_m_current_proc.get(), &QProcess::finished, this, &Cmd::slot_finished);

    if(!QFileInfo::exists(_m_current_proc->program()))
    {
        QStringList lmess;
        lmess << QObject::tr("Program not found, execution is aborted");
        lmess << QString(QObject::tr("not found file '%1'").arg(_m_current_proc->program()));
        // lmess << QString(QObject::tr("enter correct program path"));
        m_warn(lmess);
        return 1;
    }

    _m_current_proc->start();

    if(!_m_current_index)
    {
        b_command(CCmd::eCT_Clear);
        m_info(QObject::tr("build started"));
    }

    return 0;

}

void Cmd::slot_readStandardOutput()
{
    auto output = _m_current_proc->readAllStandardOutput().split('\n');

    if(output.last().size() == 0)
        output.removeLast();

    for(const auto &i : output)
        b_info(i);
}

void Cmd::slot_readStandardError()
{
    auto error = _m_current_proc->readAllStandardError().split('\n');

    if(error.last().size() == 0)
        error.removeLast();

    for(const auto &i : error)
        b_crit(i);
}

void Cmd::slot_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString message = QObject::tr("build finished");
    if(exitCode > 0)
    {
        m_warn(message);
        return;
    }

    if(_m_current_index < _m_procs.size()-1)
    {
        _m_current_index++;
        execute();
    }
    else
        m_info(message);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Cmd_compile_matiec ***
//
Cmd_compile_matiec::Cmd_compile_matiec(const QString &st_file_, const QString &build_path_, const QString &matiec_path_)
{
    auto _proc = QSharedPointer<QProcess>::create();

    _proc->setProgram(QString("%1/iec2c").arg(matiec_path_));
    _proc->setArguments(
        QStringList() << "-f" << "-l" << "-p"
                      << "-I" << QString("%1/lib").arg(matiec_path_)
                      << "-T" << QString("%1").arg(build_path_)
                      << QString("%1/%2").arg(build_path_, st_file_));

    _m_procs << _proc;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Cmd_cmake_generate ***
//
Cmd_cmake_generate::Cmd_cmake_generate(const QString &build_path_, const QString &cmake_path_)
{
    auto _proc = QSharedPointer<QProcess>::create();

    _proc->setWorkingDirectory(QString("%1/build-ex").arg(build_path_));
    _proc->setProgram(QString("%1/cmake").arg(cmake_path_));
    _proc->setArguments(QStringList() << "..");

    _m_procs << _proc;

    _proc = QSharedPointer<QProcess>::create();

    _proc->setWorkingDirectory(QString("%1/build-ex").arg(build_path_));
    _proc->setProgram(QString("%1/cmake").arg(cmake_path_));
    _proc->setArguments(QStringList() << "--build" << ".");

    _m_procs << _proc;
}
// ----------------------------------------------------------------------------

