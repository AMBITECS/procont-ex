#ifndef CWIDGETMESSAGE_H
#define CWIDGETMESSAGE_H

#include "log/Message.h"

// ----------------------------------------------------------------------------
// *** IWidgetProtocolTab ***

#include <QWidget>

/*!
 * \brief The IWidgetProtocolTab interface
 */

class IWidgetProtocolTab : public QWidget
{
    Q_OBJECT
public:
    IWidgetProtocolTab(QWidget *parent_);

    virtual void add(const CMessage &) = 0;
    virtual void exec(const CCmd &) = 0;
    virtual void set(const CText &) = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocolTab_message ***

QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)

/*!
 * \brief The CWidgetProtocolTab_message class
 */

class CWidgetProtocolTab_message : public IWidgetProtocolTab
{
    Q_OBJECT
public:
    CWidgetProtocolTab_message(QWidget *parent_);

    void add(const CMessage &message_) override;
    void exec(const CCmd &) override;
    void set(const CText &) override;

private:
    static void set_type(QTreeWidgetItem *item_, CMessage::eMsgLevel type_);

private:
    QTreeWidget * m_pWidget = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocolTab_build ***

QT_FORWARD_DECLARE_CLASS(QPlainTextEdit)
QT_FORWARD_DECLARE_CLASS(CodeEditorWidget)

/*!
 * \brief The CWidgetProtocolTab_build class
 */

class CWidgetProtocolTab_build : public IWidgetProtocolTab
{
    Q_OBJECT
public:
    CWidgetProtocolTab_build(QWidget *parent_);

    void add(const CMessage &message_) override;
    void exec(const CCmd &) override;
    void set(const CText &) override;

private slots:
    void slot_textViewToggled(bool);
    void slot_treeViewToggled(bool);
    void slot_codeViewToggled(bool);

private:
    static void set_type(QTreeWidgetItem *item_, const QString &type_);

private:
    QTreeWidget * m_pErrorTreeWidget = nullptr;
    QPlainTextEdit * m_pErrorPlainTextWidget = nullptr;
    CodeEditorWidget * m_pCodePlainTextWidget = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocol ***

#include <QTabWidget>

QT_FORWARD_DECLARE_CLASS(QUndoView)

/*!
 * \brief The CWidgetProtocol class
 */

class CWidgetProtocol : public QTabWidget
{
    Q_OBJECT
private:
    explicit CWidgetProtocol(QWidget *parent = nullptr);

public:
    virtual ~CWidgetProtocol();

public:
    static CWidgetProtocol* instance();

    static QPlainTextEdit* buildWidget();

private slots:
    void slot_add_msg(const CMessage &);
    void slot_exec_cmd(const CCmd &);
    void slot_set_txt(const CText &);

private:
    void exec(const CCmd &);

private:
    CWidgetProtocolTab_message * m_pWidgetMessage;
    CWidgetProtocolTab_build * m_pWidgetBuild;
    QUndoView * m_pWidgetAction;

private:
    static CWidgetProtocol *m_pInstance;
};
// ----------------------------------------------------------------------------

#endif // CWIDGETMESSAGE_H
