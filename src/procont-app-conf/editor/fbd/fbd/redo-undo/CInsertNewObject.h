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
    CInsertNewObject(COglWorld * world, CFbdContent* fbd, CFbdLadder *p_ladder,
                     const EPaletteElements &element, const QString &pou_name, const QPoint &pos);
    ~CInsertNewObject() override;

    void    undo() override;
    void    redo() override;

    CFbdObject * inserted_object();

private:

    CFbdLadder *m_ladder;
    EPaletteElements  m_element;
    QPoint m_pos;
    CFbdObject * m_new_obj{nullptr};
    CFbdObject * m_to_delete{nullptr};
    CFbdContent    * m_fbd;
    COglWorld      * m_world;
    QString          m_pou_name;

    void insert();
    CFbdObject* remove();
};


#endif //EDITORSD_CINSERTNEWOBJECT_H
