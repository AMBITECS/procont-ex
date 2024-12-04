//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CINTERFACE_H
#define EDITORSD_CINTERFACE_H

#include "includes.h"
#include "variables/CIfaceVars.h"
#include "CAddData.h"

class CDocumentation;

class CInterface
{
public:
    CInterface();
    CInterface(const CInterface &);
    CInterface(CInterface &&) noexcept;
    explicit CInterface(const QDomNode &node);
    ~CInterface();

    //CInterface&         operator=(const CInterface &rhs);

    QDomNode            dom_node();
    bool                is_empty() const;

    [[nodiscard]] QString             return_type() const;
    void                set_return_type(const QString &return_type);
    [[nodiscard]] bool  is_derived() const;

    CLocalVars      * local_variables();
    CTempVars       * temp_variables();
    CInVars         * input_variables();
    COutVars        * output_variables();
    CInOutVars      * in_out_variables();
    CExternalVars   * external_variables();
    CGlobalVars     * global_variables();
    CAccessVars     * access_variables();

    std::vector<CVariable*>     all_variables();
    std::vector<CVariable*>     p_inputs();
    std::vector<CVariable*>     p_outputs();

private:
    // return type
    QString               m_return_type;    //!< костыль
    CAddData              m_add_data;
    CDocumentation      * m_documentation{nullptr};

    /// required interface content is one of listed items
    CLocalVars      * m_local_vars;
    CTempVars       * m_temp_vars;
    CInVars         * m_input_vars;
    COutVars        * m_output_vars;
    CInOutVars      * m_in_out_vars;
    CExternalVars   * m_external_vars;
    CGlobalVars     * m_global_vars;
    CAccessVars     * m_access_vars;
    bool              m_is_derived{false};

    void add_child(QDomElement & element, CIfaceVars *p_vars);

    void extract_child_nodes(QDomNode &node, CIfaceVars *p_vars, const QString &node_name);
    void gather_variables(QList<CVariable*> * source_variables, std::vector<CVariable*> * dest_vars);
};


#endif //EDITORSD_CINTERFACE_H
