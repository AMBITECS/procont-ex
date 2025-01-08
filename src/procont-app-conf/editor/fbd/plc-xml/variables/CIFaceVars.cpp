//
// Created by artem on 10/20/24.
//

#include "CIfaceVars.h"
#include "../common/CPou.h"

CIfaceVars::CIfaceVars(CPou *parent)
{
    m_variables = new std::vector<CVariable*>();
    m_parent = parent;
}

CIfaceVars::CIfaceVars(const CIfaceVars &other)
{
    m_variables = new std::vector<CVariable*>(*other.m_variables);
    m_var_type = other.m_var_type;
    m_parent = other.m_parent;
}

CIfaceVars::CIfaceVars(const QDomNode &dom_node, CPou *parent)
{
    m_var_type = dom_node.nodeName();
    m_variables = new std::vector<CVariable*>();
    m_parent    = parent;

    m_name = dom_node.attributes().namedItem("name").toAttr().value();
    m_constant = dom_node.attributes().namedItem("constant").toAttr().value().toInt();
    m_retain = dom_node.attributes().namedItem("retain").toAttr().value().toInt();
    m_persistent = dom_node.attributes().namedItem("persistent").toAttr().value().toInt();

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);
        auto var = new CVariable(child, parent->interface());
        m_variables->push_back(var);
    }
}

CIfaceVars::CIfaceVars(CIfaceVars &&other) noexcept
    : m_var_type(std::move(other.m_var_type))
{
    m_variables = other.m_variables;
    other.m_variables = nullptr;
    m_parent = other.m_parent;
}

CIfaceVars::~CIfaceVars()
{
    if (!m_variables)
    {
        return;
    }

    clean();
    delete m_variables;
}

QDomNode CIfaceVars::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement(m_var_type);

    if (!m_name.isEmpty())
    {
        root.setAttribute("name", m_name);
    }

    root.setAttribute("constant", m_constant);
    root.setAttribute("retain", m_retain);
    root.setAttribute("persistent", m_persistent);

    for (auto &item : *m_variables)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

QString CIfaceVars::name() const
{
    return m_name;
}

void CIfaceVars::set_name(const QString &name)
{
    m_name = name;
}

bool CIfaceVars::is_constant() const
{
    return m_constant;
}

void CIfaceVars::set_constant(const bool &constant)
{
    m_constant = constant;
}

bool CIfaceVars::is_retain() const
{
    return m_retain;
}

void CIfaceVars::set_retain(const bool &retain)
{
    m_retain = retain;
}

bool CIfaceVars::is_persistent() const
{
    return m_persistent;
}

void CIfaceVars::set_persistent(const bool &persistent)
{
    m_persistent = persistent;
}

void CIfaceVars::clean()
{
    for (auto &item : *m_variables)
    {
        delete item;
    }
    m_variables->clear();
}

std::vector<CVariable *> *CIfaceVars::variables()
{
    return m_variables;
}

CAddData *CIfaceVars::add_data()
{
    return &m_add_data;
}

CDocumentation *CIfaceVars::documentation()
{
    return &m_document;
}

bool CIfaceVars::is_empty() const
{
    return m_variables->empty();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CAccessVars::CAccessVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "accessVars";
}

CAccessVars::~CAccessVars()
= default;

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CLocalVars::CLocalVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "localVars";
}

CLocalVars::~CLocalVars()
= default;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CExternalVars::CExternalVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "externalVars";
}

CExternalVars::~CExternalVars()
= default;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTempVars::CTempVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "tempVars";
}

CTempVars::~CTempVars()
= default;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInVars::CInVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "inputVars";
}

CInVars::~CInVars()
= default;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
COutVars::COutVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "outputVars";
}

COutVars::~COutVars()
= default;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInOutVars::CInOutVars(CPou *parent) : CIfaceVars(parent)
{
    m_var_type = "inOutVars";
}

CInOutVars::~CInOutVars()
= default;
