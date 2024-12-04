//
// Created by nechi on 12.11.2024.
//

#ifndef EDITORSD_CMOVEOBJECT_H
#define EDITORSD_CMOVEOBJECT_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

class CMoveObject : public QUndoCommand
{
public:
    CMoveObject(COglWorld * ogl_world, CLadder *source, CLadder *destination, CDiagramObject *object, const QPoint &pos);
    ~CMoveObject() override;

    void  undo() override;
    void  redo() override;
    [[nodiscard]] bool  is_error() const;

private:
    CLadder         * m_source;
    CLadder         * m_destination;
    QPoint            m_ins_pos;
    CDiagramObject  * m_object;
    COglWorld       * m_ogl_world;

    bool            m_error{false};

    int m_src_index{-1};
    int m_dst_index{-1};

    void move();
    void back();

    CDiagramObject *    remove_from_ladder(CLadder * source, CDiagramObject * object, int &from_index);
    void                insert_object(CLadder *dest, CDiagramObject *object, int &to_index);
};




#endif //EDITORSD_CMOVEOBJECT_H
