#ifndef CUNDOCOMMANDREMOVE_H
#define CUNDOCOMMANDREMOVE_H

#include "iundocommand.h"

// *** CUndoCommand_remove
class CUndoCommand_remove : public IUndoCommand
{
public:
    CUndoCommand_remove(DomModel *model_, int row_, int column_,
                 const QModelIndex &index_parent_ = QModelIndex(),
                 QDomNode node_ = QDomNode(), QDomNode node_parent = QDomNode(),
                 QUndoCommand * = nullptr);

    virtual void undo() override;
    virtual void redo() override;

protected:
    DomModel * _m_model{nullptr};
    QDomNode _m_node_current;
    QDomNode _m_node_parent;
};
// ***

// *** CUndoCommand_remove_tree
class CUndoCommand_remove_tree : public CUndoCommand_remove
{
public:
    CUndoCommand_remove_tree(DomModel *model_, const QModelIndex &index_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;
};
// ***

// *** CUndoCommand_remove_table
class CUndoCommand_remove_table : public CUndoCommand_remove
{
public:
    CUndoCommand_remove_table(DomModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, QUndoCommand * = nullptr);

    void undo() override;
};
// ***

#endif // CUNDOCOMMANDREMOVE_H
