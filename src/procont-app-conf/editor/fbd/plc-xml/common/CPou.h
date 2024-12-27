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
#include "editor/fbd/fbd/palette/palette.h"

class CTypes;
class CProject;

class CPou
{
public:
    explicit CPou(CTypes *parent);
    CPou(const CPou & other);
    explicit CPou(const QDomNode & dom_node, CTypes * parent);
    ~CPou();

    CTypes  * parent();
    void    set_parent(CTypes *parent);

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;

    CBlock      get_block();

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);
    [[nodiscard]] QString     type_name() const;
    void        set_type(const QString & type);
    [[nodiscard]] EBodyType   type() const;

    CInterface      * interface();
    QList<CBody*>   * bodies();
    CActions        * actions();
    CTransitions    * transitions();
    CAddData        * add_data();
    CDocumentation  * documentation();

    /// additional operations
    QDomNode    * sourceDomNode();
    void          setSourceDomNode(const QDomNode &dom_node);

    CFbdContent *   get_fbd();
    CLdContent  *   get_ld();
    CSfcContent *   get_sfc();
    /// user functions

    /**
     * @brief ищет в body CInVariable, соответствующий ref_id входа блока
     */
    bool    find_body_input_variable(const uint64_t & reference_id, CInVariable ** in_var, CInOutVariable ** in_out);

    /// ищет CBlock по reference_id. Using for connecting base classes (not graphical)
    bool    find_block_connecting_info(const uint64_t &ref_id, const QString &formal_param,
                                                CBlock ** block, CBlockVar **block_var);
    /// рекурсия для развертки переменных inOutVariable
    CBlock *   find_block_by_id(const uint64_t &ref_id);

    bool       recursive_find_in_out_top(CInOutVariable *in_out_variable,
                                         std::vector<CBlockVar *>* in_outs,
                                         std::vector<CVariable *> *possible_iface);

private:
    QDomNode    * m_dom_node{nullptr};
    QString       m_name;
    QString       m_type_name;
    QString       m_global_id;
    CInterface  * m_interface;
    CActions    * m_actions;
    CTransitions* m_transitions;
    CAddData    * m_add_data;
    CDocumentation * m_doc;
    EBodyType     m_type;
    CTypes      * m_parent{nullptr};
    CProject    * m_project{nullptr};

    QList<CBody*>   * m_bodies;


};


#endif //EDITORSD_CPOU_H
