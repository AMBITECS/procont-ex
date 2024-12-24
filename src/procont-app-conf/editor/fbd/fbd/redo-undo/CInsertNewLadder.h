//
// Created by nechi on 12.11.2024.
//

#ifndef EDITORSD_CINSERTNEWLADDER_H
#define EDITORSD_CINSERTNEWLADDER_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"
#include "../palette/DBlock.h"

class CInsertNewLadder : public QUndoCommand
{
public:
    CInsertNewLadder(COglWorld *ogl_world, CFbdLadder *next);
    ~CInsertNewLadder() override;

    void  undo() override;
    void  redo() override;

    CFbdLadder *  new_ladder();

private:
    CFbdLadder * m_new_ladder{nullptr};
    CFbdLadder * m_to_delete{nullptr};
    int  m_index{-1};
    COglWorld * m_ogl_world;
    CFbdLadder * m_next{nullptr};

    void      insert();
    CFbdLadder * remove();
};


#endif //EDITORSD_CINSERTNEWLADDER_H
