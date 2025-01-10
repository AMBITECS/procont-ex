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

    void addIntro();

    void renameTab(const QModelIndex &);
    void closeTab(const QModelIndex &, bool = false);

public slots:
    void slot_addTabWidget(const QModelIndex &index);

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
    // static QHash<DomItem::ItemType, QAbstractProxyModel*> _hProxyModels;
    static QAbstractItemModel * _m_model;

private:
    QHash<const QModelIndex, QWidget*> _hWidgets;
};

#endif // TABWIDGETEDITOR_H
