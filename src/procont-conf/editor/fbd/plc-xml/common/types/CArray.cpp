//
// Created by artem on 11/20/24.
//

#include "CArray.h"

CArray::CArray()
{
    m_type = EUserTypes::UT_ARRAY;
}

CArray::CArray(const CArray &other)
{
    m_type = EUserTypes::UT_ARRAY;
    m_upper = other.m_upper;
    m_lower = other.m_lower;
    m_base_type = other.m_base_type;
    m_name = other.m_name;
}

CArray::CArray(const QDomNode &node)
{
    m_type = EUserTypes::UT_ARRAY;
    m_name = node.attributes().namedItem(xmln::name).toAttr().value();
    auto arr_node = node.firstChild().firstChild();
    if (arr_node.nodeName() != (QString)xmln::array_node)
    {
        throw std::runtime_error("wrong node in 'CArray::CArray(const QDomNode &node)'");
    }

    auto dim_node = arr_node.namedItem(xmln::array_dim);
    auto base_type = arr_node.namedItem(xmln::base_type);

    m_lower = dim_node.attributes().namedItem(xmln::array_lower).toAttr().value().toInt();
    m_upper = dim_node.attributes().namedItem(xmln::array_upper).toAttr().value().toInt();
    QString bt_name = base_type.firstChild().nodeName();

    m_base_type = get_type_from_string(bt_name.toStdString());
}

CArray::~CArray()
= default;

QDomNode CArray::dom_node() const
{
    QDomDocument doc;
    auto root = doc.createElement(xmln::datatype);
    root.setAttribute(xmln::name, m_name);
    auto bt = root.appendChild(doc.createElement(xmln::base_type));
    auto arr = bt.appendChild(doc.createElement(xmln::array_node));

    auto dim = doc.createElement(xmln::array_dim);
    dim.setAttribute(xmln::array_lower, m_lower);
    dim.setAttribute(xmln::array_upper, m_upper);

    auto bt_name = doc.createElement(xmln::base_type);
    bt_name.appendChild(doc.createElement(base_types_names[m_base_type]));

    arr.appendChild(dim);
    arr.appendChild(bt_name);

    return root;
}

EDefinedDataTypes CArray::base_type() const
{
    return m_base_type;
}

QString CArray::base_type_name() const
{
    return base_types_names[m_base_type];
}

void CArray::set_base_type(const EDefinedDataTypes &type)
{
    m_base_type = type;
}

void CArray::set_base_type(const QString &type)
{
    m_base_type = get_type_from_string(type.toStdString());
}

int CArray::dimension_lower() const
{
    return m_lower;
}

void CArray::set_dim_lower(const int &dimension)
{
    m_lower = dimension;
}

int CArray::dimension_upper() const
{
    return m_upper;
}

void CArray::set_dim_upper(const int &upper)
{
    m_upper = upper;
}
