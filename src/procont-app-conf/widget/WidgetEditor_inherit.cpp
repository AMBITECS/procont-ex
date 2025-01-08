#include "WidgetEditor_inherit.h"

#include <QTableView>
#include <QToolBar>
#include <QHeaderView>
#include <QActionGroup>
#include <QVBoxLayout>

#include "model/DomModel.h"
#include "view/TableView.h"
#include "view/ItemDelegate.h"
#include "editor/st/CodeEditorWidget.h"
#include "editor/st/XmlParser.h"
#include "translator/TranslatorLD.h"
#include "main/MainWindow.h"
#include "log/Logger.h"

#include "editor/fbd/ld/clddiagram.h"

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
    // !!! for what this ??? i don't now
    // updateTblView();
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
    // !!! for what this ??? i don't now
    // updateTblView();

    vars->hide();
}

void WidgetEditor_type::slot_varTxtVarChanged()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_type::slot_varTblVarChanged()
{
    qDebug() << __PRETTY_FUNCTION__;
}

QWidget * WidgetEditor_type::createCodeEditor()
{
    // *  code editor widgets
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getDataTypeText(DomModel::toItem(_m_index)->node()));
    connect(_body_text, &CodeEditorWidget::textChanged, this, &WidgetEditor_type::slot_codeTxtChanged);
    // ***

    return _body_text;
}

void WidgetEditor_type::slot_codeTxtChanged()
{
    qDebug() << __PRETTY_FUNCTION__;

    // get new node from st editor
    auto new_node = XmlParser::getDataTypeNode
        (
            _body_text != nullptr ? _body_text->toPlainText() : QString(),
            _vars_text != nullptr ? _vars_text->toPlainText() : QString(),
             DomModel::toItem(_vars_table->rootIndex())->node()
        );

    // qDebug() << DomItem::printNode(new_node);

    // set new node to item
    DomModel::toItem(_vars_table->rootIndex())->updateNode(new_node.namedItem("baseType"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_ld ***

WidgetEditor_ld::WidgetEditor_ld(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_)
    : WidgetEditor(index_, proxy_, parent_)
{
    // *** variables editor
    addWidget(createVarsEditor());

    // *** code editor
    addWidget(createCodeEditor());

    // !!! delete when st-editor will work correctly
    // !!! for what this ??? i don't now
    // updateTblView();
}

QWidget * WidgetEditor_ld::createVarsEditor()
{
    // load types
    XmlParser::typesFromFile(":/resources/types.txt");

    // *  variables editor widgets
    // variables editor toolbar for table manipulations
    auto toolbar_table = new QToolBar;
    auto action = toolbar_table->addAction(QIcon(":/icon/images/plus.svg"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetEditor_ld::slot_varAddVariable);
    action = toolbar_table->addAction(QIcon(":/icon/images/minus.svg"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetEditor_ld::slot_varDelVariable);
    toolbar_table->setIconSize(QSize(16, 16));
    // variables editor table
    _vars_table = new TableView;
    _vars_table->setMinimumSize(500, 200);
    _vars_table->setModel(_m_proxy);
    _vars_table->setRootIndex(DomModel::p_index(DomModel::s_index(_m_index), _m_proxy));
    _vars_table->setColumnHidden(0, true);
    _vars_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _vars_table->setSelectionMode(QAbstractItemView::SingleSelection);
    _vars_table->horizontalHeader()->setHighlightSections(false);
    _vars_table->setItemDelegateForColumn(7, new CTextEditDelegate);
    connect(_vars_table, &TableView::signal_tableChanged, this, &WidgetEditor_ld::slot_varTblVarChanged);
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
    connect(_vars_text, &CodeEditorWidget::textChanged, this, &WidgetEditor_ld::slot_varTxtVarChanged);
    _vars_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor_ld::slot_varTxtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/table_9.svg"), tr("Table"));
    connect(action, &QAction::toggled, this, &WidgetEditor_ld::slot_varTblViewToggled);
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

void WidgetEditor_ld::slot_varAddVariable()
{
    WidgetEditor::slot_varAddVariable();

    qDebug() << __PRETTY_FUNCTION__;

    // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
}

void WidgetEditor_ld::slot_varDelVariable()
{
    WidgetEditor::slot_varDelVariable();

    qDebug() << __PRETTY_FUNCTION__;

    // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
}

void WidgetEditor_ld::slot_varTxtVarChanged()
{
    WidgetEditor::slot_varTxtVarChanged();

    if(_vars_text->isVisible())
    {
        qDebug() << __PRETTY_FUNCTION__;

        // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
    }
}

void WidgetEditor_ld::slot_varTblVarChanged()
{
    WidgetEditor::slot_varTblVarChanged();

    if(_vars_table->isVisible())
    {
        qDebug() << __PRETTY_FUNCTION__;

        // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
    }
}

QWidget * WidgetEditor_ld::createCodeEditor()
{
    // *  variables editor widgets
    // contauner for variables editor widgets
    auto container = new QWidget;
    // fbd view
    _m_ld_view = new CLdDiagram(DomModel::toItem(_m_index)->node(), MainWindow::instance()->toolWidget());
    _m_ld_view->setMinimumSize(500, 250);
    // connect(_m_ld_view, &CLdDiagram::changed_diagram, this, &WidgetEditor_ld::slot_codeShmChanged);
    // connect(_m_ld_view, &CLdDiagram::interface_variable_new, this, &WidgetEditor_ld::slot_interfaceVariableAdd);
    // connect(_m_ld_view, &CLdDiagram::instance_removed, this, &WidgetEditor_ld::slot_interfaceVariableDel);
    // connect(_m_ld_view, &CLdDiagram::interface_variable_rename, this, &WidgetEditor_ld::slot_interfaceVariableRename);
    // variables editor code editor
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getPouBodyText(DomModel::toItem(_m_index)->node()));
    _body_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    auto action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor_ld::slot_codeTxtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/diagram.svg"), tr("Schema"));
    connect(action, &QAction::toggled, this, &WidgetEditor_ld::slot_codeShmViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar_view->setIconSize(QSize(24, 24));
    // *  variables editor layout
    // vertical (toolbar - table/code editor)
    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(_m_ld_view);
    vertical_layout->addWidget(_body_text);
    // horizontal (vertical - toolbar for switch view)
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(toolbar_view);
    // set layout for container
    container->setLayout(horizontal_layout);
    // ***

    return container;
}

void WidgetEditor_ld::slot_codeShmViewToggled(bool)
{
    _body_text->hide();
    _m_ld_view->show();
}

void WidgetEditor_ld::slot_codeTxtViewToggled(bool)
{
    TranslatorLD translator;
    _body_text->setPlainText(translator.getSTCode_pou(DomModel::toItem(_m_index)->node()));

    _m_ld_view->hide();
    _body_text->show();
}

void WidgetEditor_ld::slot_codeShmChanged(const QDomNode &new_node_)
{
    qDebug() << __PRETTY_FUNCTION__;

    // qDebug() << DomItem::printNode(new_node_);

    QDomDocument doc = DomModel::toItem(_vars_table->rootIndex())->node().ownerDocument();
    DomModel::toItem(_vars_table->rootIndex())->updateNode(doc.importNode(new_node_, true).namedItem("body"));
}

void WidgetEditor_ld::slot_interfaceVariableAdd(const QString &type, const QString &name)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_ld::slot_interfaceVariableDel(const QString &type, const QString &name)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_ld::slot_interfaceVariableRename(const QString &old_name, const QString &new_name)
{
    qDebug() << __PRETTY_FUNCTION__;
}
// ----------------------------------------------------------------------------
