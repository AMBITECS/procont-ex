//
// Created by artem on 10/20/24.
//

#include "CVariable.h"

CVariable::CVariable()
= default;

CVariable::CVariable(const CVariable &src)
{
//    m_add_data = src.m_add_data;
//    m_type = src.m_type;
//    m_attr_addr = src.m_attr_addr;
//    m_attr_global_id = src.m_attr_global_id;
//    if (!src.m_attr_name.isNull())
//        m_attr_name = src.m_attr_name;
//    m_init_value = src.m_init_value;
//    m_doc = src.m_doc;
    *this = src;
}

CVariable::CVariable(CVariable &&tmp) noexcept
    : m_add_data(tmp.m_add_data)
    , m_type(std::move(tmp.m_type))
    , m_attr_addr(std::move(tmp.m_attr_addr))
    , m_attr_global_id(std::move(tmp.m_attr_global_id))
    , m_attr_name(std::move(tmp.m_attr_name))
    , m_init_value(std::move(tmp.m_init_value))
    , m_doc(tmp.m_doc)
{}

CVariable::CVariable(const QDomNode &node)
{
    if (!node.attributes().namedItem("name").toAttr().isNull())
        m_attr_name = node.attributes().namedItem("name").toAttr().value();
    m_attr_addr = node.attributes().namedItem("address").toAttr().value();
    m_attr_global_id = node.attributes().namedItem("globalId").toAttr().value();

    m_type = node.namedItem("type").firstChild().nodeName();
    if (m_type == "derived")
    {
        m_type = node.namedItem("type").firstChild().attributes().namedItem("name").toAttr().value();
        m_derived_name = m_type;
    }
    m_init_value = node.namedItem("initialValue").firstChild().attributes().namedItem("value").toAttr().value();
    m_doc = CDocumentation(node.namedItem("documentation"));
}

CVariable::~CVariable()
= default;

QDomNode CVariable::dom_node()
{
    QDomDocument doc;
    QDomElement node = doc.createElement("variable");

    /// setup attributes
    node.setAttribute("name", m_attr_name);

    if (!m_attr_addr.isEmpty())
    {
        node.setAttribute("address", m_attr_addr);
    }

    if (!m_attr_global_id.isEmpty())
    {
        node.setAttribute("globalId", m_attr_global_id);
    }

    /// required element 'type'
    QDomElement type_tag = doc.createElement("type");

    QDomElement type;

    if (m_derived_name.isEmpty())
        type = doc.createElement(m_type);
    else
    {
        type = doc.createElement("derived");
        type.setAttribute("name", m_derived_name);
    }
    type_tag.appendChild(type);
    node.appendChild(type_tag);

    /// options
    if (!m_init_value.isEmpty())
    {
        QDomElement init = doc.createElement("initialValue");
        QDomElement simple = doc.createElement("simpleValue");
        simple.setAttribute("value", m_init_value);
        init.appendChild(simple);
        node.appendChild(init);
    }

    if (!m_doc.is_empty())
    {
        node.appendChild(m_doc.dom_node());
    }

    return node;
}

CVariable &
CVariable::operator=(const CVariable &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    m_add_data      = rhs.m_add_data;
    m_type          = rhs.m_type;
    m_attr_addr     = rhs.m_attr_addr;
    m_attr_global_id= rhs.m_attr_global_id;
    m_attr_name     = rhs.m_attr_name;
    m_init_value    = rhs.m_init_value;
    m_doc           = rhs.m_doc;

    return *this;
}

QString CVariable::type() const
{
    return m_type;
}

void
CVariable::set_type(const QString &type)
{
    m_type = type;
}

QString
CVariable::name() const
{
    return m_attr_name;
}

void
CVariable::set_name(const QString &name)
{
    m_attr_name = name;
}

QString
CVariable::address() const
{
    return m_attr_addr;
}

void
CVariable::set_addr(const QString &addr)
{
    m_attr_addr = addr;
}

QString
CVariable::global_id() const
{
    return m_attr_global_id;
}

void
CVariable::set_global_id(const QString &global_id)
{
    m_attr_global_id = global_id;
}

QString
CVariable::init_value() const
{
    return m_init_value;
}

void
CVariable::set_init_value(const QString &str)
{
    m_init_value = str;
}

QString CVariable::comment() const
{
    if (m_doc.is_empty())
        return "";

    return m_doc.documentation();
}

void CVariable::set_comment(const QString &comment)
{
    m_doc.set_document(comment);
}


