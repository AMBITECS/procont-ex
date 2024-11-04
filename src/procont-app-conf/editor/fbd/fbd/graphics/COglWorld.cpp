//
// Created by artem on 29.10.24.
//

#include <QTimer>
#include "COglWorld.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>


COglWorld::COglWorld(CPou *pou, QPoint * hatch_pos)
{
    m_ladders = new std::vector<CLadder*> ();
    m_visible_ladders = new std::vector<CLadder*> ();
    m_hatch_topLeft = hatch_pos;
    m_pou = pou;

    QTimer::singleShot(200, this, SLOT(initial_shot()));
}

COglWorld::~COglWorld()
{
    clear_ladders();
    delete m_ladders;
    delete m_visible_ladders;
}

CLadder *COglWorld::add_new_ladder()
{
    CLadder *prev = m_ladders->empty() ? nullptr : m_ladders->back();

    auto ladder = new CLadder(m_hatch_topLeft, &m_hatch_size, prev);

    if (prev)
    {
        prev->set_next(ladder);
    }

    m_ladders->push_back(ladder);

    check_diagram_size();

    // TODO: refresh visible

    return ladder;
}

void COglWorld::insert_new_component(CLadder *p_ladder, const EPaletteElements &elements)
{
    // get new component from fabric
    // insert
    // TODO: relocate lower ladders
    check_diagram_size();
}

void COglWorld::clear_ladders()
{
    for (auto &item : *m_ladders)
    {
        delete item;
    }
    m_ladders->clear();
}

std::vector<CLadder*>  *COglWorld::ladders()
{
    return m_visible_ladders;
}

void COglWorld::reset_all_highlights()
{
    for (auto &item : *m_ladders)
    {
        item->highlights_off();
    }
}

void COglWorld::win_resized(const int &w, const int &h)
{
    m_hatch_width = w;
    m_hatch_height = h;
    m_hatch_size = QSize(w, h);

    update_visible_ladders();
}

void COglWorld::view_hatch_moved(const QPoint &pos)
{
    /// define visible ladders
    update_visible_ladders();
}

s_selection COglWorld::get_selection(const QPoint &pos)
{
    m_selection.reset();

    if (m_ladders->empty())
    {
        return m_selection;
    }

    for (auto vis : *m_visible_ladders)
    {
        if (vis->is_clicked_here(pos))
        {
            m_selection.ladder = vis;
            // TODO: request components
        }
    }
    return m_selection;
}

QPoint COglWorld::get_visible_range(const QPoint & pos)
{
    /// исходим из того, что лестниц более 100
    /// TODO: обязательно отрефакторить этот мусор
    uint16_t index = 0;
    uint16_t count = m_ladders->size();

    /// определив один видимый, мы определим начальный диаппазон +limit -limit от этого видимого и уже из этого
    /// начального диаппазона определим диаппазон реально видимых ступеней
    int limit = 20;
    int ladder_top, ladder_bottom;
    int left = 0;
    int right = count - 1;
    int mid;

    CLadder * curr_ladder = m_ladders->at(index);

    /// define one of visible by bubble method
    while ((right > left))
    {
        mid = (left + right) / 2;
        curr_ladder = m_ladders->at(mid);

        ladder_top = curr_ladder->base_relative_rect()->top();
        ladder_bottom = curr_ladder->base_relative_rect()->bottom();

        if (curr_ladder->is_visible())
        {
            break;
        }

        /// if lower
        if (ladder_top >= m_hatch_height)
        {
            right = mid - 1;
        }

        /// if higher
        if (ladder_bottom <= 0)
        {
            left = mid + 1;
        }

    }

    if (!curr_ladder->is_visible())
    {
        return {0,0};
    }

    /// Definition of the visible ladders range starts from the range -(minus) "limit" items from defined
    /// visible item till + "limit" items from defined visible item

    int first_number = curr_ladder->number() - limit;
    int last_number = curr_ladder->number() + limit;

    if (first_number < 0)
        first_number = 0;
    if (first_number >= count)
        return {0,0};

    if (last_number < 0)
        return {0,0};
    if (last_number >= count)
        last_number = count - 1;

    int last = -1;
    int first = -1;

    for (int i = first_number; i <= last_number; ++i)
    {
        auto ladder = m_ladders->at(i);

        if ( ladder->is_visible() and first < 0 )
        {
            first = i;
        }

        if ( !ladder->is_visible() && first >= 0 )
        {
            last = i; // a little reserve
            break;
        }
    }

    if ((first > 0 && first < count) && last < 0)
        last = count - 1;

    if (first < 0 || last < 0)
        return {0, 0};

    return {first, last};
}

void COglWorld::load_project()
{
    auto body = m_pou->bodies()->empty() ? nullptr : m_pou->bodies()->front();

    if (!body)
    {
        return;
    }

    CLadder *cur_ladder;
    CLadder *prev_ladder = nullptr;

    for (auto &block : *body->fbd_content()->blocks())
    {
        auto lad_index = block->local_id() / 10000000;
        cur_ladder = get_ladder(lad_index);

        if (cur_ladder != prev_ladder)
        {
            if (prev_ladder)
                prev_ladder->resort();
            prev_ladder = cur_ladder;
        }

        auto object = cur_ladder->add_object(block);

        /// setup input/output variables
        for (auto &pin : *object->pins())
        {
            if (pin->direction() == PD_INPUT)
            {
                find_in_variable(pin);
            }
            else
            {
                find_out_var(pin, block->local_id());
            }            
        }
        object->update_rel_position();
        cur_ladder->update_real_position();
    }
    cur_ladder->resort();
}

void COglWorld::initial_shot()
{
    if (!m_pou->is_empty())
    {
        load_project();
    }

    /// for develop purposes only
    for (int i = 0; i < 100; i++)
    {
        add_new_ladder();
    }

    check_diagram_size();
    update_visible_ladders();
    emit update_hatch();
}

void COglWorld::check_diagram_size()
{
    QPoint br = m_ladders->back()->real_bottom_right();

    if (m_diagram_size.width() != br.x() ||
        m_diagram_size.height() != br.y()
            )
    {
        m_diagram_size = QSize(br.x(), br.y());

        emit canvas_changed(br.x(), br.y());
    }
}

void COglWorld::mouse_clicked(const QPoint &pos)
{
    for (auto &ladder : *m_ladders)
    {
        if (ladder->is_selected())
        {
            ladder->set_selected(false);
            break;
        }
    }

    for (auto ladder : *m_visible_ladders)
    {
        if (ladder->is_clicked_here(pos))
        {
            ladder->set_selected(true);
            break;
        }
    }
}

void COglWorld::mouse_drag_over(QDragMoveEvent *event)
{
    for (auto &ladder : *m_visible_ladders)
    {
        ladder->drag_object(event);
    }
}

void COglWorld::shutdown_highlights()
{
    for (auto lad : *m_visible_ladders)
    {
        lad->highlights_off();
    }
}

CLadder *COglWorld::insert_new_ladder(CLadder *next)
{
    if (!next)
    {
        return nullptr;
    }

    int index = next->number() - 1;
    CLadder *prev = index - 1 < 0 ? nullptr : m_ladders->at(index-1);

    auto ladder = new CLadder(m_hatch_topLeft, &m_hatch_size, prev, next);

    if (prev)
    {
        prev->set_next(ladder);
    }

    m_ladders->insert(m_ladders->begin() + index, ladder);
    view_hatch_moved({});

    check_diagram_size();

    return ladder;
}

void COglWorld::update_visible_ladders()
{
    if (m_ladders->empty())
    {
        return;
    }

    auto range = get_visible_range(*m_hatch_topLeft);

    m_visible_ladders->clear();
    m_visible_ladders->insert(m_visible_ladders->end(),
                              m_ladders->begin()+range.x(),
                              m_ladders->begin() + range.y());

    for (int i = range.x(); i < range.y(); i++)
    {
        m_ladders->at(i)->update_rel_position();
    }

    emit update_hatch();
}

void COglWorld::find_in_variable(CConnectorPin *&p_pin)
{
    if (m_pou->bodies()->isEmpty() || p_pin->ref_local_id() == 0)
    {
        return;
    }

    auto body = m_pou->bodies()->front()->fbd_content();
    if (!body)
    {
        return;
    }

    uint64_t ref_id = p_pin->ref_local_id();


    for (auto &block : *body->blocks())
    {
        if (block->local_id() == ref_id)
        {
            QString pin_formal = p_pin->block_var()->point_in()->connections()->empty() ? ""
                    : p_pin->block_var()->point_in()->connections()->front()->formal_parameter();
            QString formal = block->instance_name().isEmpty() ?
                    block->type_name() + "_" + QString::number(ref_id) + "."+pin_formal :
                    block->instance_name() + "." + pin_formal;
            p_pin->set_formal_param(formal);
            return;
        }
    }

    for (auto &input : *body->inVariables())
    {
        if (input->local_id() == ref_id)
        {
            p_pin->set_in_variable(input);
            return;
        }
    }
}

bool COglWorld::find_out_var(CConnectorPin *p_pin, const uint64_t &block_id)
{
    if (m_pou->bodies()->isEmpty())
    {
        return false;
    }

    auto body = m_pou->bodies()->front()->fbd_content();
    if (!body)
    {
        return false;
    }

    QList<COutVariable*> * outs = body->out_variables();
    uint64_t  point_ref;

    for (COutVariable * &out : *outs)
    {
        point_ref = 0;
        if (!out->point_in()->connections()->empty())
        {
            point_ref = out->point_in()->connections()->front()->ref_local_id();
        }
        if (!point_ref) { continue; }

        if (point_ref == block_id)
        {
            p_pin->set_out_variable(out);
            return true;
        }
    }
    return false;
}

CLadder *COglWorld::get_ladder(const unsigned long &id_ladder)
{
    CLadder *cur_ladder = nullptr;
    if (id_ladder >= m_ladders->size())
    {
        if (m_ladders->empty())
        {
            cur_ladder = add_new_ladder();
        }
        else
            cur_ladder = m_ladders->back();
    }
    else
    {
        cur_ladder = m_ladders->at(id_ladder);
    }
    return cur_ladder;
}

void COglWorld::mouse_left_pressed(const QPoint &pos)
{
    m_selection.reset();

    for (auto &ladder : *m_ladders)
    {
        if (ladder->is_selected() && ladder != m_selection.ladder)
        {
            ladder->set_selected(false);
        }

        if (ladder->is_clicked_here(pos))
        {
            ladder->get_selected(pos, &m_selection);
        }
    }

    if (m_selection.ladder)
    {
        m_selection.ladder->set_selected(true);
    }

    m_mouse_pressed = pos;
}

void COglWorld::mouse_move(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton) || m_selection.empty())
    {
        return;
    }

    if ( (event->pos() - m_mouse_pressed).manhattanLength()
         < QApplication::startDragDistance()
       )
    {
        return;
    }

    auto *drag = new QDrag(this);
    auto   * mime = new QMimeData();
    drag->setMimeData(mime);

    mime->setProperty("element", -1);

    if (m_selection.ladder && !m_selection.object)
    {
        mime->setProperty("source", "canvas");
        mime->setProperty("object", "ladder");

        drag->setPixmap(QPixmap::fromImage(m_selection.ladder->drag_image()));
    }

    if (m_selection.object)
    {
        m_selection.object->draw_drag_image();
        drag->setPixmap(QPixmap::fromImage(m_selection.object->drag_image()));
        m_selection.object->update_rel_position();

        mime->setProperty("source", "canvas");
        mime->setProperty("object", "object");
        mime->setProperty("object_id", (int)m_selection.object->local_id());
    }

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

}

s_selection *COglWorld::get_selection()
{
    return &m_selection;
}

void COglWorld::insert_ladder(CLadder *dragged_ladder, CLadder *before)
{
    if (m_ladders->size() == 1)
    {
        return;
    }

    if (before == dragged_ladder)
    {
        return;
    }


    int index = dragged_ladder->number() - 1;
    m_ladders->erase(m_ladders->begin() + index);
    /// откуда (начало/конец/середина) взяли, там надо "сшить"<BR>

    /// from the begin
    if (!dragged_ladder->previous_ladder())
    {
        dragged_ladder->next_ladder()->set_previous(nullptr);
    }
    /// from the end
    if (!dragged_ladder->next_ladder())
    {
        dragged_ladder->previous_ladder()->set_next(nullptr);
    }
    /// from the middle
    if (dragged_ladder->previous_ladder() && dragged_ladder->next_ladder())
    {
        dragged_ladder->next_ladder()->set_previous(dragged_ladder->previous_ladder());
        dragged_ladder->previous_ladder()->set_next(dragged_ladder->next_ladder());
    }

    CLadder * start = dragged_ladder->previous_ladder() ? dragged_ladder->previous_ladder()
            : dragged_ladder->next_ladder();

    start->update_real_position();
    start->update_rel_position();
    view_hatch_moved({});


    /// куда (начало конец середина) вставка - там "разрезаем"<BR>

    /// to the end
    if (!before)
    {
        dragged_ladder->set_previous(m_ladders->back());
        m_ladders->back()->set_next(dragged_ladder);
        m_ladders->push_back(dragged_ladder);
    }

    /// to the middle
    if (before && before->next_ladder() && before->previous_ladder())
    {
        index = before->number() - 1;

        /// setup inserting ladder new prev and next
        dragged_ladder->set_previous(before->previous_ladder());
        dragged_ladder->set_next(before);

        /// setup old ladders new prev and next
        before->previous_ladder()->set_next(dragged_ladder);
        before->set_previous(dragged_ladder);


        m_ladders->insert(m_ladders->begin() + index, dragged_ladder);
    }

    /// to the begin
    if (before && !before->previous_ladder())
    {
        dragged_ladder->set_previous(nullptr);
        dragged_ladder->set_next(m_ladders->front());
        m_ladders->front()->set_previous(dragged_ladder);
        m_ladders->insert(m_ladders->begin(), dragged_ladder);
    }

    CLadder * start_refresh;

    if (!dragged_ladder->previous_ladder())
    {
        start_refresh = dragged_ladder;
    }
    else
    {
        start_refresh = dragged_ladder->previous_ladder();
    }

    start_refresh->update_real_position();
    view_hatch_moved({});

    check_diagram_size();
}

void COglWorld::ladder_size_changed()
{
    check_diagram_size();
}


