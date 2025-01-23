//
// Created by artem on 12/20/24.
//

#ifndef PROCONT_CPININVERS_H
#define PROCONT_CPININVERS_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CPinInverse : public QUndoCommand
{
public:
    CPinInverse(CPinIn *pin_in, const bool &to_inverse);
    ~CPinInverse() override;

    void redo() override;
    void undo() override;

private:
    CPinIn  * m_pin;
    bool      m_inverse;
    COglWorld * m_world;
};


#endif //PROCONT_CPININVERS_H
