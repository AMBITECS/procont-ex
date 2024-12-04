//
// Created by artem on 10/28/24.
//

#include "CPou.h"

extern  uint16_t    max_local_id;

#include "editor/fbd/fbd/variables.h"

CPou::CPou()
{
    m_interface = new CInterface();
    m_actions = new CActions();
    m_transitions = new CTransitions();
    m_add_data = new CAddData();
    m_doc = new CDocumentation();
    m_bodies = new QList<CBody*>();
    m_dom_node = new QDomNode();
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
    m_dom_node = new QDomNode(*other.m_dom_node);
}

CPou::CPou(const QDomNode &dom_node)
{
    m_dom_node = new QDomNode(dom_node);
    m_bodies = new QList<CBody*>();
    m_name = m_dom_node->attributes().namedItem(xmln::name).toAttr().value();
    m_type = m_dom_node->attributes().namedItem(xmln::pou_type).toAttr().value();

    m_interface = new CInterface(m_dom_node->namedItem("interface"));
    m_actions = new CActions(m_dom_node->namedItem("actions"));
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
    delete m_dom_node;
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

QDomNode *CPou::sourceDomNode()
{
    return m_dom_node;
}

CBlock CPou::get_block()
{
    CBlock block{};
    block.set_local_id(++max_local_id);
    block.set_type_name(m_name);

    if (m_type != (QString)xmln::function_pou_type)
    {
        block.set_instance_name("???");
    }

    QString inputs;
    QString outputs;
    QString inOuts;

    for (auto &in : *m_interface->input_variables()->variables())
    {
        auto *var = new CBlockVar();
        var->set_iface_variable(in);
        var->set_direction(EPinDirection::PD_INPUT);
        block.input_variables()->push_back(var);
        inputs += in->type() + " ";
    }

    /// if function - there is no output variables, there is return type
    if (m_type == (QString)xmln::function_pou_type)
    {
        auto out = new CBlockVar();
        out->set_formal_param("out");
        out->set_type(m_interface->return_type());
        out->set_direction(EPinDirection::PD_OUTPUT);
        block.output_variables()->push_back(out);
    }

    else
    {
        for (auto &in_out : *m_interface->in_out_variables()->variables())
        {
            auto *var = new CBlockVar();
            var->set_iface_variable(in_out);
            var->set_direction(EPinDirection::PD_IN_OUT);
            block.in_out_variables()->push_back(var);
            inOuts += in_out->type() + " ";
        }

        for(auto &out : *m_interface->output_variables()->variables())
        {
            auto var = new CBlockVar();
            var->set_iface_variable(out);
            var->set_direction(PD_OUTPUT);
            block.output_variables()->push_back(var);
            outputs += out->type();
        }
    }


    /// create CodeSys crutch
    QDomDocument doc;
    auto *inp_data = new CData();
    auto *out_data = new CData();
    auto * in_out_data = new CData();

    if (!inputs.isEmpty())
    {
        inp_data->set_name("inputparamtypes");
        QDomElement types = doc.createElement("InputParamTypes");
        types.setNodeValue(inputs);
        inp_data->set_any_node(types);

        block.add_data()->append_data(inp_data);
    }

    if (!outputs.isEmpty())
    {
        out_data->set_name("outputparamtypes");
        QDomElement types = doc.createElement("OutputParamTypes");
        types.setNodeValue(outputs);
        out_data->set_any_node(types);

        block.add_data()->append_data(out_data);
    }

    if (!inOuts.isEmpty())
    {
        in_out_data->set_name("inoutparamtypes");
        QDomElement types = doc.createElement("InoutParamTypes");
        types.setNodeValue(inOuts);
        in_out_data->set_any_node(types);

        block.add_data()->append_data(in_out_data);
    }

    return block;
}
