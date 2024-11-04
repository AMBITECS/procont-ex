//
// Created by artem on 10/23/24.
//

#include "CRelPosition.h"

CRelPosition::CRelPosition()
= default;

CRelPosition::CRelPosition(const CRelPosition &other)
= default;

CRelPosition::CRelPosition(CRelPosition &&other) noexcept
    : m_x(other.m_x)
    , m_y(other.m_y)
{}

CRelPosition::CRelPosition(const QDomNode &dom_node)
{
    m_x = dom_node.attributes().namedItem("x").toAttr().value().toFloat();
    m_y = dom_node.attributes().namedItem("y").toAttr().value().toFloat();
}

CRelPosition::~CRelPosition()
= default;

CRelPosition &CRelPosition::operator=(const CRelPosition &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    m_x = rhs.m_x;
    m_y = rhs.m_y;

    return *this;
}

QDomNode CRelPosition::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("relPosition");
    root.setAttribute("x", m_x);
    root.setAttribute("y", m_y);

    return root;
}

float CRelPosition::x() const
{
    return m_x;
}

void CRelPosition::set_x(const float &x)
{
    m_x = x;
}

float CRelPosition::y() const
{
    return m_y;
}

void CRelPosition::set_y(const float &y)
{
    m_y = y;
}

bool     operator==(const CRelPosition &lhs, const CRelPosition &rhs)
{
    return  is_floats_equal(lhs.m_x, rhs.m_x) &&
            is_floats_equal(lhs.m_y, rhs.m_y);
}