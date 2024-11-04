//
// Created by artem on 10/20/24.
//

#include "CInOutVariables.h"

CInOutVariable::CInOutVariable()
= default;

CInOutVariable::CInOutVariable(const CInOutVariable &other)
{
    *this = other;
}

CInOutVariable::CInOutVariable(const QDomNode &dom_node)
{
    m_local_id      = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_height        = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_width         = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_exec_order    = dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_negated_in    = dom_node.attributes().namedItem("negatedIn").toAttr().value().toInt();
    m_negated_out   = dom_node.attributes().namedItem("negatedOut").toAttr().value().toInt();
    m_storage_in    = (EStorageMode)dom_node.attributes().namedItem("storageIn").toAttr().value().toInt();
    m_storage_out   = (EStorageMode)dom_node.attributes().namedItem("storageOut").toAttr().value().toInt();
    m_edge_in       = (EEdge)dom_node.attributes().namedItem("edgeIn").toAttr().value().toInt();
    m_edge_out      = (EEdge)dom_node.attributes().namedItem("edgeOut").toAttr().value().toInt();
    m_global_id     = dom_node.attributes().namedItem("globalId").toAttr().value();

    // TODO: закончить!!!
}

CInOutVariable::~CInOutVariable()
= default;

QDomNode CInOutVariable::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("inOutVariable");
    QString locId = QString::number(m_local_id);

    root.setAttribute("localId", locId);

    if (!is_floats_equal(m_height, 0))
        root.setAttribute("height", m_height);
    if (!is_floats_equal(m_width, 0))
        root.setAttribute("width", m_width);
    if (m_exec_order)
        root.setAttribute("executionOrderId", m_exec_order);

    root.setAttribute("negatedIn", m_negated_in);
    root.setAttribute("negatedOut", m_negated_out);
    root.setAttribute("edgeIn", edge_types_names[m_edge_in]);
    root.setAttribute("edgeOut", edge_types_names[m_edge_out]);
    root.setAttribute("storageIn", storage_behaviour_names[m_storage_in]);
    root.setAttribute("storageOut", storage_behaviour_names[m_storage_out]);

    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_position.dom_node());

    if (!m_point_in.is_empty())
        root.appendChild(m_point_in.dom_node());
    if (!m_point_out.is_empty())
        root.appendChild(m_point_out.dom_node());
    root.appendChild(m_expression.dom_node());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

uint64_t CInOutVariable::local_id() const
{
    return m_local_id;
}

void CInOutVariable::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CInOutVariable::width() const
{
    return m_width;
}

void CInOutVariable::set_width(const float &width)
{
    m_width = width;
}

float CInOutVariable::height() const
{
    return m_height;
}

void CInOutVariable::set_height(const float &height)
{
    m_height = height;
}

uint16_t CInOutVariable::execution_order_id() const
{
    return m_exec_order;
}

void CInOutVariable::set_exec_order_id(const uint16_t &exec_order)
{
    m_exec_order = exec_order;
}

bool CInOutVariable::negated_in() const
{
    return m_negated_in;
}

void CInOutVariable::set_negated_in(const bool &negated)
{
    m_negated_in = negated;
}

EEdge CInOutVariable::edge_in() const
{
    return m_edge_in;
}

void CInOutVariable::set_edge_in(const EEdge &edge_in_type)
{
    m_edge_in = edge_in_type;
}

EStorageMode CInOutVariable::storage_behaviour_in() const
{
    return m_storage_in;
}

void CInOutVariable::set_storage_behaviour_in(const EStorageMode &behaviour_in)
{
    m_storage_in = behaviour_in;
}

bool CInOutVariable::negated_out() const
{
    return m_negated_out;
}

void CInOutVariable::set_negated_out(const bool &negated_out)
{
    m_negated_out = negated_out;
}

EEdge CInOutVariable::edge_out() const
{
    return m_edge_out;
}

void CInOutVariable::set_edge_out(const EEdge &edge)
{
    m_edge_out = edge;
}

EStorageMode CInOutVariable::storage_behaviour_out() const
{
    return m_storage_out;
}

void CInOutVariable::set_storage_behaviour_out(const EStorageMode &behaviour_out)
{
    m_storage_out = behaviour_out;
}

QString CInOutVariable::global_id() const
{
    return m_global_id;
}

void CInOutVariable::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CPosition *CInOutVariable::position()
{
    return &m_position;
}

CExpression *CInOutVariable::expression()
{
    return &m_expression;
}

CConnectionPointIn *CInOutVariable::point_in()
{
    return &m_point_in;
}

CConnectionPointOut *CInOutVariable::point_out()
{
    return &m_point_out;
}

CAddData *CInOutVariable::add_data()
{
    return &m_add_data;
}

CDocumentation *CInOutVariable::documentation()
{
    return &m_documentation;
}

CInOutVariable &CInOutVariable::operator=(const CInOutVariable &rhs)
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
    m_negated_in    = rhs.m_negated_in;
    m_negated_out   = rhs.m_negated_out;
    m_edge_in       = rhs.m_edge_in;
    m_edge_out      = rhs.m_edge_out;
    m_storage_in    = rhs.m_storage_in;
    m_storage_out   = rhs.m_storage_out;

    m_position      = rhs.m_position;
    m_expression    = rhs.m_expression;
    m_point_in      = rhs.m_point_in;
    m_point_out     = rhs.m_point_out;
    m_add_data      = rhs.m_add_data;
    m_documentation = rhs.m_documentation;

    return *this;
}

bool CInOutVariable::is_empty() const
{
    bool empty  = is_floats_equal(0, m_position.x()) &&
                  is_floats_equal(0, m_position.y()) &&
                  !m_local_id &&
                  m_expression.is_empty();
    return empty;
}
//----------------------------------------------------------------------------------------------------------------------
// CInOutVariables -----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInOutVariables::CInOutVariables()
{
    m_variables = new QList<CInOutVariable*>();
}

CInOutVariables::CInOutVariables(const CInOutVariables &other)
{
    m_variables = new QList<CInOutVariable*>();
    *this = other;
}

CInOutVariables::CInOutVariables(CInOutVariables &&other) noexcept
{
    m_variables = other.m_variables;
    other.m_variables = nullptr;
}

CInOutVariables::CInOutVariables(const QDomNode &dom_node)
{
    QString name = dom_node.nodeName();
    if (name != "inOutVariables")
    {
        throw std::runtime_error("CInOutVariables::CInOutVariables(QDomNode) - QDomNode has wrong name");
    }

    m_variables = new QList<CInOutVariable*>();

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);
        auto var = new CInOutVariable(child);
        m_variables->push_back(var);
    }
}

CInOutVariables::~CInOutVariables()
{
    if (!m_variables)
    {
        return;
    }

    clean();
    delete m_variables;
}

CInOutVariables &CInOutVariables::operator=(const CInOutVariables &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    for (auto &item : *m_variables)
    {
        delete item;
    }

    m_variables->clear();

    for (auto &alien : *rhs.m_variables)
    {
        auto in_out = new CInOutVariable(*alien);
        m_variables->push_back(in_out);
    }

    return *this;
}

QDomNode CInOutVariables::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("outputVariables");

    for (auto &item : *m_variables)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

QList<CInOutVariable *> *CInOutVariables::in_out_variables()
{
    return m_variables;
}

void CInOutVariables::clean()
{
    for (auto &item : *m_variables)
    {
        delete item;
    }

    m_variables->clear();
}

bool CInOutVariables::is_empty() const
{
    return m_variables->isEmpty();
}
