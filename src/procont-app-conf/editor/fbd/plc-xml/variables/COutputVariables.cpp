//
// Created by artem on 10/20/24.
//

#include "COutputVariables.h"
#include <QList>

COutVariable::COutVariable()
= default;

COutVariable::COutVariable(const COutVariable &other)
{
    *this = other;
}

COutVariable::COutVariable(const QDomNode &dom_node)
{
    m_local_id      = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_height        = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width         = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_exec_order    = dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_negated       = dom_node.attributes().namedItem("negated").toAttr().value().toInt();
    m_storage       = (EStorageMode)dom_node.attributes().namedItem("storage").toAttr().value().toInt();
    m_edge          = (EEdge)dom_node.attributes().namedItem("edge").toAttr().value().toInt();
    m_global_id     = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position      = CPosition(dom_node.namedItem("position"));
    m_expression    = CExpression(dom_node.namedItem("expression"));
    m_point_in      = CConnectionPointIn(dom_node.namedItem("connectionPointIn"));
    m_add_data      = CAddData(dom_node.namedItem("addData"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
}

COutVariable::~COutVariable()
= default;

COutVariable &COutVariable::operator=(const COutVariable &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    m_local_id      = rhs.m_local_id;
    m_exec_order    = rhs.m_exec_order;
    m_width         = rhs.m_width;
    m_height        = rhs.m_height;
    m_global_id     = rhs.m_global_id;
    m_negated       = rhs.m_negated;
    m_edge          = rhs.m_edge;
    m_storage       = rhs.m_storage;

    m_position      = rhs.m_position;
    m_expression    = rhs.m_expression;
    m_point_in     = rhs.m_point_in;
    m_add_data      = rhs.m_add_data;
    m_documentation = rhs.m_documentation;

    return *this;
}

QDomNode COutVariable::dom_node() const
{
    QDomDocument doc;
    QDomElement  root = doc.createElement("outVariable");

    QString locId = QString::number(m_local_id);
    root.setAttribute("localId", locId);
    root.setAttribute("executionOrderId", m_exec_order);
    root.setAttribute("negated", bool_str[m_negated]);

    if (!is_floats_equal(0, m_height) && !is_floats_equal(0, m_width))
    {
        root.setAttribute("width", m_width);
        root.setAttribute("height", m_height);
    }

    if (m_edge != EEdge::EI_NONE)
        root.setAttribute("edge", edge_types_names[m_edge]);
    if (m_storage != EStorageMode::SM_NONE)
        root.setAttribute("storage", storage_behaviour_names[m_storage]);

    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_position.dom_node());
    if (!m_point_in.is_empty())
        root.appendChild(m_point_in.dom_node());
    root.appendChild(m_expression.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

uint64_t COutVariable::local_id() const
{
    return m_local_id;
}

void COutVariable::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float COutVariable::width() const
{
    return m_width;
}

void COutVariable::set_width(const float &width)
{
    m_width = width;
}

float COutVariable::height() const
{
    return m_height;
}

void COutVariable::set_height(const float &height)
{
    m_height = height;
}

uint16_t COutVariable::execution_order_id() const
{
    return m_exec_order;
}

void COutVariable::set_exec_order_id(const uint16_t &exec_order)
{
    m_exec_order = exec_order;
}

bool COutVariable::negated() const
{
    return m_negated;
}

void COutVariable::set_negated(const bool &negated)
{
    m_negated = negated;
}

EEdge COutVariable::edge() const
{
    return m_edge;
}

void COutVariable::set_edge(const EEdge &edge_type)
{
    m_edge = edge_type;
}

EStorageMode COutVariable::storage_behaviour() const
{
    return m_storage;
}

void COutVariable::set_storage_behaviour(const EStorageMode &behaviour)
{
    m_storage = behaviour;
}

QString COutVariable::global_id() const
{
    return m_global_id;
}

void COutVariable::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

bool COutVariable::is_empty() const
{
    return  m_local_id == 0 &&
            is_floats_equal(0, m_position.x()) &&
            is_floats_equal(0, m_position.y()) &&
            m_expression.is_empty();
}

CPosition *COutVariable::position()
{
    return &m_position;
}

CExpression *COutVariable::expression()
{
    return &m_expression;
}

CConnectionPointIn *COutVariable::point_in()
{
    return &m_point_in;
}

CAddData *COutVariable::add_data()
{
    return &m_add_data;
}

CDocumentation *COutVariable::documentation()
{
    return &m_documentation;
}
//----------------------------------------------------------------------------------------------------------------------
// COutputVariables ----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

COutputVariables::COutputVariables()
{
    m_variables = new QList<COutVariable*>();
}

COutputVariables::COutputVariables(const COutputVariables &other)
{
    m_variables = new QList<COutVariable*>();

    for (auto &alien : *other.m_variables)
    {
        auto item = new COutVariable(*alien);
        m_variables->push_back(item);
    }
}

COutputVariables::COutputVariables(COutputVariables &&other) noexcept
{
    m_variables = other.m_variables;
    other.m_variables = nullptr;
}

COutputVariables::COutputVariables(const QDomNode &dom_node)
{
    QString name = dom_node.nodeName();
    if (name != "outputVariables")
    {
        throw std::runtime_error("in 'COutputVariables::COutputVariables(const QDomNode &dom_node)' wrong node name");
    }

    m_variables = new QList<COutVariable*>();

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);
        auto var = new COutVariable(child);
        m_variables->push_back(var);
    }
}

COutputVariables::~COutputVariables()
{
    if (!m_variables)
    {
        return;
    }

    clean();
    delete m_variables;
}

QDomNode COutputVariables::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("outputVariables");
    for (auto &item : *m_variables)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

bool COutputVariables::is_empty() const
{
    return m_variables->empty();
}

QList<COutVariable *> *COutputVariables::variables()
{
    return m_variables;
}

void COutputVariables::clean()
{
    for (auto &item : *m_variables)
    {
        delete item;
    }
    m_variables->clear();
}
