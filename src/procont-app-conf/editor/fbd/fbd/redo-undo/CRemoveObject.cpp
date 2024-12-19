//
// Created by artem on 19.12.24.
//

#include "CRemoveObject.h"
#include "../graphics/CGrapchicsLogic.h"

CRemoveObject::CRemoveObject( CDiagramObject *object )
{
    m_world = object->parent()->parent();
    m_object = object;
    QString obj_name = object->instance_name().isEmpty() ? object->type_name() : object->instance_name();
    setText("Удаление " + obj_name);
}

CRemoveObject::~CRemoveObject()
{
    delete m_obj_to_delete;
}

void CRemoveObject::redo()
{
    m_obj_to_delete = m_object;

    /// disconnecting
    for (auto &out : *m_object->outputs())
    {
        s_output_connection conn;
        conn.pin = out;

        for (auto &p_in : *out->graphic_connections())
        {
            conn.opposites.push_back(p_in);
        }

        for (auto &var : *out->iface_variables())
        {
            conn.variables.push_back(var);
        }

        m_output_connections.push_back(conn);
        out->reset_connections(); //TODO: check it
    }

    CVariable *if_variable;
    CPinOut   * opposite;
    QString     constant;

    for (auto &in : *m_object->inputs())
    {
        s_input_connection conn;
        conn.pin = in;

        if_variable = in->iface_variable();
        opposite = in->opposite();
        constant = in->constant();

        if (opposite)
        {
            conn.opposite = in->opposite();
        }

        if (if_variable)
        {
            conn.variable = in->iface_variable();
        }

        if (!constant.isEmpty())
        {
            conn.constant = constant;
        }

        in->disconnect();

        m_input_connections.push_back(conn);
    }


    m_object_index = remove_object(m_object);

    m_object->parent()->resort();
    m_object->parent()->refresh_graphic_connections();
    m_object->parent()->update_real_position();
    m_object->parent()->parent()->update_visible_ladders();
}

void CRemoveObject::undo()
{
    m_obj_to_delete = nullptr;
    CGraphicsLogic logic;
    int counter = 0;

    insert_object(m_object, m_object_index);
    m_object->parent()->resort();

    /// connecting again
    for (auto &in : *m_object->inputs())
    {
        auto conn = m_input_connections.at(counter);

        if (!conn.constant.isEmpty())
        {
            auto type = CFilter::get_type_from_const(conn.constant.toStdString());
            in->set_constant(type, conn.constant.toStdString());
        }

        if (conn.variable)
        {
            in->connect_iface_variable(conn.variable);
        }

        if (conn.opposite)
        {
            in->connect_pin(conn.opposite);
            auto line = logic.add_new_line(in, conn.opposite);
            if (line)
            {
                m_object->parent()->add_line(line);
            }
            conn.opposite->connect(in);
        }

        counter++;
    }

    counter = 0;
    for (auto &out : *m_object->outputs())
    {
        auto conn = m_output_connections.at(counter);

        if (!conn.variables.empty())
        {
            for (auto &var : conn.variables)
            {
                out->connect(var);
            }
        }

        if (!conn.opposites.empty())
        {
            for (auto &pin : conn.opposites)
            {
                auto line = logic.add_new_line(pin, out);
                if (line)
                {
                    m_object->parent()->add_line(line);
                }
                pin->connect_pin(out);
                out->connect(pin);
            }
        }

        counter++;
    }

    m_object->parent()->resort();
    m_object->parent()->refresh_graphic_connections();
    m_object->parent()->update_real_position();
    m_object->parent()->parent()->update_visible_ladders();
}

int CRemoveObject::remove_object(CDiagramObject *object)
{
    CLadder * ladder = m_object->parent();
    QVector<CDiagramObject*> *arr = ladder->draw_components();
    int counter = 0;

    for (auto &obj : *arr)
    {
        if (obj == object)
        {
            arr->erase(arr->cbegin() + counter);
            return counter;
        }
        counter++;
    }
    return -1;
}

void CRemoveObject::insert_object(CDiagramObject *object, const int &index)
{
    CLadder * ladder = m_object->parent();
    QVector<CDiagramObject*> *arr = ladder->draw_components();

    if (index >= arr->size())
    {
        arr->push_back(object);
        return;
    }

    arr->insert(arr->cbegin() + index, object);
}

