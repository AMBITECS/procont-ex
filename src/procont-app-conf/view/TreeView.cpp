#include "TreeView.h"

#include <QMouseEvent>

TreeView::TreeView(QWidget *parent) : QTreeView(parent)
{
}

void TreeView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());

    if (item.row() == -1 && item.column() == -1)
        clearSelection();

    QTreeView::mousePressEvent(event);
}
