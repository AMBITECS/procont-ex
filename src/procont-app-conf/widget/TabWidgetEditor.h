#ifndef TABWIDGETEDITOR_H
#define TABWIDGETEDITOR_H

#include <QTabWidget>

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(ProxyModelTable_var)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(QTableView)

class TabWidgetEditor : public QTabWidget
{
Q_OBJECT
public:
    TabWidgetEditor();

public:
    static TabWidgetEditor * instance();
    static ProxyModelTable_var * proxy_var();

public slots:
    void slot_addTabWidget(const QModelIndex &index);

protected:
    static QModelIndex m_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private slots:
    void slot_closeTab(int index);
    void slot_currentTabChanged(int index);
    void slot_addVariable();
    void slot_delVariable();

Q_SIGNALS:
    void signal_currentTabChanged(const QModelIndex &index);

private:
    static QScopedPointer<TabWidgetEditor> m_instance;
    static ProxyModelTable_var * m_proxy_var;

private:
    QHash<const QModelIndex, QWidget*> m_hWidgets;
    QHash<QWidget*, QTableView*> m_hTables;

};

#endif // TABWIDGETEDITOR_H
