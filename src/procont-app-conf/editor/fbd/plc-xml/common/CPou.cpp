//
// Created by artem on 10/28/24.
//

#include "CPou.h"

extern  uint16_t    max_local_id;

#include "editor/fbd/fbd/variables.h"
#include "editor/fbd/fbd/editors/CFilter.h"

CPou::CPou(CTypes * parent)
{
    m_interface = new CInterface(this);
    m_actions = new CActions();
    m_transitions = new CTransitions();
    m_add_data = new CAddData();
    m_doc = new CDocumentation();
    m_bodies = new QList<CBody*>();
    m_dom_node = new QDomNode();
    m_parent = parent;
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
    m_type_name = other.m_type_name;
    m_dom_node = new QDomNode(*other.m_dom_node);
    m_parent = other.m_parent;
}

CPou::CPou(const QDomNode &dom_node, CTypes * parent)
{
    m_dom_node = new QDomNode(dom_node);
    m_bodies = new QList<CBody*>();
    m_name = m_dom_node->attributes().namedItem(xmln::name).toAttr().value();
    m_type_name = m_dom_node->attributes().namedItem(xmln::pou_type).toAttr().value();

    m_interface = new CInterface(m_dom_node->namedItem("interface"), this);
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
            m_bodies->emplace_back(new CBody(child, this));
        }
    }
    m_parent = parent;
}

CPou::~CPou()
{
    for (auto &body : *m_bodies)
    {
        delete body;
    }
    delete m_bodies;

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
    root.setAttribute("pouType", m_type_name);
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

QString CPou::type_name() const
{
    return m_type_name;
}

void CPou::set_type(const QString &type)
{
    m_type_name = type;
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
    CBlock block(nullptr);
    block.set_local_id(++max_local_id);
    block.set_type_name(m_name);

    if (m_type_name != (QString)xmln::function_pou_type)
    {
        block.set_instance_name("???");
    }

    /*
    QString inputs;
    QString outputs;
    QString inOuts;
    */

    for (auto &in : *m_interface->input_variables()->variables())
    {
        auto *var = new CBlockVar(&block);
        var->set_type(in->type());
        var->set_formal_param(in->name());
        var->set_direction(EPinDirection::PD_INPUT);
        block.input_variables()->push_back(var);
        //inputs += in->type() + " ";
    }

    /// if function - there is no output variables, there is return type
    if (m_type_name == (QString)xmln::function_pou_type)
    {
        auto out = new CBlockVar(&block);
        out->set_formal_param("out");
        out->set_type(m_interface->return_type());
        out->set_direction(EPinDirection::PD_OUTPUT);
        block.output_variables()->push_back(out);
    }

    else
    {
        for (auto &in_out : *m_interface->in_out_variables()->variables())
        {
            auto *var = new CBlockVar(&block);
            //var->set_iface_variable(in_out);
            var->set_type(in_out->type());
            var->set_formal_param(in_out->name());
            var->set_direction(EPinDirection::PD_IN_OUT);
            block.in_out_variables()->push_back(var);
            //inOuts += in_out->type() + " ";
        }

        for(auto &out : *m_interface->output_variables()->variables())
        {
            auto var = new CBlockVar(&block);
            var->set_formal_param(out->name());
            //var->set_iface_variable(out);
            var->set_type(out->type());
            var->set_direction(PD_OUTPUT);
            block.output_variables()->push_back(var);
            //outputs += out->type();
        }
    }


    /// create CodeSys crutch
    /*QDomDocument doc;
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
    }*/

    return block;
}

bool CPou::find_body_input_variable(const uint64_t &reference_id, CInVariable ** in_var, CInOutVariable ** in_out_var)
{
    if (m_bodies->empty())
    {
        return false;
    }

    /// очень тонкий момент - в программе никак не отражен тот факт, что CBody в одном POU может быть несколько.
    /// И еще нет единого интерфейса для различных языков программирования
    CBody * body = m_bodies->front();

    CFbdContent * content;

    /// этот кусок костыля по-праву должен быть частью самого CBody, но только когда появится общий интерфейс, а пока такой костыль
    switch (body->diagram_lang())
    {
        case EBodyType::BT_FBD:
            content = body->fbd_content();
            if (!content)
                return false;
            break;
        default:
            return false;
    }


    for (auto &in : *content->inVariables())
    {
        if( in->local_id() == reference_id)
        {
            *in_var = in;
            return true;
        }
    }

    for (auto &in_out : *content->in_out_variables())
    {
        if (in_out->local_id() == reference_id)
        {
            *in_out_var = in_out;
            return true;
        }
    }



    return false;
}

CBlock *CPou::find_block_by_id(const uint64_t &ref_id)
{
    if (m_bodies->empty())
    {
        return nullptr;
    }

    /// очень тонкий момент - в программе никак не отражен тот факт, что CBody в одном POU может быть несколько.
    /// И еще нет единого интерфейса для различных языков программирования
    CBody * body = m_bodies->front();

    CFbdContent * content;

    /// этот кусок костыля по-праву должен быть частью самого CBody, но только когда появится общий интерфейс, а пока такой костыль
    switch (body->diagram_lang())
    {
        case EBodyType::BT_FBD:
            content = body->fbd_content();
            if (!content)
                return nullptr;
            break;
        default:
            return nullptr;
    }

    for (auto &block : *content->blocks())
    {
        if( block->local_id() == ref_id)
        {
            return block;
        }
    }
    return nullptr;
}

bool CPou::find_block_connecting_info(const uint64_t &ref_id, const QString &formal_param, CBlock **p_block,
                                      CBlockVar **p_block_var)
{
    if (m_bodies->empty())
    {
        return false;
    }

    /// очень тонкий момент - в программе никак не отражен тот факт, что CBody в одном POU может быть несколько.
    /// И еще нет единого интерфейса для различных языков программирования
    CBody * body = m_bodies->front();

    CFbdContent * content;

    /// этот кусок костыля по-праву должен быть частью самого CBody, но только когда появится общий интерфейс, а пока такой костыль
    switch (body->diagram_lang())
    {
        case EBodyType::BT_FBD:
            content = body->fbd_content();
            if (!content)
                return false;
            break;
        default:
            return false;
    }

    for (auto &block : *content->blocks())
    {
        if( block->local_id() == ref_id)
        {
            *p_block = block;
            break;
        }
    }

    if (!*p_block)
    {
        return false;
    }

    CBlock *block_item = *p_block;

    /// let find output
    for (auto &out : *block_item->output_variables())
    {
        std::string formal = out->formal_parameter().toStdString();
        CFilter::capitalize_word(formal);
        if (formal == formal_param.toStdString())
        {
            *p_block_var = out;
            return true;
        }
    }

    auto pred = [=](CBlockVar* var)
    {
        if (var->formal_parameter() == formal_param)
        {
            *p_block_var = var;
            return true;
        }
        return false;
    };

    auto res = std::any_of(block_item->in_out_variables()->begin(),
                           block_item->in_out_variables()->end(), pred);

    return res;
}

bool CPou::process_in_out(CBlockVar *block_var, CInOutVariable *in_out_variable,
                          std::vector<CBlockVar*> *possible_block_vars, std::vector<CVariable *> *possible_iface)
{
    /// возможные варианты наш block_var (должен быть входным) лишь один из задних клиентов проститутствующей in_out_variable<br>
    /// check input of the in_out_var

    if (in_out_variable->point_in()->is_empty())
    {
        return false;
    }

    bool res = recursive_find_front(in_out_variable, possible_block_vars, possible_iface);
    return res;
}

bool CPou::recursive_find_front(CInOutVariable *in_out_variable,
                                std::vector<CBlockVar *>* in_outs,std::vector<CVariable *> *possible_iface)
{
    if (!in_out_variable->expression()->expression().isEmpty())
    {
        auto var = m_interface->get_variable_by_name(in_out_variable->expression()->expression());

        if (var)
        {
            possible_iface->push_back(var);
        }
    }

    for (auto &connection : *in_out_variable->point_in()->connections())
    {
        uint64_t  ref_local_id = connection->ref_local_id();
        QString   formal_param = connection->formal_parameter();

        /// check if block
        CBlock * block = find_block_by_id(ref_local_id);

        if (block)
        {
            QList<CBlockVar*> array;
            array.append(*block->in_out_variables());
            array.append(*block->output_variables());

            for (auto &var : array)
            {
                if (var->formal_parameter() == formal_param)
                {
                    in_outs->push_back(var);
                    break;
                }
            }
            continue;
        }

        /// check interface
        for (auto &i_var : m_interface->all_variables())
        {
            if (i_var->name() == formal_param)
            {
                possible_iface->push_back(i_var);
                return true;
            }
        }

        /// nope, it damned inOutVariable with possible recursion
        auto content = get_fbd();
        if (!content)
        {
            continue;
        }

        auto data_info = content->get_var_by_local_id(ref_local_id);
        if (data_info.source == PD_IN_OUT)
        {
            auto in_out = static_cast<CInOutVariable*>(data_info.variable);
            bool res = recursive_find_front(in_out, in_outs, possible_iface);
            if (res)
                return true;
        }

        /// ниже это фантастика
        if (data_info.source == PD_OUTPUT)
        {
            throw std::runtime_error("WTF?! in 'CPou::recursive_find_front'");
        }
        if (data_info.source == PD_INPUT)
        {
            throw std::runtime_error("WTF?! in 'CPou::recursive_find_front'");
        }
    }
    return false;
}

void CPou::setSourceDomNode(const QDomNode &dom_node)
{
    *m_dom_node = dom_node;
}

CFbdContent *CPou::get_fbd()
{
    for (auto &body : *m_bodies)
    {
        if (body->diagram_lang() == EBodyType::BT_FBD)
        {
            return body->fbd_content();
        }
    }

    return nullptr;
}

EBodyType CPou::body_type() const
{
    if (m_bodies->empty())
        return EBodyType::BT_COUNT;
    return m_bodies->front()->diagram_lang();
}

CTypes *CPou::parent()
{
    return m_parent;
}

void CPou::set_parent(CTypes *parent)
{
    m_parent = parent;
}
