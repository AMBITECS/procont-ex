#include "cundocommand_edit.h"

#include "widget/TabWidgetEditor.h"
#include "model/DomModel.h"
#include "log/Logger.h"
#include "tr/translation.h"

#include <QDebug>

// *** CUndoCommand_edit
CUndoCommand_edit::CUndoCommand_edit(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, QUndoCommand *cmd_) :
    IUndoCommand(index_.row(), index_.column(), index_.parent(), cmd_),
    _m_model(model_),
    _m_value_old(value_old_),
    _m_value_new(value_new_),
    _m_item(DomModel::toItem(index_))
{
    Q_ASSERT(_m_item);
}

void CUndoCommand_edit::undo()
{
    _m_index_current = _m_model->index(_m_row, _m_column, _m_index_parent);

    Q_ASSERT(DomModel::toItem(_m_index_current));

    DomModel::toItem(_m_index_current)->setData(_m_value_old, Qt::EditRole);

    emit _m_model->dataChanged(_m_index_current, _m_index_current, {Qt::DisplayRole, Qt::EditRole});

    QString _message = {};
    if(_m_type == eEditType::eET_Edit)
        _message = QString(QObject::tr("editing of the %1 has been canceled")).arg(_m_name_ru);
    else
        _message = QString(QObject::tr("renaming of the %1 to \'%2\' has been canceled"))
                       .arg(_m_name_ru, _m_value_new.toString());
    m_info(_message);
}

void CUndoCommand_edit::redo()
{
    _m_index_current = _m_model->index(_m_row, _m_column, _m_index_parent);

    Q_ASSERT(DomModel::toItem(_m_index_current));

    DomModel::toItem(_m_index_current)->setData(_m_value_new, Qt::EditRole);

    emit _m_model->dataChanged(_m_index_current, _m_index_current, {Qt::DisplayRole, Qt::EditRole});

    QString _message = {};
    if(_m_type == eEditType::eET_Edit)
        _message = QString(QObject::tr("the %1 has been edited")).arg(_m_name_ru);
    else
        _message = QString(QObject::tr("the %1 has been renamed to \'%2\'"))
                       .arg(_m_name_ru, _m_value_new.toString());
    m_info(_message);
}
// ***

// *** CUndoCommand_edit_tree
CUndoCommand_edit_tree::CUndoCommand_edit_tree(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, QUndoCommand *cmd_) :
    CUndoCommand_edit(model_, index_, value_old_, value_new_, cmd_)
{
    _m_type = eEditType::eET_Rename;

    _m_name_ru = QString(QObject::tr("%1 \'%2\'"))
                     .arg(tr_str::instance()->ru(_m_item->node().nodeName()), _m_item->node().toElement().attribute("name"));

    setText(QString(QObject::tr("%1 %2"))
                .arg((_m_type == eEditType::eET_Edit) ? QObject::tr("Edit") : QObject::tr("Rename"), _m_name_ru));
}

void CUndoCommand_edit_tree::undo()
{
    CUndoCommand_edit::undo();

    TabWidgetEditor::instance()->renameTab(_m_index_current);
}

void CUndoCommand_edit_tree::redo()
{
    CUndoCommand_edit::redo();

    TabWidgetEditor::instance()->renameTab(_m_index_current);
}
// ***

// *** CUndoCommand_edit_table
CUndoCommand_edit_table::CUndoCommand_edit_table(QAbstractProxyModel *model_, const QModelIndex &index_, QVariant value_old_, QVariant value_new_, const QString &name_, QUndoCommand *cmd_) :
    CUndoCommand_edit(model_, index_, value_old_, value_new_, cmd_)
{
    _m_type = (_m_item->node().nodeName() == "name") ? eEditType::eET_Rename : eEditType::eET_Edit;

    _m_name_ru = QString(QObject::tr("%1 \'%2\'")).arg(tr_str::instance()->ru("variable"), name_);

    setText(QString(QObject::tr("%1 %2"))
                .arg((_m_type == eEditType::eET_Edit) ? QObject::tr("Edit") : QObject::tr("Rename"), _m_name_ru));
}
// ***
