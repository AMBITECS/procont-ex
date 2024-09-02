#ifndef CMESSANGER_H
#define CMESSANGER_H

#include "Message.h"

#define info(X) CMessanger::instance()->information((void*)this_pointer, __PRETTY_FUNCTION__, QStringList(X))
#define warn(X) CMessanger::instance()->warning((void*)this_pointer, __PRETTY_FUNCTION__, QStringList(X))
#define crit(X) CMessanger::instance()->critical((void*)this_pointer, __PRETTY_FUNCTION__, QStringList(X))

#include <QObject>
#include <QMap>

class QTreeWidget;

class CMessanger : public QObject
{
    Q_OBJECT
private:
    CMessanger();
public:
    ~CMessanger();
public:
    void add(void *, const QString &, const QStringList &, CMessage::eMsgType, const QDateTime & = QDateTime::currentDateTime());
    void information(void *object_, const QString &function_, const QStringList &);
    void warning(void *object_, const QString &function_, const QStringList &);
    void critical(void *object_, const QString &function_, const QStringList &);

signals:
    void signal_send(const CMessage &);

public:
    static CMessanger* instance();
    static QString get_function(const QString &);

private:
    static CMessanger * m_pInstance;
    // static QTreeWidget * m_pWidget;
    quint64 m_uiMessageCounter;
};

#endif // CMESSANGER_H
