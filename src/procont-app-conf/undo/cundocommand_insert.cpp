#include "cundocommand_insert.h"

#include "widget/TabWidgetEditor.h"
#include "model/DomModel.h"
#include "log/Logger.h"
#include "tr/translation.h"
#include "main/MainWindow.h"
#include "view/TreeView.h"
#include "model/ProxyModel.h"

#include <QDebug>


// *** CUndoCommand_insert
CUndoCommand_insert::CUndoCommand_insert(DomModel *model_, int row_, int column_,
                                         const QModelIndex &index_parent_,
                                         QDomNode node_current_, QDomNode node_parent_,
                                         QUndoCommand * cmd_) :
    IUndoCommand(row_, column_, index_parent_, cmd_),
    _m_model(model_),
    _m_node_current(node_current_),
    _m_node_parent(node_parent_)
{
    _m_name_ru = QString("%1 \'%2\'").arg(tr_str::instance()->ru(_m_node_current.nodeName()), _m_node_current.toElement().attribute("name"));

    setText(QString(QObject::tr("Insert %1")).arg(_m_name_ru));
}

void CUndoCommand_insert::undo()
{
    DomModel::toItem(_m_index_parent, true)->removeChild(_m_row, 0, _m_node_current);

    _m_model->removeRow(_m_row, _m_index_parent);

    m_info(QString(QObject::tr("removed %1")).arg(_m_name_ru));

    IUndoCommand::undo();
}

void CUndoCommand_insert::redo()
{
    _m_node_current = _m_node_parent.ownerDocument().importNode(_m_node_current, true);
    _m_node_current = _m_node_parent.appendChild(_m_node_current);

    _m_model->insertRow(_m_row, _m_index_parent);

    _m_index_current = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("inserted %1")).arg(_m_name_ru));

    IUndoCommand::redo();
}
// ***

// *** CUndoCommand_insert_tree
CUndoCommand_insert_tree::CUndoCommand_insert_tree(DomModel *model_, const QModelIndex &index_parent_, const QDomNode &node_, QUndoCommand * cmd_) :
    CUndoCommand_insert(
          model_,
          DomModel::toItem(index_parent_, true)->rowCount(),
          DomModel::toItem(index_parent_, true)->columnCount(),
          index_parent_,
          node_,
          DomModel::toItem(index_parent_, true)->node(),
          cmd_)
{
}

void CUndoCommand_insert_tree::undo()
{
    TabWidgetEditor::instance()->closeTab(_m_index_current, true);

    CUndoCommand_insert::undo();
}

void CUndoCommand_insert_tree::redo()
{
    CUndoCommand_insert::redo();

    emit signal_insertRow(DomModel::p_index(_m_index_current, MainWindow::instance()->pouProxy()));
}
// ***

// *** CUndoCommand_insert_table
// CUndoCommand_insert_table::CUndoCommand_insert_table(DomModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, const QDomNode &node_new_, const QDomNode &node_parent_, QUndoCommand *cmd_) :
//     CUndoCommand_insert(
//           model_,
//           index_.isValid() ? index_.row() : DomModel::toItem(index_parent_, true)->rowCount(),
//           index_.isValid() ? index_.column() : DomModel::toItem(index_parent_, true)->columnCount(),
//           index_parent_,
//           node_new_,
//           node_parent_,
//           cmd_)
// {
// }

CUndoCommand_insert_table::CUndoCommand_insert_table(QAbstractProxyModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, const QDomNode &node_new_, const QDomNode &node_parent_, QUndoCommand *cmd_) :
    CUndoCommand_insert(
        reinterpret_cast<DomModel*>(model_->sourceModel()),
        index_.isValid() ? index_.row() : DomModel::toItem(index_parent_, true)->rowCount(),
        index_.isValid() ? index_.column() : DomModel::toItem(index_parent_, true)->columnCount(),
        index_parent_,
        node_new_,
        node_parent_,
        cmd_),
    _m_model_proxy(model_)
{
}

void CUndoCommand_insert_table::redo()
{
    CUndoCommand_insert::redo();

    emit signal_insert_variable(DomModel::p_index(_m_index_current, _m_model_proxy), _m_first);

    _m_first = false;
}
// ***
