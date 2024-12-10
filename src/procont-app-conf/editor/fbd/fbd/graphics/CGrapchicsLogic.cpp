//
// Created by nechi on 29.11.2024.
//

#include "CGrapchicsLogic.h"
#include "CPinIn.h"
#include "CPinOut.h"

CGraphicsLogic::CGraphicsLogic()
= default;

CGraphicsLogic::~CGraphicsLogic()
= default;

CConnectLine *CGraphicsLogic::add_new_line(CPin *dragged_pin, CPin *target_pin)
{
    if (dragged_pin->parent()->parent() != target_pin->parent()->parent())
    {
        return nullptr;
    }

    m_ladder = dragged_pin->parent()->parent();
    m_dragged_pin = dragged_pin;
    m_target_pin = target_pin;

    auto conn_line = new CConnectLine(m_ladder->real_top_left());

    bool near = are_objects_near();

    /// it could be near but not face to ass
    if (near)
    {
        CDiagramObject* drag_obj = m_dragged_pin->parent();
        CDiagramObject* target_obj = m_target_pin->parent();
        auto left_ob = drag_obj->rect()->left() < target_obj->rect()->left() ? drag_obj : target_obj;
        auto right_ob = drag_obj->rect()->left() > target_obj->rect()->left() ? drag_obj : target_obj;

        if (left_ob == drag_obj && m_dragged_pin->direction() == PD_INPUT ||
            right_ob == drag_obj && m_dragged_pin->direction() == PD_OUTPUT )
        {
            near = false;
        }
    }

    /// если компоненты не рядом
    if (!near)
    {
        QLine drag_line = first_line(m_dragged_pin, m_target_pin);
        QLine target_line = first_line(m_target_pin, m_dragged_pin);

        QLine down_drag_line = down_line(drag_line.p2());
        QLine down_target_line = down_line(target_line.p2());

        m_ladder->bottom_line_count_increase();

        QLine last = QLine(down_drag_line.p2(), down_target_line.p2());

        conn_line->add_line(drag_line);
        conn_line->add_line(target_line);
        conn_line->add_line(down_drag_line);
        conn_line->add_line(down_target_line);
        conn_line->add_line(last);
    }

    /// рядом - линия без опуска вниз
    else
    {
        direct_connection(conn_line);
    }

    /// для быстрого пересоединения дадим пинам инфу о пинах на том конце
    auto input = m_dragged_pin->direction() == PD_INPUT ? m_dragged_pin->input() : m_target_pin->input();
    auto output = m_dragged_pin->direction() == PD_OUTPUT ? m_dragged_pin->output() : m_target_pin->output();

    output->connect(input);
    input->connect_pin(output);

    m_ladder->update_real_position();

    return conn_line;
}

QLine  CGraphicsLogic::first_line(CPin *pin, CPin *opp)
{
    /// define index of the pin on the left (input) or right (output) sid of the object
    int index = 0;
    int dist_from_bound; //!< дистанция от bound_text_rect компонента
    int dist_to_bound;    //!< дистанция от пина до bound_text_rect компонента
    auto direction = pin->direction();

    std::vector<CPin*> *pins = direction == PD_INPUT ?
                               reinterpret_cast<std::vector<CPin *> *>(pin->parent()->inputs()) :
                               reinterpret_cast<std::vector<CPin *> *>(pin->parent()->outputs());

    for (auto &item : *pins)
    {
        if (item->direction() == PD_INPUT)
        {
            index += item->is_connected() ? 1 : 0;
        }
        else
        {
            auto out = item->output();
            index += item->is_connected() ? index_of(out->graphic_connections(), opp) : 0;
        }

        if (item == pin)
        {
            break;
        }
    }

    dist_from_bound = index * def_lines_diff + def_bound_dist;

    auto bound_rect = pin->parent()->bound_text_rect();

    dist_to_bound = direction == PD_INPUT ? pin->rect()->left() - bound_rect.left() :
                                            bound_rect.right() - pin->rect()->right();

    QPoint p1;
    p1.setX(direction == PD_INPUT ? pin->rect()->left() : pin->rect()->right());
    p1.setY(pin->rect()->top() + pin->rect()->width() / 2);

    QPoint p2;
    p2.setY(p1.y());
    p2.setX(direction == PD_INPUT ? p1.x() - (dist_to_bound + dist_from_bound) :
                                          p1.x() + (dist_to_bound + dist_from_bound));

    return {p1, p2};
}

QLine CGraphicsLogic::down_line(const QPoint &upper_point)
{
    int Y = object_bottom_max + def_bound_dist + (def_lines_diff * m_ladder->bottom_line_count());
    int X = upper_point.x();
    QPoint bottom_point(X, Y);

    return {upper_point, bottom_point};
}

bool CGraphicsLogic::are_objects_near()
{
    CDiagramObject* drag_obj = m_dragged_pin->parent();
    CDiagramObject* target_obj = m_target_pin->parent();

    int index_d = -1,
        index_t = -1,
        counter = 0;
    object_bottom_max = 0;

    for (CDiagramObject* &obj : *m_ladder->draw_components())
    {
        if (obj == drag_obj)
        {
            index_d = counter;
        }

        if (obj == target_obj)
        {
            index_t = counter;
        }

        if (obj->rect()->bottom() > object_bottom_max)
        {
            object_bottom_max = obj->rect()->bottom();
        }

        counter++;
    }

    if (std::abs(index_d - index_t) == 1)
    {
        return true;
    }
    return false;
}

void CGraphicsLogic::direct_connection(CConnectLine *conn_line)
{
    QLine drag_line = first_line(m_dragged_pin, m_target_pin);
    QLine target_line = first_line(m_target_pin, m_dragged_pin);
    QLine eq_line = equalizing_line(drag_line.p2(), target_line.p2());

    conn_line->add_line(drag_line);
    conn_line->add_line(target_line);

    if (eq_line == QLine())
    {
        QLine last = {drag_line.p2(), target_line.p2()};
        conn_line->add_line(last);
    }

    else
    {
        conn_line->add_line(eq_line);
        QPoint p1 = eq_line.p2();
        QPoint p2 = eq_line.p2().x()  == drag_line.p2().x() ? target_line.p2() : drag_line.p2();

        QLine last = QLine(p1, p2);
        conn_line->add_line(last);
    }
}

QLine CGraphicsLogic::equalizing_line(const QPoint &point1, const QPoint &point2)
{
    if (point1.y() == point2.y())
    {
        return {};
    }

    int Y_start = point1.y() < point2.y() ? point1.y() : point2.y();
    int Y_end = point1.y() > point2.y() ? point1.y() : point2.y();

    int X = point1.y() < point2.y() ? point1.x() : point2.x();

    QPoint p1 = QPoint(X, Y_start);
    QPoint p2 = QPoint(X, Y_end);

    return {p1, p2};
}

int CGraphicsLogic::index_of(std::vector<CPin *> *pins_array, CPin *pin)
{
    int index = 0;
    for (auto &item : *pins_array)
    {
        if (item == pin)
        {
            return index;
        }
        index++;
    }
    return static_cast<int>(pins_array->size());
}

