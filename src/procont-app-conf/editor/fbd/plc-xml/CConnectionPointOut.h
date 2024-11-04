//
// Created by artem on 10/23/24.
//

#ifndef EDITORSD_CCONNECTIONPOINTOUT_H
#define EDITORSD_CCONNECTIONPOINTOUT_H

#include "includes.h"
#include "CRelPosition.h"
#include "CAddData.h"
#include "CExpression.h"

class CConnectionPointOut
{
public:
    CConnectionPointOut();
    CConnectionPointOut(const CConnectionPointOut &other);
    CConnectionPointOut(CConnectionPointOut &&other) noexcept;
    explicit CConnectionPointOut(const QDomNode &dom_node);
    ~CConnectionPointOut();

    CConnectionPointOut& operator=(const CConnectionPointOut &other);

    [[nodiscard]] QDomNode    dom_node() const;

    [[nodiscard]] QString     expression() const;
    void        set_expression(const QString &expression);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    CRelPosition *   rel_position();
    CAddData     *  add_data();

    bool    is_empty() const;

private:
    CExpression     m_expression;
    QString         m_attr_global_id;
    CRelPosition    m_rel_position;
    CAddData        m_add_data;
};


#endif //EDITORSD_CCONNECTIONPOINTOUT_H
