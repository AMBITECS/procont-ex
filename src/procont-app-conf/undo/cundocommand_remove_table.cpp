#include "cundocommand_remove_table.h"

#include "widget/TabWidgetEditor.h"

#include "model/DomModel.h"

#include "log/Logger.h"

#include <QDebug>

CUndoCommand_remove_table::CUndoCommand_remove_table(const QModelIndex &index_, const QModelIndex &parent_index_, QAbstractItemModel *model_, QUndoCommand * cmd_) :
    IUndoCommand(index_, model_, cmd_)
{
    setText(QObject::tr("Delete item %1").arg(index_.data().toString()));

    _m_index_parent = parent_index_;
    _m_row = index_.row();
    _m_node = toItem(index_)->node();
    _m_node_parent = _m_node.parentNode();
}

void CUndoCommand_remove_table::undo()
{
    _m_node = _m_node_parent.appendChild(_m_node);

    _m_model->insertRow(_m_row, _m_index_parent);

    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("insert item \'%1\'")).arg(_m_index.data().toString()));

    IUndoCommand::undo();
}

void CUndoCommand_remove_table::redo()
{
    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("remove item \'%1\'")).arg(_m_index.data().toString()));

    TabWidgetEditor::instance()->closeTab(_m_index, true);

    toItem(_m_index_parent)->removeChild(_m_row, 0, _m_node);

    _m_model->removeRow(_m_row, _m_index_parent);

    IUndoCommand::redo();
}
