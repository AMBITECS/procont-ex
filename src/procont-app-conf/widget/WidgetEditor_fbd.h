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

#endif // WIDGETEDITOR_FBD_H
