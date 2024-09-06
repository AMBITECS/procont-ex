#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
public:
    TableView(QWidget *parent = nullptr);

private:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // TABLEVIEW_H
