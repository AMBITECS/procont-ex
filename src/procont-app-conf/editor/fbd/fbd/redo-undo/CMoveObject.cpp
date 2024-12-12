//
// Created by nechi on 12.11.2024.
//

#include "CMoveObject.h"

CMoveObject::CMoveObject(COglWorld * ogl_world, CLadder *source, CLadder *destination,
                         CDiagramObject *object, const QPoint &pos)
        : QUndoCommand()
        , m_ogl_world(ogl_world)
        , m_source(source)
        , m_destination(destination)
        , m_ins_pos(pos)
        , m_object(object)
{
    setText("Передвижение компонента");
}

CMoveObject::~CMoveObject()
= default;

void CMoveObject::undo()
{
    back();

    CLadder *start = m_source->number() < m_destination->number() ? m_source : m_destination;

    if (m_source == m_destination)
    {
        m_source->refresh_graphic_connections();
    }
    else
    {
        m_source->refresh_graphic_connections();
        m_destination->refresh_graphic_connections();
    }

    start->update_real_position();
    m_source->highlights_off();

    m_ogl_world->update_visible_ladders();
}

void CMoveObject::redo()
{
    move();

    if (m_source == m_destination)
    {
        m_source->refresh_graphic_connections();
    }
    else
    {
        m_source->refresh_graphic_connections();
        m_destination->refresh_graphic_connections();
    }

    CLadder *start = m_source->number() < m_destination->number() ? m_source : m_destination;
    start->update_real_position();
    m_source->highlights_off();

    m_ogl_world->update_visible_ladders();
}

void CMoveObject::move()
{
    auto obj = remove_from_ladder(m_source, m_object, m_src_index);

    if (!obj)
    {
        m_error = true;
        return;
    }

    insert_object(m_destination, obj, m_dst_index);
}

void CMoveObject::back()
{
    auto obj = remove_from_ladder(m_destination, m_object, m_dst_index);

    if (!obj)
    {
        m_error = true;
        return;
    }

    insert_object(m_source, obj, m_src_index);
}

CDiagramObject *CMoveObject::remove_from_ladder(CLadder *source, CDiagramObject *object, int &from_index)
{
    QVector<CDiagramObject*> * obj_array = source->draw_components();
    int index = 0;

    if (from_index < 0)
    {
        for (auto &item: *obj_array)
        {
            if (item == object)
            {
                obj_array->erase(obj_array->cbegin() + index);
                from_index = index;
                break;
            }
            index++;
        }
    }
    else
    {
        obj_array->erase(obj_array->cbegin() + from_index);
    }

    /// update content, turn off the light and leave
    source->resort();
    source->highlights_off();

    return object;
}

void CMoveObject::insert_object(CLadder *dest, CDiagramObject *object, int &to_index)
{
    auto obj_array = dest->draw_components();

    if (obj_array->empty())
    {
        obj_array->push_back(object);
        to_index = 0;
    }
    else
    {
        int  index = 0;

        if (to_index < 0)
        {
            for (auto &obj: *obj_array)
            {
                if (obj->bound_text_rect().contains(m_ins_pos))
                {
                    to_index = index;
                    obj_array->insert(obj_array->cbegin() + to_index, object);
                    break;
                }
                index++;
            }

            if (index >= obj_array->count())
            {
                obj_array->push_back(object);
            }
        }
        else
        {
            obj_array->insert(obj_array->cbegin() + to_index, object);
        }
    }

    dest->resort();
    dest->highlights_off();
}

bool CMoveObject::is_error() const
{
    return m_error;
}
