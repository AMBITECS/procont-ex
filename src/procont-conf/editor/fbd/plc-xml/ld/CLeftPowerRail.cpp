//
// Created by artem on 1/9/25.
//

#include "CLeftPowerRail.h"

CLeftPowerRail::CLeftPowerRail(CBody *parent)
{
    m_parent = parent;
    m_add_data = new CAddData();
    m_position = new CPosition();
    m_doc      = new CDocumentation();
    m_connection_point_out = new CConnectionPointOut();
}

CLeftPowerRail::CLeftPowerRail()
{
    m_parent = nullptr;
    m_add_data = new CAddData();
    m_position = new CPosition();
    m_doc      = new CDocumentation();
    m_connection_point_out = new CConnectionPointOut();
}

CLeftPowerRail::CLeftPowerRail(const CLeftPowerRail &other)
{
    m_parent = other.m_parent;
    m_add_data = new CAddData(*other.m_add_data);
    m_position = new CPosition(*other.m_position);
    m_doc      = new CDocumentation(*other.m_doc);
    m_connection_point_out = new CConnectionPointOut(*other.m_connection_point_out);

    m_width = other.m_width;
    m_height = other.m_height;
    m_execution_order = other.m_execution_order;
    m_global_id = other.m_global_id;
}

CLeftPowerRail::CLeftPowerRail(CBody *parent, const QDomNode &node)
{
    m_parent = parent;

    m_local_id = node.attributes().namedItem("localId").toAttr().value().toLongLong();
    m_height   = node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width    = node.attributes().namedItem("width").toAttr().value().toFloat();
    m_execution_order = node.attributes().namedItem("executionOrderId").toAttr().value().toLong();
    m_global_id= node.attributes().namedItem("globalId").toAttr().value().toStdString();

    auto pos_node = node.namedItem("position");
    m_position = new CPosition(pos_node);

    auto ad_node = node.namedItem("addData");
    m_add_data = new CAddData(ad_node);

    auto doc_node = node.namedItem("documentation");
    m_doc = new CDocumentation(doc_node);

    auto conn_node = node.namedItem("connectionPointOut");
    m_connection_point_out = new CConnectionPointOut(conn_node);
}

CLeftPowerRail::~CLeftPowerRail()
{
    delete m_connection_point_out;
    delete m_add_data;
    delete m_position;
    delete m_doc;
}

CBody *CLeftPowerRail::parent()
{
    return m_parent;
}

void CLeftPowerRail::set_parent(CBody *parent)
{
    m_parent = parent;
}

QDomNode CLeftPowerRail::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("leftPowerRail");

    QString ull_val = QString::number(m_local_id);
    root.setAttribute("localId", ull_val);

    if (!is_floats_equal(m_height, 0))
    {
        root.setAttribute("height", m_height);
    }

    if (!is_floats_equal(m_width, 0))
    {
        root.setAttribute("width", m_width);
    }

    if (m_execution_order != 0)
    {
        root.setAttribute("executionOrderId", m_execution_order);
    }

    if (!m_global_id.empty())
    {
        root.setAttribute("globalId", m_global_id.c_str());
    }

    root.appendChild(m_position->dom_node());

    if (!m_connection_point_out->is_empty())
    {
        root.appendChild(m_connection_point_out->dom_node());
    }

    if (!m_add_data->is_empty())
    {
        root.appendChild(m_add_data->dom_node());
    }

    if (!m_doc->is_empty())
    {
        root.appendChild(m_doc->dom_node());
    }

    return root;
}

uint64_t CLeftPowerRail::local_id() const
{
    return m_local_id;
}

void CLeftPowerRail::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CLeftPowerRail::height() const
{
    return m_height;
}

void CLeftPowerRail::set_height(const float &height)
{
    m_height = height;
}

float CLeftPowerRail::width() const
{
    return m_width;
}

void CLeftPowerRail::set_width(const float &width)
{
    m_width = width;
}

uint32_t CLeftPowerRail::execution_order() const
{
    return m_execution_order;
}

void CLeftPowerRail::set_execution_order(const uint32_t &order)
{
    m_execution_order = order;
}

QString CLeftPowerRail::global_id() const
{
    return m_global_id.empty() ? "" : m_global_id.c_str();
}

void CLeftPowerRail::set_global_id(const QString &glob_id)
{
    if (!glob_id.isNull() && !glob_id.isEmpty())
    {
        m_global_id = glob_id.toStdString();
    }
}

CPosition *CLeftPowerRail::position()
{
    return m_position;
}

CAddData *CLeftPowerRail::add_data()
{
    return m_add_data;
}

CDocumentation *CLeftPowerRail::documentation()
{
    return m_doc;
}

CConnectionPointOut *CLeftPowerRail::connection_point_out()
{
    return m_connection_point_out;
}
