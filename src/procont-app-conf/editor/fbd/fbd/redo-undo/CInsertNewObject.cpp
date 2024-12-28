//
// Created by nechi on 12.11.2024.
//

#include "CInsertNewObject.h"
#include "../../plc-xml/common/CVariablesAnalytics.h"
#include "../../plc-xml/common/CProject.h"

extern CProject *project;

CInsertNewObject::CInsertNewObject(COglWorld * world, CFbdContent * fbd, CFbdLadder *p_ladder,
                                   const EPaletteElements &element, const QString &pou_name, const QPoint &pos)
    : QUndoCommand()
    , m_world(world)
    , m_fbd(fbd)
    , m_ladder(p_ladder)
    , m_element(element)
    , m_pos(pos)
    , m_pou_name(pou_name)
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

    m_ladder->refresh_graphic_connections();
    m_ladder->resort();
    m_ladder->highlights_off();
    m_ladder->update_real_position();
    m_world->view_hatch_moved({});
}

void CInsertNewObject::redo()
{
    m_to_delete = nullptr;
    insert();

    m_ladder->refresh_graphic_connections();
    m_ladder->resort();
    m_ladder->highlights_off();
    m_ladder->update_real_position();
    m_world->view_hatch_moved({});
}

CFbdObject *CInsertNewObject::inserted_object()
{
    return m_new_obj;
}

void CInsertNewObject::insert()
{
    CVariablesAnalytics analytics(m_world, m_world->m_pou->name());
    CBlock item(m_world->m_pou->bodies()->front());

    if (!m_new_obj)
    {
        CBlock *block;

        if (m_element >= EP_FBD)
        {
            CPou *pou = project->types()->find_pou_by_name(m_pou_name);
            item = pou->get_block();            
        }
        else
        {
            auto lib_elem_name = pou_item_names.find(m_element).value();
            item = analytics.get_block_from_library(lib_elem_name);            
        }

        item.set_parent(m_world->m_pou->bodies()->front());
        analytics.setup_block(&item);
        block = new CBlock(item);
        m_new_obj = new CFbdObject(m_ladder, block);
    }

    /// add to the deep state
    m_fbd->blocks()->push_back(m_new_obj->block());

    QVector<CFbdObject*> * obj_array = m_ladder->draw_components();

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

CFbdObject *CInsertNewObject::remove()
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
    QVector<CFbdObject*> * obj_array = m_ladder->draw_components();
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
