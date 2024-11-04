//
// Created by artem on 10/20/24.
//

#include "CInputVariables.h"

CInVariable::CInVariable()
= default;

CInVariable::CInVariable(const CInVariable &other)
{
    *this = other;
}

CInVariable::CInVariable(const QDomNode &dom_node)
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
    m_point_out     = CConnectionPointOut(dom_node.namedItem("connectionPointOut"));
    m_add_data      = CAddData(dom_node.namedItem("addData"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
}

CInVariable::~CInVariable()
= default;

CInVariable &CInVariable::operator=(const CInVariable &rhs)
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
    m_point_out     = rhs.m_point_out;
    m_add_data      = rhs.m_add_data;
    m_documentation = rhs.m_documentation;

    return *this;
}

QDomNode CInVariable::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("inVariable");

    QString locId = QString::number(m_local_id);
    root.setAttribute("localId", locId);
    root.setAttribute("executionOrderId", m_exec_order);

    if (!is_floats_equal(0, m_height) && !is_floats_equal(0, m_width))
    {
        root.setAttribute("width", m_width);
        root.setAttribute("height", m_height);
    }

    if (m_negated)
        root.setAttribute("negated", bool_str[m_negated]);
    if (m_edge != EEdge::EI_NONE)
        root.setAttribute("edge", edge_types_names[m_edge]);
    if (m_storage != EStorageMode::SM_NONE)
        root.setAttribute("storage", storage_behaviour_names[m_storage]);

    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_position.dom_node());
    if (!m_point_out.is_empty())
        root.appendChild(m_point_out.dom_node());
    root.appendChild(m_expression.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

uint64_t CInVariable::local_id() const
{
    return m_local_id;
}

void CInVariable::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CInVariable::width() const
{
    return m_width;
}

void CInVariable::set_width(const float &width)
{
    m_width = width;
}

float CInVariable::height() const
{
    return m_height;
}

void CInVariable::set_height(const float &height)
{
    m_height = height;
}

uint16_t CInVariable::execution_order_id() const
{
    return m_exec_order;
}

void CInVariable::set_exec_order_id(const uint16_t &exec_order)
{
    m_exec_order = exec_order;
}

bool CInVariable::negated() const
{
    return m_negated;
}

void CInVariable::set_negated(const bool &negated)
{
    m_negated = negated;
}

EEdge CInVariable::edge() const
{
    return m_edge;
}

void CInVariable::set_edge(const EEdge &edge_type)
{
    m_edge = edge_type;
}

EStorageMode CInVariable::storage_behaviour() const
{
    return m_storage;
}

void CInVariable::set_storage_behaviour(const EStorageMode &behaviour_in)
{
    m_storage = behaviour_in;
}

QString CInVariable::global_id() const
{
    return m_global_id;
}

void CInVariable::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

bool CInVariable::is_empty() const
{
    return  m_local_id == 0 &&
            is_floats_equal(0, m_position.x()) &&
            is_floats_equal(0, m_position.y()) &&
            m_expression.is_empty();
}

CPosition *CInVariable::position()
{
    return &m_position;
}

CExpression *CInVariable::expression()
{
    return &m_expression;
}

CConnectionPointOut *CInVariable::point_out()
{
    return &m_point_out;
}

CAddData *CInVariable::add_data()
{
    return &m_add_data;
}

CDocumentation *CInVariable::documentation()
{
    return &m_documentation;
}
//----------------------------------------------------------------------------------------------------------------------
// CInputVariables -----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInputVariables::CInputVariables()
{
    m_variables = new QList<CInVariable*>();
}

CInputVariables::CInputVariables(const CInputVariables &other)
{
    m_variables = new QList<CInVariable*>();
    for (auto &item : *other.m_variables)
    {
        auto in = new CInVariable(*item);
        m_variables->push_back(in);
    }
}

CInputVariables::CInputVariables(CInputVariables &&other) noexcept
{
    m_variables = other.m_variables;
    other.m_variables = nullptr;
}

CInputVariables::CInputVariables(const QDomNode &dom_node)
{
    if (dom_node.nodeName() != "inputVariables")
    {
        throw std::runtime_error("in 'CInputVariables::CInputVariables(const QDomNode &dom_node)' wrong node name");
    }

    m_variables = new QList<CInVariable*>();

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);
        auto var = new CInVariable(child);
        m_variables->push_back(var);
    }
}

CInputVariables::~CInputVariables()
{
    if (!m_variables)
        return;

    clean();
    delete m_variables;
}

QDomNode CInputVariables::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("inputVariables");
    for (auto &item : *m_variables)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

bool CInputVariables::is_empty() const
{
    return m_variables->empty();
}

QList<CInVariable *> *CInputVariables::variables()
{
    return m_variables;
}

void CInputVariables::clean()
{
    for (auto &item : *m_variables)
        delete item;
    m_variables->clear();
}
