#include "TabWidgetEditor.h"

#include "item/DomItem.h"
#include "model/ProxyModel.h"
#include <view/ItemDelegate.h>

#include <QLabel>
#include <QTableView>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QToolBar>
#include <QHeaderView>

QScopedPointer<TabWidgetEditor> TabWidgetEditor::m_instance = QScopedPointer<TabWidgetEditor>(nullptr);
ProxyModelTable_var * TabWidgetEditor::m_proxy_var = nullptr;

TabWidgetEditor::TabWidgetEditor()
{
    setTabsClosable(true);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_closeTab(int)));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(slot_currentTabChanged(int)));
}

TabWidgetEditor * TabWidgetEditor::instance()
{
    if(!m_instance)
        m_instance.reset(new TabWidgetEditor);

    return m_instance.get();
}

ProxyModelTable_var * TabWidgetEditor::proxy_var()
{
    if(!m_proxy_var)
        m_proxy_var = new ProxyModelTable_var;

    return m_proxy_var;
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

DomItem * TabWidgetEditor::item(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<DomItem *>(m_index(index, proxy).internalPointer());
}

void TabWidgetEditor::slot_addTabWidget(const QModelIndex &index)
{
    if(m_hWidgets.contains(index))
    {
        setCurrentWidget(m_hWidgets.value(index));
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
        m_pVarTable = new QTableView;
        m_pVarTable->setModel(proxy_var());
        m_pVarTable->setRootIndex(p_index(m_index(index), proxy_var()));
        m_pVarTable->setColumnHidden(0, true);
        m_pVarTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_pVarTable->setSelectionMode(QAbstractItemView::SingleSelection);
        m_pVarTable->horizontalHeader()->setHighlightSections(false);
        // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
        // m_pVarTable->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));
        layout->addWidget(toolbar);
        layout->addWidget(m_pVarTable);
        container->setLayout(layout);
        vSplitter->addWidget(container);
        auto text = new QPlainTextEdit();
        text->setMinimumSize(500, 300);
        text->appendPlainText("PROGRAM TEXT");
        vSplitter->addWidget(text);

        m_hWidgets.insert(index, vSplitter);
    }
    break;
    default:
    {
        m_hWidgets.insert(index, new QLabel(QString("Widget for item %1").arg(index.data().toString())));
    }
    break;
    }

    addTab(m_hWidgets.value(index), index.data().toString());
    setCurrentWidget(m_hWidgets.value(index));
}

void TabWidgetEditor::slot_currentTabChanged(int index)
{
    if(std::find(std::begin(m_hWidgets), std::end(m_hWidgets), widget(index)) != std::end(m_hWidgets))
        emit signal_currentTabChanged(m_hWidgets.key(widget(index)));
    else
        emit signal_currentTabChanged(QModelIndex());
}

void TabWidgetEditor::slot_closeTab(int index)
{
    m_hWidgets.remove(m_hWidgets.key(widget(index)));

    delete widget(index);

    setCurrentIndex((index == count()) ? index-1 : index);
}

void TabWidgetEditor::slot_addVariable()
{
    auto index = m_index(m_pVarTable->rootIndex());
    auto parentItem = item(m_pVarTable->rootIndex());

    // add node
    parentItem->addEmptyNode();

    // add item
    proxy_var()->sourceModel()->insertRow(parentItem->rowCount(), index);
}

void TabWidgetEditor::slot_delVariable()
{
    // for every selected rows
    // !!! don't work for multiselection
    for(auto index : m_pVarTable->selectionModel()->selectedRows())
    {
        // delete node
        auto childNode = item(index)->node();
        auto parentItem = item(m_pVarTable->rootIndex());
        parentItem->removeChild(m_index(index).row(), 0, childNode);

        // delete item
        proxy_var()->sourceModel()->
            removeRow(m_index(index).row(), m_index(m_pVarTable->rootIndex()));
    }
}
