#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QDomNode>

QT_FORWARD_DECLARE_CLASS(QUndoStack)

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);

public:
    virtual void setModel(QAbstractItemModel *model) override;

    QUndoStack * undoStack() const;
    void closeOpenedEditor();

private:
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles = QList<int>());
    void slot_rowsRemoved(const QModelIndex &parent, int first, int last);
    void slot_rowsInserted(const QModelIndex &parent, int first, int last);
    void slot_focusChanged(QWidget *old_, QWidget *new_);

signals:
    void signal_tableChanged();

private:
    QUndoStack * _m_undo_stack{nullptr};
};

#endif // TABLEVIEW_H
