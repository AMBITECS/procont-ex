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
    CInsertNewLadder(COglWorld *ogl_world, CLadder *next);
    ~CInsertNewLadder() override;

    void  undo() override;
    void  redo() override;

    CLadder *  new_ladder();

private:
    CLadder * m_new_ladder{nullptr};
    CLadder * m_to_delete{nullptr};
    int  m_index{-1};
    COglWorld * m_ogl_world;
    CLadder * m_next{nullptr};

    void      insert();
    CLadder * remove();
};


#endif //EDITORSD_CINSERTNEWLADDER_H
