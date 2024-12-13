//
// Created by artem on 11/17/24.
//

#include "CEditors.h"
#include "../graphics/CDiagramObject.h"
#include "../graphics/coglwidget.h"
#include "../redo-undo/CPinRename.h"
#include "../redo-undo/CPinConnecting.h"
#include "editor/fbd/resources/colors.h"

CEditors::CEditors(COglWidget *wgt, COglWorld *world, QDomNode *pou_node)
{
    m_pou_node = pou_node;
    m_obj_inst_editor = new CInstEditor(wgt);
    connect(m_obj_inst_editor, &CInstEditor::insert_new,
            this, &CEditors::insert_new_inst);

    connect(m_obj_inst_editor, &CInstEditor::rename,
            this, &CEditors::rename_inst);

    connect(m_obj_inst_editor, &CInstEditor::escaped,
            this, &CEditors::cancel_inst_naming);


    m_pin_var_editor  = new CPinVarEditor(wgt);
    connect(m_pin_var_editor, &CPinVarEditor::edit_cancel,
            this, &CEditors::pin_edit_cancel);
    connect(m_pin_var_editor, &CPinVarEditor::new_pin_connection,
            this, &CEditors::new_pin_connection);

    m_obj_inst_editor->setVisible(false);
    m_pin_var_editor->setVisible(false);

    m_var_analytics = new CVariablesAnalytics(world);
    m_wgt = wgt;
    m_world = world;

    m_model = new QVarSelectModel({});
}

CEditors::~CEditors()
{
    delete m_obj_inst_editor;
    delete m_pin_var_editor;
    delete m_var_analytics;
}

void CEditors::show_line_edit(CDiagramObject *obj)
{

    QRect rect = obj->inst_text()->text_rect();
    QPoint pos = obj->inst_text()->pos();
    pos.setY(pos.y() - rect.height());

    auto exist = m_var_analytics->get_interface_variables();

    m_inst_old_name = obj->instance_name();

    m_obj_inst_editor->set_existing(&exist,obj->instance_name(), obj->type());

    m_obj_inst_editor->move(pos);
    m_obj_inst_editor->setText(obj->instance_name());
    m_obj_inst_editor->setVisible(true);
    m_obj_inst_editor->show();
    m_obj_inst_editor->setFocus(Qt::FocusReason::PopupFocusReason);

    m_diagram_object = obj;
}

void CEditors::show_combo(CPin *pin)
{
    if (m_pin_var_editor->isVisible())
    {
        return;
    }

    m_pin = pin;

    combo_data = m_var_analytics->query(pin);

    m_model->set_data(&combo_data);
    m_pin_var_editor->setModel(m_model);
    m_pin_var_editor->expandAll();

    auto rect = pin->rect();
    QPoint pos;
    if(pin->direction() == PD_INPUT)
    {
        int x = rect->topLeft().x() - m_pin_var_editor->width();
        pos = rect->topLeft();
        pos.setX(x);
    }
    else
        pos = rect->topRight();

    m_pin_var_editor->move(pos);
    m_pin_var_editor->setVisible(true);
    m_pin_var_editor->show();
    m_pin_var_editor->setFocus(Qt::FocusReason::PopupFocusReason);

    pin->parent()->update_bound_rect();
    pin->parent()->parent()->resort();
    pin->parent()->parent()->update_real_position();
}


void CEditors::cancel_inst_naming()
{
    QColor color = m_obj_inst_editor->is_error() ? m_obj_inst_editor->color() : QColor(Qt::black);
    m_diagram_object->inst_text()->set_color(color);

    m_diagram_object = nullptr;
    m_obj_inst_editor->setVisible(false);
    m_obj_inst_editor->hide();

    m_wgt->repaint();
}

void CEditors::rename_inst()
{
    bool is_error = m_obj_inst_editor->is_error();
    QString new_name = m_obj_inst_editor->text();

    CDiagramColors colors;
    QColor err_color = is_error ? colors.base_colors().err_color : colors.base_colors().diag_text_def;

    m_diagram_object->inst_text()->set_color(err_color);

    m_diagram_object = nullptr;
    m_obj_inst_editor->setVisible(false);
    m_obj_inst_editor->hide();

    if (!is_error)
    {
        emit interface_rename(m_inst_old_name, new_name);
    }

}

void CEditors::insert_new_inst()
{
    bool is_error = m_obj_inst_editor->is_error();
    QString new_name = m_obj_inst_editor->text();

    CDiagramColors colors;
    QColor err_color = is_error ? colors.base_colors().err_color : colors.base_colors().diag_text_def;

    m_diagram_object->inst_text()->set_color(err_color);

    QString type = m_diagram_object->type_name();

    m_diagram_object = nullptr;
    m_obj_inst_editor->setVisible(false);
    m_obj_inst_editor->hide();

    if (!is_error)
    {
        emit interface_new_var(type, new_name);
    }
}

void CEditors::pin_edit_cancel()
{
    m_pin = nullptr;
    m_pin_var_editor->setVisible(false);
    m_model->set_data({});
    m_pin_var_editor->hide();
}

void CEditors::new_pin_connection(s_tree_item *selected_item, const QString &var_name)
{
    /// find opposite side of the variable
    CPin *opposite_pin = nullptr;
    CVariable   *iface_var = nullptr;
    CBlock *block = nullptr;
    QString opposite_var_name;



    if (!selected_item)
    {
        /// скорее всего это элемент массива
    }
    else
    {
        block = selected_item->block;
        iface_var = selected_item->iface_variable;
        opposite_pin = selected_item->opposite_pin;
    }



    if (opposite_pin && !iface_var && !block)
    {
        auto *cmd = new CPinConnecting(m_world, m_pin, opposite_pin);

        if (!cmd->is_error())
            m_world->undo_stack()->push(cmd);
        else
            delete cmd;
    }

    if (iface_var && !opposite_pin && !block)
    {
        auto cmd = new CPinRename(m_world, m_pin, var_name,
                                          opposite_pin, opposite_var_name, iface_var);
        m_world->undo_stack()->push(cmd);
    }

    if (block && !opposite_pin && !iface_var)
    {

    }



    m_pin = nullptr;
    m_pin_var_editor->setVisible(false);
    m_model->set_data({});
    m_pin_var_editor->hide();

    emit pin_variable_renamed();
}
