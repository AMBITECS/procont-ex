//
// Created by artem on 10/25/24.
//

#include "CReturn.h"

CReturn::CReturn()
= default;

CReturn::CReturn(const CReturn &other)
 = default;

CReturn::CReturn(const QDomNode &dom_node)
{
    m_local_id  = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_height    = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width     = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_exec_order= dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position  = CPosition(dom_node.namedItem("position"));
    m_point_in  = CConnectionPointIn(dom_node.namedItem("connectionPointIn"));
    m_add_data  = CAddData(dom_node.namedItem("addData"));
    m_doc       = CDocumentation(dom_node.namedItem("documentation"));
}

CReturn::~CReturn()
= default;

QDomNode CReturn::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("return");

    QString locId = QString::number(m_local_id);
    root.setAttribute("localId", locId);
    if (!is_floats_equal(0, m_height) && !is_floats_equal(0, m_width))
    {
        root.setAttribute("width", m_width);
        root.setAttribute("height", m_height);
    }
    root.setAttribute("executionOrder", m_exec_order);
    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);
    root.appendChild(m_position.dom_node());
    if (!m_point_in.is_empty())
        root.appendChild(m_point_in.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_doc.is_empty())
        root.appendChild(m_doc.dom_node());

    return root;
}

bool CReturn::is_empty() const
{
    return m_local_id == 0 && m_position.is_empty();
}

uint64_t CReturn::local_id() const
{
    return m_local_id;
}

void CReturn::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CReturn::width() const
{
    return m_width;
}

void CReturn::set_width(const float &width)
{
    m_width = width;
}

float CReturn::height() const
{
    return m_height;
}

void CReturn::set_height(const float &height)
{
    m_height = height;
}

uint16_t CReturn::execution_order_id() const
{
    return m_exec_order;
}

void CReturn::set_exec_id(const uint16_t &exec_id)
{
    m_exec_order = exec_id;
}

QString CReturn::global_id() const
{
    return m_global_id;
}

void CReturn::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CPosition *CReturn::position()
{
    return &m_position;
}

CConnectionPointIn *CReturn::connection_point_in()
{
    return &m_point_in;
}

CAddData *CReturn::add_data()
{
    return &m_add_data;
}

CDocumentation *CReturn::documentation()
{
    return &m_doc;
}
