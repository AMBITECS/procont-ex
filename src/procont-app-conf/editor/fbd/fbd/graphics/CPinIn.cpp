//
// Created by artem on 12/7/24.
//

#include "CPinIn.h"
#include "CDiagramObject.h"

CPinIn::CPinIn(CDiagramObject *parent, CBlockVar *base, QPoint * parent_tl) : CPin(parent, base, parent_tl)
{
    m_direction = EPinDirection::PD_INPUT;

    m_img_negated = QImage(":/codesys/images/codesys/pin_input_inv.png");
    m_img_rising = QImage("");
    m_img_falling = QImage("");
    m_img_norm    = QImage(":/codesys/images/codesys/pin_input_norm.png");
    m_draw_image = m_img_norm;

    update_condition();
}

CPinIn::~CPinIn()
= default;

bool CPinIn::is_negated() const
{
    return m_block_variable->is_negated();
}

void CPinIn::set_negated(const bool &negated)
{
    m_block_variable->set_negated(negated);

    m_draw_image = negated ? m_img_negated : m_img_norm;
}

bool CPinIn::is_rising_edge() const
{
    return m_block_variable->edge_modifier() == EEdge::EI_RISE;
}

void CPinIn::set_rising_edge(const bool &rising)
{
    EEdge edge = rising ? edge = EEdge::EI_RISE : EEdge::EI_NONE;
    m_block_variable->set_edge(edge);

    m_draw_image = rising ? m_img_rising : m_img_norm;
}

bool CPinIn::is_falling_edge() const
{
    return m_block_variable->edge_modifier() == EEdge::EI_FALL;
}

void CPinIn::set_falling_edge(const bool &falling)
{
    EEdge edge = falling ? edge = EEdge::EI_FALL : EEdge::EI_NONE;
    m_block_variable->set_edge(edge);

    m_draw_image = falling ? m_img_falling : m_img_norm;
}

bool CPinIn::is_coil_set() const
{
    return m_block_variable->storage_modifier() == EStorageMode::SM_SET;
}

void CPinIn::set_coil_set(const bool &set)
{
    EStorageMode mode = set ? EStorageMode::SM_SET : EStorageMode::SM_NONE;
    m_block_variable->set_storage_modifier(mode);
}

bool CPinIn::is_coil_reset() const
{
    return m_block_variable->storage_modifier() == EStorageMode::SM_RESET;
}

void CPinIn::set_coil_reset(const bool &reset)
{
    EStorageMode mode = reset ? EStorageMode::SM_RESET : EStorageMode::SM_NONE;
    m_block_variable->set_storage_modifier(mode);
}

void CPinIn::connect_pin(CPinOut *pin)
{
    if (!pin)
    {
        throw std::runtime_error("pin can't be null in 'void CPinIn::connect_pin(CPin *pin)'");
    }

    m_opposite = pin;
    m_is_connected = true;

    auto point_in = m_block_variable->point_in();
    point_in->set_reference_id(pin->parent()->local_id());
    point_in->set_formal_param(pin->pin_name());

    if (pin->parent()->parent() == m_parent->parent())
        m_outer_text.set_text("");
    else
        m_outer_text.set_text(pin->pin_name());
}

void CPinIn::disconnect()
{
    /// define connection type
    /// TODO: disconnect it
    m_is_connected = false;
}

void CPinIn::connect_iface_variable(CVariable * variable)
{
    /// TODO: connect it
    m_is_connected = true;
}

void CPinIn::update_condition()
{
    m_pin_name.set_text(m_block_variable->formal_parameter());
    m_outer_text.set_text(m_block_variable->point_in()->expression());

    saturate();

    if (m_block_variable->is_negated())
    {
        set_negated(true);
    }

    auto edge = m_block_variable->edge_modifier();

    if (edge == EEdge::EI_FALL)
    {
        set_falling_edge(true);
    }

    if (edge == EEdge::EI_RISE)
    {
        set_rising_edge(true);
    }
}

CPinOut *CPinIn::opposite()
{
    return m_opposite;
}

void CPinIn::set_opposite_name(const bool &set_name)
{
    if (!m_opposite)
    {
        return;
    }

    QString element = m_opposite->parent()->instance_name().isEmpty() ?
                      m_opposite->parent()->type_name() :
                      m_opposite->parent()->instance_name();

    if (!set_name)
    {
        m_outer_text.set_text("");
        return;
    }

    QString text = element + "." + opposite()->pin_name();

    m_outer_text.set_text(text);
}

uint64_t CPinIn::reference_local_id() const
{
    return m_block_variable->ref_local_id();
}

CBlockVar *CPinIn::block_variable()
{
    return m_block_variable;
}
