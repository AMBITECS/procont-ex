//
// Created by artem on 10/23/24.
//

#include "CExpression.h"

CExpression::CExpression()
{
    m_expression = "";
}

CExpression::CExpression(const CExpression &other)
{
    m_expression = "";
    if (other.m_expression.empty())
    {
        return;
    }

    m_expression = other.m_expression;
}

CExpression::CExpression(CExpression &&other) noexcept
{
    if (other.m_expression.empty())
    {
        return;
    }
    m_expression = std::move(other.m_expression);
}

CExpression::CExpression(const QDomNode &dom_node)
{
    m_expression = "";

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
        if (!elem.text().isNull() && !elem.text().isEmpty())
            m_expression = elem.text().toStdString();
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

    if (!expression.m_expression.empty())
    {
        m_expression = expression.m_expression;
    }
    return *this;
}

QDomNode CExpression::dom_node() const
{
    if (m_expression.empty())
    {
        return {};
    }

    QDomDocument doc;
    QDomNode root = doc.createElement("expression");
    QDomText text = doc.createTextNode(m_expression.c_str());
    root.appendChild(text);
    return root;
}

QString CExpression::expression() const
{
    return m_expression.empty() ? "" : m_expression.c_str();
}

void CExpression::set_expression(const QString &expression)
{
    if (expression.length() > 0)
    {
        m_expression = expression.toStdString();
    }

}

bool  operator==(const CExpression &lhs, const CExpression &rhs)
{
    return  lhs.m_expression == rhs.m_expression;
}

bool CExpression::is_empty() const
{
    return m_expression.empty();
}
