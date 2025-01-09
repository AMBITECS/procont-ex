//
// Created by artem on 1/9/25.
//

#include "CRightPowerRail.h"

CRightPowerRail::CRightPowerRail() : CLeftPowerRail()
{
    m_point_in = new CConnectionPointIn();
}

CRightPowerRail::CRightPowerRail(const CRightPowerRail &other) : CLeftPowerRail(other)
{
    m_point_in = new CConnectionPointIn(*other.m_point_in);
}

CRightPowerRail::CRightPowerRail(CBody *parent) : CLeftPowerRail(parent)
{
    m_point_in = new CConnectionPointIn();
}

CRightPowerRail::CRightPowerRail(CBody *parent, const QDomNode &node) : CLeftPowerRail(parent, node)
{
    m_point_in = new CConnectionPointIn(node.namedItem("connectionPointIn"));
}

CRightPowerRail::~CRightPowerRail()
{
    delete m_point_in;
}

CConnectionPointIn *CRightPowerRail::connection_point_in()
{
    return m_point_in;
}

CConnectionPointOut *CRightPowerRail::connection_point_out()
{
    return nullptr;
}

QDomNode CRightPowerRail::dom_node() const
{
    QDomNode root = CLeftPowerRail::dom_node();

    if (!m_point_in->is_empty())
    {
        root.appendChild(m_point_in->dom_node());
    }

    return root;
}
