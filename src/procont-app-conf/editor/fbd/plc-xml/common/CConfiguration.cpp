//
// Created by artem on 12/27/24.
//

#include "CConfiguration.h"

CConfiguration::CConfiguration(CInstances *parent)
{
    m_parent = parent;
    m_resources = new std::vector<CResource*>();
}

CConfiguration::CConfiguration(CInstances *parent, const QDomNode &node)
{
    m_parent = parent;
    m_resources = new std::vector<CResource*>();

    if (node.nodeName() == "configuration")
    {
        QString txt = node.attributes().namedItem("name").toAttr().value();
        if (!txt.isEmpty() && !txt.isNull() && !txt.isDetached())
        {
            m_name = txt.toStdString();
        }

        for (int i = 0; i < node.childNodes().count(); i++)
        {
            auto child = node.childNodes().at(i);

            auto res = new CResource(this, child);
            m_resources->push_back(res);
        }
    }
}

CConfiguration::CConfiguration(const CConfiguration & other)
{
    m_parent = other.m_parent;
    m_resources = new std::vector<CResource*>();
    m_name = other.m_name;

    for (auto &item : *other.m_resources)
    {
        auto res = new CResource(*item);
        m_resources->push_back(res);
    }
}

CConfiguration::~CConfiguration()
{
    for (auto &item : *m_resources)
    {
        delete item;
    }
    delete m_resources;
}

QDomNode CConfiguration::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("configuration");

    QString name = m_name.empty() ? "" : m_name.c_str();
    root.setAttribute("name", name);

    for (auto &item : *m_resources)
    {
        root.appendChild(item->dom_node());
    }

    return root;
}

bool CConfiguration::is_empty() const
{
    return m_name.empty() && m_resources->empty();
}

QString CConfiguration::name() const
{
    return m_name.empty() ? "" : m_name.c_str();
}

void CConfiguration::set_name(const QString &name)
{
    if (!name.isEmpty() && !name.isNull() && !name.isDetached())
    {
        m_name = name.toStdString();
    }
}

CInstances *CConfiguration::parent()
{
    return m_parent;
}

void CConfiguration::set_parent(CInstances *parent)
{
    m_parent = parent;
}

std::vector<CResource *> *CConfiguration::resources()
{
    return m_resources;
}
