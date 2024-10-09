#ifndef COMPILER_H
#define COMPILER_H

#include <QProcess>

// ----------------------------------------------------------------------------
// *** Compiler ***

/*!
 * \brief The Compiler class
 */

class Compiler : public QObject
{
    Q_OBJECT
public:
    Compiler();

    int compile();

protected slots:
    void slot_readStandardOutput();
    void slot_readStandardError();

protected:
    QString _m_compiler;
    QStringList _m_args;

private:
    QProcess _m_process;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Compiler ***

/*!
 * \brief The Compiler class
 */

class Compiler_matiec : public Compiler
{
public:
    Compiler_matiec(const QString &st_file_, const QString &build_path_, const QString &compiler_path_);
};
// ----------------------------------------------------------------------------

#endif
