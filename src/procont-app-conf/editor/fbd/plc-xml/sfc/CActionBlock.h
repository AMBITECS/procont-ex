//
// Created by artem on 10/23/24.
//

#ifndef EDITORSD_CACTIONBLOCK_H
#define EDITORSD_CACTIONBLOCK_H

#include "../includes.h"
#include "CActions.h"
#include "../CPosition.h"
#include "../CAddData.h"
#include "../CConnectionPointIn.h"
#include "../CDocumentation.h"

/**
 * @brief These are part of the common objects because their scope is beyond SFC (action, inline are the same)
 */
class CActionBlock
{
public:
    CActionBlock();
    CActionBlock(const CActionBlock &other);
    CActionBlock(CActionBlock &&other) noexcept;
    explicit CActionBlock(const QDomNode &dom_node);
    ~CActionBlock();

    CActionBlock& operator=(const CActionBlock &other);

    QDomNode    dom_node() const;

    uint64_t    local_id() const;
    void        set_local_id(const uint64_t &local_id);

    bool        is_negated() const;
    void        set_negated(const bool &negated);

    float       width() const;
    void        set_width(const float &width);

    float       height() const;
    void        set_height(const float &height);

    uint64_t    exec_order_id() const;
    void        set_exec_order(const uint64_t &exec_order);

    QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    QList<CAction*> *   actions();
    CPosition   *  position();
    CAddData    *  add_data();
    CConnectionPointIn  *   connection_point_in();
    CDocumentation  *       documentation();

private:
    uint64_t            m_attr_local_id{0};
    bool                m_attr_is_negated{false};
    float               m_attr_width{0};
    float               m_attr_height{0};
    uint64_t            m_attr_exec_order{0};
    QString             m_attr_global_id{};
    CPosition           m_position;
    CConnectionPointIn  m_connection_point_in;
    QList<CAction*>     * m_actions;
    CAddData            m_add_data;
    CDocumentation      m_document;
};


#endif //EDITORSD_CACTIONBLOCK_H
