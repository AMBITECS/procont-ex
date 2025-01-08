#include "WidgetEditor_fbd.h"

#include <QTableView>
#include <QToolBar>
#include <QHeaderView>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "model/DomModel.h"
#include "view/TableView.h"
#include "view/ItemDelegate.h"
#include "editor/st/CodeEditorWidget.h"
#include "editor/st/XmlParser.h"
#include "translator/TranslatorFbd.h"
#include "main/MainWindow.h"
#include "log/Logger.h"

#include "editor/fbd/fbd/graphics/cdiagramwidget.h"

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
    // !!! for what this ??? i don't now
    // updateTblView();
}

QWidget * WidgetEditor_fbd::createVarsEditor()
{
    // load types
    XmlParser::typesFromFile(":/resources/types.txt");

    // *  variables editor widgets
    // variables editor toolbar for table manipulations
    auto toolbar_table = new QToolBar;
    auto action = toolbar_table->addAction(QIcon(":/icon/images/plus.svg"), tr("Add"));
    connect(action, &QAction::triggered, this, &WidgetEditor_fbd::slot_varAddVariable);
    action = toolbar_table->addAction(QIcon(":/icon/images/minus.svg"), tr("Remove"));
    connect(action, &QAction::triggered, this, &WidgetEditor_fbd::slot_varDelVariable);
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
    connect(_vars_table, &TableView::signal_tableChanged, this, &WidgetEditor_fbd::slot_varTblVarChanged);
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
    connect(_vars_text, &CodeEditorWidget::textChanged, this, &WidgetEditor_fbd::slot_varTxtVarChanged);
    _vars_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_varTxtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/table_9.svg"), tr("Table"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_varTblViewToggled);
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

void WidgetEditor_fbd::slot_varAddVariable()
{
    WidgetEditor::slot_varAddVariable();

    qDebug() << __PRETTY_FUNCTION__;

    _m_fbd_view->update_interface(DomModel::toItem(_vars_table->rootIndex())->node());
}

void WidgetEditor_fbd::slot_varDelVariable()
{
    WidgetEditor::slot_varDelVariable();

    qDebug() << __PRETTY_FUNCTION__;

    _m_fbd_view->update_interface(DomModel::toItem(_vars_table->rootIndex())->node());
}

void WidgetEditor_fbd::slot_varTxtVarChanged()
{
    WidgetEditor::slot_varTxtVarChanged();

    if(_vars_text->isVisible())
    {
        qDebug() << __PRETTY_FUNCTION__;

        _m_fbd_view->update_interface(DomModel::toItem(_vars_table->rootIndex())->node());
    }
}

void WidgetEditor_fbd::slot_varTblVarChanged()
{
    WidgetEditor::slot_varTblVarChanged();

    if(_vars_table->isVisible())
    {
        qDebug() << __PRETTY_FUNCTION__;

        _m_fbd_view->update_interface(DomModel::toItem(_vars_table->rootIndex())->node());
    }
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
    _m_fbd_view = new CDiagramWidget(DomModel::toItem(_m_index)->node(), MainWindow::instance()->toolWidget());
    connect(_m_fbd_view, &CDiagramWidget::changed_diagram, this, &WidgetEditor_fbd::slot_codeShmChanged);
    connect(_m_fbd_view, &CDiagramWidget::interface_variable_new, this, &WidgetEditor_fbd::slot_interfaceVariableAdd);
    connect(_m_fbd_view, &CDiagramWidget::instance_removed, this, &WidgetEditor_fbd::slot_interfaceVariableDel);
    connect(_m_fbd_view, &CDiagramWidget::interface_variable_rename, this, &WidgetEditor_fbd::slot_interfaceVariableRename);
    // _m_fbd_view->set_active();
    _m_fbd_view->setMinimumSize(500, 250);
    // variables editor code editor
    // _txt_view = WidgetEditor::createCodeEditor();
    _body_text = new CodeEditorWidget(this);
    _body_text->setMinimumSize(500, 250);
    _body_text->setPlainText(XmlParser::getPouBodyText(DomModel::toItem(_m_index)->node()));
    _body_text->hide();
    // variables editor toolbar for switch view
    auto toolbar_view = new QToolBar();
    toolbar_view->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar_view);
    auto action = toolbar_view->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_codeTxtViewToggled);
    action->setCheckable(true); group->addAction(action);
    action = toolbar_view->addAction(QIcon(":/icon/images/diagram.svg"), tr("Schema"));
    connect(action, &QAction::toggled, this, &WidgetEditor_fbd::slot_codeShmViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    toolbar_view->setIconSize(QSize(24, 24));
    // *  variables editor layout
    // vertical (toolbar - table/code editor)
    auto vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(_m_fbd_view);
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

void WidgetEditor_fbd::slot_codeShmViewToggled(bool)
{
    _body_text->hide();
    _m_fbd_view->show();
}

void WidgetEditor_fbd::slot_codeTxtViewToggled(bool)
{
    TranslatorFBD translator;
    _body_text->setPlainText(translator.getSTCode_pou(DomModel::toItem(_m_index)->node()));

    _m_fbd_view->hide();
    _body_text->show();
}

void WidgetEditor_fbd::slot_codeShmChanged(const QDomNode &new_node_)
{
    qDebug() << "1" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;

    // qDebug() << DomItem::printNode(new_node_);

    QDomDocument doc = DomModel::toItem(_vars_table->rootIndex())->node().ownerDocument();

    qDebug() << "2" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;

    DomModel::toItem(_vars_table->rootIndex())->updateNode(doc.importNode(new_node_, true).namedItem("body"));

    qDebug() << "3" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;
}

void WidgetEditor_fbd::slot_interfaceVariableAdd(const QString &type, const QString &name)
{
    qDebug() << __PRETTY_FUNCTION__;

    auto parent = DomModel::toItem(_vars_table->rootIndex());

    auto parentNode = DomModel::toItem(_vars_table->rootIndex())->node();
    QDomElement el_variable = parentNode.ownerDocument().createElement("variable");
    el_variable.setAttribute("name", name);
    QDomElement el_variable_type = parentNode.ownerDocument().createElement("type");
    QDomElement el_variable_type_derived = parentNode.ownerDocument().createElement("derived");
    el_variable_type_derived.setAttribute("name", type);
    el_variable_type.appendChild(el_variable_type_derived);
    el_variable.appendChild(el_variable_type);
    QDomNode el_localVars = parentNode.namedItem("interface").namedItem("localVars");
    if(el_localVars.isNull())
    {
        el_localVars = parentNode.ownerDocument().createElement("localVars");
        parentNode.namedItem("interface").appendChild(el_localVars);
    }
    el_localVars.appendChild(el_variable);

    // add item
    _m_proxy->sourceModel()->insertRow(parent->rowCount(), DomModel::s_index(_vars_table->rootIndex()));
}

void WidgetEditor_fbd::slot_interfaceVariableDel(const QString &type, const QString &name)
{
    qDebug() << __PRETTY_FUNCTION__;

    QModelIndex var_index;
    for(auto i = 0;i<DomModel::toItem(_vars_table->rootIndex())->rowCount();i++)
    {
        auto index_name = _vars_table->model()->index(i, 3, _vars_table->rootIndex());
        auto index_type = _vars_table->model()->index(i, 5, _vars_table->rootIndex());
        if(index_name.data() == name && index_type.data() == type)
        {
            var_index = index_name;
            break;
        }
    }

    if(var_index.isValid())
    {
        DomModel::toItem(_vars_table->rootIndex())->
            removeChild(DomModel::s_index(var_index).row(), 0, DomModel::toItem(var_index)->node().parentNode());
        DomModel::toProxy(_vars_table->model())->sourceModel()->
            removeRow(DomModel::s_index(var_index).row(), DomModel::s_index(_vars_table->rootIndex()));
    }
}

void WidgetEditor_fbd::slot_interfaceVariableRename(const QString &old_name, const QString &new_name)
{
    qDebug() << __PRETTY_FUNCTION__;

    QModelIndex var_index;
    for(auto i = 0;i<DomModel::toItem(_vars_table->rootIndex())->rowCount();i++)
    {
        auto index = _vars_table->model()->index(i, 3, _vars_table->rootIndex());
        if(index.data() == old_name)
        {
            var_index = index;
            break;
        }
    }

    if(var_index.isValid())
    {
        DomModel::toItem(var_index)->setData(new_name, Qt::DisplayRole);
        _vars_table->setFocus();
        _m_fbd_view->setFocus();
    }
}
// ----------------------------------------------------------------------------
