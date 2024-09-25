#ifndef CWIDGETMESSAGE_H
#define CWIDGETMESSAGE_H

#include "log/Message.h"

#include <QTabWidget>

QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)
QT_FORWARD_DECLARE_CLASS(QPlainTextEdit)
QT_FORWARD_DECLARE_CLASS(QUndoView)

class CWidgetMessage : public QTabWidget
{
    Q_OBJECT
private:
    explicit CWidgetMessage(QWidget *parent = nullptr);

public:
    virtual ~CWidgetMessage();

public:
    static CWidgetMessage* instance();

    static QPlainTextEdit* buildWidget();

private slots:
    void slot_add(const CMessage &);

private:
    void set_type(QTreeWidgetItem *, CMessage::eMsgType) const;

private:
    QTreeWidget * m_pWidgetMessage;
    QUndoView * m_pWidgetAction;

private:
    static QPlainTextEdit * m_pWidgetBuild;

private:
    static CWidgetMessage *m_pInstance;
};

#endif // CWIDGETMESSAGE_H
