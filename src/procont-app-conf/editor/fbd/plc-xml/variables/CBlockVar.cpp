//
// Created by artem on 27.10.24.
//

#include "CBlockVar.h"
#include "../fbd/CBlock.h"
#include "../common/CBody.h"
#include "../common/CPou.h"

CBlockVar::CBlockVar(CBlock *parent)
{
    m_point_in  = new CConnectionPointIn();
    m_point_out = new CConnectionPointOut();
    add_data = new CAddData();
//    if (parent && parent->parent())
//        m_variable = new CVariable(parent->parent()->parent()->interface());
//    else
//        m_variable = new CVariable(nullptr);
    m_parent = parent;
}

CBlockVar::CBlockVar(const CBlockVar &other)
{
    m_point_in = new CConnectionPointIn(*other.m_point_in);
    m_point_out = new CConnectionPointOut(*other.m_point_out);
    //m_variable = new CVariable(*other.m_variable);

    m_formal_parameter = other.m_formal_parameter;
    m_is_negated = other.m_is_negated;
    m_edge_modifier = other.m_edge_modifier;
    m_store_modifier = other.m_store_modifier;
    m_type = other.m_type;
    add_data = new CAddData(*other.add_data);
    m_direction = other.m_direction;
    m_derived_type = other.m_derived_type;
    m_parent = other.m_parent;
}

CBlockVar::CBlockVar(CBlock *parent, const QDomNode &domNode)
{
    m_parent = parent;
    m_formal_parameter = domNode.attributes().namedItem("formalParameter").toAttr().value();
    m_is_negated       = domNode.attributes().namedItem("negated").toAttr().value() == "true";
    m_store_modifier   = (EStorageMode)domNode.attributes().namedItem("storage").toAttr().value().toInt();
    m_edge_modifier    = (EEdge)domNode.attributes().namedItem("edge").toAttr().value().toInt();
    add_data           = new CAddData(domNode.namedItem("addData"));

    for (uint16_t i = 0; i < domNode.childNodes().count(); ++i)
    {
        QDomNode child = domNode.childNodes().at(i);

        if (child.nodeName() == "connectionPointIn" && !m_point_in)
        {
            m_point_in = new CConnectionPointIn(child);
        }

        if (child.nodeName() == "connectionPointOut" && !m_point_out)
        {
            m_point_out = new CConnectionPointOut(child);
        }
    }

    m_direction = PD_UNDEF;

    if (m_point_in && m_point_out)
    {
        m_direction = EPinDirection::PD_IN_OUT;
    }

    if (!m_point_in)
    {
        m_point_in = new CConnectionPointIn();
        m_direction = EPinDirection::PD_OUTPUT;
    }

    if (!m_point_out)
    {
        m_point_out = new CConnectionPointOut();
        m_direction = EPinDirection::PD_INPUT;
    }

    //m_variable = new CVariable(m_parent->parent()->parent()->interface());
}

CBlockVar::~CBlockVar()
{
    delete m_point_out;
    delete m_point_in;
    // delete m_variable;
}

QDomNode CBlockVar::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("variable");
    root.setAttribute("formalParameter", m_formal_parameter);

    if (m_is_negated)
    {
        root.setAttribute("negated", "true");
    }

    if (m_store_modifier != EStorageMode::SM_NONE)
    {
        root.setAttribute("storage", storage_behaviour_names[m_store_modifier]);
    }

    if (m_edge_modifier != EEdge::EI_NONE)
    {
        root.setAttribute("edge", edge_types_names[m_edge_modifier]);
    }

    if (!m_point_in->is_empty())
    {
        root.appendChild(m_point_in->dom_node());
    }

    if (!m_point_out->is_empty())
    {
        root.appendChild(m_point_out->dom_node());
    }

    return root;
}

bool
CBlockVar::is_empty() const
{
    return m_point_in->is_empty() && m_point_out->is_empty() && m_formal_parameter.isEmpty();
}

QString
CBlockVar::formal_parameter() const
{
    return m_formal_parameter;
}

CConnectionPointIn * CBlockVar::point_in()
{
    return m_point_in;
}

CConnectionPointOut * CBlockVar::point_out()
{
    return m_point_out;
}

void CBlockVar::set_formal_param(const QString &formal_param)
{
    m_formal_parameter = formal_param;
}

bool CBlockVar::is_negated() const
{
    return m_is_negated;
}

EEdge CBlockVar::edge_modifier() const
{
    return m_edge_modifier;
}

EStorageMode CBlockVar::storage_modifier() const
{
    return m_store_modifier;
}

void CBlockVar::set_edge(const EEdge &edge_modifier)
{
    m_edge_modifier = edge_modifier;
    m_is_negated = false;
    m_store_modifier = EStorageMode::SM_NONE;
}

void CBlockVar::set_storage_modifier(const EStorageMode &storage_modifier)
{
    m_store_modifier = storage_modifier;
    m_is_negated = false;
    m_edge_modifier = EEdge::EI_NONE;
}

EPinDirection CBlockVar::direction() const
{
    return m_direction;
}

void CBlockVar::set_direction(const EPinDirection &dir)
{
    m_direction = dir;
}

EDefinedDataTypes CBlockVar::type() const
{
    return m_type;
}

QString CBlockVar::derived_type() const
{
    return m_derived_type;
}

void CBlockVar::set_type(const QString &type)
{
    m_derived_type = type;
    m_type = get_type_from_string(type.toStdString());

    if (m_type == DDT_UNDEF || m_type == DDT_DERIVED)
    {
        m_type = DDT_DERIVED;
    }
}

CBlockVar &CBlockVar::operator=(const CBlockVar &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    *m_point_in = *rhs.m_point_in;
    *m_point_out = *rhs.m_point_out;
    *add_data = *rhs.add_data;

    m_formal_parameter = rhs.m_formal_parameter;
    m_is_negated = rhs.m_is_negated;
    m_edge_modifier = rhs.m_edge_modifier;
    m_store_modifier = rhs.m_store_modifier;
    m_type = rhs.m_type;
    m_direction = rhs.m_direction;
    m_derived_type = rhs.m_derived_type;

    return *this;
}

/*CVariable *CBlockVar::get_iface_variable()
{
    return m_variable;
}

void CBlockVar::set_iface_variable(CVariable *var)
{
    *m_variable = *var;    
    this->set_type(var->type());
}*/

void CBlockVar::set_negated(const bool &negated)
{
    m_is_negated = negated;

    m_edge_modifier = EEdge::EI_NONE;
    m_store_modifier = EStorageMode::SM_NONE;
}

CBlock *CBlockVar::parent()
{
    return m_parent;
}

void CBlockVar::set_parent(CBlock *block)
{
    m_parent = block;
}

void CBlockVar::set_constant(const EDefinedDataTypes &type, const std::string &const_value)
{
    m_type = type;
    m_derived_type = base_types_names[m_type];
    m_constant_value = const_value.c_str();
}

QString CBlockVar::constant_value() const
{
    return m_constant_value;
}

