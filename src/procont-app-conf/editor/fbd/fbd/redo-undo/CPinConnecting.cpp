//
// Created by artem on 12/13/24.
//

#include "CPinConnecting.h"
#include "../graphics/CGrapchicsLogic.h"

CPinConnecting::CPinConnecting(COglWorld *world, CPin *editing_pin, CPin *opposite_pin)
: m_world(world), m_pin_edited(editing_pin), m_pin_opposite(opposite_pin)
{
    if (!m_pin_edited || !m_pin_opposite)
    {
        m_is_error = true;
        setText("Невозможно соединить пин c nullptr");
        return;
    }

    if (m_pin_edited->direction() == m_pin_opposite->direction())
    {
        m_is_error = true;
        setText("Невозможно соединить два входа или выхода");
        return;
    }

    QString pin_edit_name = m_pin_edited->parent()->instance_name().isEmpty() ?
                            m_pin_edited->type_name() :
                            m_pin_edited->parent()->instance_name();
    pin_edit_name += "." + m_pin_edited->name();

    QString pin_opp_name =  m_pin_opposite->parent()->instance_name().isEmpty() ?
                            m_pin_opposite->parent()->type_name() :
                            m_pin_opposite->parent()->instance_name();
    pin_opp_name += "." + m_pin_opposite->name();

    QString text = "Соединение " + pin_edit_name + " c " + pin_opp_name;

    setText(text);
}

CPinConnecting::~CPinConnecting()
= default;

void CPinConnecting::redo()
{
    if (m_is_error)
    {
        return;
    }

    CPinIn *in  = m_pin_edited->direction() == PD_INPUT  ? m_pin_edited->input()  : m_pin_opposite->input();
    CPinOut*out = m_pin_edited->direction() == PD_OUTPUT ? m_pin_edited->output() : m_pin_opposite->output();

    CGraphicsLogic logic;
    auto line = logic.add_new_line(m_pin_edited, m_pin_opposite);

    if (line)
    {
        CFbdLadder * ladder = m_pin_edited->parent()->parent();
        ladder->add_line(line);

    }
    else
    {
        in->update_graphic_text();
        out->refresh_connections();
    }

    in->connect_pin(out);
    out->connect(in);

    if (in->parent()->parent() == out->parent()->parent())
    {
        auto ladder = in->parent()->parent();
        ladder->resort();
        ladder->refresh_graphic_connections();
        m_world->update_hatch();
    }
    else
    {
        in->parent()->parent()->resort();
        out->parent()->parent()->resort();
    }
    m_world->update_hatch();

}

void CPinConnecting::undo()
{
    CPinIn *in = m_pin_edited->direction() == PD_INPUT ? m_pin_edited->input() : m_pin_opposite->input();
    CPinOut*out= m_pin_edited->direction() == PD_OUTPUT ? m_pin_edited->output() : m_pin_opposite->output();

    /// removing line
    if (m_pin_edited->direction() == m_pin_opposite->direction())
    {
        auto ladder = m_pin_edited->parent()->parent();

        auto line = ladder->remove_line(in);
        delete line;
    }

    in->disconnect();
    out->disconnect(in);
    m_world->update_visible_ladders();
}

bool CPinConnecting::is_error() const
{
    return m_is_error;
}
