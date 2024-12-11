//
// Created by nechi on 13.11.2024.
//

#include "CInsertLadder.h"

CInsertLadder::CInsertLadder(COglWorld *world, CLadder *dragged_ladder, CLadder *before)
    : QUndoCommand()
    , m_world(world)
    , m_walking_ladder(dragged_ladder)
    , m_init_dest(before)
{
    setText("Перенос ступени");
}

CInsertLadder::~CInsertLadder()
= default;

void CInsertLadder::redo()
{
    /// define source

    remove_from_position(m_source_index);

    CLadder * start_refresh = m_walking_ladder->previous_ladder() ?
                              m_walking_ladder->previous_ladder() :
                              m_walking_ladder->next_ladder();

    start_refresh->update_real_position();
    m_world->view_hatch_moved({});

    insert_to_position(m_dest_index);

    /// update view
    start_refresh =   m_walking_ladder->previous_ladder() ?
                      m_walking_ladder->previous_ladder() :
                      m_walking_ladder;

    start_refresh->update_real_position();
    m_world->view_hatch_moved({});
}

void CInsertLadder::undo()
{
    remove_from_position(m_dest_index);
    insert_to_position(m_source_index);

    /// update view
    CLadder * start_refresh = ! m_walking_ladder->previous_ladder() ?
                                m_walking_ladder :
                                m_walking_ladder->previous_ladder();

    start_refresh->update_real_position();
    m_world->view_hatch_moved({});
    m_world->check_diagram_size();
}

void CInsertLadder::remove_from_position(int &position)
{
    if (position < 0)
    {
        position = m_walking_ladder->number() - 1;
    }

    m_world->m_ladders->erase(m_world->m_ladders->begin() + position);

    stitch();
}

void CInsertLadder::insert_to_position(int &position)
{
    if (position < 0)
    {
        position = m_init_dest ? m_init_dest->number() - 1 : m_world->m_ladders->size();
    }

    incision(position);
}

void CInsertLadder::stitch()
{
    /// откуда (начало/конец/середина) взяли, там надо "сшить"<BR>
    /// from the begin
    if (!m_walking_ladder->previous_ladder())
    {
        m_walking_ladder->next_ladder()->set_previous(nullptr);
    }
    /// from the end
    if (!m_walking_ladder->next_ladder())
    {
        m_walking_ladder->previous_ladder()->set_next(nullptr);
    }
    /// from the middle
    if (m_walking_ladder->previous_ladder() && m_walking_ladder->next_ladder())
    {
        m_walking_ladder->next_ladder()->set_previous(m_walking_ladder->previous_ladder());
        m_walking_ladder->previous_ladder()->set_next(m_walking_ladder->next_ladder());
    }
}

void CInsertLadder::incision(int &position)
{
    /// куда (начало конец середина) вставка - там "разрезаем"<BR>
    CLadder *before = position >= m_world->m_ladders->size() ? nullptr : m_world->m_ladders->at(position);

    /// to the end
    if (!before)
    {
        m_walking_ladder->set_previous(m_world->m_ladders->back());
        m_walking_ladder->set_next(nullptr);
        m_world->m_ladders->back()->set_next(m_walking_ladder);
        m_world->m_ladders->push_back(m_walking_ladder);
    }

    /// to the middle
    if (before && before->next_ladder() && before->previous_ladder())
    {
        /// setup inserting ladder new prev and next
        m_walking_ladder->set_previous(before->previous_ladder());
        m_walking_ladder->set_next(before);

        /// setup old visible_ladders new prev and next
        before->previous_ladder()->set_next(m_walking_ladder);
        before->set_previous(m_walking_ladder);


        m_world->m_ladders->insert(m_world->m_ladders->begin() + position, m_walking_ladder);
    }

    /// to the begin
    if (before && !before->previous_ladder())
    {
        m_walking_ladder->set_previous(nullptr);
        m_walking_ladder->set_next(m_world->m_ladders->front());
        m_world->m_ladders->front()->set_previous(m_walking_ladder);
        m_world->m_ladders->insert(m_world->m_ladders->begin(), m_walking_ladder);
    }

    /// just to walk on chine
    m_walking_ladder->set_previous(m_walking_ladder->previous_ladder());
}
