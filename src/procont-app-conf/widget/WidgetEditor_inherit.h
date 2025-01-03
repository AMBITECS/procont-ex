#ifndef WIDGETEDITOR_INHERIT_H
#define WIDGETEDITOR_INHERIT_H

#include "WidgetEditor.h"

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
// *** WidgetEditor_ld ***

/*!
 * \brief The WidgetEditor_ld class
 */

QT_FORWARD_DECLARE_CLASS(CLdDiagram)

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
    virtual QWidget * createCodeEditor() override;
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_INHERIT_H
