#include "TabWidgetEditor.h"

#include "WidgetCodeEditor.h"

#include "model/ProxyModel.h"

#include <QLabel>

TabWidgetEditor * TabWidgetEditor::_instance = nullptr;
QHash<DomItem::ItemType, QAbstractProxyModel*> TabWidgetEditor::_hProxyModels;

TabWidgetEditor::TabWidgetEditor()
{
    setTabsClosable(true);

    if(_hProxyModels.size() == 0)
    {
        _hProxyModels.insert(DomItem::typePou, new ProxyModelTable_var);
        _hProxyModels.insert(DomItem::typeVar, new ProxyModelTable_global);
    }

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_closeTab(int)));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(slot_currentTabChanged(int)));
}

TabWidgetEditor * TabWidgetEditor::instance()
{
    if(_instance == nullptr)
        _instance = new TabWidgetEditor;

    return _instance;
}

void TabWidgetEditor::setModel(QAbstractItemModel *model_)
{
    for(auto i : std::as_const(_hProxyModels))
        i->setSourceModel(model_);
}

QAbstractProxyModel * TabWidgetEditor::proxyModel(DomItem::ItemType type)
{
    if(_hProxyModels.contains(type))
        return _hProxyModels.value(type);

    return nullptr;
}

QAbstractProxyModel * TabWidgetEditor::proxyModel(int type)
{
    return proxyModel(static_cast<DomItem::ItemType>(type));
}

QModelIndex TabWidgetEditor::s_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    if(proxy == nullptr)
        return reinterpret_cast<const QAbstractProxyModel*>(index.model())->mapToSource(index);

    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapToSource(index);
}

QModelIndex TabWidgetEditor::p_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapFromSource(index);
}

QAbstractProxyModel * TabWidgetEditor::proxy(QAbstractItemModel *model)
{
    return reinterpret_cast<QAbstractProxyModel*>(model);
}

DomItem * TabWidgetEditor::item(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<DomItem *>(s_index(index, proxy).internalPointer());
}

void TabWidgetEditor::slot_addTabWidget(const QModelIndex &index)
{
    if(_hWidgets.contains(index))
    {
        setCurrentWidget(_hWidgets.value(index));
        return;
    }

    DomItem::ItemType type = static_cast<DomItem::ItemType>(item(index)->type());
    switch(type)
    {
    case DomItem::typePou:
    case DomItem::typeVar:
    {
        _hWidgets.insert(index, new WidgetCodeEditor(index, proxyModel(type)));
        // _hTables.insert(vSplitter, table);
    }
    break;
    default:
    {
        _hWidgets.insert(index, new QLabel(QString("Widget for item %1").arg(index.data().toString())));
    }
    break;
    }

    addTab(_hWidgets.value(index), index.data().toString());
    setCurrentWidget(_hWidgets.value(index));
}

void TabWidgetEditor::slot_currentTabChanged(int index)
{
    if(std::find(std::begin(_hWidgets), std::end(_hWidgets), widget(index)) != std::end(_hWidgets))
        emit signal_currentTabChanged(_hWidgets.key(widget(index)));
    else
        emit signal_currentTabChanged(QModelIndex());
}

void TabWidgetEditor::slot_closeTab(int index)
{
    // _hTables.remove(widget(index));
    _hWidgets.remove(_hWidgets.key(widget(index)));

    delete widget(index);

    setCurrentIndex((index == count()) ? index-1 : index);
}

void TabWidgetEditor::closeTabs()
{
    while(count())
        delete widget(currentIndex());

    _hWidgets.clear();
}
