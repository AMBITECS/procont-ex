//
// Created by artem on 12/20/24.
//

#ifndef PROCONT_CPINRISING_H
#define PROCONT_CPINRISING_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CPinRising :public QUndoCommand
{
public:
    CPinRising(CPinIn *pin_in, const bool &is_rising);
    ~CPinRising() override;

    void redo() override;
    void undo() override;

private:
    COglWorld   * m_world;
    CPinIn      * m_pin;
    bool          m_is_rising;
};


#endif //PROCONT_CPINRISING_H
