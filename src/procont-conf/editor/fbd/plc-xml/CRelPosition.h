//
// Created by artem on 10/23/24.
//

#ifndef EDITORSD_CRELPOSITION_H
#define EDITORSD_CRELPOSITION_H

#include "includes.h"

/**
 * @brief   XML Format for IEC 61131-3 page 28
 */
class CRelPosition
{
public:
    CRelPosition();
    CRelPosition(const CRelPosition &);
    CRelPosition(CRelPosition &&) noexcept;
    explicit CRelPosition(const QDomNode &dom_node);
    ~CRelPosition();

    CRelPosition & operator=(const CRelPosition &rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] float           x() const;
    void            set_x(const float &x);
    [[nodiscard]] float           y() const;
    void            set_y(const float &y);

    friend bool     operator==(const CRelPosition &lhs, const CRelPosition &rhs);

private:
    float   m_x{0};
    float   m_y{0};

};


#endif //EDITORSD_CRELPOSITION_H
