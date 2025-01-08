#include "iundocommand.h"

IUndoCommand::IUndoCommand(int row_, int column_, const QModelIndex &index_parent_, QUndoCommand * cmd_) :  QUndoCommand(cmd_),
    _m_row(row_),
    _m_column(column_),
    _m_index_parent(index_parent_)
{
}

