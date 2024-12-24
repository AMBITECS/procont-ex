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

    emit m_ogl_widget->iface_var_rename(m_old, m_new);
}

void CRenameInst::undo()
{
    m_object->set_instance_name(m_old);
    m_ogl_widget->update_hatch();

    emit m_ogl_widget->iface_var_rename(m_new, m_old);
}
