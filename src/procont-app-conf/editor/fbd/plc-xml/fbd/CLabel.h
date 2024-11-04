//
// Created by artem on 10/25/24.
//

#ifndef EDITORSD_CLABEL_H
#define EDITORSD_CLABEL_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CAddData.h"
#include "../CDocumentation.h"

class CLabel
{
public:
    CLabel();
    CLabel(const CLabel & other);
    explicit CLabel(const QDomNode &dom_node);
    ~CLabel();

    uint64_t    local_id() const;
    void        set_local_id(const uint64_t &loc_id);

    float       width() const;
    void        set_width(const float &width);

    float       height() const;
    void        set_height(const float & height);

    QString     label() const;
    void        set_label(const QString & label);

    uint16_t    exec_order_id() const;
    void        set_exec_order_id(const uint16_t & exec_order);

    QString     global_id() const;
    void        set_global_id(const QString & glob_id);

    CPosition * position();
    CAddData  * add_data();
    CDocumentation * documentation();

    bool        is_empty() const;
    QDomNode    dom_node() const;

private:
    uint64_t    m_local_id{0};
    float       m_width{0};
    float       m_height{0};
    QString     m_label;
    QString     m_global_id;
    uint16_t    m_exec_order{0};

    CPosition   m_position;
    CAddData    m_add_data;
    CDocumentation m_documentation;
};


#endif //EDITORSD_CLABEL_H
