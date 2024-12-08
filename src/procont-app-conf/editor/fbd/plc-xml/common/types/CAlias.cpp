//
// Created by artem on 11/21/24.
//

#include "CAlias.h"

CAlias::CAlias()
{
    m_type = EUserTypes::UT_ALIAS;
}

CAlias::CAlias(const CAlias &other)
{
    m_type = EUserTypes::UT_ALIAS;
    m_name = other.m_name;
    m_base_type = other.m_base_type;
}

CAlias::CAlias(const QDomNode &node)
{
    m_type = EUserTypes::UT_ALIAS;

    if (node.isNull())
    {
        return;
    }

    m_name = node.attributes().namedItem(xmln::name).toAttr().value();

    auto type_name = node.firstChild().firstChild().nodeName();
    m_base_type = get_type_from_string(type_name.toStdString());
}

CAlias::~CAlias()
= default;

QDomNode CAlias::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement(xmln::datatype);
    root.setAttribute(xmln::name, m_name);
    auto bt = root.appendChild(doc.createElement(xmln::base_type));
    bt.appendChild(doc.createElement(base_types_names[m_base_type]));

    return root;
}

EDefinedDataTypes CAlias::base_type() const
{
    return m_base_type;
}

QString CAlias::base_type_name() const
{
    return base_types_names[m_base_type];
}

void CAlias::set_base_type(const QString &base_type_name)
{
    m_base_type = get_type_from_string(base_type_name.toStdString());
}

void CAlias::set_base_type(const EDefinedDataTypes &base_type)
{
    m_base_type = base_type;
}
