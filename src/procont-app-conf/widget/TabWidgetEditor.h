#ifndef TABWIDGETEDITOR_H
#define TABWIDGETEDITOR_H

#include <QTabWidget>

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)
QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)

QT_FORWARD_DECLARE_CLASS(QTableView)

#include "item/DomItem.h"

class TabWidgetEditor : public QTabWidget
{
Q_OBJECT
public:
    TabWidgetEditor();

    void closeTabs();

public:
    static TabWidgetEditor * instance();

    static void setModel(QAbstractItemModel *);

public slots:
    void slot_addTabWidget(const QModelIndex &index);

protected:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private slots:
    void slot_closeTab(int index);
    void slot_currentTabChanged(int index);

Q_SIGNALS:
    void signal_currentTabChanged(const QModelIndex &index);

private:
    static QAbstractProxyModel * proxyModel(DomItem::ItemType);
    static QAbstractProxyModel * proxyModel(int);

private:
    static TabWidgetEditor * _instance;
    static QHash<DomItem::ItemType, QAbstractProxyModel*> _hProxyModels;

private:
    QHash<const QModelIndex, QWidget*> _hWidgets;
    QHash<QWidget*, QTableView*> _hTables;

};

#endif // TABWIDGETEDITOR_H
