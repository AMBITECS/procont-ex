//
// Created by artem on 10/20/24.
//

#include "CActions.h"

CAction::CAction()
= default;

CAction::CAction(const CAction &other)
{
    *this = other;
}

CAction::CAction(const QDomNode &dom_node)
{
    m_local_id      = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_qualifier     = dom_node.attributes().namedItem("qualifier").toAttr().value();
    m_width         = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_height        = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_duration      = dom_node.attributes().namedItem("duration").toAttr().value();
    m_indicator     = dom_node.attributes().namedItem("indicator").toAttr().value();
    m_exec_order    = dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_global_id     = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_rel_position  = CRelPosition(dom_node.namedItem("relPosition"));
    m_reference     = dom_node.namedItem("reference").nodeValue();
    m_inline        = CInline(dom_node.namedItem("inline"));
    m_connection_point_out = CConnectionPointOut(dom_node.namedItem("connectionPointOut"));
    m_add_data      = CAddData(dom_node.namedItem("addData"));
    m_document      = CDocumentation(dom_node.namedItem("documentation"));
}

CAction::~CAction()
= default;

CAction &CAction::operator=(const CAction &other)
{
    if (this == &other)
        return *this;

    m_reference     = other.m_reference;
    m_global_id     = other.m_global_id;
    m_duration      = other.m_duration;
    m_indicator     = other.m_indicator;
    m_qualifier     = other.m_qualifier;

    m_local_id      = other.m_local_id;
    m_width         = other.m_width;
    m_height        = other.m_height;
    m_exec_order    = other.m_exec_order;

    m_rel_position  = other.m_rel_position;
    m_inline        = other.m_inline;
    m_connection_point_out = other.m_connection_point_out;
    m_add_data      = other.m_add_data;
    m_document      = other.m_document;

    return *this;
}

QDomNode CAction::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("action");

    QString loc_id = QString::number(m_local_id);
    root.setAttribute("localId", loc_id);

    if (!m_qualifier.isEmpty())
        root.setAttribute("qualifier", m_qualifier);
    if (!is_floats_equal(m_width, 0))
        root.setAttribute("width", m_width);
    if (!is_floats_equal(m_height, 0))
        root.setAttribute("height", m_height);
    if (!m_duration.isEmpty())
        root.setAttribute("duration", m_duration);
    if (!m_indicator.isEmpty())
        root.setAttribute("duration", m_duration);
    if (m_exec_order > 0)
        root.setAttribute("executionOrderId", m_exec_order);
    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_rel_position.dom_node());

    if (!m_reference.isEmpty())
    {
        QDomElement elem = doc.createElement("reference");
        elem.setNodeValue(m_reference);
        root.appendChild(elem);
    }

    if (!m_inline.is_empty())
        root.appendChild(m_inline.dom_node());
    if (!m_connection_point_out.is_empty())
        root.appendChild(m_connection_point_out.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_document.is_empty())
        root.appendChild(m_document.dom_node());

    return root;
}

uint64_t CAction::local_id() const
{
    return m_local_id;
}

void CAction::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

QString CAction::qualifier() const
{
    return m_qualifier;
}

void CAction::set_qualifier(const QString &qualifier)
{
    m_qualifier = qualifier;
}

float CAction::width() const
{
    return m_width;
}

void CAction::set_width(const float &width)
{
    m_width = width;
}

float CAction::height() const
{
    return m_height;
}

void CAction::set_height(const float &height)
{
    m_height = height;
}

QString CAction::duration() const
{
    return m_duration;
}

void CAction::set_duration(const QString &duration)
{
    m_duration = duration;
}

QString CAction::indicator() const
{
    return m_indicator;
}

void CAction::set_indicator(const QString &indicator)
{
    m_indicator = indicator;
}

uint32_t CAction::execution_order_id() const
{
    return m_exec_order;
}

void CAction::set_exec_order_id(const uint32_t &order_id)
{
    m_exec_order = order_id;
}

QString CAction::global_id() const
{
    return m_global_id;
}

void CAction::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CRelPosition *CAction::rel_position()
{
    return &m_rel_position;
}

QString CAction::reference() const
{
    return m_reference;
}

void CAction::set_reference(const QString &reference)
{
    m_reference = reference;
}

CInline *CAction::an_inline()
{
    return &m_inline;
}

CConnectionPointOut *CAction::connection_point_out()
{
    return &m_connection_point_out;
}

CAddData *CAction::add_data()
{
    return &m_add_data;
}

CDocumentation *CAction::documentation()
{
    return &m_document;
}

CActions::CActions()
{

}

CActions::CActions(const CActions &actions)
{

}

CActions::CActions(const QDomNode &dom_node)
{

}

CActions::~CActions()
{

}

bool CActions::is_empty() const
{
    return true;
}

QDomNode CActions::dom_node() const
{
    return {};
}
