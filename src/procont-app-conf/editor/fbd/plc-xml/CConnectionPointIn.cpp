//
// Created by artem on 10/22/24.
//

#include "CConnectionPointIn.h"

CConnectionPointIn::CConnectionPointIn()
{
    m_connections = new QList<CConnection*>();
}

CConnectionPointIn::CConnectionPointIn(const CConnectionPointIn &other)
{
    m_connections = new QList<CConnection*>();
    for (auto &alien : *other.m_connections)
    {
        auto item = new CConnection(*alien);
        m_connections->push_back(item);
    }

    m_add_data = other.m_add_data;
    m_rel_position = other.m_rel_position;
    m_attr_global_id = other.m_attr_global_id;
}

CConnectionPointIn::CConnectionPointIn(CConnectionPointIn &&tmp) noexcept
    : m_attr_global_id(std::move(tmp.m_attr_global_id))
    , m_add_data(tmp.m_add_data)
{
    m_connections = tmp.m_connections;
    tmp.m_connections = nullptr;
    m_rel_position = tmp.m_rel_position;
}

CConnectionPointIn::CConnectionPointIn(const QDomNode &dom_node)
{
    m_connections = new QList<CConnection*>();

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

        if (child.nodeName() == "addData")
        {
            m_add_data = CAddData(child);
        }

        if (child.nodeName() == "connection")
        {
            auto connect = new CConnection(child);
            m_connections->push_back(connect);
        }

        if (child.nodeName() == "expression")
        {
            m_expression = CExpression(child);
        }
    }
}

CConnectionPointIn::~CConnectionPointIn()
{
    if (!m_connections)
    {
        return;
    }

    for (auto &item : *m_connections)
    {
        delete item;
    }
    delete m_connections;
}

CConnectionPointIn &CConnectionPointIn::operator=(const CConnectionPointIn &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    /// remove possible connections
    for (auto &item : *m_connections)
    {
        delete item;
    }
    m_connections->clear();

    /// copy rhs connections and others
    for (auto &alien : *rhs.m_connections)
    {
        m_connections->emplaceBack(new CConnection(*alien));
    }


    m_add_data = rhs.m_add_data;
    m_rel_position = rhs.m_rel_position;
    m_attr_global_id = rhs.m_attr_global_id;

    return *this;
}

QDomNode CConnectionPointIn::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("connectionPointIn");

    if (!m_attr_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_attr_global_id);
    }

    root.appendChild(m_rel_position.dom_node());

    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }

    if (!m_expression.is_empty())
    {
        root.appendChild(m_expression.dom_node());
    }

    for (auto &item : *m_connections)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

bool CConnectionPointIn::is_empty() const
{
    bool res    = m_connections->empty() &&
                  m_expression.is_empty();

    return res;
}

QString CConnectionPointIn::expression() const
{
    return m_expression.expression();
}

void CConnectionPointIn::set_expression(const QString &expression)
{
    m_expression.set_expression(expression);
}

QList<CConnection *> *CConnectionPointIn::connections()
{
    return m_connections;
}
