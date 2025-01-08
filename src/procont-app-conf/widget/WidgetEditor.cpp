#include "WidgetEditor.h"

#include <QTableView>
#include <QSplitter>
#include <QToolBar>
#include <QHeaderView>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUndoStack>
#include <QUndoGroup>

#include "model/DomModel.h"
#include "model/ProxyModel.h"
#include "view/TableView.h"
#include "view/ItemDelegate.h"
#include "view/ItemDelegate_combobox.h"
#include "editor/st/CodeEditorWidget.h"
#include "editor/st/XmlParser.h"
#include "main/MainWindow.h"
#include "undo/cundocommand_insert.h"
#include "undo/cundocommand_remove.h"
#include "undo/cundocommand_edit.h"
#include "log/Logger.h"

WidgetEditor::WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : QSplitter(Qt::Vertical, parent_),
    _m_index(index_),
    _m_item(DomModel::toItem(_m_index)),
    _m_proxy(proxy_),
    _m_undo_stack(new QUndoStack)
{
    setChildrenCollapsible(false);

    reinterpret_cast<ProxyModelTable_var*>(proxy_)->setUndoStack(_m_undo_stack);

    MainWindow::instance()->undoGroup()->addStack(undoStack());
    connect(MainWindow::instance(), &MainWindow::signal_activateUndoStack, this, &WidgetEditor::slot_activateUndoStack);
}

QUndoStack * WidgetEditor::undoStack() const
{
    return _m_undo_stack;
}

void WidgetEditor::slot_activateUndoStack(QWidget *widget_)
{
    if(widget_ == _vars_table)
        undoStack()->setActive();
}

QWidget * WidgetEditor::createVarsEditor()
{
    // load types
    XmlParser::typesFromFile(":/resources/types.txt");

    // *  variables editor widgets
    // variables editor toolbar for table manipulations
    auto toolbar_table = new QToolBar;
    auto action = toolbar_table->addAction(QIcon(":/icon/images/plus.svg"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetEditor::slot_varAddVariable);
    action = toolbar_table->addAction(QIcon(":/icon/images/minus.svg"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetEditor::slot_varDelVariable);
    toolbar_table->setIconSize(QSize(16, 16));
    // variables editor table
    _vars_table = new TableView;
    // MainWindow::registerUndoStackWidget(_vars_table);
    _vars_table->setMinimumSize(500, 200);
    _vars_table->setItemDelegateForColumn(3, new CLineEditDelegate);
    _vars_table->setModel(_m_proxy);
    _vars_table->setRootIndex(DomModel::p_index(DomModel::s_index(_m_index), _m_proxy));
    _vars_table->setColumnHidden(0, true);
    _vars_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _vars_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _vars_table->horizontalHeader()->setHighlightSections(false);
    _vars_table->setItemDelegateForColumn(7, new CTextEditDelegate);
    QStringList varTypes = {"Scope",
                            "VAR",
                            "VAR_INPUT",
                            "VAR_OUTPUT",
                            "VAR_IN_OUT",
                            "VAR_TEMP",
                            "VAR_EXTERNAL",
                            "VAR_GLOBAL",
                            "Flags",
                            "CONSTANT",
                            "PERSISTENT",
                            "RETAIN"};
    _vars_table->setItemDelegateForColumn(2, new CComboBoxDelegate_variable_type(varTypes));
    connect(_vars_table, &TableView::signal_tableChanged, this, &WidgetEditor::slot_varTblVarChanged);
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
    _vars_text->setPlainText(XmlParser::getPouVarsText(DomModel::toItem(_m_index)->node()));
    connect(_vars_text, &CodeEditorWidget::textChanged, this, &WidgetEditor::slot_varTxtVarChanged);
    _vars_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor::slot_varTxtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/table_9.svg"), tr("Table"));
    connect(action, &QAction::toggled, this, &WidgetEditor::slot_varTblViewToggled);
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

void WidgetEditor::slot_selectRow_tree(const QModelIndex &index_, bool first_)
{
    _vars_table->clearSelection();
    _vars_table->setCurrentIndex(QModelIndex());
    QModelIndex index = _vars_table->model()->index(index_.row(), 3, index_.parent());
    _vars_table->setCurrentIndex(index);
    if(first_) _vars_table->edit(index);
}

QWidget * WidgetEditor::createCodeEditor()
{
    // *  code editor widgets
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getPouBodyText(DomModel::toItem(_m_index)->node()));
    connect(_body_text, &CodeEditorWidget::textChanged, this, &WidgetEditor::slot_codeTxtChanged);
    // ***

    return _body_text;
}

void WidgetEditor::slot_varTxtViewToggled(bool state)
{
    Q_UNUSED(state);

    _m_table_container->hide();
    _vars_text->show();
}

void WidgetEditor::slot_varTblViewToggled(bool state)
{
    Q_UNUSED(state);

    _vars_text->hide();
    _m_table_container->show();
}

void WidgetEditor::slot_codeTxtChanged()
{
    qDebug() << __PRETTY_FUNCTION__;

    // get new node from editor
    QDomNode new_node = XmlParser::getPouNode
        (
        _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
        _body_text != nullptr ? _body_text->toPlainText() : QString(),
        _m_item->node()
        );

    _m_item->updateNode(new_node.namedItem("body"));
}

void WidgetEditor::updateTblView()
{
    // get new node form txt view
    QDomNode new_node = XmlParser::getPouNode
        (
        _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
        _body_text != nullptr ? _body_text->toPlainText() : QString(),
        _m_item->node()
        );

    // remove old variables from item
    _m_item->removeChildren();
    // remove rows from model
    _m_proxy->sourceModel()->removeRows(0, _m_item->rowCount(), DomModel::s_index(_m_index));

    // set new node to item
    _m_item->updateNode(new_node.namedItem("interface"));
    // add rows to model
    auto count = new_node.namedItem("interface").toElement().elementsByTagName("variable").count();
    _m_proxy->sourceModel()->insertRows(0, count, DomModel::s_index(_m_index));
}

void WidgetEditor::slot_varTxtVarChanged()
{
    // user make changes in text view
    if(_vars_text->isVisible())
    {
        qDebug() << __PRETTY_FUNCTION__;

        updateTblView();
    }
}

void WidgetEditor::slot_varTblVarChanged()
{
    // user make changes in text view
    if(_vars_table->isVisible() || _vars_table->selectionModel()->hasSelection())
    {
        qDebug() << __PRETTY_FUNCTION__;

        // deselect vars items
        if(!_vars_table->isVisible())
            _vars_table->selectionModel()->clearSelection();

        // set new text to text view
        _vars_text->setPlainText(XmlParser::getPouVarsText(_m_item->node()));
    }
}

void WidgetEditor::slot_varAddVariable()
{
    qDebug() << __PRETTY_FUNCTION__;

    auto current = _vars_table->selectionModel()->selectedRows();
    auto node = _m_item->node().namedItem("interface").namedItem("localVars").isNull() ? _m_item->node() :
                    _m_item->node().namedItem("interface").namedItem("localVars");

    auto cmd =  new CUndoCommand_insert_table(
        _m_proxy,
        (current.count() == 1) ? current.at(0) : QModelIndex(),
        DomModel::s_index(_m_index),
        _m_item->defaultNode().toDocument().documentElement(),
        node);
    connect(cmd, &CUndoCommand_insert_table::signal_insertRow, this, &WidgetEditor::slot_selectRow_tree);
    undoStack()->push(cmd);
}

void WidgetEditor::slot_varDelVariable()
{
    qDebug() << __PRETTY_FUNCTION__;

    auto current = _vars_table->selectionModel()->selectedRows();

    if(current.count() != 1)
        return;

    undoStack()->push(
        new CUndoCommand_remove_table(
            DomModel::toModel(_m_proxy->sourceModel()),
            DomModel::s_index(current.at(0)),
            DomModel::s_index(_m_index)));
}
// ----------------------------------------------------------------------------
