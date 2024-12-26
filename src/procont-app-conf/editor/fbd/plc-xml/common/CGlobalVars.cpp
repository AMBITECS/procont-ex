//
// Created by artem on 12/26/24.
//

#include "CGlobalVars.h"

CGlobalVars::CGlobalVars(CResource *parent)
{
    m_parent = parent;
    m_variables = new std::vector<CVariable*>();
}

CGlobalVars::CGlobalVars(CResource *parent, const QDomNode &node)
{
    m_parent = parent;
    m_variables = new std::vector<CVariable*>();

    if (node.nodeName() == "globalVars")
    {
        for (int i = 0; i < node.childNodes().count(); i++)
        {
            auto child = node.childNodes().at(i);
            auto var = new CVariable(child, nullptr);
            var->set_global_parent(m_parent);
            m_variables->push_back(var);
        }
    }
}

CGlobalVars::CGlobalVars(const CGlobalVars &src)
{
    m_parent = src.m_parent;
    m_variables = new std::vector<CVariable*>();

    for (auto &alien : *src.m_variables)
    {
        auto var = new CVariable(*alien);
        var->set_global_parent(m_parent);
        m_variables->push_back(var);
    }
}

CGlobalVars::~CGlobalVars()
{
    for (auto &item : *m_variables)
    {
        delete item;
    }
    delete m_variables;
}

QDomNode CGlobalVars::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("globalVars");

    for (auto &var : *m_variables)
    {
        root.appendChild(var->dom_node());
    }

    return root;
}

bool CGlobalVars::is_empty() const
{
    return m_variables->empty();
}

CResource *CGlobalVars::parent()
{
    return m_parent;
}

CVariable *CGlobalVars::add_variable(CVariable *global_var)
{
    if (!global_var)
    {
        return nullptr;
    }

    global_var->set_global_parent(m_parent);
    m_variables->push_back(global_var);
    return m_variables->back();
}

CVariable *CGlobalVars::remove_var(CVariable *variable)
{
    int index = 0;

    for (auto &var : *m_variables)
    {
        if (var == variable)
        {
            m_variables->erase(m_variables->begin() + index);
            return variable;
        }
        index++;
    }
    return nullptr;
}

CVariable *CGlobalVars::remove_var(const uint16_t &index)
{
    if (index >= m_variables->size())
    {
        return nullptr;
    }

    CVariable * var = m_variables->at(index);
    m_variables->erase(m_variables->begin() + index);

    return var;
}

std::vector<CVariable *> *CGlobalVars::variables()
{
    return m_variables;
}
