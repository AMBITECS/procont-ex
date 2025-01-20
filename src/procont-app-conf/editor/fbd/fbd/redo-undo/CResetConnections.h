//
// Created by artem on 12/20/24.
//

#ifndef PROCONT_CRESETCONNECTIONS_H
#define PROCONT_CRESETCONNECTIONS_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CResetConnections : public QUndoCommand
{
public:
    explicit CResetConnections(CPin *pin);
    ~CResetConnections() override;

    void redo() override;
    void undo() override;

private:
    COglWorld   * m_world;
    CPin        * m_pin;

    std::vector<CPinIn*>    * m_opposites;
    std::vector<CVariable*> * m_iface_vars;

    CPinOut     * m_opposite{nullptr};
    CVariable   * m_iface_var{nullptr};
    QString       m_constant{};
};


#endif //PROCONT_CRESETCONNECTIONS_H
