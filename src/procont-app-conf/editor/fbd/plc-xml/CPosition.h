//
// Created by artem on 10/22/24.
//

#ifndef EDITORSD_CPOSITION_H
#define EDITORSD_CPOSITION_H

#include "includes.h"

/**
 * @brief   XML Format for IEC 61131-3 page 28
 */
class CPosition
{
public:
    CPosition();
    CPosition(const float &x, const float &y);
    explicit CPosition(const QDomNode &dom_node);
    CPosition(const CPosition &);
    CPosition(CPosition &&) noexcept;
    ~CPosition();

    friend bool operator==(const CPosition &lhs, const CPosition &rhs);

    CPosition&  operator=(const CPosition &rhs);

    [[nodiscard]] QDomNode    dom_node() const;

    [[nodiscard]] float       x() const;
    void        set_x(const float &X);

    [[nodiscard]] float       y() const;
    void        set_y(const float &Y);

    bool        is_empty() const;

private:
    float m_x{0};
    float m_y{0};

};


#endif //EDITORSD_CPOSITION_H
