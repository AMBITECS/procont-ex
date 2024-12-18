//
// Created by artem on 12/15/24.
//

#ifndef PROCONT_CCONSTTOPIN_H
#define PROCONT_CCONSTTOPIN_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CConstToPin : public QUndoCommand
{
public:
    CConstToPin(COglWorld *world, CPinIn *input, QString c_name);
    ~CConstToPin() override;

    void    redo() override;
    void    undo() override;
    [[nodiscard]] bool    is_error() const;

private:
    COglWorld   * m_world;
    CPinIn      * m_pin_in;
    QString       m_var_name;

    /// existing connection
    CVariable   * m_iface_var{nullptr};
    CPinOut     * m_opposite{nullptr};
    QString       m_constant;
    bool          m_is_error{false};
};


#endif //PROCONT_CCONSTTOPIN_H
