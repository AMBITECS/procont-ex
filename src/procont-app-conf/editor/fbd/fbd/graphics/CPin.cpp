//
// Created by artem on 12/6/24.
//

#include "CPin.h"
#include "CDiagramObject.h"
#include "CPinIn.h"
#include "../../resources/colors.h"

CPin::CPin(CDiagramObject *parent, CBlockVar *var, QPoint * parent_tl)
{
    m_parent             = parent;
    m_block_variable     = var;
    m_relative_parent_tp = parent_tl;

    if (var->get_iface_variable())
    {
        m_outer_text.set_text(var->get_iface_variable()->name());
    }

    if (!var->constant_value().isEmpty())
    {
        m_outer_text.set_text(var->constant_value());
    }

    CDiagramColors colors;

    m_pin_name.set_color(colors.base_colors().diag_text_alternate);
    m_outer_text.set_color(colors.base_colors().diag_text_def);

    m_texts.push_back(&m_pin_name);
    m_texts.push_back(&m_outer_text);



}

CPin::~CPin()
= default;

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
    return &m_texts;
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
        img_exp_x = m_relative_parent_tp->x() + m_pos.x() - m_outer_text.width() - m_draw_image.width() - 2;
        img_formal_x = m_relative_parent_tp->x() + m_pos.x() + 3;
    }
    else
    {
        img_pos = QPoint(m_relative_parent_tp->x() + (m_pos.x()),
                         m_relative_parent_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_relative_parent_tp->x() + m_pos.x() + m_draw_image.width() + 3;
        img_formal_x = m_relative_parent_tp->x() + m_pos.x() - m_pin_name.width() - 3;
    }

    m_rect = QRect(img_pos, img_sz);

    /// locate texts
    m_outer_text.set_pos({img_exp_x, img_pos.y() + 12});
    int img_formal_y = img_pos.y() + 10;// - m_pin_name.height() / 2;
    m_pin_name.set_pos({img_formal_x, img_formal_y});
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
    return m_pin_name.width();
}

uint16_t CPin::outer_text_width() const
{
    return m_outer_text.width();
}

QString CPin::pin_name() const
{
    return m_pin_name.text();
}

void CPin::set_pin_name(const QString &formal)
{
    m_pin_name.set_text(formal);
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
