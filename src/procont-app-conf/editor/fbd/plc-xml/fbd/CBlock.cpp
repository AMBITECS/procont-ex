//
// Created by artem on 10/24/24.
//

#include "CBlock.h"
#include "editor/fbd/fbd/editors/CFilter.h"

extern uint16_t max_local_id;

CBlock::CBlock(CBody *parent)
{
    m_in_vars       = new QList<CBlockVar*>();
    m_in_out_vars   = new QList<CBlockVar*>();
    m_out_vars      = new QList<CBlockVar*>();

    m_parent = parent;

    max_local_id++;
    set_local_id(max_local_id);
}

CBlock::CBlock(const CBlock &other)
{
    m_in_vars       = new QList<CBlockVar*>();
    m_in_out_vars   = new QList<CBlockVar*>();
    m_out_vars      = new QList<CBlockVar*>();
    m_parent        = other.m_parent;

    *this = other;
}

CBlock &CBlock::operator=(const CBlock &  other)
{
    if (this == &other)
        return *this;

    m_parent = other.m_parent;

    clear_variables();


    for (auto &alien : *other.m_in_vars)
    {
        auto var = new CBlockVar(*alien);
        var->set_parent(this);
        m_in_vars->push_back(var);
    }


    for (auto &alien : *other.m_in_out_vars)
    {
        auto var = new CBlockVar(*alien);
        var->set_parent(this);
        m_in_out_vars->push_back(var);
    }

    for (auto &alien : *other.m_out_vars)
    {
        auto var = new CBlockVar(*alien);
        var->set_parent(this);
        m_out_vars->push_back(var);
    }

//    max_local_id++;
//    set_local_id(max_local_id);

    m_width         = other.m_width;
    m_height        = other.m_height;
    m_type_name     = other.m_type_name;
    m_instance_name = other.m_instance_name;
    m_exec_order    = other.m_exec_order;
    m_global_id     = other.m_global_id;

    m_position      = CPosition(other.m_position);
    m_add_data      = CAddData(other.m_add_data);
    m_documentation = CDocumentation(other.m_documentation);

    return *this;
}

CBlock::CBlock(CBlock &&other) noexcept
    : m_type_name(std::move(other.m_type_name))
    , m_instance_name(std::move(other.m_instance_name))
    , m_global_id(std::move(other.m_global_id))
    , m_add_data(other.m_add_data)
    , m_parent(other.m_parent)

{
    m_in_vars       = other.m_in_vars;
    m_in_out_vars   = other.m_in_out_vars;
    m_out_vars      = other.m_out_vars;

    other.m_in_out_vars = nullptr;
    other.m_out_vars = nullptr;
    other.m_in_vars = nullptr;

    m_width         = other.m_width;
    m_height        = other.m_height;
    m_exec_order    = other.m_exec_order;
    m_position      = CPosition( other.m_position );
    m_documentation = CDocumentation( other.m_documentation );
}

CBlock::CBlock(const QDomNode &dom_node, CBody *parent)
{
    m_local_id  = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_parent    = parent;

    if (m_local_id == 0)
    {
        max_local_id++;
        set_local_id(max_local_id);
    }

    m_width     = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_height    = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_type_name = dom_node.attributes().namedItem("typeName").toAttr().value();
    m_instance_name = dom_node.attributes().namedItem("instanceName").toAttr().value();
    m_exec_order= dom_node.attributes().namedItem("executionOrderId").toAttr().value().toULong();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position      = CPosition(dom_node.namedItem("position") );
    m_add_data      = CAddData(dom_node.namedItem("addData"));
    //extract_params();

    m_documentation = CDocumentation(dom_node.namedItem("documentation"));

    m_in_vars       = new QList<CBlockVar*>();
    m_in_out_vars   = new QList<CBlockVar*>();
    m_out_vars      = new QList<CBlockVar*>();

    extract_vars("in", dom_node.namedItem("inputVariables"));
    extract_vars("in_out", dom_node.namedItem("inOutVariables"));
    extract_vars("out", dom_node.namedItem("outputVariables"));
}



CBlock::~CBlock()
{
    if (!m_in_vars || !m_in_out_vars || !m_out_vars)
    {
        return;
    }

    clear_variables();

    delete m_in_out_vars;
    delete m_in_vars;
    delete m_out_vars;
}

QDomNode CBlock::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("block");

    QString locId = QString::number(m_local_id);

    root.setAttribute("localId", locId);
    if (!is_floats_equal(0, m_width) && !is_floats_equal(0, m_height))
    {
        root.setAttribute("width", m_width);
        root.setAttribute("height", m_height);
    }
    root.setAttribute("typeName", m_type_name);
    if (!m_instance_name.isEmpty())
        root.setAttribute("instanceName", m_instance_name);
    root.setAttribute("executionOrderId", m_exec_order);
    if (!m_global_id.isEmpty())
        root.setAttribute("globalId", m_global_id);

    root.appendChild(m_position.dom_node());

    auto in = doc.createElement("inputVariables");
    for(auto &item : *m_in_vars)
    {
        in.appendChild(item->dom_node());
    }
    root.appendChild(in);

    auto in_out = doc.createElement("inOutVariables");
    for(auto &item : *m_in_out_vars)
    {
        in_out.appendChild(item->dom_node());
    }
    root.appendChild(in_out);

    auto out = doc.createElement("outputVariables");
    for (auto &item : *m_out_vars)
    {
        out.appendChild(item->dom_node());
    }
    root.appendChild(out);

    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

bool CBlock::is_empty() const
{
    bool empty  = m_local_id == 0 &&
                  m_type_name.isEmpty() &&
                  m_in_vars->empty() &&
                  m_out_vars->empty() &&
                  m_in_out_vars->empty();
    return empty;
}

uint64_t CBlock::local_id() const
{
    return m_local_id;
}

void CBlock::set_local_id(const uint64_t &local_id)
{
    m_local_id = local_id;
}

float CBlock::width() const
{
    return m_width;
}

void CBlock::set_width(const float &width)
{
    m_width = width;
}

float CBlock::height() const
{
    return m_height;
}

void CBlock::set_height(const float &height)
{
    m_height = height;
}

QString CBlock::type_name() const
{
    return m_type_name;
}

void CBlock::set_type_name(const QString &type_name)
{
    m_type_name = type_name;
}

QString CBlock::instance_name() const
{
    return m_instance_name;
}

void CBlock::set_instance_name(const QString &instance_name)
{
    m_instance_name = instance_name;
}

uint16_t CBlock::execution_order_id() const
{
    return m_exec_order;
}

void CBlock::set_exec_order_id(const uint16_t &order_id)
{
    m_exec_order = order_id;
}

QString CBlock::global_id() const
{
    return m_global_id;
}

void CBlock::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CPosition *CBlock::position()
{
    return &m_position;
}

QList<CBlockVar*> *CBlock::input_variables()
{
    return m_in_vars;
}

QList<CBlockVar*> *CBlock::in_out_variables()
{
    return m_in_out_vars;
}

QList<CBlockVar*> *CBlock::output_variables()
{
    return m_out_vars;
}

CAddData *CBlock::add_data()
{
    return &m_add_data;
}

CDocumentation *CBlock::documentation()
{
    return &m_documentation;
}

void
CBlock::extract_vars(const QString &direction, const QDomNode &node)
{
    QList<CBlockVar*> * vars = nullptr;

    EPinDirection dir;

    if (direction == "in")
    {
        vars = m_in_vars;
        dir = PD_INPUT;

    }
    if (direction == "in_out")
    {
        vars = m_in_out_vars;
        dir = PD_IN_OUT;
    }
    if (direction == "out")
    {
        vars = m_out_vars;
        dir = PD_OUTPUT;
    }

    if (!vars)
    {
        return;
    }

    for (uint16_t i = 0; i < node.childNodes().count(); ++i)
    {
        auto child = node.childNodes().at(i);
        auto var = new CBlockVar(this, child);
        var->set_direction(dir);

        vars->push_back(var);
    }
}

/*
void CBlock::extract_params()
{

    if (m_add_data.is_empty())
    {
        return;
    }

    for (auto &data : *m_add_data.data_list())
    {
        if (data->name() == "inputparamtypes" && !data->any_node().isNull())
        {
            QDomElement de = data->any_node().toElement();
            std::string types_s = de.text().toStdString();
            extract_pin_params(INS, types_s);
        }
        if (data->name() == "outputparamtypes" && !data->any_node().isNull())
        {
            QDomElement de = data->any_node().toElement();
            std::string types_s = de.text().toStdString();
            extract_pin_params(OUTS, types_s);
        }

}

void CBlock::extract_pin_params(const std::string &direction, const std::string &types_string)
{
    std::vector<EDefinedDataTypes> type_list;
    std::vector<EDefinedDataTypes> * vect = direction == INS ? &m_inputs : &m_outputs;
    std::string type_s;

    for (auto &letter : types_string)
    {
        if (letter == ' ')
        {
            EDefinedDataTypes type = get_type_from_string(type_s);
            type_list.push_back(type);
            type_s.clear();

            continue;
        }

        type_s += letter;
    }

    /// but last parameter was not recognized
    EDefinedDataTypes type = get_type_from_string(type_s);
    type_list.push_back(type);


    vect->clear();
    vect->insert(vect->end(), type_list.begin(), type_list.end());
}
*/

bool CBlock::normalize_block(const CBlock &n_block)
{
    if (m_in_vars->size() != n_block.m_in_vars->size() ||
        m_in_out_vars->size() != n_block.m_in_out_vars->size() ||
        m_out_vars->size() != n_block.m_out_vars->size()
    )
    {
        return false;
    }

    int counter = 0;
    for (auto &var : *n_block.m_in_out_vars)
    {
        auto local = m_in_out_vars->at(counter);
        local->set_type(var->derived_type());

        counter++;
    }

    counter = 0;
    for (auto &var : *n_block.m_in_vars)
    {
        auto local = m_in_vars->at(counter);
        local->set_type(var->derived_type());

        counter++;
    }

    counter = 0;
    for (auto &var : *n_block.m_out_vars)
    {
        auto local = m_out_vars->at(counter);
        local->set_type(var->derived_type());

        counter++;
    }

    return true;
}

CBlockVar *CBlock::get_output_by_name(const QString &name)
{
    std::string formal = name.toStdString();
    std::string pin_name;

    CFilter::capitalize_word(formal);

    for (auto &pin : *m_in_out_vars)
    {
        pin_name = pin->formal_parameter().toStdString();
        CFilter::capitalize_word(pin_name);

        if (pin_name == formal)
        {
            return pin;
        }
    }

    for (auto &pin : *m_out_vars)
    {
        pin_name = pin->formal_parameter().toStdString();
        CFilter::capitalize_word(pin_name);

        if (pin_name == formal)
        {
            return pin;
        }
    }

    return nullptr;
}

CBody *CBlock::parent()
{
    return m_parent;
}

void CBlock::set_parent(CBody *parent)
{
    m_parent = parent;

    for (auto &in : *m_in_vars)
    {
        in->set_parent(this);
    }

    for (auto &out : *m_out_vars)
    {
        out->set_parent(this);
    }

    for (auto &item : *m_in_out_vars)
    {
        item->set_parent(this);
    }
}

void CBlock::clear_variables()
{
    for (auto &in : *m_in_vars)
    {
        delete in;
    }
    m_in_vars->clear();

    for (auto &out : *m_out_vars)
    {
        delete out;
    }
    m_out_vars->clear();

    for (auto &item : *m_in_out_vars)
    {
        delete item;
    }
    m_in_out_vars->clear();
}



