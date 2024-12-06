//
// Created by artem on 10/29/24.
//

#include "CConnectorPin.h"
#include "CDiagramObject.h"
#include "editor/fbd/resources/colors.h"

CConnectorPin::CConnectorPin(CBlockVar *var, CDiagramObject* parent, const EPinDirection &direction, QPoint * obj_tl)
{
    if (!parent || !var)
    {
        throw std::runtime_error("can't create `CConnectorPin::CConnectorPin(...)` with parent or var as nullptr");
    }

    m_parent = parent;
    m_out_connections = new std::vector<CConnectorPin*>();

    m_direction = direction;
    m_variable = var;
    m_rel_obj_tp = obj_tl;

    m_type = var->type();
    if (m_type == DDT_DERIVED)
    {
        m_derived_type = var->derived_type();
    }

    m_pin_name.set_text(m_variable->formal_parameter());

    m_is_negated = var->is_negated();
    set_negated(m_is_negated);

    if (direction == EPinDirection::PD_INPUT)
    {
        auto in = m_variable->point_in();
        m_outer_text.set_text(in->expression());
    }
    else
    {
        auto out = m_variable->point_out();
        m_outer_text.set_text(out->expression());
    }

    CDiagramColors colors;
    m_pin_name.set_color(colors.base_colors().diag_text_alternate);
    m_outer_text.set_color(colors.base_colors().diag_text_def);

    m_texts.push_back(&m_pin_name);
    m_texts.push_back(&m_outer_text);

    set_selected(false);
}

CConnectorPin::~CConnectorPin()
{
    delete m_out_connections;
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
        img_exp_x = m_rel_obj_tp->x() + m_pos.x() - m_outer_text.width() - m_image.width() - 2;
        img_formal_x = m_rel_obj_tp->x() + m_pos.x() + 3;
    }
    else
    {
        img_pos = QPoint(m_rel_obj_tp->x() + (m_pos.x()),
                         m_rel_obj_tp->y() + m_pos.y() - (img_sz.height() / 2));
        img_exp_x = m_rel_obj_tp->x() + m_pos.x() + m_image.width() + 3;
        img_formal_x = m_rel_obj_tp->x() + m_pos.x() - m_pin_name.width() - 3;
    }

    m_rect = QRect(img_pos, img_sz);

    /// locate texts
    m_outer_text.set_pos({img_exp_x, img_pos.y() + 12});
    int img_formal_y = img_pos.y() + 10;// - m_pin_name.height() / 2;
    m_pin_name.set_pos({img_formal_x, img_formal_y});
}

std::vector<CObjectsText*> *CConnectorPin::texts()
{
    return &m_texts;
}

uint16_t CConnectorPin::inner_text_width() const
{
    return m_pin_name.width();
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
    if (!variable && m_direction == PD_INPUT)
    {
        m_is_connected = false;
        return;
    }

    set_negated(variable->negated());
    m_outer_text.set_text(variable->expression()->expression());

    if (m_direction == PD_INPUT)
    {
        m_is_connected = true;
    }
}

QString CConnectorPin::formal_param() const
{
    return m_pin_name.text();
}

void CConnectorPin::set_formal_param(const QString &formal)
{
    m_outer_text.set_text(formal);
}

uint16_t CConnectorPin::outer_text_width() const
{
    return m_outer_text.width();
}

CBlockVar *CConnectorPin::block_var()
{
    return m_variable;
}

void CConnectorPin::set_out_variable(COutVariable *out)
{
    if (!out)
    {
        if (m_direction == PD_INPUT)
            m_is_connected = false;
        m_outer_text.set_text("");

        return;
    }

    m_outer_text.set_text(out->expression()->expression());
    if (m_direction == PD_INPUT)
    {
        m_is_connected = true;
    }
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
    //TODO: update m_variable
}

void CConnectorPin::set_edge_modifier(const EEdge &edge)
{
    m_edge_modifier = edge;
    //TODO: update m_variable
}

EDefinedDataTypes CConnectorPin::type() const
{
    return m_type;
}

CDiagramObject *CConnectorPin::parent()
{
    return m_parent;
}

bool CConnectorPin::is_empty() const
{
    return m_variable->is_empty();
}

void CConnectorPin::reset_connections()
{
    m_variable->reset_connections();
    m_outer_text.set_text("");

    if (m_direction == PD_OUTPUT)
    {
        m_out_connections->clear();
        return;
    }

    if (m_opposite_pin)
    {
        m_opposite_pin->remove_opposite(this);
    }
    m_opposite_pin = nullptr;

}

QString CConnectorPin::derived_type() const
{
    return m_derived_type;
}

void CConnectorPin::set_type(const QString &type)
{
    m_type = get_type_from_string(type.toStdString());

    m_variable->set_type(type);

    if (m_type != DDT_UNDEF && m_type != DDT_DERIVED)
    {
        m_derived_type = "";
        return;
    }

    m_type = DDT_DERIVED;
    m_derived_type = type;
}

void CConnectorPin::set_graphic_base(const uint64_t &local_id, const CBlockVar *bloc_out, const QString &pin_label)
{
    m_graphic_conn_base.block_var = const_cast<CBlockVar*>(bloc_out);
    m_graphic_conn_base.block_local_id = local_id;
    //m_outer_text.set_text("*" + pin_label);
}

graphic_base *CConnectorPin::graphic_connection_base()
{
    return &m_graphic_conn_base;
}

void CConnectorPin::set_iface_variable(CVariable *var)
{
    //TODO: update m_variable

    if (!var)
    {
        set_type("ANY_NUM");
        m_variable->set_type("ANY_NUM");
        m_pin_name.set_text("");

        return;
    }

    this->set_type(var->type());
    m_variable->set_iface_variable(var);
    m_outer_text.set_text(var->name());
}

bool CConnectorPin::is_connected() const
{
    return m_is_connected;
}

bool CConnectorPin::pin_here(const QPoint &pos) const
{
    return m_bound_rect.contains(pos) || m_rect.contains(pos);
}

void CConnectorPin::set_opposite_pin(CConnectorPin *opposite_pin)
{
    if (m_direction == PD_INPUT)
    {
        m_opposite_pin = opposite_pin;
        m_outer_text.set_text("");
        m_is_connected = true;
    }
}

CConnectorPin *CConnectorPin::opposite_pin()
{
    return m_opposite_pin;
}

void CConnectorPin::remove_opposite(CConnectorPin *opposite)
{
    if (m_direction == PD_OUTPUT)
    {
        int index = 0;
        for (auto &item : *m_out_connections)
        {
            if (item == opposite)
            {
                m_out_connections->erase(m_out_connections->begin() + index);
                return;
            }
            index++;
        }
        return;
    }

    throw std::runtime_error("Logic broken. Can't ask about remove_connection input pin in 'CConnectorPin::remove_opposite'");
}

void CConnectorPin::add_opposite(CConnectorPin *opposite)
{
    if (!opposite)
    {
        return;
    }

    m_is_connected = true;

    for (auto &pin : *m_out_connections)
    {
        if (pin == opposite)
        {
            return;
        }
    }

    m_out_connections->push_back(opposite);
    m_parent->update_bound_rect();
}

std::vector<CConnectorPin *> *CConnectorPin::opposites()
{
    return m_out_connections;
}

void CConnectorPin::set_opposite_name(const bool &set_name)
{
    if (set_name && m_opposite_pin)
    {
        auto obj_name= m_opposite_pin->parent()->instance_name().isEmpty() ?
                               m_opposite_pin->parent()->type_name() : m_opposite_pin->parent()->instance_name();
        auto text = obj_name + "." + m_opposite_pin->m_pin_name.text();
        m_outer_text.set_text(text);
    }
    if (!set_name)
    {
        m_outer_text.set_text("");
    }
}


