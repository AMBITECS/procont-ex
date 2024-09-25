#include "Logger.h"

#include <QTreeWidgetItem>

#include <QDebug>

CMessanger * CMessanger::m_pInstance = nullptr;

CMessanger::CMessanger() :
    QObject(nullptr),
    m_uiMessageCounter(0)
{
}

CMessanger::~CMessanger()
{
}

CMessanger * CMessanger::instance()
{
    if(!m_pInstance)
        m_pInstance = new CMessanger;

    return m_pInstance;
}

QString CMessanger::get_function(const QString &function_)
{
    QString str(function_);
    str.remove(QRegularExpression("\\(.*")); str.remove(QRegularExpression(".*\\s+"));

    return str;
}

void CMessanger::add(void *object_, const QString &function_, const QStringList &text_, CMessage::eMsgType type_, const QDateTime &time_)
{
    ++m_uiMessageCounter;
    CMessage message = CMessage(object_, get_function(function_), text_, type_, m_uiMessageCounter, time_);
    qDebug() << message.toString();
    emit signal_send(message);
}

void CMessanger::information(void *object_, const QString &function_, const QStringList &text_)
{
    add(object_, function_, text_, CMessage::eMT_Info);
}

void CMessanger::warning(void *object_, const QString &function_, const QStringList &text_)
{
    add(object_, function_, text_, CMessage::eMT_Warning);
}

void CMessanger::critical(void *object_, const QString &function_, const QStringList &text_)
{
    add(object_, function_, text_, CMessage::eMT_Critical);
}
