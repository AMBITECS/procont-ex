#include "InputDialog.h"

#include "iec/StandardLibrary.h"
#include "tr/translation.h"
#include "xml/PLCopenXML.h"

#include <QLayout>
#include <QTabWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include <QListView>
#include <QTreeView>
#include <QTreeWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QLineEdit>
#include <QTableWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QPushButton>

#include <QFile>

InputDialog::InputDialog(eType type_) :
    _m_type(type_)
{
    setWindowTitle(tr("Input Assistant"));
    setMinimumSize(800, 700);

    // *** tab 1 - categories
    auto tab1 = new QSplitter(Qt::Vertical);
    tab1->setChildrenCollapsible(false);
    auto tab1_wgt_t = new QWidget;
    auto tab1_listwidget_cat = new QListView;
    tab1_listwidget_cat->setFixedWidth(200);
    tab1_listwidget_cat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _m_tab1_treeview_name = new QTreeView;
    _m_tab1_treeview_name->setMinimumSize(550, 400);
    _m_tab1_treeview_name->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto tab1_splitter_h = new QSplitter(Qt::Horizontal);
    tab1_splitter_h->addWidget(tab1_listwidget_cat);
    tab1_splitter_h->addWidget(_m_tab1_treeview_name);
    tab1_splitter_h->setChildrenCollapsible(false);
    auto vb = new QVBoxLayout;
    vb->addWidget(tab1_splitter_h);
    tab1_wgt_t->setLayout(vb);
    auto tab1_wgt_b = new QWidget;
    _m_tab1_textedit_doc = new QTextEdit;
    _m_tab1_textedit_doc->setReadOnly(true);
    _m_tab1_textedit_doc->setMinimumHeight(75);
    auto tab1_treewidget_vars = new QTreeView;
    _m_tab1_vars_model = new QStandardItemModel;
    tab1_treewidget_vars->setModel(_m_tab1_vars_model);
    tab1_treewidget_vars->setMinimumHeight(75);
    auto tab1_splitter_v = new QSplitter(Qt::Vertical, tab1_wgt_b);
    tab1_splitter_v->addWidget(_m_tab1_textedit_doc);
    tab1_splitter_v->addWidget(tab1_treewidget_vars);
    tab1_splitter_v->setChildrenCollapsible(false);
    vb = new QVBoxLayout;
    vb->addWidget(new QLabel(tr("Documentation")));
    vb->addWidget(tab1_splitter_v);
    tab1_wgt_b->setLayout(vb);
    tab1->addWidget(tab1_wgt_t);
    tab1->addWidget(tab1_wgt_b);
    {
        QStringList _categories_ru;
        for(auto i : StandardLibrary::instance()->objects())
        {
            QString type = get_type_name(i);
            if(!_m_categories.contains(type) && accept_category(type, _m_type))
            {
                _m_categories.append(type);
                _categories_ru.append(tr_str::instance()->ru(type, tr_str::eTranslateLetters::eTL_Capital));
            }
        }

        tab1_listwidget_cat->setModel(new QStringListModel(_categories_ru));
        connect(tab1_listwidget_cat->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_categoryCurrentChanged);

        _m_tab1_name_model = new QStandardItemModel;
        _m_tab1_treeview_name->setModel(_m_tab1_name_model);
        connect(_m_tab1_treeview_name->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_typeCurrentChanged_tab1);
    }
    // ***
    // *** tab 2 - find
    auto tab2 = new QSplitter(Qt::Vertical);
    tab2->setChildrenCollapsible(false);
    auto tab2_wgt_t = new QWidget;
    auto tab2_lineedit_query = new QLineEdit;
    _m_tab2_treeview_result = new QTreeView;
    _m_tab2_treeview_result->setMinimumHeight(370);
    _m_tab2_treeview_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vb = new QVBoxLayout;
    vb->addWidget(tab2_lineedit_query);
    vb->addWidget(_m_tab2_treeview_result);
    tab2_wgt_t->setLayout(vb);
    auto tab2_wgt_b = new QWidget;
    _m_tab2_textedit_doc = new QTextEdit;
    _m_tab2_textedit_doc->setMinimumHeight(75);
    _m_tab2_textedit_doc->setReadOnly(true);
    auto tab2_treewidget_vars = new QTreeView;
    _m_tab2_vars_model = new QStandardItemModel;
    tab2_treewidget_vars->setModel(_m_tab2_vars_model);
    tab2_treewidget_vars->setMinimumHeight(75);
    auto tab2_splitter_v = new QSplitter(Qt::Vertical, tab1_wgt_b);
    tab2_splitter_v->addWidget(_m_tab2_textedit_doc);
    tab2_splitter_v->addWidget(tab2_treewidget_vars);
    tab2_splitter_v->setChildrenCollapsible(false);
    vb = new QVBoxLayout;
    vb->addWidget(new QLabel(tr("Documentation")));
    vb->addWidget(tab2_splitter_v);
    tab2_wgt_b->setLayout(vb);
    tab2->addWidget(tab2_wgt_t);
    tab2->addWidget(tab2_wgt_b);
    {
        _m_tab2_filter_proxy = new QSortFilterProxyModel;
        _m_tab2_treeview_result->setModel(_m_tab2_filter_proxy);
        auto source = new QStandardItemModel;
        source->setColumnCount(3);
        source->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        source->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
        source->setHeaderData(2, Qt::Horizontal, QObject::tr("Source"));
        for(auto i : StandardLibrary::instance()->objects())
        {
            ILibrary::ObjectInfo info = StandardLibrary::instance()->object_info(i);
            if(!accept_category(info.type, _m_type))
                continue;
            auto items = QList<QStandardItem *>();
            items << new QStandardItem(info.name)
                  << new QStandardItem(tr_str::instance()->ru(info.type, tr_str::eTranslateLetters::eTL_Capital))
                  << new QStandardItem(info.source);
            source->insertRow(0, items);
        }
        _m_tab2_filter_proxy->setSourceModel(source);
        _m_tab2_treeview_result->setColumnWidth(0, 200);
        _m_tab2_treeview_result->setColumnWidth(1, 150);
        connect(_m_tab2_treeview_result->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_typeCurrentChanged_tab2);

        connect(tab2_lineedit_query, &QLineEdit::textChanged, this, &InputDialog::slot_filterTextChanged);
    }
    // ***

    _m_tabs = new QTabWidget;
    _m_tabs->addTab(tab1, tr("Categories"));
    _m_tabs->addTab(tab2, tr("Find"));
    connect(_m_tabs, &QTabWidget::currentChanged, this, &InputDialog::slot_currentTabChanged);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("OK"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto layout = new QVBoxLayout;
    layout->addWidget(_m_tabs);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

bool InputDialog::accept_category(const QString & name_, eType type_)
{
    switch(type_)
    {
    case eCT_POU:
        return (name_ != "program") && (name_ != "dataType");
        break;
    case eCT_TYPE:
        return (name_ != "program") && (name_ != "function");
    case eCT_ALL:
        return true;
        break;
    }

    return false;
}

QString InputDialog::get_type_name(const QString & name_)
{
    QString type = {};
    auto node = StandardLibrary::instance()->find_pou(name_);
    if(node.isNull())
    {
        node = StandardLibrary::instance()->find_type(name_);
        type = "dataType";
    }
    else
        type = node.toElement().attribute("pouType");

    return type;
}

QString InputDialog::get_vartype_name(const QDomNode &node_)
{
    // todo - realize this
    return "";
}

QDomNode InputDialog::selectedType() const
{
    auto list = _m_tab1_treeview_name->selectionModel()->selectedIndexes();
    if(_m_tabs->currentIndex() != 0)
        list = _m_tab2_treeview_result->selectionModel()->selectedIndexes();

    auto selection = std::find_if(list.begin(), list.end(), [](const QModelIndex &index){ return index.column() == 0; });
    if(selection != list.end())
    {
        auto node = StandardLibrary::instance()->find_pou(selection->data().toString());
        if(node.isNull())
            node = StandardLibrary::instance()->find_type(selection->data().toString());

        return node;
    }

    return {};
}

void InputDialog::slot_categoryCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    if(current.isValid())
    {
        QString type = tr_str::instance()->en(current.data().toString());
        _m_tab1_name_model->clear();
        _m_tab1_name_model->setColumnCount(3);
        _m_tab1_name_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        _m_tab1_name_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
        _m_tab1_name_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Source"));
        QMap<QString, QStandardItem *> _topItems;
        for(auto i : StandardLibrary::instance()->objects())
        {
            ILibrary::ObjectInfo info = StandardLibrary::instance()->object_info(i);
            if(get_type_name(i) == type)
            {
                if(!_topItems.contains(info.category))
                {
                    _topItems[info.category] = new QStandardItem(tr_str::instance()->ru(info.category));
                    _m_tab1_name_model->insertRow(0, _topItems[info.category]);
                }

                auto items = QList<QStandardItem *>();
                items << new QStandardItem(info.name)
                      << new QStandardItem(tr_str::instance()->ru(info.type, tr_str::eTranslateLetters::eTL_Capital))
                      << new QStandardItem(info.source);
                _topItems[info.category]->insertRow(0, items);
            }
        }
        _m_tab1_treeview_name->setColumnWidth(0, 200);
        _m_tab1_treeview_name->setColumnWidth(1, 150);
    }
}

void InputDialog::updateVarsInfo(const QModelIndex &current_type_, QTextEdit *vars_info_, QStandardItemModel *vars_model_)
{
    QDomNode node = StandardLibrary::instance()->find_pou(current_type_.data().toString());

    if(!node.isNull())
    {
        auto name = node.toElement().attribute("name");

        vars_model_->clear();
        vars_model_->setColumnCount(4);
        vars_model_->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        vars_model_->setHeaderData(1, Qt::Horizontal, QObject::tr("Value type"));
        vars_model_->setHeaderData(2, Qt::Horizontal, QObject::tr("Variable type"));
        vars_model_->setHeaderData(3, Qt::Horizontal, QObject::tr("Documentation"));

        QString ret_val = {};
        if(node.toElement().attribute("pouType") == "function")
        {
            ret_val = node.toElement().namedItem("interface").namedItem("returnType").firstChild().nodeName();
            auto items = QList<QStandardItem *>();
            items << new QStandardItem(QIcon(":/icon/images/output3.svg"), name)
                  << new QStandardItem(PLCopenXMLVariableBuilder::instance()->build(node.toElement().namedItem("interface").namedItem("returnType"))->name())
                  << new QStandardItem("VAR_OUTPUT");
            vars_model_->insertRow(0, items);
        }
        auto ret = (ret_val.size() != 0) ? QString(" => %1").arg(ret_val) : "";

        auto list_vars = node.toElement().namedItem("interface").namedItem("outputVars").childNodes();
        for(auto i=0;i<list_vars.count();i++)
        {
            auto items = QList<QStandardItem *>();
            items << new QStandardItem(QIcon(":/icon/images/output3.svg"), list_vars.at(i).toElement().attribute("name"))
                  << new QStandardItem(PLCopenXMLVariableBuilder::instance()->build(list_vars.at(i).toElement().namedItem("type"))->name())
                  << new QStandardItem("VAR_OUTPUT")
                  << new QStandardItem(list_vars.at(i).toElement().namedItem("documentation").namedItem("xhtml:p").toElement().text());
            vars_model_->insertRow(0, items);
        }

        QString i_vars = {};
        list_vars = node.toElement().namedItem("interface").namedItem("inputVars").childNodes();
        for(auto i=0;i<list_vars.count();i++)
        {
            QDomNode _type_node = list_vars.at(i).toElement().namedItem("type");

            i_vars += _type_node.firstChild().nodeName() + ", ";

            auto items = QList<QStandardItem *>();
            items << new QStandardItem(QIcon(":/icon/images/input3.svg"), list_vars.at(i).toElement().attribute("name"))
                  << new QStandardItem(PLCopenXMLVariableBuilder::instance()->build(list_vars.at(i).toElement().namedItem("type"))->name())
                  << new QStandardItem("VAR_INPUT")
                  << new QStandardItem(list_vars.at(i).toElement().namedItem("documentation").namedItem("xhtml:p").toElement().text());
            vars_model_->insertRow(0, items);
        }
        i_vars = i_vars.left(i_vars.size()-2);

        vars_info_->append(node.toElement().namedItem("documentation").namedItem("xhtml:p").toElement().text());
        vars_info_->append(QString());
        vars_info_->append(QString("%1(%2)%3").arg(name).arg(i_vars).arg(ret));
    }
}

void InputDialog::slot_currentTabChanged(int index)
{
    _m_tab1_textedit_doc->clear();
    _m_tab2_textedit_doc->clear();
    _m_tab1_vars_model->clear();
    _m_tab2_vars_model->clear();

    if(index == 0 && _m_tab1_treeview_name->currentIndex().isValid())
        updateVarsInfo(_m_tab1_treeview_name->currentIndex(), _m_tab1_textedit_doc, _m_tab1_vars_model);

    if(index == 1 && _m_tab2_treeview_result->currentIndex().isValid())
        updateVarsInfo(_m_tab2_treeview_result->currentIndex(), _m_tab2_textedit_doc, _m_tab2_vars_model);
}

void InputDialog::slot_typeCurrentChanged_tab1(const QModelIndex &current, const QModelIndex &)
{
    if(current.isValid())
    {
        _m_tab1_textedit_doc->clear();
        _m_tab2_textedit_doc->clear();
        _m_tab1_vars_model->clear();
        _m_tab2_vars_model->clear();
        updateVarsInfo(current, _m_tab1_textedit_doc, _m_tab1_vars_model);
    }
}

void InputDialog::slot_typeCurrentChanged_tab2(const QModelIndex &current, const QModelIndex &)
{
    if(current.isValid())
    {
        _m_tab1_textedit_doc->clear();
        _m_tab2_textedit_doc->clear();
        _m_tab1_vars_model->clear();
        _m_tab2_vars_model->clear();
        updateVarsInfo(current, _m_tab2_textedit_doc, _m_tab2_vars_model);
    }
}

void InputDialog::slot_filterTextChanged(const QString &text)
{
    QString pattern = QRegularExpression::escape(text);
    QRegularExpression regularExpression(pattern);
    _m_tab2_filter_proxy->setFilterRegularExpression(regularExpression);
}

