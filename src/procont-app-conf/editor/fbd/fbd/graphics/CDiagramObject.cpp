//
// Created by artem on 10/29/24.
//

#include <QPainter>
#include "CDiagramObject.h"

CDiagramObject::CDiagramObject(QPoint *ladder_top_left, CBlock *block)
{
    m_block = block;
    m_ladder_relative_tl = ladder_top_left;

    m_texts.push_back(&m_type_name);
    m_texts.push_back(&m_var_name);

    m_inputs = new std::vector<CConnectorPin*>();
    m_outputs = new std::vector<CConnectorPin*>();
    m_pins = new std::vector<CConnectorPin*>();
    m_highlights = new std::vector<std::pair<QRect, QImage>>();

    build_block();
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

void CDiagramObject::set_relative_pos(const int &x, const int &y)
{
    m_rel_x = x;
    m_rel_y = y;


    //define_size();
    update_rel_position();
    define_bound();
}

void CDiagramObject::build_block()
{

    m_type_name.set_text(m_block->type_name());
    m_var_name.set_text(m_block->instance_name());

    define_size();

    m_rect.setSize(m_size);
}

void CDiagramObject::define_size()
{
    int in_max_size = 0;
    int out_max_size = 0;
    int outer_text_max = 0;

    if (!m_pins->empty())
    {
        return;
    }

    int def_width = m_type_name.width() > m_var_name.width() ? m_type_name.width() : m_var_name.width();
    def_width += 2 * NAME_SHIFT;

    for (auto &inout : *m_block->in_out_variables())
    {
        auto pin_io = new CConnectorPin(inout, PD_INPUT, &m_top_left);
        m_inputs->push_back(pin_io);
        m_outputs->push_back(pin_io);

        if (pin_io->inner_text_width() > in_max_size)
        {
            in_max_size = pin_io->inner_text_width();
        }
        if (pin_io->rect()->width() > out_max_size)
        {
            out_max_size = pin_io->inner_text_width();
        }
    }

    for (auto &in : *m_block->input_variables())
    {
        auto in_pin = new CConnectorPin(in, PD_INPUT, &m_top_left);
        m_inputs->push_back(in_pin);

        if (in_pin->inner_text_width() > in_max_size)
        {
            in_max_size = in_pin->inner_text_width();
        }
    }

    for (auto &out : *m_block->output_variables())
    {
        auto pin_out = new CConnectorPin(out, PD_OUTPUT, &m_top_left);
        m_outputs->push_back(pin_out);

        if (pin_out->inner_text_width() > out_max_size)
        {
            out_max_size = pin_out->inner_text_width();
        }
    }

    size_t max_pins = m_inputs->size() > m_outputs->size() ? m_inputs->size() : m_outputs->size();

    def_width = def_width > (in_max_size + out_max_size + 20) ? def_width : in_max_size + out_max_size + 20;

    m_size.setWidth(def_width);
    m_size.setHeight(TOP_SHIFT + (max_pins * PIN_SHIFT) + BOTTOM_SHIFT);

    m_pins->clear();
    m_pins->insert(m_pins->end(), m_inputs->begin(), m_inputs->end());
    m_pins->insert(m_pins->end(), m_outputs->begin(), m_outputs->end());
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
    int ins_nw = m_var_name.width();

    m_type_name.set_pos({m_rect.left() + (m_rect.width()/2 - tp_w / 2), m_rect.top() + 15});
    m_var_name.set_pos({m_rect.left() + (m_rect.width()/2 - ins_nw/2), m_rect.top() - 5});

    m_top_left = m_rect.topLeft();

    locate_pins();

    if (relative_tl == m_ladder_relative_tl)
    {
        define_bound();
    }
}

QRect CDiagramObject::bound_rect() const
{
    return m_bounds;
}

void CDiagramObject::define_bound()
{
    int outer_left = 0;
    int outer_right = 0;
    int inp_w, out_w ;

    bool is_outer_l = false;
    bool is_outer_r = false;

    for (auto &in : *m_inputs)
    {
        inp_w = in->outer_text_width() + in->image()->width() + 3;



        if (inp_w > outer_left)
        {
            outer_left = inp_w;
        }
    }

    for (auto &out : *m_outputs)
    {
        out_w = out->outer_text_width() + out->image()->width() + 3;
        if (out_w > outer_right)
        {
            outer_right = out_w;
        }
    }

    int width = (m_rect.right() + outer_right) - (m_rect.left()-outer_left);
    m_bounds.setRect(m_rect.left() - outer_left, m_rect.top(), width, m_rect.height());

    draw_bound_rect();



    // тот случай когда QRect не адекватен
    //m_bounds.setSize({m_size.width() + outer_left + outer_right, m_size.height()});
    //m_bounds.setTopLeft({m_rect.left() - outer_left, m_rel_y});
}

QImage CDiagramObject::bound_image() const
{
    return m_bound_img;
}

void CDiagramObject::draw_bound_rect()
{
    m_bound_img = QImage(m_bounds.size(), QImage::Format_ARGB32);
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

void CDiagramObject::draw_drag_image()
{
    int diff = m_rect.left() - m_bounds.left();
    QPoint point(-m_rel_x + diff,0);
    update_rel_position(&point);

    QRect rect;
    rect.setRect(0,0, m_bounds.width(), m_bounds.height()+40);
    m_drag_image = QImage(rect.size(), QImage::Format_ARGB32);
    m_drag_image.fill({255,255,255,127});

    QPainter painter;
    painter.begin(&m_drag_image);

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

    m_drag_image = m_drag_image.scaled(rect.width()/2, rect.height()/2);
}

QImage CDiagramObject::drag_image() const
{
    return m_drag_image;
}

uint64_t CDiagramObject::local_id() const
{
    return m_block->local_id();
}

void CDiagramObject::set_ladders_top_left(QPoint *ltl, const QPoint & pos)
{
    m_ladder_relative_tl = ltl;
    m_top_left = pos;

    locate_pins();
    update_rel_position();
}

void CDiagramObject::locate_pins()
{
    int rel_y = TOP_SHIFT;

    for (auto &in : *m_inputs)
    {
        in->set_rel_position({0, rel_y});
        rel_y += PIN_SHIFT;
    }

    rel_y = TOP_SHIFT;
    for (auto &out : *m_outputs)
    {
        out->set_rel_position({m_rect.width(), rel_y});
        rel_y += PIN_SHIFT;
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
        QRect rect = m_bounds;
        QImage image = QImage(1, rect.height(), QImage::Format_ARGB32);
        image.fill(QColor(205,247,210, 127));
        m_highlights->emplace_back(rect, image);
        found = true;
    }

    return found;
}



