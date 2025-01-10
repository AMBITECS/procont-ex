//
// Created by artem on 12/15/24.
//

#include "CConstToPin.h"

#include <utility>

CConstToPin::CConstToPin(COglWorld *world, CPinIn *input, QString c_name)
:   m_world(world), m_pin_in(input), m_var_name(std::move(c_name))
{
    auto type = CFilter::get_type_from_const(m_var_name.toStdString());

    CVariablesAnalytics analytics(m_world, m_world->current_pou()->name());
    s_compare_types compare_types;
    auto res = analytics.check_pin_compatibility(m_pin_in->type_name(),
                                                 m_pin_in->type(),
                                                 base_types_names[type],
                                                 type,
                                                 compare_types);
    if (res)
    {
        setText("Присвоение " + m_pin_in->name_full() + " константы " + m_var_name);
    }
    else
    {
        m_is_error = true;
        setText("Неудачная попытка присвоения константы " + m_var_name + " входом " + m_pin_in->name_full());
    }
}

CConstToPin::~CConstToPin()
= default;

void CConstToPin::redo()
{
    if (m_is_error)
    {
        return;
    }
    /// get current connection
    if (m_pin_in->opposite())
    {
        m_opposite = m_pin_in->opposite();
    }
    if (m_pin_in->iface_variable())
    {
        m_iface_var = m_pin_in->iface_variable();
    }
    if (!m_pin_in->constant().isEmpty())
    {
        m_constant = m_pin_in->constant();
    }

    if (m_pin_in->is_connected())
    {
        m_pin_in->disconnect();
    }

    auto type = CFilter::get_type_from_const(m_var_name.toStdString());
    m_pin_in->set_constant(type, m_var_name.toStdString());

    m_pin_in->parent()->parent()->resort();
    m_world->update_hatch();
}

void CConstToPin::undo()
{
    if (m_is_error)
    {
        return;
    }
    m_pin_in->disconnect();

    if (m_iface_var)
    {
        m_pin_in->connect_iface_variable(m_iface_var);
    }
    if (m_opposite)
    {
        m_pin_in->connect_pin(m_opposite);
    }
    if (!m_constant.isEmpty())
    {
        auto type = CFilter::get_type_from_const(m_constant.toStdString());
        m_pin_in->set_constant(type, m_constant.toStdString());
    }
}

bool CConstToPin::is_error() const
{
    return m_is_error;
}
