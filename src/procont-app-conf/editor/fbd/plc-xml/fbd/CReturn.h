//
// Created by artem on 10/25/24.
//

#ifndef EDITORSD_CRETURN_H
#define EDITORSD_CRETURN_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CDocumentation.h"

/**
 * @brief XML Format for IEC 61131-3 page 53
 */
class CReturn
{
public:
    CReturn();
    CReturn(const CReturn & other);
    explicit CReturn(const QDomNode & dom_node);
    ~CReturn();

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;

    [[nodiscard]] uint64_t    local_id() const;
    void        set_local_id(const uint64_t & local_id);

    [[nodiscard]] float       width() const;
    void        set_width(const float & width);

    [[nodiscard]] float       height() const;
    void        set_height(const float & height);

    [[nodiscard]] uint16_t    execution_order_id() const;
    void        set_exec_id(const uint16_t & exec_id);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString & glob_id);

    CPosition   * position();
    CConnectionPointIn  * connection_point_in();
    CAddData    * add_data();
    CDocumentation  *   documentation();

private:
    uint64_t    m_local_id{0};
    float       m_width{0};
    float       m_height{0};
    uint16_t    m_exec_order{0};
    QString     m_global_id;
    CPosition   m_position;
    CAddData    m_add_data;
    CDocumentation  m_doc;
    CConnectionPointIn  m_point_in;

};


#endif //EDITORSD_CRETURN_H
