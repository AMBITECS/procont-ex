//
// Created by artem on 10/28/24.
//

#ifndef EDITORSD_CPOU_H
#define EDITORSD_CPOU_H

#include "../includes.h"
#include "../CInterface.h"
#include "CBody.h"
#include "../sfc/CActions.h"
#include "../CTransitions.h"

class CPou
{
public:
    CPou();
    CPou(const CPou & other);
    explicit CPou(const QDomNode & dom_node);
    ~CPou();

    QDomNode    dom_node() const;
    bool        is_empty() const;

    CBlock      get_block();

    QString     name() const;
    void        set_name(const QString &name);
    QString     type() const;
    void        set_type(const QString & type);

    QDomNode    * sourceDomNode();

    CInterface * interface();
    QList<CBody*>   * bodies();
    CActions        * actions();
    CTransitions    * transitions();
    CAddData        * add_data();
    CDocumentation  * documentation();

    /// user functions

    /**
     * @brief ищет в body CInVariable, соответствующий ref_id входа блока
     */
    bool    find_body_input_variable(const uint64_t & reference_id, CInVariable ** in_var, CInOutVariable ** in_out);
    /// ищет CBlock по reference_id

    bool             find_block_connecting_info(const uint64_t &ref_id, const QString &formal_param,
                                                CBlock ** block, CBlockVar **block_var);
    bool             process_in_out(CBlockVar *block_var, CInOutVariable *in_out_variable,
                                    CBlockVar **possible_block_var, std::vector<CVariable *> *possible_iface);
    CBlock *         find_block_by_id(const uint64_t &ref_id);

    bool recursive_find_front(CInOutVariable *in_out_variable,
                              CBlockVar **p_block_var,std::vector<CVariable *> *possible_iface);

private:
    QDomNode    * m_dom_node{nullptr};
    QString       m_name;
    QString       m_type;
    QString       m_global_id;
    CInterface  * m_interface;
    CActions    * m_actions;
    CTransitions* m_transitions;
    CAddData    * m_add_data;
    CDocumentation * m_doc;

    QList<CBody*>   * m_bodies;


};


#endif //EDITORSD_CPOU_H
