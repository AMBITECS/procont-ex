//
// Created by artem on 10/20/24.
//

#include "CInfo.h"


CInfo::CInfo()
= default;

CInfo::CInfo(const CInfo &src)
= default;

CInfo::CInfo(CInfo && tmp) noexcept
    : m_name(std::move(tmp.m_name))
    , m_vendor(std::move(tmp.m_vendor))
    , m_description(std::move(tmp.m_description))
    , m_version(tmp.m_version)
{}

CInfo::CInfo(const QDomNode &node)
{
    /// может проверку замутить на имя ноды - это вообще "info" или нет...
    m_name          = node.attributes().namedItem("name").toAttr().value();
    m_version       = node.attributes().namedItem("version").toAttr().value().toFloat();
    m_vendor        = node.attributes().namedItem("vendor").toAttr().value();
    m_description   = node.firstChild().nodeValue();
}

CInfo::~CInfo()
= default;

QDomNode CInfo::dom_node()
{
    QDomDocument doc;
    auto elem = doc.createElement("info");
    elem.setAttribute("name", m_name);
    elem.setAttribute("version", m_version);
    elem.setAttribute("vendor", m_vendor);

    auto desc = doc.createElement("description");
    desc.setNodeValue(m_description);

    elem.appendChild(desc);

    return elem;
}

QString CInfo::name() const
{
    return m_name;
}

void CInfo::set_name(const QString &name)
{
    m_name = name;
}

float CInfo::version() const
{
    return m_version;
}

void CInfo::set_version(const float &version)
{
    m_version = version;
}

QString CInfo::vendor() const
{
    return m_vendor;
}

void CInfo::set_vendor(const QString &vendor)
{
    m_vendor = vendor;
}

QString CInfo::description() const
{
    return m_description;
}

void CInfo::set_description(const QString &descript)
{
    m_description = descript;
}
