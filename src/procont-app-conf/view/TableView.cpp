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

void TableView::slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
    Q_UNUSED(roles);

    emit signal_tableChanged();
    }

void TableView::slot_rowsRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    emit signal_tableChanged();
}

void TableView::slot_rowsInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    emit signal_tableChanged();
}

void TableView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);

    connect(this->model(), &QAbstractItemModel::dataChanged, this, &TableView::slot_dataChanged);
    connect(this->model(), &QAbstractItemModel::rowsRemoved, this, &TableView::slot_rowsRemoved);
    connect(this->model(), &QAbstractItemModel::rowsInserted, this, &TableView::slot_rowsInserted);
}


