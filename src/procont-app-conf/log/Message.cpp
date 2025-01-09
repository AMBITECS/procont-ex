#include "Message.h"

#include <QDebug>

QString IMessage::toString_type(eMsgTab type_)
{
    switch(type_)
    {
    case IMessage::eMT_Message:
        return QString(" message  ");
        break;
    case IMessage::eMT_Action:
        return QString(" action   ");
        break;
    case IMessage::eMT_Build:
        return QString(" build    ");
        break;
    default:
        return QString(" message  ");
        break;
    }
}

CText::CText(const QString& text_) :
    m_text(text_)
{
}

CText::CText(const CText &msg_) :
    m_text(msg_.m_text)
{
}

QString CText::text() const
{
    return m_text;
}

CCmd::CCmd(eCmdType cmd_, eMsgTab type_) :
    m_cmd(cmd_),
    m_type(type_)
{
}

CCmd::CCmd(const CCmd &msg_) :
    m_cmd(msg_.m_cmd),
    m_type(msg_.m_type)
{
}

CCmd::eCmdType CCmd::cmd() const
{
    return m_cmd;
}

CCmd::eMsgTab CCmd::type() const
{
    return m_type;
}

CMessage::CMessage
    (
        void *object_, const QString &function_, const QStringList &text_,
        CMessage::eMsgLevel level_, CMessage::eMsgTab type_, quint64 number_, const QDateTime &time_
    ) :
    m_object(object_),
    m_function(function_),
    m_text(text_),
    m_level(level_),
    m_type(type_),
    m_number(number_),
    m_time(time_)
{
}

CMessage::CMessage(const CMessage &msg_) :
    m_object(msg_.m_object),
    m_function(msg_.m_function),
    m_text(msg_.m_text),
    m_level(msg_.m_level),
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

CMessage::eMsgLevel CMessage::level() const
{
    return m_level;
}

CMessage::eMsgTab CMessage::type() const
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

QString CMessage::toString_level(eMsgLevel level_)
{
    switch(level_)
    {
    case CMessage::eML_Info:
        return QString(" info     ");
        break;
    case CMessage::eML_Warning:
        return QString(" warning  ");
        break;
    case CMessage::eML_Critical:
        return QString(" critical ");
        break;
    default:
        return QString(" info     ");
        break;
    }
}

QString CMessage::toString_debug() const
{
    return QString("%1 | %2 | %3 | %4 | %5 | 0x%6 | %7")
            .arg(QString().asprintf("%08lld", number()))
            .arg(time().toString("dd.MM.yyyy hh:mm:ss.zzz"), toString_type(type()), toString_level(level()))
            .arg(function(), 30)
            .arg(*(quint64*)object(), 16, 16, QChar('0'))
            .arg(text().join(":"));
}

QString CMessage::toString_file() const
{
    QString _message_string = {};
    QTextStream _message_stream(&_message_string);
    auto n = 0;
    for(const auto & i : text())
    {
        if(!n)
            _message_stream << QString("%1 | %2 | %3 | %4 | %5 | 0x%6 | %7")
                            .arg(QString().asprintf("%08lld", number()))
                            .arg(time().toString("dd.MM.yyyy hh:mm:ss.zzz"), toString_type(type()), toString_level(level()))
                            .arg(function(), 30)
                            .arg(*(quint64*)object(), 16, 16, QChar('0'))
                            .arg(i)
                     << Qt::endl;
        else
            _message_stream << QString("%1   %2   %3   %4   %5   %6   %7")
                            .arg(QString(),  8, QChar(' '))
                            .arg(QString(), 23, QChar(' '))
                            .arg(QString(), 10, QChar(' '))
                            .arg(QString(), 10, QChar(' '))
                            .arg(QString(), 30, QChar(' '))
                            .arg(QString(), 18, QChar(' '))
                            .arg(i)
                     << Qt::endl;

        n++;
    }

    return _message_string;
}
