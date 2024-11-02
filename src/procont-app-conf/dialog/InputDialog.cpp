#include "InputDialog.h"

#include "iec/StandardLibrary.h"

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

InputDialog::InputDialog()
{
    // *** tab 1 - categories
    auto tab1 = new QSplitter(Qt::Vertical);
    tab1->setChildrenCollapsible(false);
    auto tab1_wgt_t = new QWidget;
    auto tab1_listwidget_cat = new QListView;
    tab1_listwidget_cat->setMinimumSize(250, 400);
    tab1_treewidget_lib = new QTreeView;
    tab1_treewidget_lib->setMinimumSize(550, 400);
    auto tab1_splitter_h = new QSplitter(Qt::Horizontal);
    tab1_splitter_h->addWidget(tab1_listwidget_cat);
    tab1_splitter_h->addWidget(tab1_treewidget_lib);
    tab1_splitter_h->setChildrenCollapsible(false);
    auto vb = new QVBoxLayout;
    vb->addWidget(tab1_splitter_h);
    tab1_wgt_t->setLayout(vb);
    auto tab1_wgt_b = new QWidget;
    auto tab1_textview_doc = new QTextEdit;
    tab1_textview_doc->setMinimumHeight(100);
    auto tab1_treewidget_vars = new QTreeWidget;
    tab1_treewidget_vars->setMinimumHeight(100);
    auto tab1_splitter_v = new QSplitter(Qt::Vertical, tab1_wgt_b);
    tab1_splitter_v->addWidget(tab1_textview_doc);
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

    setMinimumSize(800, 680);

    for(auto i : StandardLibrary::instance()->objects())
    {
        QString type = get_type(i);
        if(!_m_categories.contains(type))
            _m_categories.append(type);
    }

    auto catModel = new QStringListModel(_m_categories);
    tab1_listwidget_cat->setModel(catModel);
    connect(tab1_listwidget_cat->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_categoryCurrentChanged);

    auto nameModel = new QStandardItemModel;
    nameModel->setColumnCount(3);
    nameModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    nameModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    nameModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Source"));
    tab1_treewidget_lib->setModel(nameModel);
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
        QString type = current.data().toString();
        auto nameModel = reinterpret_cast<QStandardItemModel*>(tab1_treewidget_lib->model());
        nameModel->clear();
        nameModel->setColumnCount(3);
        nameModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        nameModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
        nameModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Source"));
        for(auto i : StandardLibrary::instance()->objects())
        {
            ILibrary::ObjectInfo info = StandardLibrary::instance()->object_info(i);
            if(get_type(i) == type)
            {
                nameModel->insertRow(0);
                nameModel->setData(nameModel->index(0, 0), info.name);
                nameModel->setData(nameModel->index(0, 1), info.type);
                nameModel->setData(nameModel->index(0, 2), info.source);
                nameModel->setData(nameModel->index(0, 2), info.library, Qt::ToolTipRole);
            }
        }
        tab1_treewidget_lib->setColumnWidth(0, 200);
    }
}
