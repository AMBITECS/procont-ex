//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CACTIONS_H
#define EDITORSD_CACTIONS_H

#include "../includes.h"
#include "../CRelPosition.h"
#include "CInline.h"
#include "../CConnectionPointOut.h"

/**
 * @brief These are part of the common objects because their scope is beyond SFC (action, inline are the same)
 */
class CAction
{
public:
    CAction();
    CAction(const CAction &other);
    explicit CAction(const QDomNode &dom_node);
    ~CAction();

    CAction&    operator=(const CAction & other);
    QDomNode    dom_node() const;

    uint64_t    local_id() const;
    void        set_local_id(const uint64_t &local_id);

    QString     qualifier() const;
    void        set_qualifier(const QString &qualifier);

    float       width() const;
    void        set_width(const float &width);

    float       height() const;
    void        set_height(const float &height);

    QString     duration()  const;
    void        set_duration(const QString &duration);

    QString     indicator() const;
    void        set_indicator(const QString & indicator);

    uint32_t    execution_order_id() const;
    void        set_exec_order_id(const uint32_t &order_id);

    QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    CRelPosition  * rel_position();

    QString     reference() const;
    void        set_reference(const QString &reference);

    CInline *   an_inline();
    CConnectionPointOut * connection_point_out();
    CAddData            * add_data();
    CDocumentation      * documentation();

private:
    uint64_t        m_local_id{0};
    QString         m_qualifier;
    float           m_width{0};
    float           m_height{0};
    QString         m_duration;
    QString         m_indicator;
    uint32_t        m_exec_order{0};
    QString         m_global_id;
    CRelPosition    m_rel_position;
    QString         m_reference;
    CInline         m_inline;
    CConnectionPointOut m_connection_point_out;
    CAddData        m_add_data;
    CDocumentation  m_document;
};

class CActions
{
public:
    CActions();
    CActions(const CActions & actions);
    CActions(const QDomNode & dom_node);
    ~CActions();

    bool        is_empty() const;
    QDomNode    dom_node() const;

};


#endif //EDITORSD_CACTIONS_H
