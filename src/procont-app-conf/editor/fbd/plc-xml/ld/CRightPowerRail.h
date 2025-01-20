//
// Created by artem on 1/9/25.
//

#ifndef PROCONT_CRIGHTPOWERRAIL_H
#define PROCONT_CRIGHTPOWERRAIL_H

#include "CLeftPowerRail.h"
#include "editor/fbd/plc-xml/CConnectionPointIn.h"

class CRightPowerRail : public CLeftPowerRail
{
public:
    CRightPowerRail();
    CRightPowerRail(const CRightPowerRail &);
    explicit CRightPowerRail(CBody *parent);
    CRightPowerRail(CBody *parent, const QDomNode &node);
    ~CRightPowerRail() override;

    CConnectionPointIn *    connection_point_in();
    [[nodiscard]] QDomNode  dom_node() const override;

protected:
    CConnectionPointOut * connection_point_out() override;
private:
    CConnectionPointIn  * m_point_in;

};


#endif //PROCONT_CRIGHTPOWERRAIL_H
