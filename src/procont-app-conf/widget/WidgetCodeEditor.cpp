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
    _node(item(_index)->node()),
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
    _vars_table = new TableView;
    _vars_table->setMinimumSize(500, 300);
    _vars_table->setModel(_proxy);
    _vars_table->setRootIndex(p_index(s_index(index_), _proxy));
    _vars_table->setColumnHidden(0, true);
    _vars_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _vars_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _vars_table->horizontalHeader()->setHighlightSections(false);
    _vars_table->setItemDelegateForColumn(7, new CTextEditDelegate);
    connect(_vars_table, &TableView::signal_tableChanged, this, &WidgetCodeEditor::slot_tblVarChanged);
    // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
    // table->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));
    // variables editor code editor
    _vars_text = new CodeEditorWidget(this);
    _vars_text->setMinimumSize(500, 300);
    _vars_text->setPlainText(XmlParser::getPouVarsText(item(_index)->node()));
    connect(_vars_text, &CodeEditorWidget::textChanged, this, &WidgetCodeEditor::slot_txtVarChanged);
    _vars_text->hide();
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
    vertical_layout->addWidget(_vars_table);
    vertical_layout->addWidget(_vars_text);
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
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 300);
    _body_text->setPlainText(XmlParser::getPouBodyText(item(index_)->node()));
    connect(_body_text, &CodeEditorWidget::textChanged, this, &WidgetCodeEditor::slot_codeChanged);
    // ***

    // add code editor to splitter
    addWidget(_body_text);

    // !!! delete when txt view node edit will work correct
    updateTblView();
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

void WidgetCodeEditor::slot_codeChanged()
{
    // get new node from editor
    QDomNode new_node = XmlParser::getPouNode(_vars_text->toPlainText(), _body_text->toPlainText(), item(_vars_table->rootIndex())->node());
    // set new node to item
    item(_vars_table->rootIndex())->updateNode(new_node);
}

void WidgetCodeEditor::updateTblView()
{
    // get new node form txt view
    // !!! not work correct
    QDomNode new_node = XmlParser::getPouNode
        (
            _vars_text->toPlainText(),
            _body_text->toPlainText(),
            item(_vars_table->rootIndex())->node()
            );

    QDomDocument doc;
    doc.appendChild(doc.importNode(new_node, true));
    qDebug() << "import" << doc.toString();

    // remove old variables from item
    item(_vars_table->rootIndex())->removeChildren();
    // remove roews from model
    proxy(_vars_table->model())->sourceModel()->
        removeRows(0, item(_vars_table->rootIndex())->rowCount(), s_index(_vars_table->rootIndex()));

    // set new node to item
    item(_vars_table->rootIndex())->updateNode(new_node);
    // add rows to model
    auto count = new_node.toElement().elementsByTagName("variable").count();
    _proxy->sourceModel()->insertRows(0, count, s_index(_vars_table->rootIndex()));
}

void WidgetCodeEditor::slot_txtVarChanged()
{
    // user make changes in text view
    if(_vars_text->isVisible())
        updateTblView();
}

void WidgetCodeEditor::slot_tblVarChanged()
{
    // user make changes in text view
    if(_vars_table->isVisible())
        // set new text to text view
        _vars_text->setPlainText(XmlParser::getPouVarsText(item(_index)->node()));
}

void WidgetCodeEditor::slot_txtViewToggled(bool state)
{
    Q_UNUSED(state);

    slot_tblVarChanged();

    _vars_table->hide();
    _vars_text->show();
}

void WidgetCodeEditor::slot_tblViewToggled(bool state)
{
    Q_UNUSED(state);

    slot_txtVarChanged();

    _vars_text->hide();
    _vars_table->show();
}

void WidgetCodeEditor::slot_addVariable()
{
    auto parent = item(_vars_table->rootIndex());

    // add node
    parent->addEmptyNode();

    // add item
    _proxy->sourceModel()->insertRow(parent->rowCount(), s_index(_vars_table->rootIndex()));
}

void WidgetCodeEditor::slot_delVariable()
{
    // for every selected rows
    // !!! don't work for multiselection
    for(auto index : _vars_table->selectionModel()->selectedRows())
    {
        // delete node
        item(_vars_table->rootIndex())->removeChild(s_index(index).row(), 0, item(index)->node());

        // delete item
        proxy(_vars_table->model())->sourceModel()->
            removeRow(s_index(index).row(), s_index(_vars_table->rootIndex()));
    }
}
