//
// Created by artem on 10/22/24.
//

#include "CConnector.h"

CConnector::CConnector()
= default;

CConnector::CConnector(const CConnector &src)
{
    m_name = src.m_name;
    m_local_id = src.m_local_id;
    m_position = src.m_position;
    m_add_data = src.m_add_data;
    m_documentation = src.m_documentation;

    m_connection_input_point = src.m_connection_input_point;
}

CConnector::CConnector(CConnector &&tmp) noexcept
    : m_name(std::move(tmp.m_name))
    , m_add_data(std::move(tmp.m_add_data))
{
    m_local_id = tmp.m_local_id;
    m_position = tmp.m_position;
    m_documentation = tmp.m_documentation;
    m_connection_input_point = tmp.m_connection_input_point;
}

CConnector::~CConnector()
= default;

QString CConnector::name() const
{
    return m_name;
}

void CConnector::set_name(const QString &name)
{
    m_name = name;
}

uint64_t CConnector::local_id() const
{
    return m_local_id;
}

void CConnector::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CConnector::height() const
{
    return m_height;
}

void CConnector::set_height(const float &height)
{
    m_height = height;
}

float CConnector::width() const
{
    return m_width;
}

void CConnector::set_width(const float &width)
{
    m_width = width;
}

QString CConnector::global_id() const
{
    return m_glob_id;
}

void CConnector::set_global_id(const QString &glob_id)
{
    m_glob_id = glob_id;
}

float CConnector::pos_x() const
{
    return m_position.x();
}

void CConnector::set_pos_x(const float &value)
{
    m_position.set_x(value);
}

float CConnector::pos_y() const
{
    return m_position.y();
}

void CConnector::set_pos_y(const float &value)
{
    m_position.set_y(value);
}

CConnectionPointIn * CConnector::connection_point_in()
{
    return &m_connection_input_point;
}

CAddData * CConnector::add_data()
{
    return &m_add_data;
}

CDocumentation * CConnector::documentation()
{
    return &m_documentation;
}

CConnector::CConnector(const QDomNode &dom_node)
{
    m_name = dom_node.attributes().namedItem("name").toAttr().value();
    m_local_id = dom_node.attributes().namedItem("localId").toAttr().value().toLongLong();
    m_height = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_glob_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position = CPosition(dom_node.attributes().namedItem("position"));
    m_connection_input_point = CConnectionPointIn(dom_node.namedItem("connectionPointIn"));
    m_add_data = CAddData(dom_node.namedItem("addData"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
}

QDomNode CConnector::dom_node()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("connector");

    QString s64_t = QString::number(m_local_id);

    root.setAttribute("name", m_name);
    root.setAttribute("localId", s64_t);
    root.setAttribute("height", m_height);
    root.setAttribute("width", m_width);
    root.setAttribute("globalId", m_glob_id);

    root.appendChild(m_position.dom_node());

    if (!m_connection_input_point.is_empty())
        root.appendChild(m_connection_input_point.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

bool CConnector::is_empty() const
{
    bool res = m_name.isEmpty() && m_local_id == 0 &&
               is_floats_equal(m_position.x(), 0) &&
               is_floats_equal(m_position.y(), 0);
    return res;
}
