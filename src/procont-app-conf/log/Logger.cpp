#include "Logger.h"

#include <QTreeWidgetItem>
#include <QDateTime>

#include <QDebug>

CMessanger * CMessanger::_m_instance = nullptr;
QDir CMessanger::_m_log_dir = {};
QFile CMessanger::_m_messages_file = {};
QTextStream CMessanger::_m_messages_stream = {};

CMessanger::CMessanger() :
    QObject(nullptr),
    _m_message_counter(0)
{
}

CMessanger::~CMessanger()
{
    _m_messages_stream.flush();
    _m_messages_file.flush();
    _m_messages_file.close();
}

void CMessanger::set_log_dir(const QString &path_)
{
    _m_log_dir.setPath(path_);

    if(!_m_log_dir.exists())
        _m_log_dir.mkpath(path_);

    _m_messages_file.setFileName(get_filepath(path_));
    _m_messages_file.open(QIODevice::WriteOnly);

    _m_messages_stream.setDevice(&_m_messages_file);
}

QString CMessanger::get_filepath(const QString &path_)
{
    QString _file_path = {};

    auto _file_name = QString("procont.messages.%1").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    auto i = 0;
    while(i < 1 || (QFileInfo(_file_path).exists() && i < 99))
    {
        _file_path = QString("%1/%2%3.log").arg(path_).arg(_file_name).arg((i > 0) ? "" : QString(".%1").arg(i));
        i++;
    }

    return _file_path;
}

CMessanger * CMessanger::instance()
{
    if(!_m_instance)
        _m_instance = new CMessanger;

    return _m_instance;
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
    ++_m_message_counter;
    auto message = CMessage(object_, get_function(function_), text_, level_, type_, _m_message_counter, time_);
    qDebug() << message.toString_debug();
    _m_messages_stream << message.toString_file();
    _m_messages_stream.flush();
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
