#ifndef IUNDOCOMMAND_H
#define IUNDOCOMMAND_H

#include <QUndoCommand>
#include <QPersistentModelIndex>

QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(DomItem)

// *** IUndoCommand
class IUndoCommand : public QUndoCommand
{
public:
    IUndoCommand(const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * = nullptr);
    virtual ~IUndoCommand();

    virtual void undo() override;
    virtual void redo() override;

    bool isRedo() const { return m_redo; }

protected:
    static DomItem * toItem(const QModelIndex &index);

protected:
    QPersistentModelIndex _m_index;
    QAbstractItemModel * _m_model{nullptr};
    bool m_redo;
};
// ***

#endif // IUNDOCOMMAND_H
