//
// Created by artem on 10/29/24.
//

#include "CConnectorPin.h"

CConnectorPin::CConnectorPin(CBlockVar *var, const EPinDirection &direction, QPoint * rel_tl)
{
    m_direction = direction;
    m_variable = var;
    m_rel_obj_tp = rel_tl;

    m_formal_param.set_text(m_variable->formal_parameter());

    // TODO: исправить и привести сюда этот атрибут
    set_negated(m_is_negated);

    if (direction == EPinDirection::PD_INPUT)
    {
        auto in = m_variable->point_in();
        m_expression.set_text(in->expression());
    }
    else
    {
        auto out = m_variable->point_out();
        m_expression.set_text(out->expression());
    }

    m_texts.push_back(&m_formal_param);
    m_texts.push_back(&m_expression);
}

CConnectorPin::~CConnectorPin()
= default;

void CConnectorPin::set_object_top_left(QPoint *top_left, const QPoint &rel_position)
{
    m_rel_obj_tp = top_left;
    m_pos = rel_position;
    update_position();
}

QImage *CConnectorPin::image()
{
    return &m_image;
}

QRect *CConnectorPin::rect()
{
    return &m_rect;
}

QPoint *CConnectorPin::position()
{
    return &m_pos;
}

void CConnectorPin::set_rel_position(const QPoint &pos)
{
    m_pos = pos;
    update_position();
}

void CConnectorPin::update_position()
{
    int w = m_formal_param.width();
    QSize img_sz = m_image.size();
    QPoint img_pos;
    int img_exp_x, img_formal_x;

    /// locate image and set rect
    if (m_direction == EPinDirection::PD_INPUT)
    {
        img_pos = QPoint(m_rel_obj_tp->x() + (m_pos.x() - img_sz.width()),
                         m_rel_obj_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_rel_obj_tp->x() + m_pos.x() - m_expression.width() - m_image.width() - 2;
        img_formal_x = m_rel_obj_tp->x() + m_pos.x() + 3;
    }
    else
    {
        img_pos = QPoint(m_rel_obj_tp->x() + (m_pos.x()),
                         m_rel_obj_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_rel_obj_tp->x() + m_pos.x() + m_image.width() + 3;
        img_formal_x = m_rel_obj_tp->x() + m_pos.x() - m_formal_param.width() - 3;
    }

    m_rect = QRect(img_pos, img_sz);

    /// locate texts
    m_expression.set_pos({img_exp_x, img_pos.y() + 12});
    int img_formal_y = img_pos.y() + 10;// - m_formal_param.height() / 2;
    m_formal_param.set_pos({img_formal_x, img_formal_y});
}

std::vector<CObjectsText*> *CConnectorPin::texts()
{
    return &m_texts;
}

uint16_t CConnectorPin::inner_text_width() const
{
    return m_formal_param.width();
}

bool CConnectorPin::is_negated() const
{
    return m_is_negated;
}

void CConnectorPin::set_negated(const bool &negated)
{
    m_is_negated = negated;

    if (negated)
    {
        m_image = m_direction == EPinDirection::PD_INPUT ? QImage(":/codesys/images/codesys/pin_input_inv.png")
                : QImage(":/codesys/images/codesys/pin_output_inv.png");
    }
    else
    {
        m_image = m_direction == EPinDirection::PD_INPUT ? QImage(":/codesys/images/codesys/pin_input_norm.png")
                : QImage(":/codesys/images/codesys/pin_output_norm.png");
    }
}

EPinDirection CConnectorPin::direction() const
{
    return m_direction;
}

uint64_t CConnectorPin::ref_local_id() const
{
    return m_variable->point_in()->connections()->isEmpty()? 0
            : m_variable->point_in()->connections()->front()->ref_local_id();
}

void CConnectorPin::set_in_variable(CInVariable *variable)
{
    m_input_data = variable;
    set_negated(m_input_data->negated());
    m_expression.set_text(m_input_data->expression()->expression());
}

QString CConnectorPin::formal_param() const
{
    return m_formal_param.text();
}

void CConnectorPin::set_formal_param(const QString &formal)
{
    /*QString str;
    if (!m_variable->point_in()->connections()->empty())
    {
        str = formal + "." + m_variable->point_in()->connections()->front()->formal_parameter();
    }*/

    m_expression.set_text(formal);
}

uint16_t CConnectorPin::outer_text_width() const
{
    return m_expression.width();
}

CBlockVar *CConnectorPin::block_var()
{
    return m_variable;
}

void CConnectorPin::set_out_variable(COutVariable *out)
{
    m_out_variable = out;
    m_expression.set_text(out->expression()->expression());
}

void CConnectorPin::set_selected(const bool &selected)
{

}


