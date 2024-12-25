#include "cundocommand_insert.h"

#include "widget/TabWidgetEditor.h"

#include "log/Logger.h"

#include <QDebug>

CUndoCommand_insert::CUndoCommand_insert(const QDomNode &node_new_, const QModelIndex &index_, QAbstractItemModel *model_, QUndoCommand * cmd_) :
    IUndoCommand(index_, model_, cmd_)
{
    _m_index_parent = index_;
    _m_row = item(_m_index_parent)->rowCount();
    _m_node_new = node_new_;
}

CUndoCommand_insert::~CUndoCommand_insert()
{
    if(!isRedo())
        item(_m_index_parent)->removeChild(_m_row, 0, _m_node_new);
}

void CUndoCommand_insert::undo()
{
    m_info(QString(QObject::tr("remove item \'%1\'")).arg(_m_index.data().toString()));

    TabWidgetEditor::instance()->closeTab(_m_index, true);
    _m_model->removeRow(_m_row, _m_index.parent());

    IUndoCommand::undo();
}

void CUndoCommand_insert::redo()
{
    item(_m_index_parent)->addNode(_m_node_new);
    _m_model->insertRow(_m_row, _m_index_parent);
    _m_index = _m_model->index(_m_row, 0, _m_index_parent);

    setText(QObject::tr("Insert item %1").arg(_m_index.data().toString()));

    m_info(QString(QObject::tr("insert item \'%1\'")).arg(_m_index.data().toString()));

    IUndoCommand::redo();
}
