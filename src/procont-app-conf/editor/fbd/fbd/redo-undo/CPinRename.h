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
    CPinRename(COglWorld *ogl_world, CPin *pin, QString  old_var, CPin *opposite_pin,
               QString new_var, CVariable *iface_var);
    ~CPinRename() override;

    void  redo() override;
    void  undo() override;

private:
    COglWorld       * m_world;
    CPin   * m_pin;
    CPin   * m_opposite_pin;
    QString           m_pin_var;
    QString           m_pin_old_var;
    QString           m_opposite_var;
    QString           m_opposite_old_var;
    CVariable       * m_iface_var{nullptr};
    CVariable       * m_old_iface_var{nullptr};
    CConnectLine    * m_line{nullptr};
    CConnectLine    * m_line_to_del{nullptr};

    void refresh_view();
};


#endif //EDITORSD_CPINRENAME_H
