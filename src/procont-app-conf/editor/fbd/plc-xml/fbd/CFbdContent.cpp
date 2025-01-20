//
// Created by artem on 10/24/24.
//

#include "CFbdContent.h"
#include "editor/fbd/fbd/editors/CFilter.h"
#include "../common/CBody.h"

CFbdContent::CFbdContent(CBody *parent)
{
    m_blocks            = new QList<CBlock*>();
    m_labels            = new QList<CLabel*>();
    m_jumps             = new QList<CJump*>();
    m_returns           = new QList<CReturn*>();
    m_comments          = new QList<CComment*>();
    m_inVariables       = new QList<CInVariable*>();
    m_out_variables     = new QList<COutVariable*>();
    m_in_out_variables  = new QList<CInOutVariable*>();
    m_parent = parent;
}

CFbdContent::CFbdContent(const CFbdContent &other)
{
    m_blocks            = new QList<CBlock*>(*other.m_blocks);
    m_labels            = new QList<CLabel*>(*other.m_labels);
    m_out_variables     = new QList<COutVariable*>(*other.m_out_variables);
    m_in_out_variables  = new QList<CInOutVariable*>(*other.m_in_out_variables);
    m_jumps             = new QList<CJump*>(*other.m_jumps);
    m_returns           = new QList<CReturn*>(*other.m_returns);
    m_inVariables       = new QList<CInVariable*>(*other.m_inVariables);
    m_comments          = new QList<CComment*>(*other.m_comments);
    m_parent            = other.m_parent;
}

CFbdContent::CFbdContent(CFbdContent &&other) noexcept
{
    m_blocks            = other.m_blocks;
    m_labels            = other.m_labels;
    m_out_variables     = other.m_out_variables;
    m_in_out_variables  = other.m_in_out_variables;
    m_jumps             = other.m_jumps;
    m_returns           = other.m_returns;
    m_inVariables       = other.m_inVariables;
    m_comments          = other.m_comments;
    m_parent            = other.m_parent;

    other.m_blocks              = nullptr;
    other.m_labels              = nullptr;
    other.m_jumps               = nullptr;
    other.m_returns             = nullptr;
    other.m_out_variables       = nullptr;
    other.m_in_out_variables    = nullptr;
    other.m_inVariables         = nullptr;
    other.m_comments            = nullptr;
}

CFbdContent::CFbdContent(const QDomNode &dom_node, CBody *parent)
{
    /// suppose root tag is <FBD> - like

    if (dom_node.nodeName() != "FBD")
    {
        throw std::runtime_error("in 'CFbdContent::CFbdContent(const QDomNode &dom_node)' wrong node name");
    }

    m_blocks            = new QList<CBlock*>();
    m_labels            = new QList<CLabel*>();
    m_jumps             = new QList<CJump*>();
    m_returns           = new QList<CReturn*>();
    m_comments          = new QList<CComment*>();
    m_inVariables       = new QList<CInVariable*>();
    m_out_variables     = new QList<COutVariable*>();
    m_in_out_variables  = new QList<CInOutVariable*>();
    m_parent            = parent;

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);

        if (child.nodeName() == "outVariable")
        {
            m_out_variables->emplace_back(new COutVariable(child, m_parent));
        }
        if (child.nodeName() == "block")
        {
            m_blocks->emplace_back(new CBlock(child, m_parent));
        }
        if (child.nodeName() == "inVariable")
        {
            m_inVariables->emplace_back(new CInVariable(child));
        }
        if (child.nodeName() == "inOutVariable")
        {
            m_in_out_variables->emplace_back(new CInOutVariable(child));
        }
        if (child.nodeName() == "label")
        {
            m_labels->emplace_back(new CLabel(child));
        }
        if (child.nodeName() == "jump")
        {
            m_jumps->emplace_back(new CJump(child));
        }
        if (child.nodeName() == "return")
        {
            m_returns->emplace_back(new CReturn(child));
        }
        if (child.nodeName() == "comment")
        {
            m_comments->emplace_back(new CComment(child));
        }
    }
}

CFbdContent::~CFbdContent()
{
    if (m_blocks == nullptr)
    {
        return;
    }

    for (auto &item : *m_out_variables)
        delete item;
    for (auto &item : *m_inVariables)
        delete item;
    for (auto &item : *m_in_out_variables)
        delete item;

    delete m_out_variables;
    delete m_in_out_variables;
    delete m_inVariables;

    for (auto &item : *m_blocks)
        delete item;
    for (auto &item : *m_labels)
        delete item;
    for (auto &item : *m_jumps)
        delete item;
    for (auto &item : *m_returns)
        delete item;
    for (auto &item : *m_comments)
        delete item;

    delete m_blocks;
    delete m_labels;
    delete m_jumps;
    delete m_returns;
    delete m_comments;
}

QList<CBlock *> *CFbdContent::blocks()
{
    return m_blocks;
}

QList<CInVariable*> *CFbdContent::inVariables()
{
    return m_inVariables;
}

QList<COutVariable*> *CFbdContent::out_variables()
{
    return m_out_variables;
}

QList<CInOutVariable*> *CFbdContent::in_out_variables()
{
    return m_in_out_variables;
}

QList<CLabel *> *CFbdContent::labels()
{
    return m_labels;
}

QList<CJump *> *CFbdContent::jumps()
{
    return m_jumps;
}

QList<CReturn *> *CFbdContent::returns()
{
    return m_returns;
}

QDomNode CFbdContent::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("FBD");

    if (!m_blocks->empty())
    {
        for (auto &item : *m_blocks)
        {
            root.appendChild(item->dom_node());
        }
    }

    if (!m_labels->empty())
    {
        for (auto &item : *m_labels)
        {
            root.appendChild(item->dom_node());
        }
    }
    if (!m_out_variables->empty())
    {
        for (auto &item : *m_out_variables)
            root.appendChild(item->dom_node());
    }

    if (!m_in_out_variables->empty())
    {
        for (auto &item : *m_in_out_variables)
        root.appendChild(item->dom_node());
    }

    if(!m_jumps->empty())
    {
        for (auto &item : *m_jumps)
            root.appendChild(item->dom_node());
    }

    if (!m_returns->empty())
    {
        for (auto &item : *m_returns)
            root.appendChild(item->dom_node());
    }

    if (!m_inVariables->empty())
    {
        for (auto &item : *m_inVariables)
            root.appendChild(item->dom_node());
    }

    if (!m_comments->empty())
    {
        for (auto &item : *m_comments)
            root.appendChild(item->dom_node());
    }

    return root;
}

QList<CComment *> *CFbdContent::comments()
{
    return m_comments;
}

s_variable_data CFbdContent::get_var_by_local_id(const uint64_t &id)
{
    s_variable_data data;

    for (auto &var : *m_in_out_variables)
    {
        if (var->local_id() == id)
        {
            data.source = PD_IN_OUT;
            data.variable = var;
            data.local_id = id;

            return data;
        }
    }

    for (auto &var : *m_inVariables)
    {
        if (var->local_id() == id)
        {
            data.source = PD_INPUT;
            data.variable = var;
            data.local_id = id;

            return data;
        }
    }

    for (auto &var : *m_out_variables)
    {
        if (var->local_id() == id)
        {
            data.source = PD_OUTPUT;
            data.variable = var;
            data.local_id = id;

            return data;
        }
    }

    return data;
}

CBlock *CFbdContent::get_block_by_id(const uint64_t &id)
{
    for (auto &block : *m_blocks)
    {
        if (block->local_id() == id)
        {
            return block;
        }
    }
    return nullptr;
}

CInVariable* CFbdContent::remove_in_variable_ny_id(const uint64_t &loc_id)
{
    int counter = 0;
    CInVariable *var = nullptr;

    for (auto &in : *m_inVariables)
    {
        if (in->local_id() == loc_id)
        {
            var = in;
            m_inVariables->erase(m_inVariables->cbegin() + counter);
            return var;
        }
        counter++;
    }
    return var;
}

COutVariable *CFbdContent::find_output_var_by_iface_name(const QString &iface_var_name)
{
    std::string search_name = iface_var_name.toStdString();
    CFilter::capitalize_word(search_name);
    std::string current;

    for (auto &out_var : *m_out_variables)
    {
        if (out_var->expression()->is_empty())
        {
            continue;
        }

        current = out_var->expression()->expression().toStdString();
        CFilter::capitalize_word(current);

        if (current == search_name)
        {
            return out_var;
        }
    }
    return nullptr;
}

CBlock *CFbdContent::remove_block(CBlock *block)
{
    int counter = 0;
    for (auto &item : *m_blocks)
    {
        if (item == block)
        {
            m_blocks->erase(m_blocks->cbegin() + counter);
            return block;
        }
        counter++;
    }
    return nullptr;
}
