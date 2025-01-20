//
// Created by nechi on 13.11.2024.
//

#ifndef EDITORSD_CINSERTLADDER_H
#define EDITORSD_CINSERTLADDER_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"


class CInsertLadder : public QUndoCommand
{
public:
    CInsertLadder(COglWorld * world, CFbdLadder *dragged_ladder, CFbdLadder *before);
    ~CInsertLadder() override;

    void    redo() override;
    void    undo() override;

private:
    int       m_source_index{-1};
    int       m_dest_index{-1};
    CFbdLadder * m_walking_ladder;
    CFbdLadder * m_init_dest;
    COglWorld   * m_world;

    void      remove_from_position(int & position);
    void      insert_to_position(int & position);
    void      stitch();
    void      incision(int &position);
};


#endif //EDITORSD_CINSERTLADDER_H
