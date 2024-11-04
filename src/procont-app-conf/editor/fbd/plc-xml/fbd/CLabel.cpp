//
// Created by artem on 10/25/24.
//

#include "CLabel.h"

CLabel::CLabel()
= default;

CLabel::CLabel(const CLabel &other)
= default;

CLabel::CLabel(const QDomNode &dom_node)
{
    m_local_id  = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_width     = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_height    = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_label     = dom_node.attributes().namedItem("label").toAttr().value();
    m_exec_order= dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position  = CPosition(dom_node.namedItem("position"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
    m_add_data  = CAddData(dom_node.namedItem("addData"));
}

CLabel::~CLabel()
= default;

uint64_t CLabel::local_id() const
{
    return m_local_id;
}

void CLabel::set_local_id(const uint64_t &loc_id)
{
    m_local_id = loc_id;
}

float CLabel::width() const
{
    return m_width;
}

void CLabel::set_width(const float &width)
{
    m_width = width;
}

float CLabel::height() const
{
    return m_height;
}

void CLabel::set_height(const float &height)
{
    m_height = height;
}

QString CLabel::label() const
{
    return m_label;
}

void CLabel::set_label(const QString &label)
{
    m_label = label;
}

uint16_t CLabel::exec_order_id() const
{
    return m_exec_order;
}

void CLabel::set_exec_order_id(const uint16_t &exec_order)
{
    m_exec_order = exec_order;
}

QString CLabel::global_id() const
{
    return m_global_id;
}

void CLabel::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CPosition *CLabel::position()
{
    return &m_position;
}

CAddData *CLabel::add_data()
{
    return &m_add_data;
}

CDocumentation *CLabel::documentation()
{
    return &m_documentation;
}

bool CLabel::is_empty() const
{
    return  m_local_id == 0 &&
            m_label.isEmpty();
}

QDomNode CLabel::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("label");

    QString locId = QString::number(m_local_id);
    root.setAttribute("localId", locId);
    if (!is_floats_equal(0, m_width))
    {
        root.setAttribute("width", m_width);
    }
    if (!is_floats_equal(0, m_height))
    {
        root.setAttribute("height", m_height);
    }
    root.setAttribute("label", m_label);
    if (m_exec_order > 0)
    {
        root.setAttribute("executionOrderId", m_exec_order);
    }
    if (!m_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_global_id);
    }

    root.appendChild(m_position.dom_node());
    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }
    if (!m_documentation.is_empty())
    {
        root.appendChild(m_documentation.dom_node());
    }

    return root;
}
