//
// Created by artem on 12/6/24.
//

#include <QFontMetrics>
#include "CPin.h"
#include "CDiagramObject.h"
#include "CPinIn.h"
#include "../../resources/colors.h"

CPin::CPin(CDiagramObject *parent, CBlockVar *var, QPoint * parent_tl)
{
    m_parent             = parent;
    m_block_variable     = var;
    m_relative_parent_tp = parent_tl;

    m_texts = new std::vector<CObjectsText*>();
    m_outer_texts = new std::vector<CObjectsText*>();
    m_outs_graphics = new std::vector<CObjectsText*>();
    m_pin_name = new CObjectsText();
    m_outer_text = new CObjectsText();

    m_current_ladder     = m_parent->parent();

    QString formal_param = m_block_variable->formal_parameter() + ":"+var->derived_type();

    m_pin_name->set_text(formal_param);

    auto iface_var = m_block_variable->get_iface_variable();
    if (!iface_var->is_empty())
    {
        m_outer_text->set_text(iface_var->name());
        m_is_connected = true;
    }

    if (!m_block_variable->constant_value().isEmpty())
    {
        m_outer_text->set_text(m_block_variable->constant_value());
        m_is_connected = true;
    }

    CDiagramColors colors;

    m_pin_name->set_color(colors.base_colors().diag_text_alternate);
    m_outer_text->set_color(colors.base_colors().diag_text_def);

    m_texts->push_back(m_pin_name);
    m_texts->push_back(m_outer_text);
}

CPin::~CPin()
{
    for (auto &item : *m_texts)
        delete item;
    delete m_texts;

    for (auto &item : *m_outer_texts)
        delete item;
    delete m_outer_texts;

    for (auto &item : *m_outs_graphics)
        delete item;
    delete m_outs_graphics;
}

CDiagramObject *CPin::parent()
{
    return m_parent;
}

QImage *CPin::image()
{
    return &m_draw_image;
}

QRect *CPin::rect()
{
    return &m_rect;
}

std::vector<CObjectsText *> *CPin::texts()
{
    return m_texts;
}

QPoint *CPin::position()
{
    return &m_pos;
}

void CPin::set_rel_position(const QPoint &pos)
{
    m_pos = pos;
    update_position();
}

void CPin::update_position()
{
    QSize img_sz = m_draw_image.size();
    QPoint img_pos;
    int img_exp_x, img_formal_x;

    /// locate image and set rect
    if (m_direction == EPinDirection::PD_INPUT)
    {
        img_pos = QPoint(m_relative_parent_tp->x() + (m_pos.x() - img_sz.width()),
                         m_relative_parent_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_relative_parent_tp->x() + m_pos.x() - m_outer_text->width() - m_draw_image.width() - 2;
        img_formal_x = m_relative_parent_tp->x() + m_pos.x() + 3;
    }
    else
    {
        img_pos = QPoint(m_relative_parent_tp->x() + (m_pos.x()),
                         m_relative_parent_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_relative_parent_tp->x() + m_pos.x() + m_draw_image.width() + 3;
        img_formal_x = m_relative_parent_tp->x() + m_pos.x() - m_pin_name->width() - 3;
    }

    m_rect = QRect(img_pos, img_sz);

    /// locate texts
    m_outer_text->set_pos({img_exp_x, img_pos.y() + 12});
    int img_formal_y = img_pos.y() + 10;// - m_pin_name.height() / 2;
    m_pin_name->set_pos({img_formal_x, img_formal_y});

    resort_outers();
}

bool CPin::is_selected() const
{
    return m_is_selected;
}

void CPin::set_selected(const bool &selected)
{
    m_is_selected = selected;
    m_draw_image = selected ? m_img_selected : m_img_norm;
}

bool CPin::is_error_state() const
{
    return m_is_error;
}

void CPin::set_error(const bool &is_error)
{
    m_is_error = is_error;
    m_draw_image = is_error ? m_img_error : m_img_norm;
}

EPinDirection CPin::direction() const
{
    return m_direction;
}

uint16_t CPin::pin_name_width() const
{
    return m_pin_name->width();
}

uint16_t CPin::outer_text_width() const
{
    return m_outer_text->width();
}

QString CPin::pin_name() const
{
    return m_block_variable->formal_parameter();
}

void CPin::set_pin_name(const QString &formal)
{
    m_block_variable->set_formal_param(formal);
    m_pin_name->set_text(formal + ":" + m_block_variable->derived_type());
}

QString CPin::type_name() const
{
    return !m_block_variable->derived_type().isEmpty() ? m_block_variable->derived_type() :
                                                         base_types_names[m_block_variable->type()];
}

EDefinedDataTypes CPin::type() const
{
    return m_block_variable->type();
}

void CPin::set_type(const QString &type)
{
    m_block_variable->set_type(type);
}

CPinIn *CPin::input()
{
    if (m_direction == PD_INPUT)
        return dynamic_cast<CPinIn*>(this);
    return nullptr;
}

CPinOut *CPin::output()
{
    return dynamic_cast<CPinOut*>(this);
}

void CPin::saturate()
{
    m_img_selected = m_img_norm;
    for (auto x = 0; x < m_img_selected.width(); x++)
    {
        for (auto y = 0; y < m_img_selected.height(); y++)
        {
            QColor color = m_img_selected.pixelColor(x, y);
            if (color.alpha() == 0)
            {
                continue;
            }

            color.setHslF(0.7,
                          1.0,
                          color.lightnessF());

            m_img_selected.setPixelColor(x, y, color);
        }
    }
}

bool CPin::is_pin_at_pos(const QPoint &pos) const
{
    return m_bound_rect.contains(pos) || m_rect.contains(pos);
}

bool CPin::is_connected() const
{
    return m_is_connected;
}

CBlockVar *CPin::block_variable()
{
    return m_block_variable;
}

void CPin::resort_outers()
{
    QPoint top_left = m_rect.bottomLeft();
    top_left.setX(top_left.x() + 2);

    int height = m_pin_name->height();
    int Y = top_left.y();
    int h_in = 0, h_out = 0, h;
    int w = 0;

    for (auto &txt_block : *m_outer_texts)
    {
        h_in += height + OUTER_SHIFT;
        Y += height + OUTER_SHIFT;
        txt_block->set_pos({top_left.x(), Y});

        if (txt_block->width() > w)
        {
            w = txt_block->width();
        }
    }

    for (auto txt_block : *m_outs_graphics)
    {
        h_out += height + OUTER_SHIFT;
        Y += height + OUTER_SHIFT;
        txt_block->set_pos({top_left.x(), Y});
        if (txt_block->width() > w)
        {
            w = txt_block->width();
        }
    }

    h = h_in + h_out;// ? h_in : h_out;

    h += m_rect.height();

    m_out_texts_size = {w, h};

    m_texts->clear();


    m_texts->push_back(m_pin_name);
    m_texts->push_back(m_outer_text);
    m_texts->insert(m_texts->end(), m_outer_texts->begin(), m_outer_texts->end());
    m_texts->insert(m_texts->end(), m_outs_graphics->begin(), m_outs_graphics->end());

}

QString CPin::make_pin_text(CPin *pin)
{
    QString text;

    QString obj_name = pin->parent()->instance_name().isEmpty() ?
                       pin->parent()->type_name() :
                       pin->parent()->instance_name();
    text = obj_name + "." + pin->block_variable()->formal_parameter();

    return text;
}

