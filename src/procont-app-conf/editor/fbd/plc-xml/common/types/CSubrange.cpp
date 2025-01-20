//
// Created by artem on 11/21/24.
//

#include "CSubrange.h"

CSubrange::CSubrange()
{
    m_type = EUserTypes::UT_SUB_RANGE;
}

CSubrange::CSubrange(const CSubrange &other)
    : m_lower(other.m_lower)
    , m_upper(other.m_upper)
    , m_base_type(other.m_base_type)
{
    m_type = other.m_type;
    m_name = other.m_name;
}

CSubrange::CSubrange(const QDomNode &node)
{
    m_type = EUserTypes::UT_SUB_RANGE;

    if (node.isNull())
    {
        return;
    }
    m_name = node.attributes().namedItem(xmln::name).toAttr().value();
    auto base_type = node.namedItem(xmln::base_type);
    auto init_val = node.namedItem(xmln::initial_value_node);

    if (base_type.isNull())
    {
        return;
    }

    /// define base of the range
    auto wrapper = base_type.firstChild();
    auto range_node = wrapper.namedItem(xmln::range_node);
    m_lower = range_node.attributes().namedItem(xmln::array_lower).toAttr().value().toInt();
    m_upper = range_node.attributes().namedItem(xmln::array_upper).toAttr().value().toInt();

    /// define base type
    auto type_node = wrapper.namedItem(xmln::base_type);
    m_base_type_name = type_node.firstChild().nodeName();
    m_base_type = get_type_from_string(m_base_type_name.toStdString());
    // TODO: реализовать derived тип

    /// define init value
    auto simple_val = init_val.firstChild();
    m_init_val = simple_val.attributes().namedItem(xmln::name).toAttr().value();
}

CSubrange::~CSubrange()
= default;

QDomNode CSubrange::dom_node() const
{
    QDomDocument doc;
    auto root = doc.createElement(xmln::datatype);
    auto subRange_signed = root.appendChild(doc.createElement(xmln::base_type).appendChild(
                                                        doc.createElement(xmln::subrange_node)));
    auto range = subRange_signed.appendChild(doc.createElement(xmln::range_node)).toElement();
    range.setAttribute(xmln::array_lower, m_lower);
    range.setAttribute(xmln::array_upper, m_upper);

    auto bt = subRange_signed.appendChild(doc.createElement(xmln::base_type));
    bt.appendChild(doc.createElement(base_types_names[m_base_type]));

    QDomElement initVal = root.appendChild(doc.createElement(xmln::initial_value_node)).toElement();
    auto simple = initVal.appendChild(doc.createElement(xmln::simple_value)).toElement();
    simple.setAttribute(xmln::value, m_init_val);

    return root;
}

int CSubrange::lower() const
{
    return m_lower;
}

void CSubrange::set_lower(const int &lower)
{
    m_lower = lower;
}

int CSubrange::upper() const
{
    return m_upper;
}

void CSubrange::set_upper(const int &upper)
{
    m_upper = upper;
}

EDefinedDataTypes CSubrange::base_type() const
{
    return m_base_type;
}

void CSubrange::set_base_type(const QString &base_type_name)
{
    m_base_type = get_type_from_string(base_type_name.toStdString());
    m_base_type_name = base_type_name;
}

void CSubrange::set_base_type(const EDefinedDataTypes &base_type)
{
    m_base_type = base_type;
}

QString CSubrange::base_type_name() const
{
    return m_base_type_name;
}
