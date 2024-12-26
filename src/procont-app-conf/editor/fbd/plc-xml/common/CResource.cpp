//
// Created by artem on 12/26/24.
//

#include "CResource.h"

CResource::CResource(CConfiguration *parent)
{
    m_parent = parent;
    m_global_vars = new CGlobalVars(this);
    m_task        = new CTask(this);
}

CResource::CResource(CConfiguration *parent, const QDomNode &node)
{
    m_parent = parent;

    QString n_name = node.attributes().namedItem("name").toAttr().value();
    if (!n_name.isNull() && !n_name.isEmpty() && n_name.length() > 0)
    {
        m_name = n_name.toStdString();
    }

    QDomNode task = node.namedItem("task");
    QDomNode glob = node.namedItem("globalVars");

    m_task        = task.isNull() ? new CTask(this)       : new CTask(this, task);
    m_global_vars = glob.isNull() ? new CGlobalVars(this) : new CGlobalVars(this, glob);
}

CResource::CResource(const CResource &other)
{
    m_parent = other.m_parent;
    m_name = other.m_name;

    m_global_vars = new CGlobalVars(*other.m_global_vars);
    m_task = new CTask(*other.m_task);
}

CResource::~CResource()
{
    delete m_global_vars;
    delete m_task;
}

QDomNode CResource::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("resource");
    QString r_name = m_name.empty() ? "" : m_name.c_str();
    root.setAttribute("name", r_name);

    if (!m_global_vars->is_empty())
    {
        root.appendChild(m_global_vars->dom_node());
    }

    if (!m_task->is_empty())
    {
        root.appendChild(m_task->dom_node());
    }

    return root;
}

QString CResource::name() const
{
    return m_name.empty() ? "" : m_name.c_str();
}

void CResource::set_name(const QString &name)
{
    if (!name.isNull() && !name.isEmpty() && name.length() > 0)
    {
        m_name = name.toStdString();
    }
}

CTask *CResource::task()
{
    return m_task;
}

CGlobalVars *CResource::global_vars()
{
    return m_global_vars;
}

CConfiguration *CResource::parent()
{
    return m_parent;
}
