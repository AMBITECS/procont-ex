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
    // *** variables editor
    // *  variables editor widgets
    // contauner for variables editor widgets
    auto container = new QWidget;
    // variables editor toolbar for table manipulations
    auto toolbar_table = new QToolBar;
    auto action = toolbar_table->addAction(QIcon(":/icon/images/plus.svg"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetCodeEditor::slot_addVariable);
    action = toolbar_table->addAction(QIcon(":/icon/images/minus.svg"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetCodeEditor::slot_delVariable);
    toolbar_table->setIconSize(QSize(16, 16));
    // variables editor table
    _var_table = new TableView;
    _var_table->setMinimumSize(500, 300);
    _var_table->setModel(_proxy);
    _var_table->setRootIndex(p_index(s_index(_index), _proxy));
    _var_table->setColumnHidden(0, true);
    _var_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _var_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _var_table->horizontalHeader()->setHighlightSections(false);
    _var_table->setItemDelegateForColumn(7, new CTextEditDelegate);
    // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
    // table->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));
    // variables editor code editor
    _var_text = new CodeEditorWidget(this);
    _var_text->setMinimumSize(500, 300);
    _var_text->setPlainText(XmlParser::getPouVarsText(item(index_)->node()));
    connect(_var_text, &CodeEditorWidget::textChanged, this, &WidgetCodeEditor::slot_textChanged);
    _var_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetCodeEditor::slot_txtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/table_9.svg"), tr("Table"));
    connect(action, &QAction::toggled, this, &WidgetCodeEditor::slot_tblViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar_view->setIconSize(QSize(24, 24));
    // *  variables editor layout
    // vertical (toolbar - table/code editor)
    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(toolbar_table);
    vertical_layout->addWidget(_var_table);
    vertical_layout->addWidget(_var_text);
    // horizontal (vertical - tollbar for switch view)
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(toolbar_view);
    container->setLayout(horizontal_layout);
    // set layout for container
    // container->setLayout(vertical_layout);
    // ***

    // add variables editor to splitter
    addWidget(container);

    // *** code editor
    _text = new CodeEditorWidget(this);
    _text->setMinimumSize(500, 300);
    _text->setPlainText(XmlParser::getPouBodyText(item(index_)->node()));
    connect(_text, &CodeEditorWidget::textChanged, this, &WidgetCodeEditor::slot_textChanged);
    // ***

    // add code editor to splitter
    addWidget(_text);
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

void WidgetCodeEditor::slot_textChanged()
{
}

void WidgetCodeEditor::slot_txtViewToggled(bool state)
{
    _var_table->hide();
    _var_text->show();
}

void WidgetCodeEditor::slot_tblViewToggled(bool state)
{
    _var_text->hide();
    _var_table->show();
}

void WidgetCodeEditor::slot_addVariable()
{
    auto parent = item(_var_table->rootIndex());

    // add node
    parent->addEmptyNode();

    // add item
    _proxy->sourceModel()->insertRow(parent->rowCount(), s_index(_var_table->rootIndex()));
}

void WidgetCodeEditor::slot_delVariable()
{
    // for every selected rows
    // !!! don't work for multiselection
    for(auto index : _var_table->selectionModel()->selectedRows())
    {
        // delete node
        item(_var_table->rootIndex())->removeChild(s_index(index).row(), 0, item(index)->node());

        // delete item
        proxy(_var_table->model())->sourceModel()->
            removeRow(s_index(index).row(), s_index(_var_table->rootIndex()));
    }
}
