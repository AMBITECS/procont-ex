//
// Created by artem on 12/20/24.
//

#include "CResetConnections.h"
#include "editor/fbd/fbd/graphics/CGrapchicsLogic.h"

CResetConnections::CResetConnections(CPin *pin)
{
    m_pin = pin;
    m_world = pin->parent()->parent()->parent();
    QString text = m_pin->direction() == PD_INPUT ? "Разъединить пин " + pin->name_full() :
                                                    "Сбросить все соединения " + pin->name_full();
    setText(text);

    m_opposites = new std::vector<CPinIn*>();
    m_iface_vars = new std::vector<CVariable*>();
}

CResetConnections::~CResetConnections()
{
    delete m_opposites;
    delete m_iface_vars;
}

void CResetConnections::redo()
{
    if (m_pin->direction() == PD_INPUT)
    {
        auto in = m_pin->input();

        m_iface_var = in->iface_variable();
        m_opposite = in->opposite();
        m_constant = in->constant();

        in->disconnect();
    }
    else
    {
        auto out = m_pin->output();
        auto ladder = out->parent()->parent();

        for (auto &pin : *out->graphic_connections())
        {

            m_opposites->push_back(pin);
        }

        for (auto &var : *out->iface_variables())
        {
            m_iface_vars->push_back(var);
        }

        out->reset_connections();
    }

    m_pin->parent()->update_bound_rect();
    m_pin->parent()->parent()->resort();
    m_world->update_visible_ladders();
}

void CResetConnections::undo()
{
    auto logic = new CGraphicsLogic();
    auto ladder = m_pin->parent()->parent();

    if (m_pin->direction() == PD_INPUT)
    {
        auto in = m_pin->input();

        if (m_iface_var)
        {
            in->connect_iface_variable(m_iface_var);
        }

        if (m_opposite)
        {
            in->connect_pin(m_opposite);
            m_opposite->connect(in);
            auto line = logic->add_new_line(in, m_opposite);
            if (line)
            {
                ladder->add_line(line);
            }
        }

        if (!m_constant.isEmpty())
        {
            EDefinedDataTypes type = CFilter::get_type_from_const(m_constant.toStdString());
            in->set_constant(type, m_constant.toStdString());
        }
    }
    else
    {
        auto out = m_pin->output();


        for (auto pin : *m_opposites)
        {
            out->connect(pin);
            pin->connect_pin(out);

            auto line = logic->add_new_line(out, pin);
            if (line)
            {
                ladder->add_line(line);
            }
        }

        for (auto &var : *m_iface_vars)
        {
            out->connect(var);
        }
    }

    delete logic;

    m_pin->parent()->update_bound_rect();
    m_pin->parent()->parent()->resort();
    m_pin->parent()->parent()->refresh_graphic_connections();
    //m_pin->parent()->parent()->update_real_position();
    m_world->update_visible_ladders();
}
