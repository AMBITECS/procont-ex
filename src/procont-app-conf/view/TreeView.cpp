#include "TreeView.h"

#include "model/DomModel.h"
#include "item/DomItem.h"
#include "main/MainWindow.h"

#include <QMouseEvent>
#include <QUndoStack>
#include <QUndoGroup>
#include <QApplication>


TreeView::TreeView(QUndoStack *stack_, QWidget *parent) : QTreeView(parent),
    _m_undo_stack(stack_ != nullptr ? stack_ : new QUndoStack)
{
    connect(qApp, &QApplication::focusChanged, this, &TreeView::slot_focusChanged);
}

QUndoStack * TreeView::undoStack() const
{
    return _m_undo_stack;
}

void TreeView::slot_focusChanged(QWidget *old_, QWidget *new_)
{
    if(new_ == this)
        undoStack()->setActive();
    else
        clearFocus();
}

void TreeView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());

    if(item.row() == -1 || item.column() == -1)
    {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }

    setFocus();

    QTreeView::mousePressEvent(event);
}
