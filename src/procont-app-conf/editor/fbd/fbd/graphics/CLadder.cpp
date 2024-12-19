//
// Created by artem on 10/29/24.
//

#include "CLadder.h"

#include <QPainter>
#include <QMimeData>

#include "COglWorld.h"
#include "editor/fbd/general/QtDialogs.h"
#include "CGrapchicsLogic.h"
#include "editor/fbd/resources/colors.h"
#include "../redo-undo/CRemoveObject.h"

extern uint16_t    max_local_id;


CLadder::CLadder(COglWorld *world, QPoint *hatch_top_left, QSize *hatch_size, CLadder *prev_ladder, CLadder *next)
{
    m_hatch_pos     = hatch_top_left;
    m_previous      = prev_ladder;
    m_next          = next;
    m_hatch_size    = hatch_size;
    m_objects       = new QList<CDiagramObject*>();
    m_ladder_draw   = new QVector<QPair<QRect*, QImage*>>();
    m_texts = new std::vector<CObjectsText*>();
    m_lines = new std::vector<CConnectLine*>();
    m_parent        = world;

    if (!m_parent)
    {
        throw std::runtime_error("parent is null in 'CLadder::CLadder(...)'");
    }

    if (m_previous)
    {
        m_previous->set_next(this);
    }

    if (m_next)
    {
        m_next->set_previous(this);
    }

    CDiagramColors colors;

    m_number = 0;
    m_num_text = new CObjectsText();
    m_num_text->set_text(QString::number(m_number));
    m_num_text->set_color(colors.ladder_colors().ladder_number);
    m_texts->push_back(m_num_text);



    m_colors.def_left = colors.ladder_colors().normal.left_part;
    m_colors.def_right = colors.ladder_colors().normal.base_part;
    m_colors.selected_left = colors.ladder_colors().selected.left_part;
    m_colors.selected_right = colors.ladder_colors().selected.base_part;
    m_colors.divider = colors.ladder_colors().rail;
    m_colors.gray_field = colors.ladder_colors().grey_part;
    m_colors.gray_bottom = m_colors.gray_field;
    m_colors.landing_brick = colors.ladder_colors().landing_brick;
    m_colors.landing_strip = colors.ladder_colors().landing_strip;

    fill_ladder_image();
    set_selected(false);

    m_current_width = 5000;
    m_ladder_width  = m_current_width;

    update_real_position();
}

CLadder::~CLadder()
{
    for (auto line : *m_lines)
    {
        delete line;
    }
    delete m_lines;

    for (auto & obj : *m_objects)
    {
        delete obj;
    }

    for (auto &txt : *m_texts)
        delete txt;

    delete m_texts;

    delete m_objects;
    delete m_ladder_draw;
}

void CLadder::set_previous(CLadder *ladder)
{
    m_previous      = ladder;
    m_prev_changed  = true;
}

void CLadder::set_next(CLadder *ladder)
{
    m_next          = ladder;
    m_next_changed  = true;
}

bool CLadder::is_visible() const
{
    if (m_hatch_size->width() <= 0 || m_hatch_size->height() <= 0)
    {
        return true; // Такое может возникнуть при первичном разворачивании компонента QOpenGLWidget.
                     // В общем нестандартная ситуация. true - работает нормально.
    }
    QRect hatch = QRect({0, 0}, *m_hatch_size);

    int rel_left = m_abs_rects.base.left() - m_hatch_pos->x();
    int rel_top = m_abs_rects.base.top() - m_hatch_pos->y();

    auto rel = QRect(rel_left,
                     rel_top,
                     m_abs_rects.base.width(),
                     m_abs_rects.base.height());

    bool visible = hatch.contains(rel) || hatch.intersects(rel);

    return visible; // TODO: not tested situation when single ladder's `height` is more then QOpenGLWidget height
}

void CLadder::highlights_off()
{
    m_highlights.clear();

    bool is = false;

    for (auto &obj : *m_objects)
    {
        is = obj->switch_highlights({16000,-1}); // TODO: numbers in the code is not good
        obj->set_selected(false);
    }

    // т.к. для выключения подсветки указывается область с большой ординатой и если там всё-таки что-то есть,
    // это удивляет
    if (is)
    {
        QtDialogs::warn_user("Ваша настойчивость поражает");
    }
}

void CLadder::update_real_position(CLadder *sender)
{
    if (sender != m_previous && sender != nullptr)
    {
        m_previous = sender;
        sender->set_next(this);
        m_prev_changed = true;
    }

    int number = m_previous ? m_previous->number() + 1 : 1;
    QPoint  top_left = m_previous ? m_previous->m_abs_rects.base.bottomLeft() : QPoint(0,0);
    top_left.setY(top_left.y() + 1);
    uint16_t height = define_height();


    /// translate to chine if something changed
    bool do_chine = m_current_height != height ||
                    number != m_number ||
                    m_abs_rects.base.topLeft() != top_left ||
                    m_next_changed || m_prev_changed;

    m_current_height = height;
    m_number = number;
    m_num_text->set_text(QString::number(m_number));
    m_current_width = m_ladder_width;

    m_next_changed = false;
    m_prev_changed = false;



    m_abs_rects.base = QRect(top_left.x(), top_left.y(),
                              m_current_width, m_current_height);

    QPoint absolute_tl = m_abs_rects.base.topLeft();

    m_abs_rects.left = QRect(absolute_tl.x(), absolute_tl.y(),
                              LEFT_WIDTH, m_current_height);
    m_abs_rects.right = QRect(absolute_tl.x() + LEFT_WIDTH, absolute_tl.y(),
                               m_current_width - LEFT_WIDTH, m_current_height);
    m_abs_rects.divider = QRect(LEFT_WIDTH, absolute_tl.y(),
                                 DIVIDER_WIDTH, m_current_height);
    m_abs_rects.field = QRect(LEFT_WIDTH + DIVIDER_WIDTH,
                              absolute_tl.y(), GRAY_WIDTH, m_current_height);
    m_abs_rects.bottom = QRect(absolute_tl.x(), absolute_tl.y() + m_current_height-1,
                               m_current_width, 1);

    if (do_chine)
    {
        update_relative_position();
    }
    if (do_chine && m_next)
    {
        m_next->update_real_position(this);
    }
}

QVector<QPair<QRect *, QImage *>> *CLadder::draw_ladder()
{
    return m_ladder_draw;
}

QVector<CDiagramObject *> *CLadder::draw_components()
{
    return m_objects;
}

std::vector<CObjectsText *> *CLadder::ladder_texts()
{
    return m_texts;
}

const uint16_t * CLadder::height()
{
    return &m_current_height;
}

QRect *CLadder::base_relative_rect()
{
    int rel_left = m_abs_rects.base.left() - m_hatch_pos->x();
    int rel_top = m_abs_rects.base.top() - m_hatch_pos->y();

    m_base_rel = QRect(rel_left,
                       rel_top,
                       m_abs_rects.base.width(),
                       m_abs_rects.base.height());
    return &m_base_rel;
}

uint16_t CLadder::number() const
{
    return m_number;
}

QVector<QPair<QRect, QImage>> CLadder::draw_highlights()
{
    return m_highlights;
}

uint16_t CLadder::define_height() const
{
    uint16_t height = DEF_HEIGHT - HEIGHT_RESERVE;

    for (auto & obj : *m_objects)
    {
        int h = obj->rect()->height();
        if ( h > height)
        {
            height = h;
        }
    }

    height += (m_bottom_lines * def_lines_diff) + def_bound_dist;

    height = height < DEF_HEIGHT ? DEF_HEIGHT : height + HEIGHT_RESERVE + OBJECTS_TOP_SHIFT;

    return height;
}

void CLadder::set_selected(const bool &is_selected)
{
    if (is_selected == m_is_selected)
    {
        return;
    }

    m_is_selected = is_selected;

    if (!is_selected)
    {
        for (auto & obj : *m_objects)
        {
            obj->set_selected(false);
        }
    }

    /// setup_colors

    m_images.left = QImage({5, m_current_height-1}, QImage::Format_ARGB32);
    m_images.left.fill(is_selected ? m_colors.selected_left : m_colors.def_left);

    m_images.right = QImage({5, m_current_height - 1}, QImage::Format_ARGB32);
    m_images.right.fill(is_selected ? m_colors.selected_right : m_colors.def_right);
}

bool CLadder::is_selected() const
{
    return m_is_selected;
}

void CLadder::fill_ladder_image()
{
    m_ladder_draw->push_back({&m_relative.left, &m_images.left});
    m_ladder_draw->push_back({&m_relative.right, &m_images.right});
    m_ladder_draw->push_back({&m_relative.field, &m_images.gray});
    m_ladder_draw->push_back({&m_relative.bottom, &m_images.bottom});
    m_ladder_draw->push_back({&m_relative.divider, &m_images.divider});

    m_images.gray = QImage({5, m_current_height-1}, QImage::Format_ARGB32);
    m_images.gray.fill(m_colors.gray_field);
    m_images.bottom = QImage({5, 1}, QImage::Format_ARGB32);
    m_images.bottom.fill(m_colors.gray_bottom);
    m_images.divider = QImage({3, m_current_height}, QImage::Format_ARGB32);
    m_images.divider.fill(m_colors.divider);
    m_images.landing_bottom = QImage({5, BOT_LANDING_HEIGHT}, QImage::Format_ARGB32);
    m_images.landing_bottom.fill(m_colors.landing_strip);
}

void CLadder::update_relative_position()
{
    m_relative.base.setRect(-m_hatch_pos->x(), m_abs_rects.left.top() - m_hatch_pos->y(),
                            m_current_width, m_current_height);
    m_relative.left.setRect(- m_hatch_pos->x(), m_abs_rects.left.top() - m_hatch_pos->y(),
                            m_abs_rects.left.width(), m_current_height);
    m_relative.right.setRect(m_abs_rects.right.left() - m_hatch_pos->x(), m_abs_rects.left.top() - m_hatch_pos->y(),
                             m_current_width - LEFT_WIDTH, m_abs_rects.right.height());
    m_relative.field.setRect(m_abs_rects.field.left() - m_hatch_pos->x(), m_abs_rects.field.top() - m_hatch_pos->y(),
                             m_abs_rects.field.width(), m_abs_rects.field.height());
    m_relative.bottom.setRect(- m_hatch_pos->x(), m_abs_rects.bottom.top() - m_hatch_pos->y(),
                              m_current_width, m_abs_rects.bottom.height());
    m_relative.divider.setRect(m_abs_rects.divider.left() - m_hatch_pos->x(), m_abs_rects.divider.top() - m_hatch_pos->y(),
                               m_abs_rects.divider.width(), m_abs_rects.divider.height());
    m_relative_tl = m_relative.base.topLeft();

    m_num_text->set_pos({m_relative.left.right() - m_num_text->width() - 15, m_relative.left.top() + m_num_text->height()});

    for (auto &obj : *m_objects)
    {
        obj->update_position();
    }

    for (auto &line : *m_lines)
    {
        line->update_position();
    }
}

bool CLadder::is_clicked_here(const QPoint &pos) const
{
    return m_relative.base.contains(pos);
}

void CLadder::drag_object(QDragMoveEvent *event)
{
    if (!is_clicked_here(event->position().toPoint()))
    {
        highlights_off();
        return;
    }

    const QMimeData * mime = event->mimeData();

    m_highlights.clear();

    QString source = mime->property(txt_vars::drag_source_prop).toString();

    /// если из палитры или из поля диаграммы
    if (source == txt_vars::drag_src_palette || // "palette"
        source == txt_vars::drag_src_canvas     // "canvas"
       )
    {
        EPaletteElements type = (EPaletteElements)event->mimeData()->property(txt_vars::drag_element).toInt();

        /// если лесенка
        if (type == EPaletteElements::EG_CIRCUIT ||
            mime->property(txt_vars::drag_obj_prop_name).toString() == txt_vars::dragging_ladder
           )
        {
            show_landing_highlight();
        }
        /// если компонент
        auto drag_item_name = mime->property(txt_vars::drag_obj_prop_name).toString();
        if (drag_item_name == txt_vars::dragging_object || (type >= EL_AND && type < EPaletteElements::EP_FBD) )
        {
            if (m_objects->empty())
            {
                show_brick();
            }
            else
            {
                bool found = false;
                for (auto &obj : *m_objects)
                {
                    found = obj->switch_highlights(event->position().toPoint());
                    if (found)
                    {
                        break;
                    }
                }

                if (!found)
                {
                    show_brick();
                }
            }
        }

        /// if this is pin
        if (mime->property(txt_vars::drag_obj_prop_name).toString() == txt_vars::drag_pin)
        {
            //bool is_over_other_pin = what_is_here(event->position().toPoint());
        }
    }
}

void CLadder::show_landing_highlight()
{
    m_ladder_landing = QRect(m_relative.base.topLeft(),
                             QSize(m_relative.base.width(), BOT_LANDING_HEIGHT));
    m_highlights.push_back({m_ladder_landing, m_images.landing_bottom});
}

void CLadder::show_brick()
{
    QRect rect;
    QImage image;

    if (m_objects->empty())
    {
        rect = m_relative.right;
        image = QImage({1, 1/*rect.width()*/}, QImage::Format_ARGB32);
    }

    else
    {
        int right = m_objects->back()->bound_text_rect().right();
        int width = m_abs_rects.base.right() - right;
        rect = QRect(right, m_relative.base.top(), width, m_current_height);
        image = QImage({1, rect.width()}, QImage::Format_ARGB32);
    }

    image.fill(m_colors.landing_brick);
    m_highlights.push_back({rect, image});
}

CDiagramObject *CLadder::add_object(CBlock *object)
{
    m_objects->emplace_back(new CDiagramObject(this, object));
    resort();
    return m_objects->back();
}

void CLadder::resort()
{
    if (m_objects->empty())
    {
        update_real_position();
        return;
    }

    uint16_t index = 0;
    uint16_t difference;    //!< distance between left bound_text_rect and left component rect
    int prev_last = 0;

    for (auto & obj : *m_objects)
    {
        obj->update_bound_rect();
        obj->update_position();
        difference = obj->rect()->left() - obj->bound_graph_rect().left();

        int last_right = index == 0 ?
                LEFT_WIDTH + GRAY_WIDTH + OBJECTS_DISTANCE/2 + difference :
                         prev_last + m_objects->at(index - 1)->bound_graph_rect().width() + OBJECTS_DISTANCE + difference;

        obj->set_ladders_relative_top_left(this, {last_right, OBJECTS_TOP_SHIFT});
        prev_last = last_right - difference;

        index++;
    }

    if (m_objects->back()->bound_text_rect().right() > m_ladder_width)
    {
        m_ladder_width = m_objects->back()->bound_text_rect().right();
    }

    update_real_position();

    refresh_graphic_connections();
}

void CLadder::get_selected(const QPoint &point, s_selection *p_selection)
{
    p_selection->ladder = this;

    this->set_selected(true);

    for (auto &obj : *m_objects)
    {
        bool obj_sel = obj->rect()->contains(point);

        if (obj_sel)
        {
            p_selection->object = obj;
        }

        obj->set_selected(obj_sel);


        for (auto & pin : *obj->pins())
        {
            bool pin_sel = pin->rect()->contains(point);

            if (pin_sel)
            {
                p_selection->pin = pin;
            }
            pin->set_selected(pin_sel);
        }
    }
}

/*void CLadder::put_dragged_object(CDiagramObject *dragged_obj, const QPoint &pos)
{
    if (m_objects->empty())
    {
        m_objects->push_back(dragged_obj);
    }

    /// define objects on witch dropped. it will be after
    else
    {
        int  index = 0;
        bool found = false;

        for (auto &obj: *m_objects)
        {
            if (obj->bound_text_rect().contains(pos))
            {
                found = true;
                break;
            }
            index++;
        }

        if (!found)
        {
            m_objects->push_back(dragged_obj);
        }
        else
        {
            m_objects->insert(m_objects->cbegin() + index, dragged_obj);
        }
    }

    resort();
    highlights_off();

    update_real_position();
}*/

/*CDiagramObject *CLadder::remove_object(CDiagramObject *dragged_obj)
{
    int index = 0;
    for (auto &obj : *m_objects)
    {
        if (obj == dragged_obj)
        {
            m_objects->erase(m_objects->cbegin() + index);
            resort();
            update_real_position();
            return dragged_obj;
        }
        index++;
    }

    return nullptr;
}*/

QImage CLadder::drag_image()
{

    m_drag_image = QImage({m_hatch_size->width(), static_cast<int>((float)m_current_height*0.6f)}, QImage::Format_ARGB32);
    m_drag_image.fill({255,255,255,127});

    QPainter painter;
    painter.begin(&m_drag_image);

    int last_right = 10;

    for (auto &obj : *m_objects)
    {
        QImage comp_img = obj->drag_image(true);
        QRect rect = {last_right, OBJECTS_TOP_SHIFT, comp_img.width(), comp_img.height()};

        if (rect.right() > m_hatch_size->width())
        {
            obj->update_position();
            break;
        }

        painter.drawImage(rect, comp_img);
        last_right += comp_img.width() + OBJECTS_DISTANCE;
        obj->update_position();
    }

    painter.end();

    m_drag_image = m_drag_image.scaled(m_drag_image.width()/2, m_drag_image.height()/2);

    return m_drag_image;
}

CLadder * CLadder::previous_ladder()
{
    return m_previous;
}

CLadder * CLadder::next_ladder()
{
    return m_next;
}

QPoint CLadder::real_bottom_right() const
{
    return m_abs_rects.base.bottomRight();
}

QPoint *CLadder::real_top_left()
{
    return &m_relative_tl;
}

short CLadder::bottom_line_count() const
{
    return m_bottom_lines;
}

CConnectLine *CLadder::add_line(CConnectLine *line)
{
    m_lines->push_back(line);

    if (line->lines()->size() == 5)
    {
        m_bottom_lines ++;
    }

    return line;
}

std::vector<CConnectLine *> *CLadder::connecting_lines()
{
    return m_lines;
}

void CLadder::refresh_graphic_connections()
{
    m_bottom_lines = 0;
    //CPin *opposite;

    for (auto &line : *m_lines)
    {
        delete line;
    }
    m_lines->clear();

    CGraphicsLogic connect_algo;

    for (auto &obj : *m_objects)
    {
        for (auto &pin : *obj->outputs())
        {
            if (pin->graphic_connections()->empty())
            {
                continue;
            }

            for (auto &conn : *pin->graphic_connections())
            {
                auto line = connect_algo.add_new_line(conn, pin);
                if (line)
                {
                    m_lines->push_back(line);
                }
            }
        }
        obj->refresh_graphic_connections();
    }
}

CConnectLine *CLadder::remove_line(CConnectLine *line)
{
    int counter = 0;
    m_bottom_lines--;   // тут совсем не факт TODO: fix this moment

    for (auto &item : *m_lines)
    {
        if (item == line)
        {
            m_lines->erase(m_lines->begin() + counter);
            if (item->lines()->size() == 5)
            {
                m_bottom_lines--;
            }
            return line;
        }
        counter++;
    }
    return nullptr;
}

COglWorld *CLadder::parent()
{
    return m_parent;
}

CConnectLine *CLadder::remove_line(CPinIn *pin_input)
{
    int counter = 0;
    for (auto &line : *m_lines)
    {
        if (line->get_pin_in() == pin_input)
        {
            m_lines->erase(m_lines->begin() + counter);

            if (line->lines()->size() == 5)
            {
                m_bottom_lines--;
            }

            return line;
        }
        counter++;
    }
    return nullptr;
}

void CLadder::erase_object(CDiagramObject *obj)
{
    if (obj->parent() != this)
    {
        return;
    }

    auto cmd = new CRemoveObject(obj);
    m_parent->undo_stack()->push(cmd);
}





