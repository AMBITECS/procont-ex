//
// Created by nechi on 12.11.2024.
//

#include "CInsertNewLadder.h"

CInsertNewLadder::CInsertNewLadder(COglWorld *ogl_world, CLadder *next)
    : QUndoCommand(), m_ogl_world(ogl_world), m_next(next)
{
    setText("Вставить новую ступень");
}

CInsertNewLadder::~CInsertNewLadder()
{
    delete m_to_delete;
}

void CInsertNewLadder::undo()
{
    m_to_delete = remove();

    /// update
    CLadder *start = m_new_ladder->previous_ladder() ?
                     m_new_ladder->previous_ladder() :
                     m_new_ladder->next_ladder();

    start->update_real_position();
    m_ogl_world->view_hatch_moved({});
    m_ogl_world->check_diagram_size();

}

void CInsertNewLadder::redo()
{
    m_to_delete = nullptr;
    insert();

    CLadder * start =  m_new_ladder->previous_ladder() ?
                       m_new_ladder->previous_ladder() :
                       m_new_ladder;

    start->update_real_position();
    m_ogl_world->view_hatch_moved({});
    m_ogl_world->check_diagram_size();
}

CLadder *CInsertNewLadder::new_ladder()
{
    return m_new_ladder;
}

void CInsertNewLadder::insert()
{
    if (m_index < 0)
    {
        m_index = m_next ? m_next->number() - 1 : m_ogl_world->m_ladders->size();
    }

    CLadder *prev = m_index - 1 < 0 ? nullptr : m_ogl_world->m_ladders->at(m_index-1);

    if (!m_new_ladder)
    {
        m_new_ladder = new CLadder(m_ogl_world, m_ogl_world->m_hatch_topLeft,
                                   &m_ogl_world->m_hatch_size,
                                   prev,
                                   m_next);
    }

    CLadder *prev_l = m_new_ladder->previous_ladder();
    CLadder *next_l = m_next;

    /// for walk on chine
    m_new_ladder->set_previous(prev_l);

    /// делаем разрез и вшиваем себя
    if (prev_l)
        prev_l->set_next(m_new_ladder);
    if (next_l)
        next_l->set_previous(m_new_ladder);


    if (m_index < m_ogl_world->m_ladders->size())
        m_ogl_world->m_ladders->insert(m_ogl_world->m_ladders->begin() + (m_index), m_new_ladder);
    else
        m_ogl_world->m_ladders->push_back(m_new_ladder);
}

CLadder* CInsertNewLadder::remove()
{
    /// склеить разрыв
    if (m_new_ladder->previous_ladder())
        m_new_ladder->previous_ladder()->set_next(m_new_ladder->next_ladder());
    if (m_new_ladder->next_ladder())
        m_new_ladder->next_ladder()->set_previous(m_new_ladder->previous_ladder());

    /// remove
    m_ogl_world->m_ladders->erase(m_ogl_world->m_ladders->begin() + m_index);

    return m_new_ladder;
}
