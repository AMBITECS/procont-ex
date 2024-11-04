//
// Created by artem on 10/22/24.
//

#include "CPosition.h"

CPosition::CPosition()
= default;

CPosition::CPosition(const float &x, const float &y)
    : m_x(x), m_y(y)
{}

CPosition::CPosition(const QDomNode &dom_node)
{
    m_x = dom_node.attributes().namedItem("x").toAttr().value().toFloat();
    m_y = dom_node.attributes().namedItem("y").toAttr().value().toFloat();
}

CPosition::CPosition(const CPosition &other)
    : m_x(other.m_x)
    , m_y(other.m_y)
{}

CPosition::CPosition(CPosition && tmp) noexcept
        : m_x(tmp.m_x), m_y(tmp.m_y)
{}

CPosition::~CPosition()
= default;

QDomNode CPosition::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("position");
    root.setAttribute("x", m_x);
    root.setAttribute("y", m_y);

    return root;
}

float CPosition::x() const
{
    return m_x;
}

void CPosition::set_x(const float &X)
{
    m_x = X;
}

float CPosition::y() const
{
    return m_y;
}

void CPosition::set_y(const float &Y)
{
    m_y = Y;
}

CPosition &CPosition::operator=(const CPosition &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    m_x = rhs.m_x;
    m_y = rhs.m_y;

    return *this;
}

bool operator==(const CPosition &lhs, const CPosition &rhs)
{
    return is_floats_equal(lhs.m_x, rhs.m_x) &&
           is_floats_equal(lhs.m_y, rhs.m_y);
}

bool CPosition::is_empty() const
{
    return  is_floats_equal(0, m_x) &&
            is_floats_equal(0, m_y);
}
