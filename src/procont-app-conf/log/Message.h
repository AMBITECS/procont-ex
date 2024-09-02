#ifndef MESSAGE_H
#define MESSAGE_H

#include <QStringList>
#include <QDateTime>
#include <QMetaType>

class CMessage
{
public:
    enum eMsgType
    {
        eMT_Info = 1,
        eMT_Warning = 2,
        eMT_Critical = 3
    };
    CMessage() = default;
    CMessage(void *, const QString &, const QStringList &, eMsgType, quint64, const QDateTime &);
    CMessage(const CMessage &);
    ~CMessage() = default;
    CMessage & operator= (const CMessage &) = default;

public:
    quint64 number() const;
    void * object() const;
    QString function() const;
    QStringList text() const;
    eMsgType type() const;
    QDateTime time() const;
    QString toString() const;

private:
    static QString toString_type(eMsgType);

private:
    void * m_object;
    QString m_function;
    QStringList m_text;
    eMsgType m_type;
    quint64 m_number;
    QDateTime m_time;
};

Q_DECLARE_METATYPE(CMessage)

#endif // MESSAGE_H
