#include "cundocommand_edit.h"

// #include "../cwidgetproject.h"
// #include "../cwidgetview.h"

// #include "../../../aconfcore/item/citemtree.h"
// #include "../../../aconfcore/item/iitemtreeview.h"

// #include "../../../aconfcore/message/cmessanger.h"

// #include <QTreeWidgetItem>

// #include <QDebug>

// #define this_pointer this

// CUndoCommand_edit::CUndoCommand_edit(const QModelIndex &index_/*, const QDomElement &element_*/, QUndoCommand * cmd_) :
//     IUndoCommand(index_, cmd_)/*,
//     m_element_new(reinterpret_cast<CItemTree*>(m_item)->xmlnode_get().cloneNode().toElement()),
//     m_element_old(element_.cloneNode().toElement())*/
// {
//     setText(QObject::tr("Edit item %1").arg(_m_index.data().toString()));
// }

// CUndoCommand_edit::~CUndoCommand_edit()
// {
// }

// void CUndoCommand_edit::undo()
// {
//     // info(QString(QObject::tr("restore item \'%1\'")).arg(m_item->text(0)));

//     // m_document->addView(m_item);
//     // reinterpret_cast<CItemTree*>(m_item)->widget()->update(m_element_old.cloneNode().toElement());

//     IUndoCommand::undo();
// }

// void CUndoCommand_edit::redo()
// {
//     // info(QString(QObject::tr("edit item \'%1\'")).arg(m_item->text(0)));

//     // m_document->addView(m_item);
//     // reinterpret_cast<CItemTree*>(m_item)->widget()->update(m_element_new.cloneNode().toElement());

//     IUndoCommand::redo();
// }

// #undef this_pointer
