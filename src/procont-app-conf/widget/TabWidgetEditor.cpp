#include "TabWidgetEditor.h"

#include "WidgetEditor.h"
#include "WidgetEditor_fbd.h"
#include "WidgetEditor_inherit.h"

#include "model/DomModel.h"
#include "model/ProxyModel.h"
#include "editor/fbd/general/OglWidget.h"
#include "main/MainWindow.h"

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
        _hProxyModels.insert(DomItem::typeType, new ProxyModelTable_var);
    }

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_closeTab(int)));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(slot_currentTabChanged(int)));
}

void TabWidgetEditor::addIntro()
{
    auto wgt = new OglWidget(widget(0));
    addTab(wgt, tr("Intro"));
    setCurrentWidget(wgt);
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

void TabWidgetEditor::slot_addTabWidget(const QModelIndex &index)
{
    QModelIndex _index = DomModel::s_index(index);

    if(_hWidgets.contains(_index))
    {
        setCurrentWidget(_hWidgets.value(_index));
        return;
    }

    DomItem::ItemType type = static_cast<DomItem::ItemType>(DomModel::toItem(index)->type());
    switch(type)
    {
    case DomItem::typePou:
    {
        QWidget *editor = nullptr;
        if(!DomModel::toItem(index)->node().toElement().namedItem("body").namedItem("ST").isNull())
            editor = new WidgetEditor_st(index, proxyModel(type));
        if(!DomModel::toItem(index)->node().toElement().namedItem("body").namedItem("FBD").isNull())
            editor = new WidgetEditor_fbd(index, proxyModel(type));
        if(!DomModel::toItem(index)->node().toElement().namedItem("body").namedItem("LD").isNull())
            editor = new WidgetEditor_ld(index, proxyModel(type));

        if(editor != nullptr)
            _hWidgets.insert(_index, editor);
        else
            _hWidgets.insert(_index, new QLabel(QString("Widget for item %1").arg(index.data().toString())));

    }
    break;
    case DomItem::typeType:
    {
        _hWidgets.insert(_index, new WidgetEditor_type(index, proxyModel(type)));
    }
    break;
    case DomItem::typeVar:
    {
        _hWidgets.insert(_index, new WidgetEditor_vars(index, proxyModel(type)));
    }
    break;
    default:
        _hWidgets.insert(_index, new QLabel(QString("Widget for item %1").arg(index.data().toString())));
    break;
    }

    addTab(_hWidgets.value(_index), index.data().toString());
    setCurrentWidget(_hWidgets.value(_index));
}

void TabWidgetEditor::renameTab(const QModelIndex &index_)
{
    QModelIndex index = DomModel::s_index(index_);

    if(_hWidgets.contains(index))
        setTabText(indexOf(_hWidgets.value(index)), index.data().toString());
}

void TabWidgetEditor::closeTab(const QModelIndex &index_, bool source_)
{
    QModelIndex index = source_ ? index_ : DomModel::s_index(index_);

    if(_hWidgets.contains(index))
        slot_closeTab(indexOf(_hWidgets.value(index)));
}

void TabWidgetEditor::slot_currentTabChanged(int index)
{
    if(std::find(std::begin(_hWidgets), std::end(_hWidgets), widget(index)) != std::end(_hWidgets))
        emit signal_currentTabChanged(_hWidgets.key(widget(index)));
    else
        emit signal_currentTabChanged(QModelIndex());

    // if(dynamic_cast<WidgetEditor_fbd*>(widget(index)))
    //     reinterpret_cast<WidgetEditor_fbd*>(widget(index))->activate();
}

void TabWidgetEditor::slot_closeTab(int index)
{
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
