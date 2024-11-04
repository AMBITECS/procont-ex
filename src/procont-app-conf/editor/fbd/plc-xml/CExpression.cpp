//
// Created by artem on 10/23/24.
//

#include "CExpression.h"

CExpression::CExpression()
= default;

CExpression::CExpression(const CExpression &other)
 = default;

CExpression::CExpression(CExpression &&other) noexcept
    : m_expression(std::move(other.m_expression))
{}

CExpression::CExpression(const QDomNode &dom_node)
{
    if (dom_node.isNull())
    {
        // fprintf(stderr, "CExpression::CExpression(const QDomNode &dom_node) is null\n");
        return;
    }

    if (dom_node.nodeName() != "expression")
    {
        return;
    }

    if (dom_node.isElement())
    {
        QDomElement elem = dom_node.toElement();
        m_expression = elem.text();
    }
}

CExpression::~CExpression()
= default;

CExpression &CExpression::operator=(const CExpression &expression)
{
    if (this == &expression)
    {
        return *this;
    }

    m_expression = expression.m_expression;
    return *this;
}

QDomNode CExpression::dom_node() const
{
    if (m_expression.isNull())
    {
        return {};
    }

    QDomDocument doc;
    QDomNode root = doc.createElement("expression");
    QDomText text = doc.createTextNode(m_expression);
    root.appendChild(text);
    return root;
}

QString CExpression::expression() const
{
    return m_expression;
}

void CExpression::set_expression(const QString &expression)
{
    m_expression = expression;
}

bool  operator==(const CExpression &lhs, const CExpression &rhs)
{
    return  lhs.m_expression == rhs.m_expression;
}

bool CExpression::is_empty() const
{
    return m_expression.isEmpty();
}
