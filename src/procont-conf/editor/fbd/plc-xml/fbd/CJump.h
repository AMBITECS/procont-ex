//
// Created by artem on 10/25/24.
//

#ifndef EDITORSD_CJUMP_H
#define EDITORSD_CJUMP_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CDocumentation.h"

/**
 * @note  XML Format for IEC 61131-3 page 52
 */
class CJump
{
public:
    CJump();
    CJump(const CJump & src);
    explicit CJump(const QDomNode & dom_node);
    ~CJump();

    [[nodiscard]] uint64_t    local_id() const;
    void        set_local_id(const uint64_t & local_id);

    [[nodiscard]] float       width() const;
    void        set_width(const float & width);

    [[nodiscard]] float       height() const;
    void        set_height(const float & height);

    [[nodiscard]] QString     label() const;
    void        set_label(const QString & label);

    [[nodiscard]] uint16_t    execution_order_id() const;
    void        set_exec_order(const uint16_t & exec_order_id);

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;

    CPosition *  position();
    CConnectionPointIn  *  connection_point_in();
    CAddData  *  add_data();
    CDocumentation * documentation();

private:
    uint64_t        m_local_id{0};
    float           m_width{0};
    float           m_height{0};
    QString         m_label;
    uint16_t        m_exec_order_id{0};
    QString         m_global_id;

    CPosition       m_position;
    CConnectionPointIn  m_point_in;
    CAddData        m_add_data;
    CDocumentation  m_documentation;
};


#endif //EDITORSD_CJUMP_H
