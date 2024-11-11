//
// Created by artem on 10/29/24.
//

#include "CConnectorPin.h"

CConnectorPin::CConnectorPin(CBlockVar *var, CDiagramObject* parent, const EPinDirection &direction, QPoint * obj_tl)
{
    if (!parent || !var)
    {
        throw std::runtime_error("can't create `CConnectorPin::CConnectorPin(...)` with parent or var as nullptr");
    }

    m_parent = parent;

    m_direction = direction;
    m_variable = var;
    m_rel_obj_tp = obj_tl;

    m_formal_param.set_text(m_variable->formal_parameter());

    m_is_negated = var->is_negated();
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

    set_selected(false);
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
        m_norm_img = m_direction == EPinDirection::PD_INPUT ? QImage(":/codesys/images/codesys/pin_input_inv.png")
                : QImage(":/codesys/images/codesys/pin_output_inv.png");
    }
    else
    {
        m_norm_img = m_direction == EPinDirection::PD_INPUT ? QImage(":/codesys/images/codesys/pin_input_norm.png")
                : QImage(":/codesys/images/codesys/pin_output_norm.png");
    }

    saturate_image();
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
    m_image = selected ? m_selected_img : m_norm_img;
    m_is_selected = selected;
}

void CConnectorPin::saturate_image()
{
    m_selected_img = QImage(m_norm_img);
    for (auto x = 0; x < m_selected_img.width(); x++)
    {
        for (auto y = 0; y <m_selected_img.height(); y++)
        {
            QColor color = m_selected_img.pixelColor(x, y);
            color.setHslF(0.7,
                          1.0,
                          color.lightnessF());
            m_selected_img.setPixelColor(x, y, color);
        }
    }
}

bool CConnectorPin::is_selected() const
{
    return m_is_selected;
}

EEdge CConnectorPin::edge_modifier() const
{
    return m_edge_modifier;
}

void CConnectorPin::set_edge_modifier(const EEdge &edge)
{
    m_edge_modifier = edge;
    m_out_variable->set_edge(edge);
}

EDefinedDataTypes CConnectorPin::type() const
{
    return DDT_UINT;
}


