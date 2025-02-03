//
// Created by artem on 10/23/24.
//

#ifndef EDITORSD_CEXPRESSION_H
#define EDITORSD_CEXPRESSION_H

#include "includes.h"

class CExpression
{
public:
    CExpression();
    CExpression(const CExpression &other);
    CExpression(CExpression &&other) noexcept;
    explicit CExpression(const QDomNode &dom_node);
    ~CExpression();

    CExpression& operator=(const CExpression &expression);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] QString         expression() const;
    void            set_expression(const QString &expression);

    friend  bool  operator==(const CExpression &lhs, const CExpression &rhs);

    [[nodiscard]] bool    is_empty() const;

private:
    std::string    m_expression{};
};


#endif //EDITORSD_CEXPRESSION_H
