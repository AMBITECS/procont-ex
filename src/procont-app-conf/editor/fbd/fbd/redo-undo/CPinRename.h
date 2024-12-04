//
// Created by artem on 11/23/24.
//

#ifndef EDITORSD_CPINRENAME_H
#define EDITORSD_CPINRENAME_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CPinRename : public QUndoCommand
{
public:
    CPinRename(COglWorld *ogl_world, CConnectorPin *pin, QString  old_var, CConnectorPin *opposite_pin,
               QString new_var, CVariable *iface_var);
    ~CPinRename() override;

    void  redo() override;
    void  undo() override;

private:
    COglWorld       * m_world;
    CConnectorPin   * m_pin;
    CConnectorPin   * m_opposite_pin;
    QString           m_pin_var;
    QString           m_pin_old_var;
    QString           m_opposite_var;
    QString           m_opposite_old_var;
    CVariable       * m_iface_var{nullptr};
    CVariable       * m_old_iface_var{nullptr};

    void refresh_view();
};


#endif //EDITORSD_CPINRENAME_H
