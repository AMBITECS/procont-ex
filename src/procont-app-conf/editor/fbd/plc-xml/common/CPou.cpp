//
// Created by artem on 10/28/24.
//

#include "CPou.h"

CPou::CPou()
{
    m_interface = new CInterface();
    m_actions = new CActions();
    m_transitions = new CTransitions();
    m_add_data = new CAddData();
    m_doc = new CDocumentation();
    m_bodies = new QList<CBody*>();
}

CPou::CPou(const CPou &other)
{
    m_interface = new CInterface(*other.m_interface);
    m_actions = new CActions(*other.m_actions);
    m_transitions = new CTransitions(*other.m_transitions);
    m_add_data = new CAddData(*other.m_add_data);
    m_doc = new CDocumentation(*other.m_doc);

    m_bodies = new QList<CBody*>();

    for (auto &alien : *other.m_bodies)
    {
        auto body = new CBody(*alien);
        m_bodies->push_back(body);
    }

    m_name = other.m_name;
    m_type = other.m_type;
}

CPou::CPou(const QDomNode &dom_node)
{
    m_bodies = new QList<CBody*>();

    m_interface = new CInterface(dom_node.namedItem("interface"));
    m_actions = new CActions(dom_node.namedItem("actions"));
    m_transitions = new CTransitions(dom_node.namedItem("transitions"));
    m_add_data = new CAddData(dom_node.namedItem("addData"));
    m_doc = new CDocumentation(dom_node.namedItem("documentation"));

    /// standard supposes 1...inf bodies in the pou
    for (int i = 0; i < dom_node.childNodes().count(); ++i)
    {
        auto child = dom_node.childNodes().at(i);
        if (child.nodeName() == "body")
        {
            m_bodies->emplace_back(new CBody(child));
        }
    }
}

CPou::~CPou()
{
    delete m_interface;
    delete m_actions;
    delete m_transitions;
    delete m_add_data;
    delete m_doc;
}

QDomNode CPou::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("pou");
    root.setAttribute("name", m_name);
    root.setAttribute("pouType", m_type);
    if (!m_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_global_id);
    }

    if (!m_interface->is_empty())
    {
        root.appendChild(m_interface->dom_node());
    }

    if (!m_actions->is_empty())
    {
        root.appendChild(m_actions->dom_node());
    }

    if (!m_transitions->is_empty())
    {
        root.appendChild((m_transitions->dom_node()));
    }

    for (auto &body : *m_bodies)
    {
        root.appendChild(body->body_node());
    }

    if (!m_add_data->is_empty())
    {
        root.appendChild(m_add_data->dom_node());
    }
    if (!m_doc->is_empty())
    {
        root.appendChild(m_doc->dom_node());
    }

    return root;
}

bool CPou::is_empty() const
{
    bool empty = m_interface->is_empty() &&
                 m_actions->is_empty() &&
                 m_transitions->is_empty() &&
                 m_bodies->empty() &&
                 m_add_data->is_empty() &&
                 m_doc->is_empty();
    return empty;
}

QString CPou::name() const
{
    return m_name;
}

void CPou::set_name(const QString &name)
{
    m_name = name;
}

QString CPou::type() const
{
    return m_type;
}

void CPou::set_type(const QString &type)
{
    m_type = type;
}

CInterface *CPou::interface()
{
    return m_interface;
}

QList<CBody *> *CPou::bodies()
{
    return m_bodies;
}

CActions *CPou::actions()
{
    return m_actions;
}

CTransitions *CPou::transitions()
{
    return m_transitions;
}

CAddData *CPou::add_data()
{
    return m_add_data;
}

CDocumentation *CPou::documentation()
{
    return m_doc;
}
