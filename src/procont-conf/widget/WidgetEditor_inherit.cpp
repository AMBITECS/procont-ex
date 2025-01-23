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
    auto _vars = createVarsEditor();
    addWidget(_vars);

    // *** code editor
    addWidget(createCodeEditor());

    _vars->hide();
}

void WidgetEditor_type::slot_varTxtVarChanged()
{
    // qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_type::slot_varTblVarChanged()
{
    // qDebug() << __PRETTY_FUNCTION__;
}

QWidget * WidgetEditor_type::createCodeEditor()
{
    // *  code editor widgets
    _m_body_text = new CodeEditorWidget(false, this);
    _m_body_text->setMinimumSize(500, 250);
    _m_body_text->setPlainText(XmlParser::getDataTypeText(DomModel::toItem(_m_index)->node()));
    connect(_m_body_text, &CodeEditorWidget::textChanged, this, &WidgetEditor_type::slot_codeTxtChanged);
    // ***

    return _m_body_text;
}

void WidgetEditor_type::slot_codeTxtChanged()
{
    // qDebug() << __PRETTY_FUNCTION__;

    // get new node from st editor
    auto new_node = XmlParser::getDataTypeNode
        (
            _m_body_text != nullptr ? _m_body_text->toPlainText() : QString(),
            _m_vars_text != nullptr ? _m_vars_text->toPlainText() : QString(),
             DomModel::toItem(_m_vars_table->rootIndex())->node()
        );

    // set new node to item
    DomModel::toItem(_m_vars_table->rootIndex())->updateNode(new_node.namedItem("baseType"));
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
}

void WidgetEditor_ld::slot_varAddVariable()
{
    WidgetEditor::slot_varAddVariable();

    // qDebug() << __PRETTY_FUNCTION__;

    // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
}

void WidgetEditor_ld::slot_varDelVariable()
{
    WidgetEditor::slot_varDelVariable();

    // qDebug() << __PRETTY_FUNCTION__;

    // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
}

void WidgetEditor_ld::slot_varTxtVarChanged()
{
    WidgetEditor::slot_varTxtVarChanged();

    if(_m_vars_text->isVisible())
    {
        // qDebug() << __PRETTY_FUNCTION__;

        // _m_ld_view->update_interface(item(_vars_table->rootIndex())->node());
    }
}

void WidgetEditor_ld::slot_varTblVarChanged()
{
    WidgetEditor::slot_varTblVarChanged();

    if(_m_vars_table->isVisible())
    {
        // qDebug() << __PRETTY_FUNCTION__;

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
    _m_body_text = new CodeEditorWidget(true, this);
    _m_body_text->setMinimumSize(500, 250);
    _m_body_text->setPlainText(XmlParser::getPouBodyText(DomModel::toItem(_m_index)->node()));
    _m_body_text->hide();
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
    vertical_layout->addWidget(_m_body_text);
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
    _m_body_text->hide();
    _m_ld_view->show();
}

void WidgetEditor_ld::slot_codeTxtViewToggled(bool)
{
    TranslatorLD translator;
    _m_body_text->setPlainText(translator.getSTCode_pou(DomModel::toItem(_m_index)->node()));

    _m_ld_view->hide();
    _m_body_text->show();
}

void WidgetEditor_ld::slot_codeShmChanged(const QDomNode &new_node_)
{
    // qDebug() << __PRETTY_FUNCTION__;

    QDomDocument doc = DomModel::toItem(_m_vars_table->rootIndex())->node().ownerDocument();
    DomModel::toItem(_m_vars_table->rootIndex())->updateNode(doc.importNode(new_node_, true).namedItem("body"));
}

void WidgetEditor_ld::slot_interfaceVariableAdd(const QString &type, const QString &name)
{
    // qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_ld::slot_interfaceVariableDel(const QString &type, const QString &name)
{
    // qDebug() << __PRETTY_FUNCTION__;
}

void WidgetEditor_ld::slot_interfaceVariableRename(const QString &old_name, const QString &new_name)
{
    // qDebug() << __PRETTY_FUNCTION__;
}
// ----------------------------------------------------------------------------
