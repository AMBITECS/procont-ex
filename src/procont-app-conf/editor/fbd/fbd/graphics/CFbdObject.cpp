//
// Created by artem on 10/29/24.
//

#include <QPainter>
#include "CFbdObject.h"
#include "CFbdLadder.h"
#include "editor/fbd/resources/colors.h"
#include "editor/fbd/fbd/editors/CFilter.h"

CFbdObject::CFbdObject(CFbdLadder *ladder, CBlock *block) //QPoint *ladder_top_left
{
    m_block = block;
    m_block->set_global_id(QString::number(ladder->number()));

    m_ladder_relative_tl = ladder->real_top_left();
    m_parent = ladder;

    CDiagramColors colors;
    m_type_name.set_color(colors.base_colors().diag_text_alternate);
    m_instance_name.set_color(colors.base_colors().diag_text_def);

    m_color_norm = colors.ladder_colors().normal.block;//{226, 234, 247};
    m_color_sel = colors.ladder_colors().selected.block;//{80,176,243};
    m_color_curr = m_color_norm;

    m_texts.push_back(&m_type_name);
    m_texts.push_back(&m_instance_name);

    m_inputs = new std::vector<CPinIn*>();
    m_outputs = new std::vector<CPinOut*>();
    m_pins = new std::vector<CPin*>();
    m_highlights = new std::vector<std::pair<QRect, QImage>>();

    m_type_name.set_text(m_block->type_name());
    m_instance_name.set_text(m_block->instance_name());

    define_size();

    locate_pins();

    m_rect.setSize(m_size);
    m_primary_type = m_inputs->front()->type();

    m_pin_types = define_is_concrete_types(m_inputs->front()->type());
}

CFbdObject::~CFbdObject()
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

QRect *CFbdObject::rect()
{
    return &m_rect;
}

QImage *CFbdObject::image()
{
    return &m_image;
}

std::vector<CPin *> *CFbdObject::pins()
{
    return m_pins;
}

std::vector<CObjectText *> *CFbdObject::texts()
{
    return &m_texts;
}

void CFbdObject::define_size()
{
    if (!m_pins->empty())
    {
        return;
    }

    int def_width = m_type_name.width() > m_instance_name.width() ? m_type_name.width() : m_instance_name.width();
    int inner_left_max = 0;
    int inner_right_max = 0;
    int inner = 0;
    int h_in = 0, h_out = 0, h;

    def_width += 2 * NAME_SHIFT;

    for (auto &inout : *m_block->in_out_variables())
    {
        auto pin_i = new CPinIn(this, inout, &m_base_shift);
        auto pin_o = new CPinOut(this, inout, &m_base_shift);
        m_inputs->push_back(pin_i);
        m_outputs->push_back(pin_o);
    }

    for (auto &in : *m_block->input_variables())
    {
        auto in_pin = new CPinIn(this, in, &m_base_shift);
        m_inputs->push_back(in_pin);
    }

    for (auto &out : *m_block->output_variables())
    {
        auto pin_out = new CPinOut(this, out, &m_base_shift);
        m_outputs->push_back(pin_out);
    }


    for (auto *&in : *m_inputs)
    {
        inner = in->pin_name_width() + 3;
        if (inner > inner_left_max)
        {
            inner_left_max = inner;
        }

        h_in += in->rect()->height() + PIN_SHIFT;
    }

    for (auto &outp : *m_outputs)
    {
        inner = outp->pin_name_width() + 3;
        if (inner > inner_right_max)
        {
            inner_right_max = inner;
        }
        int height = outp->outer_height() > PIN_SHIFT ? outp->outer_height() : PIN_SHIFT;
        h_out += height;
    }

    h = h_in > h_out ? h_in : h_out;

    def_width = def_width > (inner_left_max + inner_right_max + 20) ? def_width
                : inner_left_max + inner_right_max + 20;

    m_size.setWidth(def_width);
    m_size.setHeight(TOP_SHIFT + (h) + BOTTOM_SHIFT);
    m_rect.setSize(m_size);

    m_pins->clear();
    m_pins->insert(m_pins->end(), m_inputs->begin(), m_inputs->end());
    m_pins->insert(m_pins->end(), m_outputs->begin(), m_outputs->end());

    // TODO: initial m_text_bounds size is wrong. images sizes are known but not used
    m_text_bounds.setSize(m_size);
}

void CFbdObject::update_rel_position(QPoint * relative_tl)
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

    for (auto &pin : *m_pins)
    {
        pin->update_position();
    }

    update_bound_rect();
}

QRect CFbdObject::bound_text_rect() const
{
    return m_text_bounds;
}

QImage CFbdObject::bound_image() const
{
    return m_bound_img;
}

//void CDiagramObject::draw_bound_rect()
//{
//    m_bound_img = QImage(m_text_bounds.size(), QImage::Format_ARGB32);
//    m_bound_img.fill(QColor(255,255,255,0));
//
//    QPainter painter(&m_bound_img);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(QPen(Qt::blue, 1));
//
//    painter.drawLine(QPointF(0, 0),
//                     QPointF(m_bound_img.width(), 0));
//    painter.drawLine(QPointF(m_bound_img.width(), 0),
//                     QPointF(m_bound_img.width(), m_bound_img.height()));
//    painter.drawLine(QPointF(m_bound_img.width(), m_bound_img.height()),
//                     QPointF(0, m_bound_img.height()));
//    painter.drawLine(QPointF(0, m_bound_img.height()),
//                     QPointF(0, 0));
//}

void CFbdObject::set_selected(const bool &selected)
{
    m_is_selected = selected;

    m_color_curr = m_is_selected ? m_color_sel : m_color_norm;

    m_image.fill(m_color_curr);
}

bool CFbdObject::is_selected() const
{
    return m_is_selected;
}

QImage CFbdObject::drag_image(const bool &is_transparent)
{
    int diff = m_rect.left() - m_text_bounds.left();

    QPoint point(-m_rel_x + diff,0);
    QImage image;
    QRect rect;

    update_rel_position(&point);

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

uint64_t CFbdObject::local_id() const
{
    return m_block->local_id();
}

void CFbdObject::set_ladders_relative_top_left(CFbdLadder *ladder, const QPoint & rtl_shift)
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

void CFbdObject::update_position()
{
    locate_pins();

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

void CFbdObject::locate_pins()
{
    int rel_in_y = TOP_SHIFT;
    int rel_out_y = TOP_SHIFT;
    int h, w_in = 0, w_out = 0, w;

    for (auto &pin : *m_pins)
    {
        if (pin->direction() == EPinDirection::PD_INPUT)
        {
            pin->set_rel_position({0, rel_in_y});
            rel_in_y += PIN_SHIFT;

            if(pin->pin_name_width() > w_in)
                w_in = pin->pin_name_width();
        }

        else
        {
            pin->set_rel_position({m_rect.width(), rel_out_y});

            int height = pin->output()->outer_height() > PIN_SHIFT ? pin->output()->outer_height() : PIN_SHIFT;
            rel_out_y += height;

            if (pin->pin_name_width() > w_out)
                w_out = pin->pin_name_width();
        }
    }

    h = rel_in_y > rel_out_y ? rel_in_y : rel_out_y;
    w = w_in + w_out + BOTTOM_SHIFT;

    h = m_rect.height() > h ? m_rect.height() : h;
    w = m_rect.width() > w ? m_rect.width() : w;

    //m_rect.setHeight(h);
    m_rect = QRect(m_rect.topLeft(), QSize(w, h));
    m_size = QSize(w, h);
    m_text_bounds.setHeight(h);
    m_graph_bounds.setHeight(h);
}

std::vector<std::pair<QRect, QImage>> *CFbdObject::highlights()
{
    return m_highlights;
}

bool CFbdObject::switch_highlights(const QPoint &pos)
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

void CFbdObject::update_bound_rect()
{
    int outer_left = 0;
    int outer_right = 0;
    int outer_left_gr = 0;
    int outer_right_max = 0;
    int inp_w, out_w, out_t;

    for (auto &in : *m_inputs)
    {
        inp_w = in->outer_text_width() + in->image()->width() + 3;

        if (inp_w > outer_left)
        {
            outer_left = inp_w;
        }
    }

    outer_left_gr = outer_left + (outer_left_gr * def_lines_diff) + def_bound_dist;

    for (auto &out : *m_outputs)
    {
        out_t = out->outer_text_width() + out->image()->width() + 3;
        out_w = out->outer_width() + 3;
        out_w = out_t > out_w ? out_t : out_w;

        if (out_w > outer_right)
        {
            outer_right = out_w;
        }

        if (!out->graphic_connections()->empty())
        {
            if (out->graphic_connections()->size() > outer_right_max)
            {
                outer_right_max = (int)out->graphic_connections()->size();
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
}

QString CFbdObject::instance_name() const
{
    return m_instance_name.text();
}

QString CFbdObject::type_name() const
{
    return m_type_name.text();
}

CFbdLadder *CFbdObject::parent()
{
    return m_parent;
}

CBlock *CFbdObject::block()
{
    update_block_data();
    return m_block;
}

void CFbdObject::update_block_data()
{

}

CObjectText *CFbdObject::inst_text()
{
    return &m_instance_name;
}

EDefinedDataTypes CFbdObject::type() const
{
    return get_type_from_string(m_type_name.text().toStdString());
}

void CFbdObject::set_instance_name(const QString &name)
{
    m_instance_name.set_text(name);
    m_block->set_instance_name(name);

    for (auto &pin : *m_pins)
    {
        if (pin->direction() == PD_INPUT)
        {
            if (pin->input()->opposite())
            {
                pin->input()->opposite()->load_project_connect(pin);
            }
        }
        else
        {
            for (auto &opp : *pin->output()->graphic_connections())
            {
                opp->load_project_connect_pin(pin->output());
            }
        }
    }
}

std::vector<CPinOut*> *CFbdObject::outputs()
{
    return m_outputs;
}

std::vector<CPinIn *> *CFbdObject::inputs()
{
    return m_inputs;
}

QRect CFbdObject::bound_graph_rect() const
{
    return m_graph_bounds;
}

CPinOut *CFbdObject::get_output_by_name(const QString &formal)
{
    std::string form = formal.toStdString();
    CFilter::capitalize_word(form);
    std::string pin_name;

    for (auto &out : *m_outputs)
    {
        pin_name = out->block_variable()->formal_parameter().toStdString();
        CFilter::capitalize_word(pin_name);

        if (pin_name == form)
        {
            return out;
        }
    }
    return nullptr;
}

void CFbdObject::refresh_graphic_connections()
{
    for (auto &in : *m_inputs)
    {
        if (in->opposite())
        {
            in->update_graphic_text();
        }
    }

    for (auto &out : *m_outputs)
    {
        if (!out->graphic_connections()->empty())
        {
            out->refresh_connections();
        }
    }

    update_bound_rect();
}

void CFbdObject::im_connected(const QString &type, CPin *pin)
{
    /// решил не приводить типы пинов ко всяким ANY_XXX от ANY, т.к. в одном блоке может быть и ANY и BOOL и INT.
    /// Да и ADD(+) INT и REAL тоже не лишено логики. Можно поразмышлять на счёт выходов... Позже.
    return;


    auto alien = get_type_from_string(type.toStdString());
    auto alien_type = define_is_concrete_types(alien);

    /// если чужак менее конкретен чем мы, то выходим
    if (m_pin_types >= alien_type || m_set_type_done)
    {
        return;
    }

    /// похоже наоборот
    if (alien_type == EPT_ANY_CON)
    {
        set_all_pins_any_concrete(alien);
        return;
    }

    /// попробуем привести конкретику к любому ANY_INT/ANY_REAL/ANY_BOOL и сделаем таким всё
    if (is_convertible_to_any_num(alien))
    {
        if (is_convertible_to_bool(alien))
        {
            set_all_pins_any_concrete(DDT_ANY_BIT);
        }

        if (is_convertible_to_anyint(alien))
        {
            set_all_pins_any_concrete(DDT_ANY_INT);
        }

        if(is_convertible_to_anyfloat(alien))
        {
            set_all_pins_any_concrete(DDT_ANY_REAL);
        }

        return;
    }

    /// тут что-то термоядерное. Садим везде конкретику
    for (auto &item : *m_pins)
    {
        item->set_type(pin->type_name());
    }
    m_set_type_done = true;
}

EPinTypes CFbdObject::define_is_concrete_types(const EDefinedDataTypes &type)
{
    if (type == DDT_ANY ||
        type == DDT_ANY_NUM ||
        type == DDT_UNDEF)
    {
        return EPT_ANY;
    }

    if (type == DDT_ANY_INT  ||
        type == DDT_ANY_REAL ||
        type == DDT_ANY_BIT  ||
        type == DDT_ANY_UINT)
    {
        return EPT_ANY_CON;
    }

    return EPT_CONCRETE;
}

void CFbdObject::im_disconnected(CPin *pin)
{
    bool connected = false;

    for (auto &item : *m_pins)
    {
        if (item->is_connected())
        {
            connected = true;
        }
    }
    if (connected)
    {
        return;
    }

    m_set_type_done = false;

    set_all_pins_any_concrete(m_primary_type);
}

void CFbdObject::set_all_pins_any_concrete(const EDefinedDataTypes &types)
{
    for (auto &pin : *m_pins)
    {
        auto type_lvl = define_is_concrete_types(pin->type());

        if (type_lvl != EPT_ANY)
        {
            continue;
        }

        pin->set_type(base_types_names[types]);
    }
    m_set_type_done = true;
}



