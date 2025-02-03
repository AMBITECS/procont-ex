//
// Created by artem on 12/20/24.
//

#include "CPinInvers.h"

CPinInverse::CPinInverse(CPinIn *pin_in, const bool &to_inverse)
{
    QString text = !to_inverse ? "Сбросить инверсию входа" : "Установить инверсию входа";
    setText(text);

    m_pin = pin_in;
    m_inverse = to_inverse;
    m_world = m_pin->parent()->parent()->parent();
}

CPinInverse::~CPinInverse()
= default;

void CPinInverse::redo()
{
    m_pin->set_negated(m_inverse);
    m_world->update_visible_ladders();
}

void CPinInverse::undo()
{
    m_pin->set_negated(!m_inverse);
    m_world->update_visible_ladders();
}
