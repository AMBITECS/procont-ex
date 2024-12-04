//
// Created by nechi on 12.11.2024.
//

#include "CAddNewLadder.h"

CAddNewLadder::CAddNewLadder(COglWorld *oglWorld, QUndoCommand *parent)
    : QUndoCommand(parent), m_ogl_world(oglWorld)
{
    setText("Добавить ступень в конец.");
}

CAddNewLadder::~CAddNewLadder()
{
    delete m_to_delete;
}

void CAddNewLadder::redo()
{
    m_to_delete = nullptr;
    add();
}

void CAddNewLadder::undo()
{
    m_to_delete = remove();
}

CLadder *CAddNewLadder::new_ladder()
{
    return m_new_ladder;
}

void CAddNewLadder::add()
{
    CLadder *prev = m_ogl_world->m_ladders->empty() ? nullptr : m_ogl_world->m_ladders->back();

    if (!m_new_ladder)
    {
        m_new_ladder = new CLadder(m_ogl_world->m_hatch_topLeft,
                                   &m_ogl_world->m_hatch_size,
                                   prev);
    }

    if (prev)
    {
        prev->set_next(m_new_ladder);
    }

    m_ogl_world->m_ladders->push_back(m_new_ladder);

    CLadder *start = prev == nullptr ? m_new_ladder : prev;
    start->update_real_position();

    m_ogl_world->check_diagram_size();
    m_ogl_world->update_visible_ladders();

}

CLadder *CAddNewLadder::remove()
{
    if (!m_new_ladder)
        return nullptr;

    m_index = m_new_ladder->number() - 1;
    CLadder *found = nullptr;

    int index = 0;
    for (CLadder *&item : *m_ogl_world->m_ladders)
    {
        if (item == m_new_ladder)
        {
            found = item;
            m_ogl_world->m_ladders->erase(m_ogl_world->m_ladders->begin() + index);
            break;
        }
        index++;
    }

    if (found)
    {
        CLadder *prev = m_new_ladder->previous_ladder();
        CLadder *next = m_new_ladder->next_ladder();
        CLadder *start = prev ? prev : next;

        /// from begin
        if (!prev && next)
        {
            next->set_previous(nullptr);
        }

        /// from the middle
        if (prev && next)
        {
            prev->set_next(next);
            next->set_previous(prev);
        }

        /// from the end
        if (prev && !next)
        {
            prev->set_next(nullptr);
        }

        start->update_real_position();
        m_ogl_world->update_visible_ladders();
    }

    return m_new_ladder;
}
