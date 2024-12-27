//
// Created by artem on 12/27/24.
//

#include "CInstances.h"

CInstances::CInstances(CProject *parent)
{
    m_parent = parent;
    m_configurations = new std::vector<CConfiguration*>();
}

CInstances::CInstances(const CInstances & other)
{
    m_parent = other.m_parent;
    m_configurations = new std::vector<CConfiguration*>();

    for (auto &item : *other.m_configurations)
    {
        auto config = new CConfiguration(*item);
        m_configurations->push_back(config);
    }
}

CInstances::CInstances(CProject *parent, const QDomNode &node)
{
    m_parent = parent;
    m_configurations = new std::vector<CConfiguration*>();

    if (node.nodeName() == "instances")
    {
        QDomNode container = node.namedItem("configurations");

        for (int i = 0; i < container.childNodes().count(); i++)
        {
            auto child = container.childNodes().at(i);

            auto conf = new CConfiguration(this, child);
            m_configurations->push_back(conf);
        }
    }
}

CInstances::~CInstances()
{
    for (auto &item : *m_configurations)
    {
        delete item;
    }
    delete m_configurations;
}

QDomNode CInstances::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("instances");
    auto container = doc.createElement("configurations");

    for (auto &conf : *m_configurations)
    {
        container.appendChild(conf->dom_node());
    }

    root.appendChild(container);

    return root;
}

CProject *CInstances::parent()
{
    return m_parent;
}

CConfiguration *CInstances::add_configuration(CConfiguration *configuration)
{
    if (!configuration)
    {
        return nullptr;
    }

    configuration->set_parent(this);

    for(auto &item : *m_configurations)
    {
        if (item == configuration)
        {
            return nullptr;
        }
    }

    m_configurations->push_back(configuration);

    return m_configurations->back();
}

CConfiguration *CInstances::add_configuration()
{
    m_configurations->emplace_back(new CConfiguration(this));
    return m_configurations->back();
}

CConfiguration *CInstances::remove_configuration(CConfiguration *configuration)
{
    if (!configuration)
    {
        return nullptr;
    }

    int counter = 0;

    for (auto &conf : *m_configurations)
    {
        if (conf == configuration)
        {
            m_configurations->erase(m_configurations->begin() + counter);
            return configuration;
        }
        counter++;
    }

    return nullptr;
}

CConfiguration *CInstances::remove_configuration(const uint16_t &index)
{
    if (index >= m_configurations->size())
    {
        return nullptr;
    }

    CConfiguration *config = m_configurations->at(index);
    m_configurations->erase(m_configurations->begin() + index);

    return config;
}

CConfiguration *CInstances::get_configuration(const uint16_t &index)
{
    if (index >= m_configurations->size())
    {
        return nullptr;
    }

    return m_configurations->at(index);
}

std::vector<CConfiguration *> *CInstances::configurations()
{
    return m_configurations;
}

CConfiguration *CInstances::find_config_by_name(const QString &name)
{
    for (auto &conf : *m_configurations)
    {
        if (conf->name() == name)
        {
            return conf;
        }
    }
    return nullptr;
}

bool CInstances::is_empty() const
{
    return m_configurations->empty();
}
