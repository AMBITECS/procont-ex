//
// Created by artem on 27.10.24.
//

#include "CBlockVar.h"

CBlockVar::CBlockVar()
{
    m_point_in  = new CConnectionPointIn();
    m_point_out = new CConnectionPointOut();
    add_data = new CAddData();
}

CBlockVar::CBlockVar(const CBlockVar &other)
{
    m_point_in = new CConnectionPointIn(*other.m_point_in);
    m_point_out = new CConnectionPointOut(*other.m_point_out);

    m_formal_parameter = other.m_formal_parameter;
    m_is_negated = other.m_is_negated;
    m_edge_modifier = other.m_edge_modifier;
    m_store_modifier = other.m_store_modifier;
    m_type = other.m_type;
    add_data = new CAddData(*other.add_data);
}

CBlockVar::CBlockVar(const QDomNode &domNode)
{
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

    if (!m_point_in)
    {
        m_point_in = new CConnectionPointIn();
    }

    if (!m_point_out)
    {
        m_point_out = new CConnectionPointOut();
    }
}

CBlockVar::~CBlockVar()
{
    delete m_point_out;
    delete m_point_in;
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

CConnectionPointIn *
CBlockVar::point_in()
{
    return m_point_in;
}

CConnectionPointOut *
CBlockVar::point_out()
{
    return m_point_out;
}

void
CBlockVar::set_formal_param(const QString &formal_param)
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

}

void CBlockVar::set_storage_modifier(const EStorageMode &storage_modifier)
{

}

