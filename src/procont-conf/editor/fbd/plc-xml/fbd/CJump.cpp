//
// Created by artem on 10/25/24.
//

#include "CJump.h"

CJump::CJump()
= default;

CJump::CJump(const CJump &src)
= default;

CJump::CJump(const QDomNode &dom_node)
{
    m_local_id = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_height  = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width  = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_label = dom_node.attributes().namedItem("label").toAttr().value();
    m_exec_order_id = dom_node.attributes().namedItem("executionOrder").toAttr().value().toULong();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position = CPosition(dom_node.namedItem("position"));
    m_point_in = CConnectionPointIn(dom_node.namedItem("connectionPointIn"));
    m_add_data  = CAddData(dom_node.namedItem("addData"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
}

CJump::~CJump()
= default;

uint64_t CJump::local_id() const
{
    return m_local_id;
}

void CJump::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CJump::width() const
{
    return m_width;
}

void CJump::set_width(const float &width)
{
    m_width = width;
}

float CJump::height() const
{
    return m_height;
}

void CJump::set_height(const float &height)
{
    m_height = height;
}

QString CJump::label() const
{
    return m_label;
}

void CJump::set_label(const QString &label)
{
    m_label = label;
}

uint16_t CJump::execution_order_id() const
{
    return m_exec_order_id;
}

void CJump::set_exec_order(const uint16_t &exec_order_id)
{
    m_exec_order_id = exec_order_id;
}

CPosition *CJump::position()
{
    return &m_position;
}

CConnectionPointIn *CJump::connection_point_in()
{
    return &m_point_in;
}

CAddData *CJump::add_data()
{
    return &m_add_data;
}

CDocumentation *CJump::documentation()
{
    return &m_documentation;
}

QDomNode CJump::dom_node() const
{
    QDomDocument    doc;
    QDomElement  root = doc.createElement("jump");

    QString  locId = QString::number(m_local_id);
    root.setAttribute("localId", locId);
    if (!is_floats_equal(0, m_width) && !is_floats_equal(0, m_height))
    {
        root.setAttribute("width", m_width);
        root.setAttribute("height", m_height);
    }
    root.setAttribute("label", m_label);
    if (m_exec_order_id)
        root.setAttribute("executionOrderId", m_exec_order_id);
    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_position.dom_node());
    if (!m_point_in.is_empty())
        root.appendChild(m_point_in.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

bool CJump::is_empty() const
{
    bool empty  = m_local_id == 0 &&
                  m_label.isEmpty() &&
                  m_position.is_empty();
    return empty;
}
