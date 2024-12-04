//
// Created by nechi on 19.11.2024.
//

#include "CEnum.h"

CEnum::CEnum()
{
    m_type = EUserTypes::UT_ENUM;
    m_values = new std::vector<std::string>();
}

CEnum::CEnum(const CEnum &src)
{
    m_type = UT_ENUM;

    if (src.m_type != m_type)
    {
        throw std::runtime_error("in 'CEnum::CEnum(const CEnum &src)' wrong type");
    }

    m_name = src.m_name;
    m_values = new std::vector<std::string>();
    m_values->insert(m_values->end(), src.m_values->begin(), src.m_values->end());
}

CEnum::CEnum(CEnum && src) noexcept
{
    m_values = src.m_values;
    src.m_values = nullptr;
}

CEnum::CEnum(const QDomNode &node)
{
    if (node.nodeName() != xmln::datatype || node.isNull())
    {
        throw std::runtime_error("in 'CEnum::CEnum(const QDomNode &node)' wrong node");
    }
    m_type = UT_ENUM;

    auto type_name = node.firstChild().firstChild().nodeName();

    if (type_name != (QString)UserTypeName[m_type])
    {
        throw std::runtime_error("in 'CEnum::CEnum(const QDomNode &node)' wrong type");
    }

    m_name = node.attributes().namedItem(xmln::name).toAttr().value();
    m_values = new std::vector<std::string>();
    QDomNode values = node.firstChild().firstChild().firstChild();

    for (int i = 0; i < values.childNodes().count(); i++)
    {
        auto child = values.childNodes().at(i);
        std::string name = child.attributes().namedItem(xmln::name).toAttr().value().toStdString();
        m_values->push_back(name);
    }
}

CEnum::~CEnum()
{
    delete m_values;
}

QDomNode CEnum::dom_node() const
{
    QDomDocument doc;
    auto root = doc.createElement(xmln::datatype);
    root.setAttribute(xmln::name, m_name);

    auto base_type = root.appendChild(doc.createElement(xmln::base_type));
    auto type = base_type.appendChild(doc.createElement(UserTypeName[m_type]));
    auto values = type.appendChild(doc.createElement(xmln::values));

    for (auto &item : *m_values)
    {
        auto value = doc.createElement(xmln::value);
        value.setAttribute(xmln::name, item.c_str());
        values.appendChild(value);
    }

    return root;
}

bool CEnum::add_value(const std::string &value)
{
    if (find_value(value) >= 0)
    {
        return false;
    }
    m_values->push_back(value);
    return true;
}

void CEnum::remove_value(const std::string &value)
{
    int index = find_value(value);
    if (index < 0)
    {
        return;
    }

    m_values->erase(m_values->begin() + index);
}

int CEnum::find_value(const std::string &value)
{
    int counter = 0;
    for (auto &item : *m_values)
    {
        if (item == value)
        {
            return counter;
        }
        counter++;
    }
    return -1;
}

std::vector<std::string> *CEnum::values()
{
    return m_values;
}
