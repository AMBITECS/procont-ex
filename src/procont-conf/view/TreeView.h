#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

QT_FORWARD_DECLARE_CLASS(QUndoStack)

class TreeView : public QTreeView
{
public:
    TreeView(QUndoStack *stack_ = nullptr, QWidget *parent_ = nullptr);

    QUndoStack * undoStack() const;

private:
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void slot_focusChanged(QWidget *old_, QWidget *new_);

private:
    QUndoStack * _m_undo_stack{nullptr};

};

#endif // TREEVIEW_H
