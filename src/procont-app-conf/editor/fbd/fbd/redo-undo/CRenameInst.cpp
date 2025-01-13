//
// Created by artem on 11/18/24.
//

#include "CRenameInst.h"

CRenameInst::CRenameInst(COglWorld *wgt, CFbdObject *obj, const QString &oldName, const QString &newName)
{
    m_ogl_widget = wgt;
    m_object = obj;
    m_old = oldName;
    m_new = newName;
    setText("Переименование объекта");
}

CRenameInst::~CRenameInst()
= default;

void CRenameInst::redo()
{
    m_object->set_instance_name(m_new);
    m_ogl_widget->update_hatch();

    if (m_old != "???")
    {
        emit m_ogl_widget->iface_var_rename(m_old, m_new);
    }
    else
    {
        emit m_ogl_widget->iface_var_new(m_object->type_name(), m_new);
    }
    emit m_ogl_widget->diagram_changed(m_ogl_widget->current_pou()->dom_node());
}

void CRenameInst::undo()
{
    m_object->set_instance_name(m_old);
    m_ogl_widget->update_hatch();

    if (m_old != "???")
        emit m_ogl_widget->iface_var_rename(m_new, m_old);
    else
        emit m_ogl_widget->instance_removed(m_object->type_name(), m_new);

    emit m_ogl_widget->diagram_changed(m_ogl_widget->current_pou()->dom_node());
}
