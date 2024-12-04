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
    CInsertLadder(COglWorld * world, CLadder *dragged_ladder, CLadder *before);
    ~CInsertLadder() override;

    void    redo() override;
    void    undo() override;

private:
    int       m_source_index{-1};
    int       m_dest_index{-1};
    CLadder * m_walking_ladder;
    CLadder * m_init_dest;
    COglWorld   * m_world;

    void      remove_from_position(int & position);
    void      insert_to_position(int & position);
    void      stitch();
    void      incision(int &position);
};


#endif //EDITORSD_CINSERTLADDER_H
