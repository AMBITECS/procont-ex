//
// Created by artem on 11/17/24.
//

#include "CEditors.h"
#include "../graphics/CDiagramObject.h"
#include "../graphics/coglwidget.h"
#include "../redo-undo/CPinRename.h"

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

    /*connect(m_obj_inst_editor, &CInstEditor::returnPressed,
            this, &CEditors::inst_editor_complete);*/

    m_pin_var_editor  = new CPinVarEditor(wgt);
    connect(m_pin_var_editor, &CPinVarEditor::edit_cancel, this, &CEditors::pin_edit_cancel);
    connect(m_pin_var_editor, &CPinVarEditor::new_variable_name, this, &CEditors::pin_new_variable);

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

void CEditors::show_combo(CConnectorPin *pin)
{
    if (m_pin_var_editor->isVisible())
    {
        return;
    }

    m_pin = pin;

    auto model_data = m_var_analytics->query(pin);
    m_model->set_data(&model_data);
    m_pin_var_editor->setModel(m_model);
    m_pin_var_editor->expandAll();

    auto rect = pin->rect();
    QPoint pos = rect->topLeft();

    m_pin_var_editor->move(pos);
    m_pin_var_editor->setVisible(true);
    m_pin_var_editor->show();
    m_pin_var_editor->setFocus(Qt::FocusReason::PopupFocusReason);

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

    QColor color = is_error ? m_obj_inst_editor->color() : QColor(Qt::black);
    m_diagram_object->inst_text()->set_color(color);

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

    QColor color = is_error ? m_obj_inst_editor->color() : QColor(Qt::black);
    m_diagram_object->inst_text()->set_color(color);

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

void CEditors::pin_new_variable(const QString &var_name)
{
    /// find opposite side of the variable
    CConnectorPin *opposite_pin = nullptr;
    CVariable   *iface_var = nullptr;
    QString opposite_var_base;
    QString opposite_var_name;


    if (!m_var_analytics->find_target(var_name.toStdString(), &opposite_pin, &iface_var))
    {
        throw std::runtime_error("What the fuck in 'CEditors::pin_new_variable'");
    }

    if (opposite_pin)
    {
        opposite_var_base = m_pin->parent()->instance_name().isEmpty() ?
                                    m_pin->parent()->type_name() + QString::number(m_pin->parent()->local_id()) :
                                    m_pin->parent()->instance_name();
        opposite_var_name = opposite_var_base + "." + m_pin->formal_param();
    }

    auto cmd_pin_var = new CPinRename(m_world, m_pin, var_name,
                                      opposite_pin, opposite_var_name, iface_var);
    m_world->undo_stack()->push(cmd_pin_var);

    m_pin = nullptr;
    m_pin_var_editor->setVisible(false);
    m_model->set_data({});
    m_pin_var_editor->hide();

    emit pin_variable_renamed();
}
