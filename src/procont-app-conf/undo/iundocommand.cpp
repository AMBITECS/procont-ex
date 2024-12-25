#include "iundocommand.h"

IUndoCommand::IUndoCommand(const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * cmd_) :
    QUndoCommand(cmd_),
    _m_index(index_),
    _m_model(model_)
{
}

IUndoCommand::~IUndoCommand()
{
}

void IUndoCommand::undo()
{
    m_redo = false;
}

void IUndoCommand::redo()
{
    m_redo = true;
}

DomItem * IUndoCommand::item(const QModelIndex &index)
{
    return reinterpret_cast<DomItem *>(index.internalPointer());
}

