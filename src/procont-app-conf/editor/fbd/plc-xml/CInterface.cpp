//
// Created by artem on 10/20/24.
//

#include "CInterface.h"

CInterface::CInterface()
{
    m_local_vars    = new CLocalVars();
    m_temp_vars     = new CTempVars();
    m_input_vars    = new CInVars();
    m_output_vars   = new COutVars();
    m_in_out_vars   = new CInOutVars();
    m_external_vars = new CExternalVars();
    m_global_vars   = new CGlobalVars();
    m_access_vars   = new CAccessVars();
    m_documentation = new CDocumentation();

}

CInterface::CInterface(const CInterface &src)
{
    m_local_vars    = new CLocalVars(*src.m_local_vars);
    m_temp_vars     = new CTempVars(*src.m_temp_vars);
    m_input_vars    = new CInVars(*src.m_input_vars);
    m_output_vars   = new COutVars(*src.m_output_vars);
    m_in_out_vars   = new CInOutVars(*src.m_in_out_vars);
    m_external_vars = new CExternalVars(*src.m_external_vars);
    m_global_vars   = new CGlobalVars(*src.m_global_vars);
    m_access_vars   = new CAccessVars(*src.m_access_vars);
    m_documentation = new CDocumentation(*src.m_documentation);

    m_add_data      = src.m_add_data;
    m_return_type   = src.m_return_type;
}

CInterface::CInterface(CInterface &&tmp) noexcept
    : m_return_type(std::move(tmp.m_return_type))
{
    m_local_vars    = tmp.m_local_vars;
    m_temp_vars     = tmp.m_temp_vars;
    m_input_vars    = tmp.m_input_vars;
    m_output_vars   = tmp.m_output_vars;
    m_in_out_vars   = tmp.m_in_out_vars;
    m_external_vars = tmp.m_external_vars;
    m_global_vars   = tmp.m_global_vars;
    m_access_vars   = tmp.m_access_vars;
    m_documentation = tmp.m_documentation;

    tmp.m_local_vars    = nullptr;
    tmp.m_temp_vars     = nullptr;
    tmp.m_input_vars    = nullptr;
    tmp.m_output_vars   = nullptr;
    tmp.m_in_out_vars   = nullptr;
    tmp.m_external_vars = nullptr;
    tmp.m_global_vars   = nullptr;
    tmp.m_access_vars   = nullptr;
    tmp.m_documentation = nullptr;

    m_add_data          = tmp.m_add_data;
}

CInterface::CInterface(const QDomNode &node)
{
    if (node.nodeName() != "interface")
    {
        throw std::runtime_error("in 'CInterface::CInterface(const QDomNode &node)' wrong node name");
    }

    m_local_vars    = new CLocalVars();
    m_temp_vars     = new CTempVars();
    m_input_vars    = new CInVars();
    m_output_vars   = new COutVars();
    m_in_out_vars   = new CInOutVars();
    m_external_vars = new CExternalVars();
    m_global_vars   = new CGlobalVars();
    m_access_vars   = new CAccessVars();


    for (uint16_t i = 0; i < node.childNodes().count(); ++i)
    {
        QDomNode child = node.childNodes().at(i);

        extract_child_nodes(child, m_local_vars, "localVars");
        extract_child_nodes(child, m_temp_vars, "tempVars");
        extract_child_nodes(child, m_input_vars, "inputVars");
        extract_child_nodes(child, m_output_vars, "outputVars");
        extract_child_nodes(child, m_in_out_vars, "inOutVars");
        extract_child_nodes(child, m_external_vars, "externalVars");
        extract_child_nodes(child, m_global_vars, "globalVars");
        extract_child_nodes(child, m_access_vars, "accessVars");
    }
    m_documentation = new CDocumentation(node.namedItem("documentation"));
}

CInterface::~CInterface()
{
    delete m_local_vars;
    delete m_temp_vars;
    delete m_input_vars;
    delete m_output_vars;
    delete m_in_out_vars;
    delete m_external_vars;
    delete m_global_vars;
    delete m_access_vars;
    delete m_documentation;
}

QDomNode
CInterface::dom_node()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("interface");

    add_child(root, m_local_vars);
    add_child(root, m_temp_vars);
    add_child(root, m_input_vars);
    add_child(root, m_output_vars);
    add_child(root, m_in_out_vars);
    add_child(root, m_external_vars);
    add_child(root, m_global_vars);
    add_child(root, m_access_vars);

    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }
    if (!m_documentation->is_empty())
    {
        root.appendChild(m_documentation->dom_node());
    }

    return root;
}

QString
CInterface::return_type() const
{
    return m_return_type;
}

void
CInterface::set_return_type(const QString &return_type)
{
    m_return_type = return_type;
}

CLocalVars *
CInterface::local_variables()
{
    return m_local_vars;
}

CTempVars *
CInterface::temp_variables()
{
    return m_temp_vars;
}

CInVars *
CInterface::input_variables()
{
    return m_input_vars;
}

COutVars *
CInterface::output_variables()
{
    return m_output_vars;
}

CInOutVars *
CInterface::in_out_variables()
{
    return m_in_out_vars;
}

CExternalVars *
CInterface::external_variables()
{
    return m_external_vars;
}

CGlobalVars *
CInterface::global_variables()
{
    return m_global_vars;
}

CAccessVars *
CInterface::access_variables()
{
    return m_access_vars;
}

void CInterface::add_child(QDomElement & element, CIfaceVars *p_vars)
{
    if (!p_vars->is_empty())
    {
        element.appendChild(p_vars->dom_node());
    }
}

void CInterface::extract_child_nodes(QDomNode &node, CIfaceVars *p_vars, const QString &node_name)
{
    if (node.nodeName() == node_name && !node.isNull())
    {
        for (uint16_t c = 0; c < node.childNodes().count(); ++c)
        {
            auto varNode = new CVariable(node.childNodes().at(c));
            p_vars->variables()->push_back(varNode);
        }
    }
}

bool CInterface::is_empty() const
{
    bool empty = m_add_data.is_empty() &&
                 m_documentation->is_empty() &&
                 m_local_vars->is_empty() &&
                 m_temp_vars->is_empty() &&
                 m_input_vars->is_empty() &&
                 m_output_vars->is_empty() &&
                 m_in_out_vars->is_empty() &&
                 m_external_vars->is_empty() &&
                 m_global_vars->is_empty() &&
                 m_access_vars->is_empty();
    return empty;
}

