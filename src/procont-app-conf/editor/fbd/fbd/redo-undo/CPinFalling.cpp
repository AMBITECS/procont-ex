//
// Created by artem on 12/20/24.
//

#include "CPinFalling.h"

CPinFalling::CPinFalling(CPinIn *pin_in, const bool &is_fall)
{
    QString text = is_fall ? "Установить ниспадающий фронт на пин " + pin_in->name_full() :
                             "Сбросить ниспадающий фронт на пине " + pin_in->name_full();
    setText(text);

    m_pin = pin_in;
    m_edge = is_fall;
    m_world = m_pin->parent()->parent()->parent();
}

CPinFalling::~CPinFalling()
= default;

void CPinFalling::redo()
{
    m_pin->set_falling_edge(m_edge);
    m_world->update_visible_ladders();
}

void CPinFalling::undo()
{
    m_pin->set_falling_edge(!m_edge);
    m_world->update_visible_ladders();
}
