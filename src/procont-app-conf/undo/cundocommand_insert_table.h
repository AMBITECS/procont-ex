#ifndef CUNDOCOMMANDINSERTTABLE_H
#define CUNDOCOMMANDINSERTTABLE_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_insert_table
class CUndoCommand_insert_table : public IUndoCommand
{
public:
    CUndoCommand_insert_table(const QDomNode &node_new_, const QDomNode &node_parent_, const QModelIndex &index_, const QModelIndex &parent_index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _m_index_parent;
    int _m_row{-1};
    QDomNode _m_node_new;
    QDomNode _m_node_parent;
};
// ***

#endif // CUNDOCOMMANDINSERTTABLE_H
