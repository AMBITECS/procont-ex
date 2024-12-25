#ifndef CUNDOCOMMANDREMOVE_H
#define CUNDOCOMMANDREMOVE_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_remove
class CUndoCommand_remove : public IUndoCommand
{
public:
    CUndoCommand_remove(const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);
    ~CUndoCommand_remove();

    void undo() override;
    void redo() override;

private:
    QPersistentModelIndex _m_index_parent;
    int _m_row{-1};
    QDomNode _m_node;
};
// ***

#endif // CUNDOCOMMANDREMOVE_H
