#include "cundocommand_remove.h"

#include "widget/TabWidgetEditor.h"
#include "model/DomModel.h"
#include "log/Logger.h"
#include "tr/translation.h"

#include <QDebug>

// *** CUndoCommand_remove
CUndoCommand_remove::CUndoCommand_remove(DomModel *model_, int row_, int column_,
                            const QModelIndex &index_parent_,
                           QDomNode node_current_, QDomNode node_parent_,
                           QUndoCommand * cmd_) :
    IUndoCommand(row_, column_, index_parent_, cmd_),
    _m_model(model_),
    _m_node_current(node_current_),
    _m_node_parent(node_parent_)
{
}

void CUndoCommand_remove::undo()
{
    _m_model->insertRow(_m_row, _m_index_parent);

    _m_index_current = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("inserted %1")).arg(_m_name_ru));

    IUndoCommand::undo();
}

void CUndoCommand_remove::redo()
{
    DomModel::toItem(_m_index_parent, true)->removeChild(_m_row, _m_column, _m_node_current);

    _m_model->removeRow(_m_row, _m_index_parent);

    m_info(QString(QObject::tr("removed %1")).arg(_m_name_ru));

    IUndoCommand::redo();
}
// ***

// *** CUndoCommand_remove_tree
CUndoCommand_remove_tree::CUndoCommand_remove_tree(DomModel *model_, const QModelIndex &index_, QUndoCommand * cmd_) :
    CUndoCommand_remove(
          model_,
          index_.row(),
          index_.column(),
          index_.parent(),
          DomModel::toItem(index_, true)->node(),
          DomModel::toItem(index_, true)->node().parentNode(),
          cmd_)
{
    _m_name_ru = QString("%1 \'%2\'").arg(tr_str::instance()->ru(_m_node_current.nodeName()), index_.data().toString());

    setText(QString(QObject::tr("Delete %1")).arg(_m_name_ru));
}

void CUndoCommand_remove_tree::undo()
{
    if(_m_node_parent.childNodes().item(_m_row).isNull())
        _m_node_current = _m_node_parent.appendChild(_m_node_current);
    else
        _m_node_current = _m_node_parent.insertBefore(_m_node_current, _m_node_parent.childNodes().item(_m_row));

    CUndoCommand_remove::undo();
}

void CUndoCommand_remove_tree::redo()
{
    TabWidgetEditor::instance()->closeTab(_m_index_current, true);

    CUndoCommand_remove::redo();
}
// ***

// *** CUndoCommand_remove_table
CUndoCommand_remove_table::CUndoCommand_remove_table(DomModel *model_, const QModelIndex &index_, const QModelIndex &index_parent_, QUndoCommand * cmd_) :
    CUndoCommand_remove(
          model_,
          index_.row(),
          index_.column(),
          index_parent_,
          DomModel::toItem(index_, true)->node(),
          DomModel::toItem(index_, true)->node().parentNode(),
          cmd_)
{
    _m_name_ru = QString("%1 \'%2\'").arg(tr_str::instance()->ru(_m_node_current.nodeName()), _m_node_current.toElement().attribute("name"));

    setText(QString(QObject::tr("Delete %1")).arg(_m_name_ru));
}

void CUndoCommand_remove_table::undo()
{
    _m_node_current = _m_node_parent.appendChild(_m_node_current);

    CUndoCommand_remove::undo();
}
// ***
