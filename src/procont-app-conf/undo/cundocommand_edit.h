#ifndef CUNDOCOMMANDEDIT_H
#define CUNDOCOMMANDEDIT_H

#include "iundocommand.h"

#include <QAbstractProxyModel>

// *** CUndoCommand_edit
class CUndoCommand_edit : public IUndoCommand
{
public:
    CUndoCommand_edit(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, QUndoCommand * = nullptr);

    virtual void undo() override;
    virtual void redo() override;

protected:
    enum class eEditType
    {
        eET_Edit,
        eET_Rename
    };

protected:
    eEditType _m_type{eEditType::eET_Edit};
    QAbstractProxyModel * _m_model{nullptr};
    QVariant _m_value_old;
    QVariant _m_value_new;
    DomItem * _m_item{nullptr};
};
// ***

// *** CUndoCommand_edit_tree
class CUndoCommand_edit_tree : public CUndoCommand_edit
{
public:
    CUndoCommand_edit_tree(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;   
};
// ***

// *** CUndoCommand_edit_table
class CUndoCommand_edit_table : public CUndoCommand_edit
{
    Q_OBJECT
public:
    CUndoCommand_edit_table(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, const QString &name_, QUndoCommand * = nullptr);
};
// ***


#endif // CUNDOCOMMANDEDIT_H
