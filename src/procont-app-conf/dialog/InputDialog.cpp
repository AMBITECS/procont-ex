#include "InputDialog.h"

#include "iec/StandardLibrary.h"
#include "tr/translation.h"

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

#include <QFile>

InputDialog::InputDialog()
{
    setWindowTitle(tr("Input Assistant"));
    setMinimumSize(800, 700);

    // *** tab 1 - categories
    auto tab1 = new QSplitter(Qt::Vertical);
    tab1->setChildrenCollapsible(false);
    auto tab1_wgt_t = new QWidget;
    auto tab1_listwidget_cat = new QListView;
    tab1_listwidget_cat->setFixedWidth(250);
    tab1_listwidget_cat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _m_treeview_name = new QTreeView;
    _m_treeview_name->setMinimumSize(550, 400);
    _m_treeview_name->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto tab1_splitter_h = new QSplitter(Qt::Horizontal);
    tab1_splitter_h->addWidget(tab1_listwidget_cat);
    tab1_splitter_h->addWidget(_m_treeview_name);
    tab1_splitter_h->setChildrenCollapsible(false);
    auto vb = new QVBoxLayout;
    vb->addWidget(tab1_splitter_h);
    tab1_wgt_t->setLayout(vb);
    auto tab1_wgt_b = new QWidget;
    _m_textedit_doc = new QTextEdit;
    _m_textedit_doc->setReadOnly(true);
    _m_textedit_doc->setMinimumHeight(75);
    auto tab1_treewidget_vars = new QTreeView;
    tab1_treewidget_vars->setMinimumHeight(75);
    auto tab1_splitter_v = new QSplitter(Qt::Vertical, tab1_wgt_b);
    tab1_splitter_v->addWidget(_m_textedit_doc);
    tab1_splitter_v->addWidget(tab1_treewidget_vars);
    tab1_splitter_v->setChildrenCollapsible(false);
    vb = new QVBoxLayout;
    vb->addWidget(tab1_splitter_v);
    tab1_wgt_b->setLayout(vb);
    tab1->addWidget(tab1_wgt_t);
    tab1->addWidget(tab1_wgt_b);
    // ***
    // *** tab 2 - find
    auto tab2 = new QSplitter(Qt::Vertical);
    tab2->setChildrenCollapsible(false);
    auto tab2_wgt_t = new QWidget;
    auto tab2_lineedit_query = new QLineEdit;
    auto tab2_tablewidget_result = new QTableWidget;
    tab2_tablewidget_result->setMinimumHeight(350);
    vb = new QVBoxLayout;
    vb->addWidget(tab2_lineedit_query);
    vb->addWidget(tab2_tablewidget_result);
    tab2_wgt_t->setLayout(vb);
    auto tab2_wgt_b = new QWidget;
    auto tab2_textview_doc = new QTextEdit;
    tab2_textview_doc->setMinimumHeight(100);
    auto tab2_treewidget_vars = new QTreeWidget;
    tab2_treewidget_vars->setMinimumHeight(100);
    auto tab2_splitter_v = new QSplitter(Qt::Vertical, tab1_wgt_b);
    tab2_splitter_v->addWidget(tab2_textview_doc);
    tab2_splitter_v->addWidget(tab2_treewidget_vars);
    tab2_splitter_v->setChildrenCollapsible(false);
    vb = new QVBoxLayout;
    vb->addWidget(tab2_splitter_v);
    tab2_wgt_b->setLayout(vb);
    tab2->addWidget(tab2_wgt_t);
    tab2->addWidget(tab2_wgt_b);
    // ***

    auto tabs = new QTabWidget;
    tabs->addTab(tab1, tr("Categories"));
    tabs->addTab(tab2, tr("Find"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto layout = new QVBoxLayout;
    layout->addWidget(tabs);
    layout->addWidget(buttonBox);

    setLayout(layout);

    // QFile file("./lib.csv");
    // file.open(QIODevice::WriteOnly);
    // for(auto i : StandardLibrary::instance()->objects())
    // {
    //     QString type = get_type(i);
    //     if(!_m_categories.contains(type) && _m_view_content.contains(type))
    //         _m_categories.append(type);

    //     QDomNode node = StandardLibrary::instance()->find_pou(i);

    //     QString name = node.toElement().attribute("name");
    //     QString i_vars = {};
    //     QDomNodeList list_vars = node.toElement().namedItem("interface").namedItem("inputVars").childNodes();
    //     for(auto i=0;i<list_vars.count();i++)
    //         i_vars += list_vars.at(i).toElement().namedItem("type").firstChild().nodeName() + ", ";
    //     i_vars = i_vars.left(i_vars.size()-2);
    //     QString ret_val = {};
    //     if(node.toElement().attribute("pouType") == "function")
    //         ret_val = node.toElement().namedItem("interface").namedItem("returnType").firstChild().nodeName();

    //     QString ret = (ret_val.size() != 0) ? QString(" => %1").arg(ret_val) : "";

    //     file.write(QString("%1;%2;%3;%4\n").arg(name, QString("%1(%2)%3").arg(name).arg(i_vars).arg(ret),
    //         node.namedItem("addData").namedItem("data").namedItem("group").toElement().attribute("name"),
    //         node.namedItem("documentation").namedItem("xhtml:p").toElement().text()).toLatin1());
    // }
    // file.close();

    QStringList _categories_ru;
    for(auto i : StandardLibrary::instance()->objects())
    {
        QString type = get_type(i);
       if(!_m_categories.contains(type))
        {
            _m_categories.append(type);
            _categories_ru.append(tr_str::instance()->ru(type));
        }
    }

    auto catModel = new QStringListModel(_categories_ru);
    tab1_listwidget_cat->setModel(catModel);
    connect(tab1_listwidget_cat->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_categoryCurrentChanged);

    _m_treeview_name->setModel(new QStandardItemModel);
    connect(_m_treeview_name->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_typeCurrentChanged);

    tab1_treewidget_vars->setModel(new QStandardItemModel);
}

QString InputDialog::get_type(const QString & name_)
{
    QString type = {};
    QDomNode node = StandardLibrary::instance()->find_pou(name_);
    if(node.isNull())
    {
        node = StandardLibrary::instance()->find_type(name_);
        type = "dataType";
    }
    else
        type = node.toElement().attribute("pouType");

    return type;
}

void InputDialog::slot_categoryCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    if(current.isValid())
    {
        QString type = tr_str::instance()->en(current.data().toString());
        auto nameModel = reinterpret_cast<QStandardItemModel*>(_m_treeview_name->model());
        nameModel->clear();
        nameModel->setColumnCount(3);
        nameModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        nameModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
        nameModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Source"));
        QMap<QString, QStandardItem *> _topItems;
        for(auto i : StandardLibrary::instance()->objects())
        {
            ILibrary::ObjectInfo info = StandardLibrary::instance()->object_info(i);
            if(get_type(i) == type)
            {
                if(!_topItems.contains(info.category))
                {
                    _topItems[info.category] = new QStandardItem(info.category);
                    nameModel->insertRow(0, _topItems[info.category]);
                }

                auto items = QList<QStandardItem *>();
                items << new QStandardItem(info.name)
                      << new QStandardItem(tr_str::instance()->ru(info.type))
                      << new QStandardItem(info.source);
                _topItems[info.category]->insertRow(0, items);
                // nameModel->setData(nameModel->index(0, 0), info.name);
                // nameModel->setData(nameModel->index(0, 1), tr_str::instance()->ru(info.type));
                // nameModel->setData(nameModel->index(0, 2), info.source);
            }
        }
        _m_treeview_name->setColumnWidth(0, 200);
    }
}

void InputDialog::slot_typeCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    if(current.isValid())
    {
        _m_textedit_doc->clear();

        QDomNode node = StandardLibrary::instance()->find_pou(current.data().toString());
        if(!node.isNull())
        {
            QString name = node.toElement().attribute("name");
            QString i_vars = {};
            QDomNodeList list_vars = node.toElement().namedItem("interface").namedItem("inputVars").childNodes();
            for(auto i=0;i<list_vars.count();i++)
                i_vars += list_vars.at(i).toElement().namedItem("type").firstChild().nodeName() + ", ";
            i_vars = i_vars.left(i_vars.size()-2);
            QString ret_val = {};
            if(node.toElement().attribute("pouType") == "function")
                ret_val = node.toElement().namedItem("interface").namedItem("returnType").firstChild().nodeName();

            QString ret = (ret_val.size() != 0) ? QString(" => %1").arg(ret_val) : "";

            _m_textedit_doc->append(QString("%1(%2)%3").arg(name).arg(i_vars).arg(ret));
            _m_textedit_doc->append(QString());
            _m_textedit_doc->append(node.toElement().namedItem("documentation").namedItem("xhtml:p").toElement().text());
        }
    }
}
