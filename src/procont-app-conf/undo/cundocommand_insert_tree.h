#ifndef CUNDOCOMMANDINSERTTREE_H
#define CUNDOCOMMANDINSERTTREE_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_insert_tree
class CUndoCommand_insert_tree : public IUndoCommand
{
public:
    CUndoCommand_insert_tree(const QDomNode &node_new_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);
    // CUndoCommand_insert_tree(const QDomNode &node_new_, const QDomNode &node_parent_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _m_index_parent;
    int _m_row{-1};
    QDomNode _m_node_new;
    QDomNode _m_node_parent;
};
// ***

#endif // CUNDOCOMMANDINSERTTREE_H
