//
// Created by artem on 10/29/24.
//

#include "CLadder.h"
#include "../palette/palette.h"
#include "COglWorld.h"
#include "../../general/QtDialogs.h"
#include <QPainter>
#include <QMimeData>

CLadder::CLadder(QPoint *hatch_top_left, QSize * hatch_size, CLadder *prev_ladder, CLadder *next)
{
    m_hatch_pos     = hatch_top_left;
    m_previous      = prev_ladder;
    m_next          = next;
    m_hatch_size    = hatch_size;
    m_objects       = new QList<CDiagramObject*>();
    m_ladder_draw = new QVector<QPair<QRect*, QImage*>>();

    m_number = 0;
    m_num_text.set_text(QString::number(m_number));
    m_texts.push_back(&m_num_text);
    m_num_text.set_color(m_colors.divider);

    fill_ladder_image();
    set_selected(false);

    m_current_width = 5000;
    m_ladder_width =   m_current_width;

    update_real_position();
}

CLadder::~CLadder()
{
    for (auto & obj : *m_objects)
    {
        delete obj;
    }
    delete m_objects;
    delete m_ladder_draw;
}

void CLadder::set_previous(CLadder *ladder)
{
    m_previous = ladder;
    m_prev_changed = true;
}

void CLadder::set_next(CLadder *ladder)
{
    m_next = ladder;
    m_next_changed = true;
}

bool CLadder::is_visible() const
{
    if (m_hatch_size->width() <= 0 || m_hatch_size->height() <= 0)
    {
        return true; // ???
    }
    QRect hatch = QRect({0, 0}, *m_hatch_size);

    int rel_left = m_abs_rects.base.left() - m_hatch_pos->x();
    int rel_top = m_abs_rects.base.top() - m_hatch_pos->y();

    auto rel = QRect(rel_left,
                       rel_top,
                       m_abs_rects.base.width(),
                       m_abs_rects.base.height());

    bool visible = hatch.contains(rel) || hatch.intersects(rel);
    return visible;
}

/*void CLadder::hatch_moving(const QPoint &cur_position)
{

}*/

void CLadder::highlights_off()
{
    m_highlights.clear();

    bool is = false;

    for (auto &obj : *m_objects)
    {
        is = obj->switch_highlights({6000,-1});
    }

    if (is)
    {
        // something strange
        QtDialogs::warn_user("Ваша настойчивость поражает");
    }
}

void CLadder::update_real_position(CLadder *sender)
{
    if (sender != m_previous && sender != nullptr)
    {
        m_previous = sender;
        m_prev_changed = true;
    }

    int number = m_previous ? m_previous->number() + 1 : 1;
    QPoint  top_left = m_previous ? m_previous->m_abs_rects.base.bottomLeft() : QPoint(0,0);
    uint16_t height = define_height();


    /// translate to chine if something changed
    bool do_chine = m_current_height != height ||
                    number != m_number ||
                    m_absolute_tl != top_left ||
                    m_next_changed || m_prev_changed;

    m_absolute_tl = top_left;
    m_abs_rects.base.setTopLeft(top_left);
    m_current_height = height;
    m_number = number;
    m_num_text.set_text(QString::number(m_number));
    m_current_width = m_ladder_width;

    m_next_changed = false;
    m_prev_changed = false;


    m_abs_rects.base = QRect(m_absolute_tl.x(), m_absolute_tl.y(),
                              m_current_width, m_current_height);
    m_abs_rects.left = QRect(m_absolute_tl.x(), m_absolute_tl.y(),
                              LEFT_WIDTH, m_current_height);
    m_abs_rects.right = QRect(m_absolute_tl.x() + LEFT_WIDTH, m_absolute_tl.y(),
                               m_current_width - LEFT_WIDTH, m_current_height);
    m_abs_rects.divider = QRect(LEFT_WIDTH, m_absolute_tl.y(),
                                 DIVIDER_WIDTH, m_current_height);
    m_abs_rects.field = QRect(LEFT_WIDTH + DIVIDER_WIDTH,
                               m_absolute_tl.y(), GRAY_WIDTH, m_current_height);
    m_abs_rects.bottom = QRect(m_absolute_tl.x(), m_absolute_tl.y() + m_current_height-1,
                               m_current_width, 1);

    if (do_chine && m_next)
    {
        update_rel_position();
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

QVector<CObjectsText *> *CLadder::ladder_texts()
{
    return &m_texts;
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
/*
void CLadder::hatch_resized()
{
    update_real_position();
}*/

QVector<QPair<QRect, QImage>> CLadder::draw_highlights()
{
    return m_highlights;
}

uint16_t CLadder::define_height() const
{
    uint16_t height = DEF_HEIGHT - HEIGHT_RESERVE;

    for (auto & obj : *m_objects)
    {
        int h = obj->bound_rect().height();
        if ( h > height)
        {
            height = h;
        }
    }

    height = height < DEF_HEIGHT ? DEF_HEIGHT : height + HEIGHT_RESERVE + OBJECTS_TOP_SHIFT;

    return height;
}

void CLadder::set_selected(const bool &is_selected)
{
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

void CLadder::update_rel_position()
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

    m_num_text.set_pos({m_relative.left.right() - m_num_text.width() - 15, m_relative.left.top() + m_num_text.height()});

    for (auto &obj : *m_objects)
    {
        obj->update_rel_position();
    }
}

bool CLadder::is_clicked_here(const QPoint &pos) const
{
    return m_relative.base.contains(pos);
}

QImage CLadder::drag_image() const
{
    QImage image(m_relative.base.size(), QImage::Format_ARGB32);

    QPainter painter(dynamic_cast<QPaintDevice*>(&image));
    painter.drawImage(QRect(0,0, LEFT_WIDTH,
                            m_current_height), m_images.left);
    painter.drawImage(QRect(LEFT_WIDTH, 0, GRAY_WIDTH,
                            m_current_height), m_images.gray);
    painter.drawImage(QRect(LEFT_WIDTH, 0, DIVIDER_WIDTH,
                            m_current_height), m_images.divider);

    image = image.scaled(m_hatch_size->width()/2, m_current_height/2);
    return image;
}

void CLadder::drag_object(QDragMoveEvent *event)
{
    if (!is_clicked_here(event->position().toPoint()))
    {
        highlights_off();
        return;
    }

    auto mime = event->mimeData();

    m_highlights.clear();

    /// если из палитры или из поля диаграммы
    if (mime->property("palette").toInt() == 1 ||
        mime->property("source").toString() == "canvas"
       )
    {
        EPaletteElements type = (EPaletteElements)event->mimeData()->property("element").toInt();

        /// если лесенка
        if (type == EPaletteElements::EG_CIRCUIT ||
            mime->property("object").toString() == "ladder"
           )
        {
            show_landing_highlight();
        }
        /// если компонент
        else
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
        image = QImage({1, rect.width()}, QImage::Format_ARGB32);
    }

    else
    {
        int right = m_objects->back()->bound_rect().right();
        int width = m_abs_rects.base.right() - right;
        rect = QRect(right, m_relative.base.top(), width, m_current_height);
        image = QImage({1, rect.width()}, QImage::Format_ARGB32);
    }

    image.fill(m_colors.landing_brick);
    m_highlights.push_back({rect, image});
}

CDiagramObject *CLadder::add_object(CBlock *object)
{
    auto d_obj = new CDiagramObject(&m_relative_tl, object);

    auto last_right = m_objects->empty() ? LEFT_WIDTH + GRAY_WIDTH + OBJECTS_DISTANCE/2 : m_objects->back()->bound_rect().right() + OBJECTS_DISTANCE;

    d_obj->set_relative_pos(last_right, OBJECTS_TOP_SHIFT);
    m_objects->push_back(d_obj);

    int obj_height = d_obj->rect()->height();

    if (obj_height + HEIGHT_RESERVE + OBJECTS_TOP_SHIFT > m_current_height )
    {
        m_current_height = OBJECTS_TOP_SHIFT + obj_height + HEIGHT_RESERVE;
        update_real_position();
    }

    return m_objects->back();
}

void CLadder::resort()
{
    if (m_objects->empty())
    {
        m_current_height = DEF_HEIGHT;
        update_real_position();
        return;
    }

    uint16_t index = 0;
    uint16_t difference;    //!< distance between left bound_rect and left component rect
    int prev_last = 0;

    for (auto & obj : *m_objects)
    {
        difference = obj->rect()->left() - obj->bound_rect().left();
        int last_right = index == 0 ? LEFT_WIDTH + GRAY_WIDTH + OBJECTS_DISTANCE/2 + difference :
                prev_last + m_objects->at(index-1)->bound_rect().width() + OBJECTS_DISTANCE + difference;

        obj->set_relative_pos(last_right, OBJECTS_TOP_SHIFT);
        //obj->set_absolute_pos(last_right, OBJECTS_TOP_SHIFT);

        prev_last = last_right - difference;

        index++;
    }

    if (m_objects->back()->bound_rect().right() > m_ladder_width)
    {
        m_ladder_width = m_objects->back()->bound_rect().right();
    }

    update_real_position();
}

void CLadder::get_selected(const QPoint &point, s_selection *p_selection)
{
    p_selection->ladder = this;

    this->set_selected(true);

    for (auto &obj : *m_objects)
    {
        if (obj->rect()->contains(point))
        {
            p_selection->object = obj;
            obj->set_selected(true);
        }
        else
        {
            obj->set_selected(false);
        }

        for (auto & pin : *obj->pins())
        {
            if (pin->rect()->contains(point))
            {
                p_selection->pin = pin;
                pin->set_selected(true);
                return;
            }
        }
    }
}

void CLadder::put_dragged_object(CDiagramObject *dragged_obj, const QPoint &pos)
{
    int diff = dragged_obj->rect()->left() - dragged_obj->bound_rect().left();

    int height = m_current_height;
    int width = m_current_width;

    if (m_objects->empty())
    {
        auto last_right = LEFT_WIDTH + GRAY_WIDTH + OBJECTS_DISTANCE/2 + diff;
        dragged_obj->set_ladders_top_left(&m_relative_tl, {last_right, OBJECTS_TOP_SHIFT});
        m_objects->push_back(dragged_obj);
    }

    /// define previous and next objects
    else
    {
        int index = 0;
        bool found = false;
        CDiagramObject *prev = nullptr;
        for (auto &obj: *m_objects)
        {
            if (obj->bound_rect().contains(pos))
            {
                found = true;
                break;
            }
            prev = obj;
            index++;
        }

        if (!found)
        {
            prev = m_objects->back();
        }

        auto last_right = prev == nullptr ? LEFT_WIDTH + GRAY_WIDTH + OBJECTS_DISTANCE / 2 :
                          prev->bound_rect().right() + OBJECTS_DISTANCE;

        dragged_obj->set_ladders_top_left(&m_relative_tl, {last_right + diff, OBJECTS_TOP_SHIFT});
        m_objects->insert(m_objects->begin() + index, dragged_obj);
    }

    update_real_position();
    highlights_off();
    resort();

    if (m_current_height != height || m_current_width != width)
    {
        ; /// don't want to make CLadder as an QObject
    }
}

/*void CLadder::drag_over_object(const QPoint &pos)
{

}*/

CDiagramObject *CLadder::remove_object(CDiagramObject *dragged_obj)
{
    int index = 0;
    for (auto &obj : *m_objects)
    {
        if (obj == dragged_obj)
        {
            m_objects->erase(m_objects->begin() + index);
            //update_rel_position();
            resort();
            return dragged_obj;
        }
        index++;
    }

    return nullptr;
}

QImage CLadder::drag_image()
{

    m_drag_image = QImage({m_hatch_size->width(), m_current_height}, QImage::Format_ARGB32);
    m_drag_image.fill({255,255,255,127});

    QPainter painter;
    painter.begin(&m_drag_image);

    int counter = 0;
    int last_right = 10;

    for (auto &obj : *m_objects)
    {
        obj->draw_drag_image();
        QImage comp_img = obj->drag_image();
        QRect rect = {last_right, OBJECTS_TOP_SHIFT, comp_img.width(), comp_img.height()};

        if (rect.right() > m_hatch_size->width())
        {
            obj->update_rel_position();
            break;
        }

        painter.drawImage(rect, comp_img);
        last_right += comp_img.width() + OBJECTS_DISTANCE;
        obj->update_rel_position();
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


/*
void CLadder::highlights_on(const QPoint &pos)
{
    //for (auto &obj : *m_objects)
}
*/


