#ifndef IUNDOCOMMAND_H
#define IUNDOCOMMAND_H

#include <QUndoCommand>
#include <QPersistentModelIndex>
#include <QDomNode>
#include <QObject>

QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(DomModel)
QT_FORWARD_DECLARE_CLASS(DomItem)

// *** IUndoCommand
class IUndoCommand : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    IUndoCommand(int row_, int column_, const QModelIndex &index_parent_ = QModelIndex(), QUndoCommand * = nullptr);

protected:
    int _m_row{-1};
    int _m_column{-1};
    QPersistentModelIndex _m_index_current;
    QPersistentModelIndex _m_index_parent;
    QString _m_name_ru{};
};
// ***

#endif // IUNDOCOMMAND_H
