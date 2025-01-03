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
#include "view/TableView.h"
#include "view/ItemDelegate.h"
#include "editor/st/CodeEditorWidget.h"
#include "editor/st/XmlParser.h"
// #include "translator/TranslatorLD.h"
#include "main/MainWindow.h"
#include "undo/cundocommand_insert_table.h"
#include "undo/cundocommand_remove_table.h"
#include "log/Logger.h"

WidgetEditor::WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : QSplitter(Qt::Vertical, parent_),
    _index(index_),
    _node(DomModel::toItem(_index)->node()),
    _proxy(proxy_),
    _m_undo_stack(new QUndoStack)
{
    setChildrenCollapsible(false);

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
    {
        qDebug() << __PRETTY_FUNCTION__;
        undoStack()->setActive();
    }
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
    _vars_table->setModel(_proxy);
    _vars_table->setRootIndex(DomModel::p_index(DomModel::s_index(_index), _proxy));
    _vars_table->setColumnHidden(0, true);
    _vars_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _vars_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _vars_table->horizontalHeader()->setHighlightSections(false);
    _vars_table->setItemDelegateForColumn(7, new CTextEditDelegate);
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
    _vars_text->setPlainText(XmlParser::getPouVarsText(DomModel::toItem(_index)->node()));
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

QWidget * WidgetEditor::createCodeEditor()
{
    // *  code editor widgets
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getPouBodyText(DomModel::toItem(_index)->node()));
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
        DomModel::toItem(_vars_table->rootIndex())->node()
        );

    // qDebug() << DomItem::printNode(new_node);

    DomModel::toItem(_vars_table->rootIndex())->updateNode(new_node.namedItem("body"));
}

void WidgetEditor::updateTblView()
{
    qDebug() << __PRETTY_FUNCTION__;

    // get new node form txt view
    QDomNode new_node = XmlParser::getPouNode
        (
        _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
        _body_text != nullptr ? _body_text->toPlainText() : QString(),
        DomModel::toItem(_vars_table->rootIndex())->node()
        );

    // remove old variables from item
    DomModel::toItem(_vars_table->rootIndex())->removeChildren();
    // remove rows from model
    DomModel::toProxy(_vars_table->model())->sourceModel()->
        removeRows(0, DomModel::toItem(_vars_table->rootIndex())->rowCount(), DomModel::s_index(_vars_table->rootIndex()));

    // set new node to item
    DomModel::toItem(_vars_table->rootIndex())->updateNode(new_node.namedItem("interface"));
    // add rows to model
    auto count = new_node.namedItem("interface").toElement().elementsByTagName("variable").count();
    _proxy->sourceModel()->insertRows(0, count, DomModel::s_index(_vars_table->rootIndex()));
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
        _vars_text->setPlainText(XmlParser::getPouVarsText(DomModel::toItem(_index)->node()));
    }
}

void WidgetEditor::slot_varAddVariable()
{
    qDebug() << __PRETTY_FUNCTION__;

    auto parent = DomModel::toItem(_vars_table->rootIndex());
    auto index_parent = DomModel::s_index(_vars_table->rootIndex());
    auto node = parent->node().namedItem("interface");

    auto current = _vars_table->selectionModel()->selectedRows();
    auto index = (current.count() == 1) ? current.at(0) : QModelIndex();

    undoStack()->push(
        new CUndoCommand_insert_table(parent->defaultNode().toDocument().documentElement(), node, index, index_parent, _proxy->sourceModel()));

}

void WidgetEditor::slot_varDelVariable()
{
    qDebug() << __PRETTY_FUNCTION__;

    // for every selected rows
    // !!! don't work for multiselection
    for(auto index : _vars_table->selectionModel()->selectedRows())
    {
        // delete node
        // DomModel::toItem(_vars_table->rootIndex())->removeChild(DomModel::s_index(index).row(), 0, DomModel::toItem(index)->node());

        // delete item
        // DomModel::toProxy(_vars_table->model())->sourceModel()->
        //     removeRow(DomModel::s_index(index).row(), DomModel::s_index(_vars_table->rootIndex()));

        // qDebug() << DomModel::toProxy(_vars_table->model())->sourceModel()->rowCount(DomModel::s_index(_vars_table->rootIndex()))
        //          << DomModel::s_index(index).row();

        undoStack()->push(
            new CUndoCommand_remove_table(DomModel::s_index(index), DomModel::s_index(_vars_table->rootIndex()), _proxy->sourceModel()));
    }
}
// ----------------------------------------------------------------------------
