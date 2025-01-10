#ifndef CUNDOCOMMANDINSERT_H
#define CUNDOCOMMANDINSERT_H

#include "iundocommand.h"

#include <QDomNode>

// *** CUndoCommand_insert
class CUndoCommand_insert : public IUndoCommand
{
public:
    CUndoCommand_insert(DomModel *model_, int row_, int column_,
                        const QModelIndex &index_parent_ = QModelIndex(),
                        QDomNode node_current_ = QDomNode(), QDomNode node_parent_ = QDomNode(),
                        QUndoCommand * = nullptr);

    virtual void undo() override;
    virtual void redo() override;

protected:
    DomModel * _m_model{nullptr};
    QPersistentModelIndex _m_index_current;
    QDomNode _m_node_current;
    QDomNode _m_node_parent;
};
// ***

// *** CUndoCommand_insert_tree
class CUndoCommand_insert_tree : public CUndoCommand_insert
{
    Q_OBJECT
public:
    CUndoCommand_insert_tree(DomModel *model_, const QModelIndex &index_, const QDomNode &node_new_, QUndoCommand * = nullptr);

    void undo() override;
    void redo() override;

signals:
    void signal_insertRow(const QModelIndex &index_);
};
// ***

// *** CUndoCommand_insert_table

QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)

class CUndoCommand_insert_table : public CUndoCommand_insert
{
    Q_OBJECT
public:
    CUndoCommand_insert_table(DomModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, const QDomNode &node_new_, const QDomNode &node_parent_, QUndoCommand * = nullptr);
    CUndoCommand_insert_table(QAbstractProxyModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, const QDomNode &node_new_, const QDomNode &node_parent_, QUndoCommand * = nullptr);

    void redo() override;

signals:
    void signal_insertRow(const QModelIndex &index_, bool = false);

private:
    QAbstractProxyModel * _m_model_proxy;
    bool _m_first = true;
};
// ***

#endif // CUNDOCOMMANDINSERT_H
