#ifndef CUNDOCOMMANDINSERT_H
#define CUNDOCOMMANDINSERT_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_insert
class CUndoCommand_insert : public IUndoCommand
{
public:
    CUndoCommand_insert(const QDomNode &new_node_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);
    ~CUndoCommand_insert();

    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _m_index_parent;
    int _m_row{-1};
    QDomNode _m_node_new;
};
// ***

#endif // CUNDOCOMMANDINSERT_H
