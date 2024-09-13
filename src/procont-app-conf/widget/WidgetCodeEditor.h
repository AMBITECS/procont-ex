#ifndef WIDGETCODEEDITOR_H
#define WIDGETCODEEDITOR_H

#include <QSplitter>

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)
QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)

#include <QAbstractProxyModel>

class WidgetCodeEditor : public QSplitter
{
    Q_OBJECT
public:
    WidgetCodeEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

private:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private slots:
    void slot_addVariable();
    void slot_delVariable();
    void slot_txtViewToggled(bool);
    void slot_tblViewToggled(bool);

private:
    QModelIndex _index;
    QAbstractProxyModel * _proxy;
};

#endif // WIDGETCODEEDITOR_H
