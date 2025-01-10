//
// Created by artem on 11/23/24.
//

#include "CPinRename.h"
#include "editor/fbd/fbd/graphics/CGrapchicsLogic.h"

#include <utility>

CPinRename::CPinRename(COglWorld *ogl_world, CPin *pin, QString  pin_var,
                       CPin *opposite_pin, QString opposite_var, CVariable *iface_var)
    : QUndoCommand()
    , m_world(ogl_world)
    , m_pin(pin)
    , m_pin_var(std::move(pin_var))
    , m_opposite_pin(opposite_pin)
    , m_opposite_var(std::move(opposite_var))
    , m_iface_var(iface_var)
{
    m_pin_old_var = m_pin->name();

    QString txt = "Присвоить пину " + pin->name_full() + " переменную";
    setText(txt);


    if (m_opposite_pin)
    {
        m_opposite_old_var = m_opposite_pin->name();
    }
}

CPinRename::~CPinRename()
{
    delete m_line_to_del;
}

void CPinRename::redo()
{
    if ( (m_opposite_pin && (m_opposite_pin->parent()->parent() == m_pin->parent()->parent())) || m_line )
    {
        delete m_line;

        CGraphicsLogic logic;

        m_line = logic.add_new_line(m_pin, m_opposite_pin);
        m_pin->parent()->parent()->add_line(m_line);
        m_pin->parent()->parent()->refresh_graphic_connections();

        auto input = m_pin->direction() == PD_INPUT ? m_pin->input() : m_opposite_pin->input();
        auto output = m_pin->direction() == PD_OUTPUT ? m_pin->output() : m_opposite_pin->output();

        output->disconnect(input);
        input->disconnect();

        m_line_to_del = nullptr;
    }

    else
    {
        if (m_iface_var)
        {
            if (m_pin->direction() == PD_INPUT)
            {
                m_pin->input()->connect_iface_variable(m_iface_var);
            }
            else
            {
                m_pin->output()->connect(m_iface_var);
            }
        }

        else
        {
            throw std::runtime_error("Strange conditions in 'CPinRename::redo()'");
//            m_pin->set_pin_name(m_pin_var);
//            m_opposite_pin->set_pin_name(m_opposite_var);
//            m_opposite_pin->parent()->update_bound_rect();
        }
    }

    refresh_view();
}

void CPinRename::undo()
{
    if (m_line)
    {
        m_line_to_del = m_line;
        m_pin->parent()->parent()->remove_line(m_line);

        if (m_pin->direction() == PD_OUTPUT)
        {
            m_pin->output()->disconnect(m_opposite_pin->input());
            m_opposite_pin->input()->disconnect();
        }
        else
        {
            m_opposite_pin->output()->disconnect(m_pin->input());
            m_pin->input()->disconnect();
        }
    }
    else
    {
        if (m_iface_var)
        {
            //m_pin->block_variable()->set_iface_variable(m_old_iface_var);
            if (m_pin->direction() == PD_INPUT)
            {
                m_pin->input()->disconnect();
            }
            else
            {
                m_pin->output()->disconnect(m_iface_var);
            }
        }

        else
        {
            throw std::runtime_error("Strange conditions in 'CPinRename::undo()'");
//            m_pin->set_pin_name(m_pin_old_var);
//            m_opposite_pin->set_pin_name(m_opposite_old_var);
//            m_opposite_pin->parent()->update_bound_rect();

        }
    }

    m_pin->parent()->update_bound_rect();

    refresh_view();
}

void CPinRename::refresh_view()
{
    CFbdLadder *base_ladder = m_pin->parent()->parent();
    CFbdLadder *opposite_ladder = m_opposite_pin ? m_opposite_pin->parent()->parent() : nullptr;

    if (base_ladder == opposite_ladder)
    {
        m_pin->parent()->parent()->resort();
    }
    else
    {
        base_ladder->resort();

        if (opposite_ladder)
        {
            opposite_ladder->resort();
        }
    }

    if (m_line)
    {
        m_pin->parent()->parent()->refresh_graphic_connections();
    }

    m_world->update_hatch();
}
