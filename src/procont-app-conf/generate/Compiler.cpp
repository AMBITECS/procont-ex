#include "Compiler.h"

#include "log/Logger.h"

#define this_pointer this

// ----------------------------------------------------------------------------
// *** Compiler ***
//
Compiler::Compiler() :
    _m_process(new QProcess)
{
    connect(&_m_process, &QProcess::readyReadStandardOutput, this, &Compiler::slot_readStandardOutput);
    connect(&_m_process, &QProcess::readyReadStandardError, this, &Compiler::slot_readStandardError);
}

int Compiler::compile()
{
    b_command(CCmd::eCT_Clear);

    _m_process.start(_m_compiler, _m_args);

    return 0;
}

void Compiler::slot_readStandardOutput()
{
    auto output = _m_process.readAllStandardOutput().split('\n');

    if(output.last().size() == 0)
        output.removeLast();

    // if(output.size()) CWidgetMessage::buildWidget()->appendPlainText(output.join('\n'));
}

void Compiler::slot_readStandardError()
{
    auto error = _m_process.readAllStandardError().split('\n');

    if(error.last().size() == 0)
        error.removeLast();

    for(auto i : error)
        b_crit(i);
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

#undef this_pointer
