#include "TabWidgetEditor.h"

#include "item/DomItem.h"
#include "model/ProxyModel.h"
#include "view/ItemDelegate.h"
#include "view/TableView.h"

#include <QLabel>
#include <QTableView>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QToolBar>
#include <QHeaderView>

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
    for(auto i : _hProxyModels)
        i->setSourceModel(model_);
}

QAbstractProxyModel * TabWidgetEditor::proxyModel(DomItem::ItemType type)
{
    if(_hProxyModels.contains(type))
        return _hProxyModels.value(type);

    return nullptr;
}

QModelIndex TabWidgetEditor::m_index(const QModelIndex &index, QAbstractItemModel * proxy)
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
    return reinterpret_cast<DomItem *>(m_index(index, proxy).internalPointer());
}

void TabWidgetEditor::slot_addTabWidget(const QModelIndex &index)
{
    if(_hWidgets.contains(index))
    {
        setCurrentWidget(_hWidgets.value(index));
        return;
    }

    switch(item(index)->type())
    {
    case DomItem::typePou:
    case DomItem::typeVar:
    {
        auto vSplitter = new QSplitter(Qt::Vertical);
        auto container = new QWidget;
        auto layout = new QVBoxLayout;
        auto toolbar = new QToolBar;
        auto action = toolbar->addAction(QIcon(":/icon/images/add.png"), tr("Add"));
        connect(action, &QAction::triggered, this, &TabWidgetEditor::slot_addVariable);
        action = toolbar->addAction(QIcon(":/icon/images/delete.png"), tr("Remove"));
        connect(action, &QAction::triggered, this, &TabWidgetEditor::slot_delVariable);
        toolbar->setIconSize(QSize(16,16));
        auto table = new TableView;
        table->setModel(proxyModel(static_cast<DomItem::ItemType>(item(index)->type())));
        table->setRootIndex(p_index(m_index(index), proxyModel(static_cast<DomItem::ItemType>(item(index)->type()))));
        table->setColumnHidden(0, true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->horizontalHeader()->setHighlightSections(false);
        table->setItemDelegateForColumn(7, new CTextEditDelegate);
        // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
        // table->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));
        layout->addWidget(toolbar);
        layout->addWidget(table);
        container->setLayout(layout);
        vSplitter->addWidget(container);
        auto text = new QPlainTextEdit();
        text->setMinimumSize(500, 300);
        text->appendPlainText("PROGRAM TEXT");
        vSplitter->addWidget(text);

        _hWidgets.insert(index, vSplitter);
        _hTables.insert(vSplitter, table);
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
    _hTables.remove(widget(index));
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

void TabWidgetEditor::slot_addVariable()
{
    auto index = m_index(_hTables.value(currentWidget())->rootIndex());
    auto parentItem = item(_hTables.value(currentWidget())->rootIndex());

    // add node
    parentItem->addEmptyNode();

    // add item
    proxy(_hTables.value(widget(currentIndex()))->model())->sourceModel()->insertRow(parentItem->rowCount(), index);
}

void TabWidgetEditor::slot_delVariable()
{
    // for every selected rows
    // !!! don't work for multiselection
    for(auto index : _hTables.value(currentWidget())->selectionModel()->selectedRows())
    {
        // delete node
        auto childNode = item(index)->node();
        auto parentItem = item(_hTables.value(currentWidget())->rootIndex());
        parentItem->removeChild(m_index(index).row(), 0, childNode);

        // delete item
        proxy(_hTables.value(widget(currentIndex()))->model())->sourceModel()->
            removeRow(m_index(index).row(), m_index(_hTables.value(currentWidget())->rootIndex()));
    }
}
