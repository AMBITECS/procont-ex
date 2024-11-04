//
// Created by artem on 27.10.24.
//

#include "CBlockVar.h"

CBlockVar::CBlockVar()
{
    m_point_in  = new CConnectionPointIn();
    m_point_out = new CConnectionPointOut();
}

CBlockVar::CBlockVar(const CBlockVar &other)
{
    m_point_in  = new CConnectionPointIn(*other.m_point_in);
    m_point_out = new CConnectionPointOut(*other.m_point_out);
    m_formal_parameter = other.m_formal_parameter;
}

CBlockVar::CBlockVar(const QDomNode &domNode)
{
    m_formal_parameter = domNode.attributes().namedItem("formalParameter").toAttr().value();

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

QDomNode
CBlockVar::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("variable");
    root.setAttribute("formalParameter", m_formal_parameter);

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

/*CPosition *
CBlockVar::position()
{
    return nullptr;
}*/

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
