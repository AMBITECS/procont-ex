#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);

public:
    virtual void setModel(QAbstractItemModel *model) override;

private:
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles = QList<int>());
    void slot_rowsRemoved(const QModelIndex &parent, int first, int last);
    void slot_rowsInserted(const QModelIndex &parent, int first, int last);

    bool edit(const QModelIndex &index, QAbstractItemView::EditTrigger trigger, QEvent *event) override;

signals:
    void signal_tableChanged();
};

#endif // TABLEVIEW_H
