//
// Created by nechi on 12.11.2024.
//

#ifndef EDITORSD_CADDNEWLADDER_H
#define EDITORSD_CADDNEWLADDER_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CAddNewLadder : public QUndoCommand
{
public:
    explicit CAddNewLadder(COglWorld *oglWorld, QUndoCommand *parent = nullptr);
    ~CAddNewLadder() override;

    void    redo() override;
    void    undo() override;
    CLadder *  new_ladder();

private:
    CLadder     * m_new_ladder{nullptr};
    CLadder     * m_to_delete{nullptr};
    COglWorld   * m_ogl_world;
    int           m_index{-1};

    void  add();
    CLadder *  remove();
};


#endif //EDITORSD_CADDNEWLADDER_H
