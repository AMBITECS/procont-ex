#include "WidgetEditor.h"

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
#include "editor/st/CodeEditorWidget.h"
#include "editor/st/XmlParser.h"
#include "translator/SchemaViewer.h"
#include "translator/TranslatorFbd.h"
#include "main/MainWindow.h"

WidgetEditor::WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : QSplitter(Qt::Vertical, parent_),
    _index(index_),
    _node(item(_index)->node()),
    _proxy(proxy_)
{
    setChildrenCollapsible(false);
}

QWidget * WidgetEditor::createVarsEditor()
{
    // load types
    XmlParser::typesFromFile(":/resources/types.txt");

    // *  variables editor widgets
    // variables editor toolbar for table manipulations
    auto toolbar_table = new QToolBar;
    auto action = toolbar_table->addAction(QIcon(":/icon/images/plus.svg"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetEditor::slot_addVariable);
    action = toolbar_table->addAction(QIcon(":/icon/images/minus.svg"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetEditor::slot_delVariable);
    toolbar_table->setIconSize(QSize(16, 16));
    // variables editor table
    _vars_table = new TableView;
    _vars_table->setMinimumSize(500, 200);
    _vars_table->setModel(_proxy);
    _vars_table->setRootIndex(p_index(s_index(_index), _proxy));
    _vars_table->setColumnHidden(0, true);
    _vars_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _vars_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _vars_table->horizontalHeader()->setHighlightSections(false);
    _vars_table->setItemDelegateForColumn(7, new CTextEditDelegate);
    connect(_vars_table, &TableView::signal_tableChanged, this, &WidgetEditor::slot_tblVarChanged);
    auto vb_table = new QVBoxLayout;
    vb_table->addWidget(toolbar_table);
    vb_table->addWidget(_vars_table);
    _m_table_container = new QWidget;
    _m_table_container->setLayout(vb_table);
    // QStringList varTypes = {"localVars", "inputVars", "outputVars", "tempVars", "inOutVars", "externalVars", "globalVars", "accessVars"};
    // table->setItemDelegateForColumn(2, new CComboBoxDelegate(varTypes));
    // variables editor code editor
    _vars_text = new CodeEditorWidget(this);
    _vars_text->setMinimumSize(500, 200);
    _vars_text->setPlainText(XmlParser::getPouVarsText(item(_index)->node()));
    connect(_vars_text, &CodeEditorWidget::textChanged, this, &WidgetEditor::slot_txtVarChanged);
    _vars_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor::slot_txtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/table_9.svg"), tr("Table"));
    connect(action, &QAction::toggled, this, &WidgetEditor::slot_tblViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar_view->setIconSize(QSize(24, 24));
    // *  variables editor layout
    // vertical (toolbar - table/code editor)
    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(_m_table_container);
    vertical_layout->addWidget(_vars_text);
    // horizontal (vertical - toolbar for switch view)
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(toolbar_view);
    // contauner for variables editor widgets
    auto container = new QWidget;
    // set layout for container
    container->setLayout(horizontal_layout);
    // ***

    return container;
}

QWidget * WidgetEditor::createCodeEditor()
{
    // *  code editor widgets
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getPouBodyText(item(_index)->node()));
    connect(_body_text, &CodeEditorWidget::textChanged, this, &WidgetEditor::slot_codeChanged);
    // ***

    return _body_text;
}

QModelIndex WidgetEditor::s_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    if(proxy == nullptr)
        return reinterpret_cast<const QAbstractProxyModel*>(index.model())->mapToSource(index);

    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapToSource(index);
}

QModelIndex WidgetEditor::p_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapFromSource(index);
}

QAbstractProxyModel * WidgetEditor::proxy(QAbstractItemModel *model)
{
    return reinterpret_cast<QAbstractProxyModel*>(model);
}

DomItem * WidgetEditor::item(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<DomItem *>(s_index(index, proxy).internalPointer());
}

void WidgetEditor::slot_codeChanged()
{
    // get new node from editor
    QDomNode new_node = XmlParser::getPouNode
        (
        _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
        _body_text != nullptr ? _body_text->toPlainText() : QString(),
        item(_vars_table->rootIndex())->node()
        );
    // set new node to item
    item(_vars_table->rootIndex())->updateNode(new_node);
}

void WidgetEditor::updateTblView()
{
    // get new node form txt view
    // !!! not work correct
    QDomNode new_node = XmlParser::getPouNode
        (
            _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
            _body_text != nullptr ? _body_text->toPlainText() : QString(),
            item(_vars_table->rootIndex())->node()
            );

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

void WidgetEditor::slot_txtVarChanged()
{
    // user make changes in text view
    if(_vars_text->isVisible())
        updateTblView();
}

void WidgetEditor::slot_tblVarChanged()
{
    // user make changes in text view
    if(_vars_table->isVisible())
        // set new text to text view
        _vars_text->setPlainText(XmlParser::getPouVarsText(item(_index)->node()));
}

void WidgetEditor::slot_txtViewToggled(bool state)
{
    Q_UNUSED(state);

    slot_tblVarChanged();

    _m_table_container->hide();
    _vars_text->show();
}

void WidgetEditor::slot_tblViewToggled(bool state)
{
    Q_UNUSED(state);

    slot_txtVarChanged();

    _vars_text->hide();
    _m_table_container->show();
}

void WidgetEditor::slot_addVariable()
{
    auto parent = item(_vars_table->rootIndex());

    // add node
    parent->addNode();

    // add item
    _proxy->sourceModel()->insertRow(parent->rowCount(), s_index(_vars_table->rootIndex()));
}

void WidgetEditor::slot_delVariable()
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
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_st ***

WidgetEditor_st::WidgetEditor_st(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : WidgetEditor(index_, proxy_, parent_)
{
    // *** variables editor
    addWidget(createVarsEditor());

    // *** code editor
    addWidget(createCodeEditor());

    // !!! delete when st-editor will work correctly
    updateTblView();
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_fbd ***

WidgetEditor_fbd::WidgetEditor_fbd(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : WidgetEditor(index_, proxy_, parent_)
{
    // *** variables editor
    addWidget(createVarsEditor());

    // *** code editor
    addWidget(createCodeEditor());

    // !!! delete when st-editor will work correctly
    updateTblView();
}

QWidget * WidgetEditor_fbd::createCodeEditor()
{
    // *  variables editor widgets
    // contauner for variables editor widgets
    auto container = new QWidget;
    // fbd view
    // _fbd_view = new FBDviewer;
    // _fbd_view->setMinimumSize(500, 250);
    // _fbd_view->showNode(item(_index)->node());
    _m_fbd_view = new CDiagramWidget(item(_index)->node(), MainWindow::instance()->toolWidget());
    // _m_fbd_view->set_active();
    _m_fbd_view->setMinimumSize(500, 250);
    // variables editor code editor
    _txt_view = WidgetEditor::createCodeEditor();
    _txt_view->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    auto action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_txtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/diagram.svg"), tr("Schema"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_shmViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar_view->setIconSize(QSize(24, 24));
    // *  variables editor layout
    // vertical (toolbar - table/code editor)
    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(_m_fbd_view);
    vertical_layout->addWidget(_txt_view);
    // horizontal (vertical - toolbar for switch view)
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(toolbar_view);
    // set layout for container
    container->setLayout(horizontal_layout);
    // ***

    return container;
}

void WidgetEditor_fbd::slot_shmViewToggled(bool)
{
    // _fbd_view->showNode(item(_index)->node());

    _txt_view->hide();
    _m_fbd_view->show();
}

void WidgetEditor_fbd::slot_txtViewToggled(bool)
{
    TranslatorFBD translator;
    _body_text->setPlainText(translator.getSTCode_pou(item(_index)->node()));

    _m_fbd_view->hide();
    _txt_view->show();
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_vars ***

WidgetEditor_vars::WidgetEditor_vars(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : WidgetEditor(index_, proxy_, parent_)
{
    // *** variables editor
    addWidget(createVarsEditor());
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_type ***

WidgetEditor_type::WidgetEditor_type(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : WidgetEditor(index_, proxy_, parent_)
{
    // *** variables editor
    QWidget * vars = createVarsEditor();
    addWidget(vars);

    // *** code editor
    addWidget(createCodeEditor());

    // !!! delete when st-editor will work correctly
    updateTblView();

    vars->hide();
}

QWidget * WidgetEditor_type::createCodeEditor()
{
    // *  code editor widgets
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);

    // !!! parse node to ST text
    qDebug() << "new code for parse node" << item(_index)->node().nodeName() << item(_index)->type();
    // QString text = XmlParser::getPouBodyText(item(_index)->node());
    QString text = {};

    _body_text->setPlainText(XmlParser::getDataTypeText(item(_index)->node()));

    connect(_body_text, &CodeEditorWidget::textChanged, this, &WidgetEditor_type::slot_codeChanged);
    // ***

    return _body_text;
}

void WidgetEditor_type::slot_codeChanged()
{
    qDebug() << "new code for update node" << item(_vars_table->rootIndex())->node().nodeName();

    //QDomNode new_node = {};
    // // get new node from st editor
    QDomNode new_node = XmlParser::getDataTypeNode
        (
            _body_text != nullptr ? _body_text->toPlainText() : QString(),
            _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
             item(_vars_table->rootIndex())->node()
        );

    qDebug() << DomItem::printNode(new_node);

    // set new node to item
    item(_vars_table->rootIndex())->updateNode(new_node);
}
// ----------------------------------------------------------------------------
