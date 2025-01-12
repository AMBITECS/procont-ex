#ifndef WIDGETEDITOR_FBD_H
#define WIDGETEDITOR_FBD_H

#include "WidgetEditor.h"

// ----------------------------------------------------------------------------
// *** WidgetEditor_fbd ***

/*!
 * \brief The WidgetEditor_fbd class
 */

QT_FORWARD_DECLARE_CLASS(CDiagramWidget)

class WidgetEditor_fbd : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_fbd(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

    void set_active() override;

protected:
    QWidget * createCodeEditor() override;

protected slots:
    void slot_codeShmViewToggled(bool);
    void slot_codeTxtViewToggled(bool);
    void slot_codeShmChanged(const QDomNode &new_node_);
    void slot_interfaceVariableAdd(const QString &type_, const QString &name_);
    void slot_interfaceVariableDel(const QString &type_, const QString &name_);
    void slot_interfaceVariableRename(const QString &old_name_, const QString &new_name_);
    // void slot_undo_enabled();
    void slot_object_selected();
    void slot_user_clicked();

    void slot_varAddVariable();
    void slot_varDelVariable();
    void slot_varTxtVarChanged() override;
    void slot_varTblVarChanged() override;

private:
    CDiagramWidget * _m_fbd_view = nullptr;
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_FBD_H
