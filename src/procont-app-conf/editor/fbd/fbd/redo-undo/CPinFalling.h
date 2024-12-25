//
// Created by artem on 12/20/24.
//

#ifndef PROCONT_CPINFALLING_H
#define PROCONT_CPINFALLING_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CPinFalling : public QUndoCommand
{
public:
    CPinFalling(CPinIn *pin_in, const bool &is_fall);
    ~CPinFalling() override;

    void redo() override;
    void undo() override;

private:
    CPinIn      * m_pin;
    COglWorld   * m_world;
    bool         m_edge;
};


#endif //PROCONT_CPINFALLING_H
