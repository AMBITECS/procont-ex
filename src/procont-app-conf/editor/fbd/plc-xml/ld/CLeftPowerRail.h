//
// Created by artem on 1/9/25.
//

#ifndef PROCONT_CLEFTPOWERRAIL_H
#define PROCONT_CLEFTPOWERRAIL_H

#include <QDomNode>
#include "editor/fbd/plc-xml/CPosition.h"
#include "editor/fbd/plc-xml/CAddData.h"
#include "editor/fbd/plc-xml/CDocumentation.h"
#include "editor/fbd/plc-xml/CConnectionPointOut.h"



class CBody;

class CLeftPowerRail
{
public:
    explicit CLeftPowerRail(CBody * parent);
    CLeftPowerRail();
    CLeftPowerRail(const CLeftPowerRail &);
    CLeftPowerRail(CBody *parent, const QDomNode &node);
    virtual ~CLeftPowerRail();

    CBody   *   parent();
    void        set_parent(CBody *parent);

    [[nodiscard]] virtual QDomNode    dom_node() const;

    [[nodiscard]] uint64_t    local_id() const;
    void        set_local_id(const uint64_t &local_id);

    [[nodiscard]] float       height() const;
    void        set_height(const float &height);
    [[nodiscard]] float       width() const;
    void        set_width(const float &width);

    [[nodiscard]] uint32_t    execution_order() const;
    void        set_execution_order(const uint32_t &order);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    CPosition * position();
    CAddData  * add_data();
    CDocumentation * documentation();

    virtual CConnectionPointOut * connection_point_out();

protected:
    CBody       * m_parent;
    uint64_t      m_local_id{0};
    uint32_t      m_execution_order{0};
    float         m_width{0};
    float         m_height{0};
    std::string   m_global_id{};

    CAddData    * m_add_data;
    CPosition   * m_position;
    CDocumentation  * m_doc;
    CConnectionPointOut * m_connection_point_out;
};


#endif //PROCONT_CLEFTPOWERRAIL_H
