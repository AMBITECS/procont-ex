#include "Message.h"

#include <QDebug>

CMessage::CMessage
    (
        void *object_, const QString &function_, const QStringList &text_,
        CMessage::eMsgType type_, quint64 number_, const QDateTime &time_
    ) :
    m_object(object_),
    m_function(function_),
    m_text(text_),
    m_type(type_),
    m_number(number_),
    m_time(time_)
{
}

CMessage::CMessage(const CMessage &msg_) :
    m_object(msg_.m_object),
    m_function(msg_.m_function),
    m_text(msg_.m_text),
    m_type(msg_.m_type),
    m_number(msg_.m_number),
    m_time(msg_.m_time)
{
}

void * CMessage::object() const
{
    return m_object;
}

QString CMessage::function() const
{
    return m_function;
}

QStringList CMessage::text() const
{
    return m_text;
}

CMessage::eMsgType CMessage::type() const
{
    return m_type;
}

quint64 CMessage::number() const
{
    return m_number;
}

QDateTime CMessage::time() const
{
    return m_time;
}

QString CMessage::toString_type(eMsgType type_)
{
    switch(type_)
    {
    case CMessage::eMT_Info:
        return QString(" info     ");
        break;
    case CMessage::eMT_Warning:
        return QString(" warning  ");
        break;
    case CMessage::eMT_Critical:
        return QString(" critical ");
        break;
    default:
        return QString(" info     ");
        break;
    }
}

QString CMessage::toString() const
{
    return QString("%1 | %2 | %3 | %4 | 0x%5 | %6")
            .arg(QString().asprintf("%08lld", number()))
            .arg(time().toString("dd.MM.yyyy hh:mm:ss.zzz"), toString_type(type()))
            .arg(function(), 30)
            .arg(*(quint64*)object(), 16, 16, QChar('0')).arg(text().join(":"));
}
