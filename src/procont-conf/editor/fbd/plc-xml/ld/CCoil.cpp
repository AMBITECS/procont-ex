//
// Created by artem on 1/9/25.
//

#include "CCoil.h"
#include "editor/fbd/plc-xml/CInterface.h"
#include "editor/fbd/plc-xml/common/CBody.h"
#include "editor/fbd/plc-xml/common/CPou.h"


CCoil::CCoil()
{
    m_parent = nullptr;
    m_position = new CPosition();
    m_connection_point_in = new CConnectionPointIn();
    m_connection_point_out = new CConnectionPointOut();
    m_variable = new CVariable(nullptr);
    m_add_data = new CAddData();
    m_documentation = new CDocumentation();
}

CCoil::CCoil(const CCoil & other)
{
    m_parent = other.m_parent;
    m_position = new CPosition(*other.m_position);
    m_connection_point_in = new CConnectionPointIn(*other.m_connection_point_in);
    m_connection_point_out = new CConnectionPointOut(*other.m_connection_point_out);
    m_variable = new CVariable(*other.m_variable);
    m_add_data = new CAddData(*other.m_add_data);
    m_documentation = new CDocumentation(*other.m_documentation);

    m_global_id = other.m_global_id;
    m_storage = other.m_storage;
    m_edge = other.m_edge;
    m_negated = other.m_negated;
    m_execution_order = other.m_execution_order;
    m_width = other.m_width;
    m_height = other.m_height;
    m_local_id = other.m_local_id;
}

CCoil::CCoil(CBody *parent)
{
    m_parent = parent;
    m_variable = new CVariable(m_parent->parent()->interface());
    m_position = new CPosition();
    m_connection_point_in = new CConnectionPointIn();
    m_connection_point_out = new CConnectionPointOut();
    m_add_data = new CAddData();
    m_documentation = new CDocumentation();
}

CCoil::CCoil(CBody *parent, const QDomNode &node)
{
    m_parent = parent;
    m_local_id = node.attributes().namedItem("localId").toAttr().value().toLongLong();
    m_height   = node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width    = node.attributes().namedItem("width").toAttr().value().toFloat();
    m_execution_order = node.attributes().namedItem("executionOrderId").toAttr().value().toLong();
    m_negated = !node.attributes().namedItem("negated").toAttr().isNull() &&
                node.attributes().namedItem("negated").toAttr().value().toStdString() == "true";
    m_edge    = node.attributes().namedItem("edge").toAttr().isNull() ? EEdge::EI_NONE :
                get_edge_from_string(node.attributes().namedItem("edge").toAttr().value());
    m_storage = node.attributes().namedItem("storage").toAttr().isNull() ? EStorageMode::SM_NONE :
                get_storage_from_str(node.attributes().namedItem("storage").toAttr().value());
    m_global_id = node.attributes().namedItem("globalId").toAttr().value().toStdString();

    m_variable = new CVariable(node.namedItem("variable"), m_parent->parent()->interface());
    m_position = new CPosition(node.namedItem("position"));
    m_connection_point_in = new CConnectionPointIn(node.namedItem("connectionPointIn"));
    m_connection_point_out = new CConnectionPointOut(node.namedItem("connectionPointOut"));
    m_add_data = new CAddData(node.namedItem("addData"));
    m_documentation = new CDocumentation(node.namedItem("documentation"));
}

CCoil::~CCoil()
{
    delete m_parent;
    delete m_position;
    delete m_connection_point_in;
    delete m_connection_point_out;
    delete m_variable;
    delete m_add_data;
    delete m_documentation;
}

CBody *CCoil::parent()
{
    return m_parent;
}

void CCoil::set_parent(CBody *parent)
{
    m_parent = parent;
    delete m_variable;
    m_variable = new CVariable(m_parent->parent()->interface());
}

QDomNode CCoil::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("coil");

    QString loc_id = QString::number(m_local_id);
    root.setAttribute("localId", loc_id);

    if (!is_floats_equal(m_width, 0))
    {
        root.setAttribute("width", m_width);
    }
    if (!is_floats_equal(m_height, 0))
    {
        root.setAttribute("height", m_height);
    }
    if (m_execution_order > 0)
    {
        root.setAttribute("executionOrder", m_execution_order);
    }
    if (m_negated)
    {
        root.setAttribute("negated", bool_str[m_negated]);
    }
    if (m_storage != EStorageMode::SM_NONE)
    {
        root.setAttribute("storage", storage_behaviour_names[m_storage]);
    }
    if (m_edge != EEdge::EI_NONE)
    {
        root.setAttribute("edge", edge_types_names[m_edge]);
    }
    if (m_global_id.length() > 0)
    {
        root.setAttribute("globalId", m_global_id.c_str());
    }

    root.appendChild(m_position->dom_node());

    if (!m_connection_point_in->is_empty())
    {
        root.appendChild(m_connection_point_in->dom_node());
    }
    if (!m_connection_point_out->is_empty())
    {
        root.appendChild(m_connection_point_out->dom_node());
    }

    root.appendChild(m_variable->dom_node());

    if (!m_add_data->is_empty())
    {
        root.appendChild(m_add_data->dom_node());
    }
    if (!m_documentation->is_empty())
    {
        root.appendChild(m_documentation->dom_node());
    }
    return root;
}

uint64_t CCoil::local_id() const
{
    return m_local_id;
}

void CCoil::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

void CCoil::set_height(const float &height)
{
    m_height = height;
}

float CCoil::height() const
{
    return m_height;
}

void CCoil::set_width(const float &width)
{
    m_width = width;
}

float CCoil::width() const
{
    return m_width;
}

uint32_t CCoil::execution_order() const
{
    return m_execution_order;
}

void CCoil::set_execution_order(const uint32_t &order)
{
    m_execution_order = order;
}

void CCoil::set_negated(const bool &negated)
{
    m_negated = negated;
}

bool CCoil::is_negated() const
{
    return m_negated;
}

void CCoil::set_edge(const EEdge &edge_modifier)
{
    m_edge = edge_modifier;
}

EEdge CCoil::edge_modifier() const
{
    return m_edge;
}

void CCoil::set_storage(const EStorageMode &storage_modifier)
{
    m_storage = storage_modifier;
}

EStorageMode CCoil::storage_modifier() const
{
    return m_storage;
}

QString CCoil::global_id() const
{
    return m_global_id.empty() ? "" : m_global_id.c_str();
}

void CCoil::set_global_id(const QString &glob_id)
{
    if (glob_id.isNull() || glob_id.isEmpty())
    {
        return;
    }
    m_global_id = glob_id.toStdString();
}

CPosition *CCoil::position()
{
    return m_position;
}

CConnectionPointIn *CCoil::connection_point_in()
{
    return m_connection_point_in;
}

CConnectionPointOut *CCoil::connection_point_out()
{
    return m_connection_point_out;
}

CVariable *CCoil::variable()
{
    return m_variable;
}

CAddData *CCoil::add_data()
{
    return m_add_data;
}

CDocumentation *CCoil::documentation()
{
    return m_documentation;
}
