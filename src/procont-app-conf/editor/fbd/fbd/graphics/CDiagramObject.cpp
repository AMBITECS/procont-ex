//
// Created by artem on 10/29/24.
//

#include <QPainter>
#include "CDiagramObject.h"
#include "CLadder.h"

CDiagramObject::CDiagramObject(CLadder *ladder, CBlock *block) //QPoint *ladder_top_left
{
    m_block = block;
    m_block->set_global_id(QString::number(ladder->number() - 1));

    m_ladder_relative_tl = ladder->real_top_left();
    m_parent = ladder;

    m_texts.push_back(&m_type_name);
    m_texts.push_back(&m_instance_name);

    m_inputs = new std::vector<CConnectorPin*>();
    m_outputs = new std::vector<CConnectorPin*>();
    m_pins = new std::vector<CConnectorPin*>();
    m_highlights = new std::vector<std::pair<QRect, QImage>>();

    m_type_name.set_text(m_block->type_name());
    m_instance_name.set_text(m_block->instance_name());

    define_size();

    locate_pins();

    m_rect.setSize(m_size);
}

CDiagramObject::~CDiagramObject()
{
    for (auto &pin : *m_inputs)
    {
        delete pin;
    }

    for (auto &pin : *m_outputs)
    {
        delete pin;
    }

    delete m_inputs;
    delete m_outputs;
    delete m_pins;
    delete m_highlights;
}

QRect *CDiagramObject::rect()
{
    return &m_rect;
}

QImage *CDiagramObject::image()
{
    return &m_image;
}

std::vector<CConnectorPin *> *CDiagramObject::pins()
{
    return m_pins;
}

std::vector<CObjectsText *> *CDiagramObject::texts()
{
    return &m_texts;
}

void CDiagramObject::define_size()
{
    if (!m_pins->empty())
    {
        return;
    }

    int def_width = m_type_name.width() > m_instance_name.width() ? m_type_name.width() : m_instance_name.width();
    int inner_left_max = 0;
    int inner_right_max = 0;

    def_width += 2 * NAME_SHIFT;

    for (auto &inout : *m_block->in_out_variables())
    {
        auto pin_i = new CConnectorPin(inout, this, PD_INPUT, &m_base_shift);
        auto pin_o = new CConnectorPin(inout, this, PD_OUTPUT, &m_base_shift);
        m_inputs->push_back(pin_i);
        m_outputs->push_back(pin_o);
    }

    for (auto &in : *m_block->input_variables())
    {
        auto in_pin = new CConnectorPin(in, this, PD_INPUT, &m_base_shift);
        m_inputs->push_back(in_pin);
    }

    for (auto &out : *m_block->output_variables())
    {
        auto pin_out = new CConnectorPin(out, this, PD_OUTPUT, &m_base_shift);
        m_outputs->push_back(pin_out);
    }

    int inner = 0;
    for (auto &in : *m_inputs)
    {
        inner = in->inner_text_width() + 3;
        if (inner > inner_left_max)
        {
            inner_left_max = inner;
        }
    }

    for (auto &out : *m_outputs)
    {
        inner = out->inner_text_width() + 3;
        if (inner > inner_right_max)
        {
            inner_right_max = inner;
        }
    }

    size_t max_pins = m_inputs->size() > m_outputs->size() ? m_inputs->size() : m_outputs->size();

    def_width = def_width > (inner_left_max + inner_right_max + 20) ? def_width
                : inner_left_max + inner_right_max + 20;

    m_size.setWidth(def_width);
    m_size.setHeight(TOP_SHIFT + (max_pins * PIN_SHIFT) + BOTTOM_SHIFT);
    m_rect.setSize(m_size);

    m_pins->clear();
    m_pins->insert(m_pins->end(), m_inputs->begin(), m_inputs->end());
    m_pins->insert(m_pins->end(), m_outputs->begin(), m_outputs->end());

    // TODO: initial m_text_bounds size is wrong. images sizes are known but not used
    m_text_bounds.setSize(m_size);
}

void CDiagramObject::update_rel_position(QPoint * relative_tl)
{
    if (!relative_tl)
    {
        relative_tl = m_ladder_relative_tl;
    }

    m_rect = QRect({relative_tl->x() + m_rel_x, relative_tl->y() + m_rel_y}, m_size);
    m_image = QImage({2, m_rect.height()}, QImage::Format_ARGB32);
    m_image.fill(m_color_curr);

    int tp_w = m_type_name.width();
    int ins_nw = m_instance_name.width();

    m_type_name.set_pos({m_rect.left() + (m_rect.width()/2 - tp_w / 2), m_rect.top() + 15});
    m_instance_name.set_pos({m_rect.left() + (m_rect.width() / 2 - ins_nw / 2), m_rect.top() - 5});

    m_base_shift = m_rect.topLeft();


    //locate_pins();
    for (auto &pin : *m_pins)
    {
        pin->update_position();
    }

    update_bound_rect();
}

QRect CDiagramObject::bound_text_rect() const
{
    return m_text_bounds;
}

QImage CDiagramObject::bound_image() const
{
    return m_bound_img;
}

void CDiagramObject::draw_bound_rect()
{
    m_bound_img = QImage(m_text_bounds.size(), QImage::Format_ARGB32);
    m_bound_img.fill(QColor(255,255,255,0));

    QPainter painter(&m_bound_img);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::blue, 1));

    painter.drawLine(QPointF(0, 0),
                     QPointF(m_bound_img.width(), 0));
    painter.drawLine(QPointF(m_bound_img.width(), 0),
                     QPointF(m_bound_img.width(), m_bound_img.height()));
    painter.drawLine(QPointF(m_bound_img.width(), m_bound_img.height()),
                     QPointF(0, m_bound_img.height()));
    painter.drawLine(QPointF(0, m_bound_img.height()),
                     QPointF(0, 0));
}

void CDiagramObject::set_selected(const bool &selected)
{
    m_is_selected = selected;

    m_color_curr = m_is_selected ? m_color_sel : m_color_norm;

    m_image.fill(m_color_curr);
}

bool CDiagramObject::is_selected() const
{
    return m_is_selected;
}

QImage CDiagramObject::drag_image(const bool &is_transparent)
{
    int diff = m_rect.left() - m_text_bounds.left();

    QPoint point(-m_rel_x + diff,0);
    update_rel_position(&point);

    QImage image;

    QRect rect;
    rect.setRect(0, 0, m_text_bounds.width(), m_text_bounds.height() + 40);
    image = QImage(rect.size(), QImage::Format_ARGB32);

    int alpha = is_transparent ? 0 : 127;

    image.fill({255,255,255,alpha});

    QPainter painter;
    painter.begin(&image);

    painter.drawImage(*this->rect(), *this->image());
    for (auto &txt : *this->texts())
    {
        painter.drawText(txt->pos(), txt->text());
    }

    for (auto &cap : *this->m_pins)
    {
        painter.drawImage(*cap->rect(), *cap->image());
        for (auto &txt : *cap->texts())
        {
            painter.drawText(txt->pos(), txt->text());
        }
    }

    painter.end();

    image = image.scaled(rect.width()/2, rect.height()/2);
    return image;
}

uint64_t CDiagramObject::local_id() const
{
    return m_block->local_id();
}

void CDiagramObject::set_ladders_relative_top_left(CLadder *ladder, const QPoint & rtl_shift)
{
    if (m_parent != ladder)
    {
        m_block->set_global_id(QString::number(m_parent->number() - 1));
    }

    m_parent = ladder;
    m_ladder_relative_tl = m_parent->real_top_left();
    m_base_shift = rtl_shift;
    m_rel_x = rtl_shift.x();
    m_rel_y = rtl_shift.y();

    update_rel_position();
    update_bound_rect();
    int b_width = m_text_bounds.width();

    m_text_bounds.setRect(m_rect.x() - m_text_bound_shift, m_rect.top(), b_width, m_rect.height());
    m_graph_bounds.setRect(m_rect.x() - m_graph_bound_shift, m_rect.top(), m_graph_bounds.width(), m_rect.height());
}

void CDiagramObject::update_position()
{
    update_rel_position();

    for (auto &pin : *m_pins)
    {
        pin->update_position();
    }

    update_bound_rect();
    int b_width = m_text_bounds.width();

    m_text_bounds.setRect(m_rect.x() - m_text_bound_shift, m_rect.top(), b_width, m_rect.height());
    m_graph_bounds.setRect(m_rect.x() - m_graph_bound_shift, m_rect.top(), m_graph_bounds.width(), m_rect.height());
}

void CDiagramObject::locate_pins()
{
    int rel_in_y = TOP_SHIFT;
    int rel_out_y = TOP_SHIFT;

    for (auto &pin : *m_pins)
    {
        if (pin->direction() == EPinDirection::PD_INPUT)
        {
            pin->set_rel_position({0, rel_in_y});
            rel_in_y += PIN_SHIFT;
        }

        else
        {
            pin->set_rel_position({m_rect.width(), rel_out_y});
            rel_out_y += PIN_SHIFT;
        }
    }
}

std::vector<std::pair<QRect, QImage>> *CDiagramObject::highlights()
{
    return m_highlights;
}

bool CDiagramObject::switch_highlights(const QPoint &pos)
{
    m_highlights->clear();

    bool found = false;

    if (m_rect.contains(pos))
    {
        QRect rect = m_text_bounds;
        QImage image = QImage(1, rect.height(), QImage::Format_ARGB32);
        image.fill(QColor(205,247,210, 127));
        m_highlights->emplace_back(rect, image);
        found = true;
    }

    return found;
}

void CDiagramObject::update_bound_rect()
{
    int outer_left = 0;
    int outer_right = 0;
    int outer_left_gr = 0;
    int outer_right_max = 0;
    int inp_w, out_w ;



    for (auto &in : *m_inputs)
    {
        if (in->opposite_pin())
        {
            if (in->opposite_pin()->parent()->parent() != m_parent)
            {
                in->set_opposite_name(true);
            }
            else
            {
                outer_left_gr += 1;
                in->set_opposite_name(false);
            }
        }

        inp_w = in->outer_text_width() + in->image()->width() + 3;

        if (inp_w > outer_left)
        {
            outer_left = inp_w;
        }
    }

    outer_left_gr = outer_left + (outer_left_gr * def_lines_diff) + def_bound_dist;

    for (auto &out : *m_outputs)
    {
        out_w = out->outer_text_width() + out->image()->width() + 3;
        if (out_w > outer_right)
        {
            outer_right = out_w;
        }

        if (!out->opposites()->empty())
        {
            if (out->opposites()->size() > outer_right_max)
            {
                outer_right_max = (int)out->opposites()->size();
            }
        }
    }

    outer_right_max = outer_right + def_bound_dist + outer_right_max * def_lines_diff;

    int width = (m_rect.right() + outer_right) - (m_rect.left()-outer_left);
    int graph_width = (m_rect.right() + outer_right_max) - (m_rect.left() - outer_left_gr);
    m_text_bounds.setSize({width, m_rect.height()});
    m_graph_bounds.setSize({graph_width, m_rect.height()});

    m_text_bound_shift = outer_left;
    m_graph_bound_shift = outer_left_gr;
    //draw_bound_rect();
}

QString CDiagramObject::instance_name() const
{
    return m_instance_name.text();
}

QString CDiagramObject::type_name() const
{
    return m_type_name.text();
}

CLadder *CDiagramObject::parent()
{
    return m_parent;
}

CBlock *CDiagramObject::block()
{
    update_block_data();
    return m_block;
}

void CDiagramObject::update_block_data()
{

}

CObjectsText *CDiagramObject::inst_text()
{
    return &m_instance_name;
}

EDefinedDataTypes CDiagramObject::type() const
{
    return get_type_from_string(m_type_name.text().toStdString());
}

void CDiagramObject::set_instance_name(const QString &name)
{
    m_instance_name.set_text(name);
    m_block->set_instance_name(name);
}

std::vector<CConnectorPin *> *CDiagramObject::outputs()
{
    return m_outputs;
}

std::vector<CConnectorPin *> *CDiagramObject::inputs()
{
    return m_inputs;
}

QRect CDiagramObject::bound_graph_rect() const
{
    return m_graph_bounds;
}



