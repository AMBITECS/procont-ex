//
// Created by nechi on 19.11.2024.
//

#include "CStruct.h"

CStruct::CStruct()
{
    m_type = EUserTypes::UT_STRUCT;
    m_variables = new std::vector<CVariable*>();
}

CStruct::CStruct(const CStruct &src)
{
    m_type = EUserTypes::UT_STRUCT;

    if (m_type != src.m_type)
    {
        throw std::runtime_error("in 'CStruct::CStruct(const CStruct &src)' wrong type.");
    }

    m_name = src.m_name;
    m_variables = new std::vector<CVariable*>();

    for (auto &item : *src.m_variables)
    {
        auto var = new CVariable(*item);
        m_variables->push_back(var);
    }
}

CStruct::CStruct(const QDomNode &node)
{
    if (node.isNull() || node.nodeName() != xmln::datatype)
    {
        throw std::runtime_error("wrong node in 'CStruct::CStruct(const QDomNode &node)'");
    }
    m_type = EUserTypes::UT_STRUCT;
    m_name = node.attributes().namedItem(xmln::name).toAttr().value();

    /// check node is STRUCT node
    if (node.firstChild().firstChild().nodeName() != UserTypeName[m_type])
    {
        throw std::runtime_error("wrong type in 'CStruct::CStruct(const QDomNode &node)'");
    }

    m_variables = new std::vector<CVariable*>();

    auto struct_node = node.firstChild().firstChild();

    for (int i = 0; i < struct_node.childNodes().count(); i++)
    {
        auto child = struct_node.childNodes().at(i);
        auto var = new CVariable(child);
        m_variables->push_back(var);
    }
}

CStruct::CStruct(CStruct &&other) noexcept
{
    m_type = other.m_type;
    m_name = std::move(other.m_name);

    m_variables = other.m_variables;
    other.m_variables = nullptr;
}

CStruct::~CStruct()
{
    for (auto &item : *m_variables)
    {
        delete item;
    }
    delete m_variables;
}

QDomNode CStruct::dom_node() const
{
    QDomDocument doc;
    auto root = doc.createElement(xmln::datatype);
    root.setAttribute(xmln::name, m_name);
    auto struct_node = root.appendChild(
                          doc.createElement(xmln::base_type)
                                      .appendChild(
                          doc.createElement(xmln::struct_node)));
    for (auto &var : *m_variables)
    {
        struct_node.appendChild(var->dom_node());
    }

    return root;
}

void CStruct::add_variable(const std::string &name, const EDefinedDataTypes &var_type, const std::string &init_value)
{
    auto var = new CVariable();

    var->set_type(UserTypeName[var_type]);
    var->set_name(name.c_str());
    var->set_init_value( init_value.c_str());

    m_variables->push_back(var);
}

void CStruct::remove_value(const std::string &name)
{
    for (int i = 0; i < m_variables->size(); ++i)
    {
        auto var = m_variables->at(i);
        if (var->name().toStdString() == name)
        {
            m_variables->erase(m_variables->begin() + i);
            delete var;
            return;
        }
    }
}

std::vector<CVariable *> *CStruct::variables()
{
    return m_variables;
}

bool CStruct::is_empty() const
{
    return m_variables->empty();
}


