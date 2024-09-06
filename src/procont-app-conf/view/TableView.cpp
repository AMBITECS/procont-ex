#include "TableView.h"
#include <QMouseEvent>

TableView::TableView(QWidget *parent) : QTableView(parent)
{
}

void TableView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());

    if (item.row() == -1 && item.column() == -1)
        clearSelection();

    QTableView::mousePressEvent(event);
}
