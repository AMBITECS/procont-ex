#ifndef WIDGETEDITOR_H
#define WIDGETEDITOR_H

#include <QSplitter>
#include <QDomNode>

// ----------------------------------------------------------------------------
// *** WidgetCodeEditor ***

/*!
 * \brief The WidgetCodeEditor class
 */

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(CodeEditorWidget)
QT_FORWARD_DECLARE_CLASS(TableView)

#include <QAbstractProxyModel>

class WidgetEditor : public QSplitter
{
    Q_OBJECT
public:
    WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

 protected:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

protected slots:
    void slot_varTxtViewToggled(bool);
    void slot_varTblViewToggled(bool);
    void slot_varAddVariable();
    void slot_varDelVariable();
    virtual void slot_varTxtVarChanged();
    virtual void slot_varTblVarChanged();

    void slot_codeTxtChanged();

protected:
    void updateTblView();
    virtual QWidget * createVarsEditor();
    virtual QWidget * createCodeEditor();

protected:
    QModelIndex _index = {};
    QDomNode _node = {};
    QAbstractProxyModel * _proxy = nullptr;

protected:
    TableView * _vars_table = nullptr;
    CodeEditorWidget * _vars_text = nullptr;
    CodeEditorWidget * _body_text = nullptr;
    QWidget * _m_table_container = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_vars ***

/*!
 * \brief The WidgetEditor_vars class
 */
class WidgetEditor_vars : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_vars(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_st ***

/*!
 * \brief The WidgetEditor_st class
 */
class WidgetEditor_st : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_st(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_fbd ***

#include "editor/fbd/fbd/graphics/cdiagramwidget.h"

/*!
 * \brief The WidgetEditor_fbd class
 */

QT_FORWARD_DECLARE_CLASS(CDiagramWidget)

class WidgetEditor_fbd : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_fbd(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

protected:
    QWidget * createCodeEditor() override;
    QWidget * createVarsEditor() override;

protected slots:
    void slot_codeShmViewToggled(bool);
    void slot_codeTxtViewToggled(bool);
    void slot_codeShmChanged(const QDomNode &);
    void slot_interfaceVariableAdd(const QString &type, const QString &name);
    void slot_interfaceVariableDel(const QString &type, const QString &name);
    void slot_interfaceVariableRename(const QString &old_name, const QString &new_name);

    void slot_varAddVariable();
    void slot_varDelVariable();
    void slot_varTxtVarChanged() override;
    void slot_varTblVarChanged() override;

private:
    CDiagramWidget * _m_fbd_view = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_ld ***

#include "editor/fbd/ld/clddiagram.h"

/*!
 * \brief The WidgetEditor_ld class
 */

QT_FORWARD_DECLARE_CLASS(CDiagramWidget)

class WidgetEditor_ld : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_ld(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

protected:
    QWidget * createCodeEditor() override;
    QWidget * createVarsEditor() override;

protected slots:
    void slot_codeShmViewToggled(bool);
    void slot_codeTxtViewToggled(bool);
    void slot_codeShmChanged(const QDomNode &);
    void slot_interfaceVariableAdd(const QString &type, const QString &name);
    void slot_interfaceVariableDel(const QString &type, const QString &name);
    void slot_interfaceVariableRename(const QString &old_name, const QString &new_name);

    void slot_varAddVariable();
    void slot_varDelVariable();
    void slot_varTxtVarChanged() override;
    void slot_varTblVarChanged() override;

private:
    CLdDiagram * _m_ld_view = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_type ***

/*!
 * \brief The WidgetEditor_type class
 */
class WidgetEditor_type : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_type(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

private slots:
    void slot_codeTxtChanged();

    void slot_varTxtVarChanged() override;
    void slot_varTblVarChanged() override;

protected:
    virtual QWidget * createCodeEditor();
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_H
