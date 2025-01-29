#ifndef CMESSANGER_H
#define CMESSANGER_H

#include "Message.h"

#define m_info(X) CMessanger::instance()->information((void*)this, __PRETTY_FUNCTION__, QStringList(X))
#define m_warn(X) CMessanger::instance()->warning((void*)this, __PRETTY_FUNCTION__, QStringList(X))
#define m_crit(X) CMessanger::instance()->critical((void*)this, __PRETTY_FUNCTION__, QStringList(X))

#define m_command(X) CMessanger::instance()->add_cmd(X, CMessage::eMT_Message)

#define b_info(X) CMessanger::instance()->information((void*)this, __PRETTY_FUNCTION__, QStringList(X), CMessage::eMT_Build)
#define b_warn(X) CMessanger::instance()->warning((void*)this, __PRETTY_FUNCTION__, QStringList(X), CMessage::eMT_Build)
#define b_crit(X) CMessanger::instance()->critical((void*)this, __PRETTY_FUNCTION__, QStringList(X), CMessage::eMT_Build)

#define b_command(X) CMessanger::instance()->add_cmd(X, CMessage::eMT_Build)

#define b_text(X) CMessanger::instance()->add_txt(X)

#include <QObject>
#include <QMap>
#include <QTextStream>
#include <QDir>

class QTreeWidget;

class CMessanger : public QObject
{
    Q_OBJECT
private:
    CMessanger();
public:
    ~CMessanger();

public:
    static void set_log_dir(const QString &path_);

public:
    void add_message(void *, const QString &, const QStringList &, CMessage::eMsgLevel,
             IMessage::eMsgTab = IMessage::eMT_Message, const QDateTime & = QDateTime::currentDateTime());
    void add_cmd(CCmd::eCmdType, IMessage::eMsgTab = IMessage::eMT_Build);
    void add_txt(const QString &);

    void information(void *object_, const QString &function_, const QStringList &, IMessage::eMsgTab type_ = IMessage::eMT_Message);
    void warning(void *object_, const QString &function_, const QStringList &, IMessage::eMsgTab type_ = IMessage::eMT_Message);
    void critical(void *object_, const QString &function_, const QStringList &, IMessage::eMsgTab type_ = IMessage::eMT_Message);

signals:
    void signal_send_msg(const CMessage &);
    void signal_send_cmd(const CCmd &);
    void signal_send_txt(const CText &);

public:
    static CMessanger* instance();
    static QString get_function(const QString &);
    static QString get_filepath(const QString &path_);

private:
    static CMessanger * _m_instance;
    static QDir _m_log_dir;
    static QFile _m_messages_file;
    static QTextStream _m_messages_stream;

private:
    quint64 _m_message_counter;
};

#endif // CMESSANGER_H
