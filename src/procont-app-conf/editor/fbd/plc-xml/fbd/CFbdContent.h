//
// Created by artem on 10/24/24.
//

#ifndef EDITORSD_CFBDCONTENT_H
#define EDITORSD_CFBDCONTENT_H

#include "../includes.h"
#include "../variables/CInputVariables.h"
#include "../variables/COutputVariables.h"
#include "../variables/CInOutVariables.h"
#include "CBlock.h"
#include "CLabel.h"
#include "CJump.h"
#include "CReturn.h"
#include "../common/CComment.h"

struct s_variable_data
{
    void    * variable{nullptr};
    uint64_t  local_id{0};
    EPinDirection   source{PD_UNDEF};
};

/**
 * @brief These elements are a collection of objects, which are defined in FBD. They can be used in all
 *  graphical bodies.
 * @details XML Format for IEC 61131-3 page 47
 */
class CFbdContent
{
public:
    CFbdContent();
    CFbdContent(const CFbdContent & other);
    CFbdContent(CFbdContent && other) noexcept;
    explicit CFbdContent(const QDomNode & dom_node);
    ~CFbdContent();

    [[nodiscard]] QDomNode            dom_node() const;

    QList<CBlock*>      * blocks();
    QList<CInVariable*> * inVariables();
    QList<COutVariable*>* out_variables();
    QList<CInOutVariable*> * in_out_variables();
    QList<CLabel*>      * labels();
    QList<CJump*>       * jumps();
    QList<CReturn*>     * returns();
    QList<CComment*>    * comments();

    s_variable_data     get_var_by_local_id(const uint64_t &id);
    CBlock  *           get_block_by_id(const uint64_t &id);

private:
    QList<CBlock*>      * m_blocks;
    QList<CLabel*>      * m_labels;
    QList<CJump*>       * m_jumps;
    QList<CReturn*>     * m_returns;
    QList<CComment*>    * m_comments;
    QList<CInVariable*> * m_inVariables;
    QList<COutVariable*>* m_out_variables;
    QList<CInOutVariable*>     * m_in_out_variables;
};


#endif //EDITORSD_CFBDCONTENT_H
