//
// Created by artem on 11/17/24.
//

#ifndef EDITORSD_CEDITORS_H
#define EDITORSD_CEDITORS_H

#include <QObject>
#include <QLineEdit>
#include <QComboBox>

#include "CVariablesAnalytics.h"
#include "qvarselectmodel.h"
#include "CInstEditor.h"
#include "CPinVarEditor.h"

class COglWidget;

class CEditors : public QObject
{
    Q_OBJECT
public:
    explicit CEditors(COglWidget *wgt, COglWorld *world, QDomNode *pou_node);
    ~CEditors() override;

    void    show_line_edit(CDiagramObject *obj);
    void    show_combo(CPin *pin);

signals:
    /// blocks new/rename
    void   interface_new_var(const QString & type,      const QString & name);
    void   interface_rename( const QString & old_name,  const QString & new_name);
    /// block's pins bind variables
    void   pin_variable_renamed();


protected slots:
    //void  inst_editor_complete();
    void  cancel_inst_naming();
    void  rename_inst();
    void  insert_new_inst();
    void  pin_edit_cancel();
    void  new_pin_connection(s_tree_item * m_selected_item, const QString &m_new_variable);


private:
    CPinVarEditor   * m_pin_var_editor;
    CInstEditor * m_obj_inst_editor;
    QDomNode    * m_pou_node;
    CVariablesAnalytics * m_var_analytics;
    COglWidget  * m_wgt;
    QString       m_inst_old_name;
    QVarSelectModel *m_model;
    COglWorld   * m_world;

    std::vector<s_tree_item>    combo_data;

    CDiagramObject  * m_diagram_object{nullptr};
    CPin   * m_pin{nullptr};
};


#endif //EDITORSD_CEDITORS_H
