#include "qvarselectmodel.h"
#include <QApplication>
#include <QPalette>
#include <QStyle>

QVarSelectModel::QVarSelectModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_root = new TreeItem({});

    m_def_color = QApplication::palette().text().color();
    m_type_color = QColor(197,37,107);

    auto font = QApplication::font();

    m_type_font = font;
    m_type_font.setItalic(true);
    m_type_font.setPointSize(8);

    m_name_font = font;
}

QVarSelectModel::~QVarSelectModel()
{
    delete m_root;
}

QVariant QVarSelectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return {};
    if(section == 0)
    {
        return "Наименование";
    }
    return "Тип";
}

QModelIndex QVarSelectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    TreeItem *parentItem = parent.isValid()
                           ? static_cast<TreeItem*>(parent.internalPointer())
                           : m_root;


    if (auto *childItem = parentItem->child(row))
        return createIndex(row, column, childItem);
    return {};
}

QModelIndex QVarSelectModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    auto *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    return parentItem != m_root
           ? createIndex(parentItem->row(), 0, parentItem) : QModelIndex{};
}

int QVarSelectModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    const TreeItem *parentItem = parent.isValid()
                                 ? static_cast<const TreeItem*>(parent.internalPointer())
                                 : m_root;

    return parentItem->childCount();
}

int QVarSelectModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant QVarSelectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    if (role != Qt::DisplayRole && role != Qt::DecorationRole && role != Qt::ForegroundRole && role != Qt::FontRole)
    {
        return {};
    }

    if (role == Qt::DecorationRole)
    {
        return {};
    }

    if (role == Qt::ForegroundRole)
    {
        return index.column() > 0 ? m_type_color : m_def_color;
    }

    if(role == Qt::FontRole)
    {
        return index.column() == 0 ? m_name_font : m_type_font;
    }

    auto *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

bool QVarSelectModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
    /*beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;*/
}

bool QVarSelectModel::removeRows(int row, int count, const QModelIndex &parent)
{
    /*beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();*/
    return false;
}

QVarSelectModel::QVarSelectModel(const QVarSelectModel &other) : QAbstractItemModel()
{
    for (auto &item : other.m_rows)
    {
        auto n_item = new TreeItem(*item->item());
        m_rows.push_back(n_item);
    }
}

QVarSelectModel &QVarSelectModel::operator=(const QVarSelectModel &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    for (auto &item : m_rows)
        delete item;
    m_rows.clear();

    for (auto &item : rhs.m_rows)
    {
        auto n_item = new TreeItem(*item->item());
        m_rows.push_back(n_item);
    }

    return *this;
}

void QVarSelectModel::set_data(std::vector<s_tree_item> *variables)
{
    beginResetModel();

    delete m_root;
    m_root = new TreeItem({});

    for (auto &item : m_rows)
    {
        delete item;
    }

    m_rows.clear();

    if (variables)
    {
        std::string name, type;
        bool is_complex;

        for (auto &item: *variables)
        {
            if (item.id_parent == 0)
            {
                auto data = new TreeItem(item);
                m_root->appendChild(data);
                m_rows.push_back(data);
            }
            else
            {
                auto data = new TreeItem(item);
                setup_data(data);
            }
        }
    }
    endResetModel();
}



void QVarSelectModel::setup_data(TreeItem *item)
{
    for (auto &unit : m_rows)
    {
        if (unit->item()->id == item->item()->id_parent)
        {
            unit->appendChild(item);
            return;
        }
    }
}

Qt::ItemFlags QVarSelectModel::flags(const QModelIndex &index) const
{
    auto item = static_cast<TreeItem*>(index.internalPointer());
    if (item->childCount() > 0)
    {
        return  Qt::ItemIsEnabled;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
