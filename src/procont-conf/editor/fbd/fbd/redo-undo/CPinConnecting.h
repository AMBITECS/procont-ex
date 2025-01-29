//
// Created by artem on 12/13/24.
//

#ifndef PROCONT_CPINCONNECTING_H
#define PROCONT_CPINCONNECTING_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CPinConnecting : public QUndoCommand
{
public:
    CPinConnecting(COglWorld * world, CPin * editing_pin, CPin * opposite_pin);
    ~CPinConnecting() override;

    void redo() override;
    void undo() override;

    [[nodiscard]] bool    is_error() const;

private:
    CPin    * m_pin_edited;
    CPin    * m_pin_opposite;
    COglWorld * m_world;
    bool      m_is_error{false};
};


#endif //PROCONT_CPINCONNECTING_H
