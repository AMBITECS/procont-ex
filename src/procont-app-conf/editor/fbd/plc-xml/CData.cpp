//
// Created by artem on 10/20/24.
//

#include "CData.h"

CData::CData()
= default;

CData::CData(const CData &src)
    : m_name(src.m_name)
    , m_handle_undef(src.m_handle_undef)
    , m_any(src.m_any)
{}

/*
CData::CData(CData &&tmp) noexcept
    : m_name(std::move(tmp.m_name))
    , m_handle_undef(std::move(tmp.m_handle_undef))
    , m_any(tmp.m_any)
{}*/

CData::CData(const QDomNode &node)
{
    m_name = node.attributes().namedItem("name").toAttr().value();
    m_handle_undef = node.attributes().namedItem("handleUnknown").toAttr().value();

    if (node.hasChildNodes())
    {
        m_any = node.firstChild();
    }
}

CData::~CData()
= default;

QString CData::name() const
{
    return m_name;
}

void CData::set_name(const QString &name)
{
    m_name = name;
}

QString CData::handle_unknown() const
{
    return m_handle_undef;
}

void CData::set_handle_unknown(const QString &handle_unknown)
{
    m_handle_undef = handle_unknown;
}

QDomNode CData::dom_node()
{
    QDomDocument doc;
    auto root = doc.createElement("data");
    root.setAttribute("name", m_name);
    root.setAttribute("handleUnknown", m_handle_undef);

    if (!m_any.isNull())
    {
        root.appendChild(m_any);
    }

    return root;
}


QDomNode CData::any_node() const
{
    return m_any;
}

void CData::set_any_node(const QDomNode &any_instance)
{
    m_any = any_instance;
}
