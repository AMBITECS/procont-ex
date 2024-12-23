//
// Created by artem on 11/18/24.
//

#ifndef EDITORSD_CRENAMEINST_H
#define EDITORSD_CRENAMEINST_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CRenameInst : public  QUndoCommand
{
public:
    CRenameInst(COglWorld * wgt, CDiagramObject * obj, const QString &oldName, const QString &newName);
    ~CRenameInst() override;

    void  redo() override;
    void  undo() override;

private:
    COglWorld       * m_ogl_widget;
    CDiagramObject  * m_object;
    QString           m_old;
    QString           m_new;
};


#endif //EDITORSD_CRENAMEINST_H
