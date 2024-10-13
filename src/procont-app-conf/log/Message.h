#ifndef MESSAGE_H
#define MESSAGE_H

#include <QStringList>
#include <QDateTime>
#include <QMetaType>

class IMessage
{
public:
    enum eMsgTab
    {
        eMT_Message = 1,
        eMT_Action = 2,
        eMT_Build = 3
    };
public:
    IMessage() = default;

protected:
    static QString toString_type(eMsgTab);
};

class CText : public IMessage
{
public:
    CText() = default;
    CText(const QString &);
    CText(const CText &);
    ~CText() = default;
    CText & operator= (const CText &) = default;

public:
    QString text() const;

private:
    QString m_text;
};

class CCmd : public IMessage
{
public:
    enum eCmdType
    {
        eCT_Clear = 1,
        eCT_Show = 2
    };
    CCmd() = default;
    CCmd(eCmdType, eMsgTab);
    CCmd(const CCmd &);
    ~CCmd() = default;
    CCmd & operator= (const CCmd &) = default;

public:
    eCmdType cmd() const;
    eMsgTab type() const;

private:
    eCmdType m_cmd;
    eMsgTab m_type;
};

class CMessage : public IMessage
{
public:
    enum eMsgLevel
    {
        eML_Info = 1,
        eML_Warning = 2,
        eML_Critical = 3
    };
    CMessage() = default;
    CMessage(void *, const QString &, const QStringList &, eMsgLevel, eMsgTab, quint64, const QDateTime &);
    CMessage(const CMessage &);
    ~CMessage() = default;
    CMessage & operator= (const CMessage &) = default;

public:
    quint64 number() const;
    void * object() const;
    QString function() const;
    QStringList text() const;
    eMsgLevel level() const;
    eMsgTab type() const;
    QDateTime time() const;
    QString toString() const;

private:
    static QString toString_level(eMsgLevel);

private:
    void * m_object;
    QString m_function;
    QStringList m_text;
    eMsgLevel m_level;
    eMsgTab m_type;
    quint64 m_number;
    QDateTime m_time;
};

Q_DECLARE_METATYPE(CMessage)

#endif // MESSAGE_H
