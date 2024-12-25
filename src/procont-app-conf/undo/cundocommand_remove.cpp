#include "cundocommand_remove.h"

#include "widget/TabWidgetEditor.h"

#include "log/Logger.h"

#include <QDebug>

CUndoCommand_remove::CUndoCommand_remove(const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * cmd_) :
    IUndoCommand(index_, model_, cmd_)
{
    setText(QObject::tr("Delete item %1").arg(index_.data().toString()));

    _m_index_parent = index_.parent();
    _m_row = index_.row();
    _m_node = item(index_)->node();
}

CUndoCommand_remove::~CUndoCommand_remove()
{
    if(isRedo())
        item(_m_index_parent)->removeChild(_m_row, 0, _m_node);
}

void CUndoCommand_remove::undo()
{
    _m_model->insertRow(_m_row, _m_index_parent);
    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    m_info(QString(QObject::tr("insert item \'%1\'")).arg(_m_index.data().toString()));

    IUndoCommand::undo();
}

void CUndoCommand_remove::redo()
{
    m_info(QString(QObject::tr("remove item \'%1\'")).arg(_m_index.data().toString()));

    TabWidgetEditor::instance()->closeTab(_m_index, true);
    _m_model->removeRow(_m_index.row(), _m_index.parent());

    IUndoCommand::redo();
}
