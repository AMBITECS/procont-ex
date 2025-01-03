#ifndef CUNDOCOMMANDREMOVETABLE_H
#define CUNDOCOMMANDREMOVETABLE_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_remove_table
class CUndoCommand_remove_table : public IUndoCommand
{
public:
    CUndoCommand_remove_table(const QModelIndex &index_, const QModelIndex &parent_index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _m_index_parent;
    int _m_row{-1};
    QDomNode _m_node;
    QDomNode _m_node_parent;
};
// ***

#endif // CUNDOCOMMANDREMOVETABLE_H
