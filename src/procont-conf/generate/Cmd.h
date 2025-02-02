#ifndef CMD_H
#define CMD_H

#include <QSharedPointer>
#include <QProcess>

// ----------------------------------------------------------------------------
// *** Cmd ***

/*!
 * \brief The Cmd class
 */

class Cmd : public QObject
{
    Q_OBJECT
public:
    Cmd() = default;

    int execute();

public slots:
    void slot_readStandardOutput();
    void slot_readStandardError();
    void slot_finished(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    qsizetype _m_current_index{0};
    QSharedPointer<QProcess> _m_current_proc{nullptr};
    QList<QSharedPointer<QProcess>> _m_procs;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Cmd_compile_matiec ***

/*!
 * \brief The Cmd_compile_matiec class
 */

class Cmd_compile_matiec : public Cmd
{
public:
    Cmd_compile_matiec(const QString &st_file_, const QString &build_path_, const QString &compiler_path_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Cmd_cmake_generate ***

/*!
 * \brief The Cmd_cmake_generate class
 */

class Cmd_cmake_generate : public Cmd
{
public:
    Cmd_cmake_generate(const QString &build_path_, const QString &cmake_path_);
};
// ----------------------------------------------------------------------------

#endif
