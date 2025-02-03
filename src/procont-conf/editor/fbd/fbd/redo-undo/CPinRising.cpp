//
// Created by artem on 12/20/24.
//

#include "CPinRising.h"

CPinRising::CPinRising(CPinIn *pin_in, const bool &is_rising)
{
    QString text = is_rising ?  "Установить восходящий фронт на пин " + pin_in->name_full() :
                                "Сбросить восходящий фронт на пине " + pin_in->name_full();
    setText(text);

    m_pin = pin_in;
    m_is_rising = is_rising;
    m_world = m_pin->parent()->parent()->parent();
}

CPinRising::~CPinRising()
= default;

void CPinRising::redo()
{
    m_pin->set_rising_edge(m_is_rising);
    m_world->update_visible_ladders();
}

void CPinRising::undo()
{
    m_pin->set_rising_edge(!m_is_rising);
    m_world->update_visible_ladders();
}
