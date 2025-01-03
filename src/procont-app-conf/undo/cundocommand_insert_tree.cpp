#include "cundocommand_insert_tree.h"

#include "widget/TabWidgetEditor.h"

#include "model/DomModel.h"

#include "log/Logger.h"

#include <QDebug>

CUndoCommand_insert_tree::CUndoCommand_insert_tree(const QDomNode &node_new_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * cmd_) :
    IUndoCommand(index_, model_, cmd_),
    _m_index_parent(index_),
    _m_row(toItem(_m_index_parent)->rowCount()),
    _m_node_new(node_new_),
    _m_node_parent(toItem(_m_index_parent)->node())
{
    // _m_node_new = _m_node_parent.ownerDocument().importNode(_m_node_new, true);
}

// CUndoCommand_insert_tree::CUndoCommand_insert_tree(const QDomNode &node_new_, const QDomNode &node_parent_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand *cmd_) :
//     IUndoCommand(index_, model_, cmd_),
//     _m_index_parent(index_),
//     _m_row(toItem(_m_index_parent)->rowCount()),
//     _m_node_new(node_new_),
//     _m_node_parent(node_parent_)
// {
// }

void CUndoCommand_insert_tree::undo()
{
    m_info(QString(QObject::tr("remove item \'%1\'")).arg(_m_index.data().toString()));

    qDebug() << _m_node_new.nodeName() << _m_node_new.parentNode().nodeName();

    TabWidgetEditor::instance()->closeTab(_m_index, true);

    toItem(_m_index_parent)->removeChild(_m_row, 0, _m_node_new);

    _m_model->removeRow(_m_row, _m_index_parent);

    IUndoCommand::undo();
}

void CUndoCommand_insert_tree::redo()
{
    _m_node_new = _m_node_parent.ownerDocument().importNode(_m_node_new, true);
    _m_node_new = _m_node_parent.appendChild(_m_node_new);

    _m_model->insertRow(_m_row, _m_index_parent);

    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    setText(QObject::tr("Insert item %1").arg(_m_index.data().toString()));

    m_info(QString(QObject::tr("insert item \'%1\'")).arg(_m_index.data().toString()));

    IUndoCommand::redo();
}
