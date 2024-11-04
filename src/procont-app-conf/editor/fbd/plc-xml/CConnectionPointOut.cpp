//
// Created by artem on 10/23/24.
//

#include "CConnectionPointOut.h"

CConnectionPointOut::CConnectionPointOut()
= default;

CConnectionPointOut::CConnectionPointOut(const CConnectionPointOut &other)
{
    *this = other;
}

CConnectionPointOut::CConnectionPointOut(CConnectionPointOut &&other) noexcept
    :   m_attr_global_id(std::move(other.m_attr_global_id))
    ,   m_add_data(std::move(other.m_add_data))
    ,   m_rel_position(std::move(other.m_rel_position))
    ,   m_expression(std::move(other.m_expression))
{}

CConnectionPointOut::CConnectionPointOut(const QDomNode &dom_node)
{
    if (dom_node.hasAttributes())
    {
        m_attr_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();
    }

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);

        if (child.nodeName() == "relPosition")
        {
            m_rel_position = CRelPosition(child);
        }

        if (child.nodeName() == "expression")
        {
            m_expression = CExpression(child);
        }

        if (child.nodeName() == "addData")
        {
            m_add_data = CAddData(child);
        }
    }
}

CConnectionPointOut::~CConnectionPointOut()
= default;

CConnectionPointOut &CConnectionPointOut::operator=(const CConnectionPointOut &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_expression        = other.m_expression;
    m_attr_global_id    = other.m_attr_global_id;
    m_rel_position      = other.m_rel_position;
    m_add_data          = other.m_add_data;

    return *this;
}

QDomNode CConnectionPointOut::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("connectionPointOut");

    if (!m_attr_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_attr_global_id);
    }

    root.appendChild(m_rel_position.dom_node());
    if (!m_expression.is_empty())
    {
        root.appendChild(m_expression.dom_node());
    }

    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }

    return root;
}

QString CConnectionPointOut::expression() const
{
    return m_expression.expression();
}

void CConnectionPointOut::set_expression(const QString &expression)
{
    m_expression.set_expression(expression);
}

QString CConnectionPointOut::global_id() const
{
    return m_attr_global_id;
}

void CConnectionPointOut::set_global_id(const QString &glob_id)
{
    m_attr_global_id = glob_id;
}

CRelPosition *CConnectionPointOut::rel_position()
{
    return &m_rel_position;
}

CAddData *CConnectionPointOut::add_data()
{
    return &m_add_data;
}

bool CConnectionPointOut::is_empty() const
{
    bool res = m_expression.is_empty() &&
               m_attr_global_id.isEmpty() &&
               m_rel_position.x() == 0 && m_rel_position.y() == 0 &&
               m_add_data.is_empty();
    return res;
}
