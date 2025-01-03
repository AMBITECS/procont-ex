#include "cundocommand_insert_table.h"

#include "widget/TabWidgetEditor.h"

#include "model/DomModel.h"

#include "log/Logger.h"

#include <QDebug>

CUndoCommand_insert_table::CUndoCommand_insert_table(const QDomNode &node_new_, const QDomNode &node_parent_, const QModelIndex &index_, const QModelIndex &parent_index_, QAbstractItemModel *model_, QUndoCommand *cmd_) :
    IUndoCommand(index_, model_, cmd_),
    _m_index_parent(parent_index_),
    _m_row(index_.isValid() ? index_.row() : toItem(_m_index_parent)->rowCount()),
    _m_node_new(node_new_),
    _m_node_parent(node_parent_)
{
}

void CUndoCommand_insert_table::undo()
{
    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("remove item \'%1\'")).arg(_m_index.data().toString()));

    TabWidgetEditor::instance()->closeTab(_m_index, true);

    toItem(_m_index_parent)->removeChild(_m_row, 0, _m_node_new);

    _m_model->removeRow(_m_row, _m_index_parent);

    IUndoCommand::undo();
}

void CUndoCommand_insert_table::redo()
{
    _m_node_new = _m_node_parent.ownerDocument().importNode(_m_node_new, true);
    _m_node_new = _m_node_parent.appendChild(_m_node_new);

    _m_model->insertRow(_m_row, _m_index_parent);

    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("insert item \'%1\'")).arg(_m_index.data().toString()));

    IUndoCommand::redo();
}
