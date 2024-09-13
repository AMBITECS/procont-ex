#include "WidgetCodeEditor.h"

#include <QTableView>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QHeaderView>
#include <QActionGroup>
#include <QVBoxLayout>

#include "item/DomItem.h"
#include "view/TableView.h"
#include "view/ItemDelegate.h"
#include "editor-st/CodeEditorWidget.h"
#include "editor-st/XmlParser.h"

WidgetCodeEditor::WidgetCodeEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : QSplitter(Qt::Vertical, parent_),
    _index(index_),
    _proxy(proxy_)
{
    // auto splitter = new QSplitter(Qt::Vertical, parent_);
    auto container = new QWidget;

    auto toolbar = new QToolBar;
    auto action = toolbar->addAction(QIcon(":/icon/images/add.png"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetCodeEditor::slot_addVariable);
    action = toolbar->addAction(QIcon(":/icon/images/delete.png"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetCodeEditor::slot_delVariable);
    toolbar->setIconSize(QSize(16, 16));

    auto table = new TableView;
    table->setModel(proxy_);
    table->setRootIndex(p_index(s_index(_index), proxy_));
    table->setColumnHidden(0, true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setHighlightSections(false);
    table->setItemDelegateForColumn(7, new CTextEditDelegate);
    // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
    // table->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));

    auto vars = new CodeEditorWidget(this);
    vars->setMinimumSize(500, 300);
    vars->setPlainText(XmlParser::getPouBodyText(item(index_)->node()));

    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(toolbar);
    vertical_layout->addWidget(table);
    vertical_layout->addWidget(vars);
    vars->hide();

    toolbar = new QToolBar();
    toolbar->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar);
    action = toolbar->addAction(tr("Txt"));
    connect(action, &QAction::toggled, this, &WidgetCodeEditor::slot_txtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar->addAction(tr("Tbl"));
    connect(action, &QAction::toggled, this, &WidgetCodeEditor::slot_tblViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar->setIconSize(QSize(16,16));

    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(toolbar);
    container->setLayout(horizontal_layout);

    container->setLayout(vertical_layout);
    addWidget(container);

    auto text = new CodeEditorWidget(this);
    text->setMinimumSize(500, 300);
    text->setPlainText(XmlParser::getPouBodyText(item(index_)->node()));
    addWidget(text);
}

QModelIndex WidgetCodeEditor::s_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    if(proxy == nullptr)
        return reinterpret_cast<const QAbstractProxyModel*>(index.model())->mapToSource(index);

    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapToSource(index);
}

QModelIndex WidgetCodeEditor::p_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapFromSource(index);
}

QAbstractProxyModel * WidgetCodeEditor::proxy(QAbstractItemModel *model)
{
    return reinterpret_cast<QAbstractProxyModel*>(model);
}

DomItem * WidgetCodeEditor::item(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<DomItem *>(s_index(index, proxy).internalPointer());
}

void WidgetCodeEditor::slot_txtViewToggled(bool state)
{
    qDebug() << "txt" << state;
}

void WidgetCodeEditor::slot_tblViewToggled(bool state)
{
    qDebug() << "tbl" << state;
}

void WidgetCodeEditor::slot_addVariable()
{
    // auto index = m_index(_hTables.value(currentWidget())->rootIndex());
    // auto parentItem = item(_hTables.value(currentWidget())->rootIndex());

    // // add node
    // parentItem->addEmptyNode();

    // // add item
    // proxy(_hTables.value(widget(currentIndex()))->model())->sourceModel()->insertRow(parentItem->rowCount(), index);
}

void WidgetCodeEditor::slot_delVariable()
{
//     // for every selected rows
//     // !!! don't work for multiselection
//     for(auto index : _hTables.value(currentWidget())->selectionModel()->selectedRows())
//     {
//         // delete node
//         auto childNode = item(index)->node();
//         auto parentItem = item(_hTables.value(currentWidget())->rootIndex());
//         parentItem->removeChild(m_index(index).row(), 0, childNode);

//         // delete item
//         proxy(_hTables.value(widget(currentIndex()))->model())->sourceModel()->
//             removeRow(m_index(index).row(), m_index(_hTables.value(currentWidget())->rootIndex()));
//     }
}
