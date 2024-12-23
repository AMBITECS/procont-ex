//
// Created by nechi on 12.11.2024.
//

#ifndef EDITORSD_CINSERTNEWOBJECT_H
#define EDITORSD_CINSERTNEWOBJECT_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CInsertNewObject : public QUndoCommand
{
public:
    CInsertNewObject(COglWorld * world, CFbdContent* fbd, CLadder *p_ladder,
                     const EPaletteElements &element, const QString &pou_name, const QPoint &pos);
    ~CInsertNewObject() override;

    void    undo() override;
    void    redo() override;

    CDiagramObject * inserted_object();

private:

    CLadder *m_ladder;
    EPaletteElements  m_element;
    QPoint m_pos;
    CDiagramObject * m_new_obj{nullptr};
    CDiagramObject * m_to_delete{nullptr};
    CFbdContent    * m_fbd;
    COglWorld      * m_world;
    QString          m_pou_name;

    void insert();
    CDiagramObject* remove();
};


#endif //EDITORSD_CINSERTNEWOBJECT_H
