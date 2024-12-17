//
// Created by nechi on 12.11.2024.
//

#include "CInsertNewObject.h"
#include "../../plc-xml/common/CVariablesAnalytics.h"

CInsertNewObject::CInsertNewObject(COglWorld * world, CFbdContent * fbd, CLadder *p_ladder,
                                   const EPaletteElements &element, const QPoint &pos)
    : QUndoCommand()
    , m_world(world)
    , m_fbd(fbd)
    , m_ladder(p_ladder)
    , m_element(element)
    , m_pos(pos)
{
    setText("Вставка нового объекта из палитры");
}

CInsertNewObject::~CInsertNewObject()
{
    if (m_to_delete)
        delete m_to_delete->block();
    delete m_to_delete;
}

void CInsertNewObject::undo()
{
    m_to_delete = remove();

    m_ladder->resort();
    m_ladder->highlights_off();
    m_ladder->refresh_graphic_connections();
    m_ladder->update_real_position();
    m_world->view_hatch_moved({});
}

void CInsertNewObject::redo()
{
    m_to_delete = nullptr;
    insert();

    m_ladder->resort();
    m_ladder->highlights_off();
    m_ladder->refresh_graphic_connections();
    m_ladder->update_real_position();
    m_world->view_hatch_moved({});
}

CDiagramObject *CInsertNewObject::inserted_object()
{
    return m_new_obj;
}

void CInsertNewObject::insert()
{
    CVariablesAnalytics analytics(m_world, m_world->m_pou->name());
    if (!m_new_obj)
    {
        auto lib_elem_name = pou_item_names.find(m_element).value();
        CBlock item = analytics.get_block_from_library(lib_elem_name);
        analytics.setup_block(&item);
        auto *block = new CBlock(item);

        m_new_obj = new CDiagramObject(m_ladder, block);
    }

    /// add to the deep state
    m_fbd->blocks()->push_back(m_new_obj->block());

    QVector<CDiagramObject*> * obj_array = m_ladder->draw_components();

    /// add to the ladder
    if (obj_array->empty())
    {
        obj_array->push_back(m_new_obj);
    }
    else
    {
        int  index = 0;

        for (auto &obj: *obj_array)
        {
            if (obj->bound_text_rect().contains(m_pos))
            {
                obj_array->insert(obj_array->cbegin() + index, m_new_obj);
                break;
            }
            index++;
        }

        if (index == obj_array->count())
        {
            obj_array->push_back(m_new_obj);
        }

    }
}

CDiagramObject *CInsertNewObject::remove()
{
    /// remove from deep state
    int index = 0;
    auto arr = m_fbd->blocks();

    // theoretically we can't to not find
    for (auto &item : *arr)
    {
        if (item == m_new_obj->block())
        {
            arr->erase(arr->cbegin() + index);
        }
        index++;
    }

    /// remove from target ladder
    QVector<CDiagramObject*> * obj_array = m_ladder->draw_components();
    index = 0;

    for (auto &item : *obj_array)
    {
        if (item == m_new_obj)
        {
            obj_array->erase(obj_array->cbegin() + index);
            break;
        }
        index++;
    }

    return m_new_obj;
}
