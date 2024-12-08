//
// Created by artem on 10/22/24.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef EDITORSD_CCONNECTIONPOINTIN_H
#define EDITORSD_CCONNECTIONPOINTIN_H

#include "includes.h"
#include "CAddData.h"
#include "CRelPosition.h"
#include "CConnection.h"
#include "CExpression.h"

/**
 * @brief XML Format for IEC 61131-3 page 32
 */
class CConnectionPointIn
{
public:
    CConnectionPointIn();
    CConnectionPointIn(const CConnectionPointIn &);
    CConnectionPointIn(CConnectionPointIn &&) noexcept;
    explicit CConnectionPointIn(const QDomNode &dom_node);
    ~CConnectionPointIn();

    CConnectionPointIn & operator=(const CConnectionPointIn &rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] bool    is_empty() const;
    [[nodiscard]] QString expression() const;
    void    set_expression(const QString &expression);

    QList<CConnection*>  * connections();
    [[nodiscard]] uint64_t    ref_local_id() const;
    void        set_reference_id(const uint64_t &ref_id);

    QString   formal_param() const;
    void      set_formal_param(const QString &param);

private:
    QString         m_attr_global_id;
    CRelPosition    m_rel_position;
    QString         m_name;
    uint64_t        m_ref_local_id{0};
    uint64_t        fix_var{0};

    QList<CConnection*>  * m_connections;
    CExpression            m_expression;
    CAddData        m_add_data;

};


#endif //EDITORSD_CCONNECTIONPOINTIN_H

#pragma clang diagnostic pop