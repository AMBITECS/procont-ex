#include "TableView.h"

#include "model/DomModel.h"
#include "item/DomItem.h"
#include "main/MainWindow.h"

#include <QMouseEvent>
#include <QUndoStack>
#include <QUndoGroup>
#include <QApplication>

TableView::TableView(QWidget *parent) : QTableView(parent),
    _m_undo_stack(new QUndoStack(this))
{
    MainWindow::addStack(undoStack());
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(slot_focusChanged(QWidget *, QWidget *)));
}

TableView::~TableView()
{
    delete _m_undo_stack;
}

QUndoStack * TableView::undoStack() const
{
    return _m_undo_stack;
}

void TableView::slot_focusChanged(QWidget *old_, QWidget *new_)
{
    if(new_ == this)
        undoStack()->setActive();
    else
        clearFocus();
}

void TableView::closeOpenedEditor()
{
    closeEditor(indexWidget(currentIndex()), QAbstractItemDelegate::RevertModelCache);
}

void TableView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());

    if (item.row() == -1 && item.column() == -1)
    {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }

    setFocus();

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

    clearSelection();
    setCurrentIndex(QModelIndex());
}
