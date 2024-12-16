//
// Created by artem on 12/7/24.
//

#include "CPinIn.h"
#include "CDiagramObject.h"
#include "../../resources/colors.h"
#include "COglWorld.h"

extern uint16_t max_local_id;
extern CVariablesAnalytics * xml_variable_analytic;

CPinIn::CPinIn(CDiagramObject *parent, CBlockVar *base, QPoint * parent_tl) : CPin(parent, base, parent_tl)
{
    m_direction = EPinDirection::PD_INPUT;

    m_img_negated = QImage(":/codesys/images/codesys/pin_input_inv.png");
    m_img_rising = QImage("");
    m_img_falling = QImage("");
    m_img_norm    = QImage(":/codesys/images/codesys/pin_input_norm.png");
    m_draw_image = m_img_norm;

    CDiagramColors colors;

    m_color_def = colors.base_colors().diag_text_def;
    m_color_graph = colors.ladder_colors().line_color;

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

void CPinIn::load_project_connect_pin(CPinOut *pin)
{
    if (!pin)
    {
        throw std::runtime_error("pin can't be null in 'void CPinIn::connect_pin(CPin *pin)'");
    }

    m_opposite = pin;
    m_is_connected = true;

    if (pin->parent()->parent() == m_parent->parent())
        m_outer_text->set_text("");
    else
    {
        QString pin_parent = pin->parent()->instance_name().isEmpty() ?
                             pin->parent()->type_name() :
                             pin->parent()->instance_name();
        QString pin_full_name = pin_parent + "." + pin->name();
        m_outer_text->set_text(pin_full_name);
        update_position();
    }
}

void CPinIn::load_project_connect_iface_var(CVariable *variable)
{
    m_is_connected = true;

    //m_block_variable->set_iface_variable(variable);
    m_outer_text->set_text(variable->name());
    set_type(variable->type());
    QString text = m_block_variable->formal_parameter() + ":" + variable->type();
    m_pin_name->set_text(text);
    update_position();
}

void CPinIn::connect_pin(CPinOut *pin)
{
    if (m_is_connected)
    {
        return;
    }

    load_project_connect_pin(pin);

    /// connecting in XML
    auto point_in = m_block_variable->point_in();

    if (!point_in->connections()->isEmpty())
    {
        for (auto &conn : *point_in->connections())
        {
            delete conn;
        }
        point_in->connections()->clear();
    }

    auto connections = m_block_variable->point_in()->connections();
    if (!connections->empty())
    {
        for (auto &item : *connections)
        {
            delete item;
        }
        connections->clear();
    }

    auto connection = new CConnection();
    connection->set_formal_param(pin->name());
    connection->set_ref_local_id(pin->parent()->local_id());
    point_in->connections()->push_back(connection);
}

void CPinIn::disconnect(CPinOut *sender)
{
    if (!m_is_connected)
    {
        return;
    }

    m_is_connected = false;
    auto point_in = m_block_variable->point_in();
    auto connections = point_in->connections();

    /// it could be graphic connection
    if (m_opposite)
    {
        /// graphical disconnecting
        if (!sender)
        {
            m_opposite->disconnect(this, this);
        }
        m_opposite = nullptr;

        m_parent->parent()->remove_line(this);
    }
    /// nope its connected to the interface variable or constant
    //if (point_in->connections()->front()->formal_parameter().isEmpty() && point_in->connections()->front()->ref_local_id() > 0)
    if (m_iface_var)
    {
        COglWorld * world = m_parent->parent()->parent();

        xml_variable_analytic->remove_input_variable_by_id(connections->front()->ref_local_id());


        CVariable var;
        // m_block_variable->set_iface_variable(&var);
        m_iface_var = nullptr;
    }

    /// constant
    if (!m_constant.isEmpty())
    {

        xml_variable_analytic->remove_input_variable_by_id(connections->front()->ref_local_id());
        m_iface_input_var_id = 0;

        m_constant.clear();
    }

    /// remove local connection data
    if (!connections->empty())
    {
        for (auto &item : *connections)
        {
            delete item;
        }
        connections->clear();
    }

    resort_outers();
}

void CPinIn::connect_iface_variable(CVariable * variable)
{
    if (m_is_connected)
    {
        return;
    }

    load_project_connect_iface_var(variable);

    /// connect in XML<br>
    /// create outside inVariable
    auto in_var = new CInVariable();
    in_var->set_local_id(++max_local_id);
    in_var->expression()->set_expression(variable->name());

    /// set connection to local CBlockVar pointing to the outside inVariable
    auto connection = new CConnection();
    connection->set_ref_local_id(in_var->local_id());

    /// check CBlockVar has not any connections
    if (!m_block_variable->point_in()->connections()->empty())
    {
        auto connections = m_block_variable->point_in()->connections();
        for (auto &conn: *connections) {
            delete conn;
        }
        connections->clear();
    }

    m_block_variable->point_in()->connections()->push_back(connection);

    xml_variable_analytic->add_input_variable(in_var);


    m_iface_var = variable;
}

void CPinIn::update_condition()
{
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

void CPinIn::set_constant(const EDefinedDataTypes &type, const std::string &const_val)
{
    load_project_connect_const(type, const_val.c_str());
    //m_block_variable->set_constant(type, const_val.toStdString()); ???

    /// connect in XML<br>
    /// set outside inVariable
    auto in_var = new CInVariable();
    in_var->set_local_id(++max_local_id);
    in_var->expression()->set_expression(const_val.c_str());

    /// check if inner variable has connections
    if (!m_block_variable->point_in()->connections()->empty())
    {
        for (auto &conn : *m_block_variable->point_in()->connections())
        {
            delete conn;
        }
        m_block_variable->point_in()->connections()->clear();
    }

    auto conn = new CConnection();
    conn->set_ref_local_id(in_var->local_id());
    m_block_variable->point_in()->connections()->push_back(conn);



    xml_variable_analytic->add_input_variable(in_var);


    m_is_connected = true;
    m_constant = const_val.c_str();
}

void CPinIn::load_project_connect_const(const EDefinedDataTypes &type, const QString &const_val)
{
    m_outer_text->set_text(const_val);
    m_outer_text->set_color(m_color_def);

    QString text = m_block_variable->formal_parameter() + ":" + base_types_names[type];
    m_pin_name->set_text(text);

    m_is_connected = true;
    update_position();
}

void CPinIn::update_graphic_text()
{
    if (!m_opposite)
    {
        m_outer_text->set_color(m_color_def);
        return;
    }

    m_outer_text->set_color(m_color_graph);
    if (m_opposite->parent()->parent() != m_parent->parent())
    {
        m_outer_text->set_text(make_pin_text(m_opposite));
    }
    else
    {
        m_outer_text->set_text("");
    }
}

CVariable *CPinIn::iface_variable()
{
    return m_iface_var;
}

QString CPinIn::constant() const
{
    return m_constant;
}





