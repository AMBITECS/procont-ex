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

void CMessanger::add_message(void *object_, const QString &function_, const QStringList &text_,
                     CMessage::eMsgLevel level_, IMessage::eMsgTab type_, const QDateTime &time_)
{
    ++m_uiMessageCounter;
    auto message = CMessage(object_, get_function(function_), text_, level_, type_, m_uiMessageCounter, time_);
    qDebug() << message.toString();
    emit signal_send_msg(message);
}

void CMessanger::add_cmd(CCmd::eCmdType cmd_, IMessage::eMsgTab type_)
{
    auto cmd = CCmd(cmd_, type_);
    emit signal_send_cmd(cmd);
}

void CMessanger::add_txt(const QString &text_)
{
    auto text = CText(text_);
    emit signal_send_txt(text);
}

void CMessanger::information(void *object_, const QString &function_, const QStringList &text_, IMessage::eMsgTab type_)
{
    add_message(object_, function_, text_, CMessage::eML_Info, type_);
}

void CMessanger::warning(void *object_, const QString &function_, const QStringList &text_, IMessage::eMsgTab type_)
{
    add_message(object_, function_, text_, CMessage::eML_Warning, type_);
}

void CMessanger::critical(void *object_, const QString &function_, const QStringList &text_, IMessage::eMsgTab type_)
{
    add_message(object_, function_, text_, CMessage::eML_Critical, type_);
}
