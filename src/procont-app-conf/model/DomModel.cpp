#include "DomModel.h"

#include "item/DomItem.h"

#include <QtXml>

DomModel::DomModel(const QDomDocument &document, QObject *parent)
    : QAbstractItemModel(parent),
    domDocument(document),
    rootItem(new DomItem(domDocument))
{
}

DomModel::~DomModel()
{
    delete rootItem;
}

QVariant DomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
        return QVariant{};

    const DomItem *item = static_cast<DomItem*>(index.internalPointer());

    Q_ASSERT(item);

    return item->data(role);
}

bool DomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DomItem *item = static_cast<DomItem*>(index.internalPointer());

    Q_ASSERT(item);

    item->setData(value, role);

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return true;
}

QVariant DomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Value");
        default:
            break;
        }
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex DomModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    auto parentItem = item(parent);
    auto childItem = parentItem->insertChild(row, column, parentItem->node());

    return (childItem) ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex DomModel::parent(const QModelIndex &child) const
{ 
    if (!child.isValid())
        return QModelIndex();

    auto childItem = static_cast<DomItem*>(child.internalPointer());
    Q_ASSERT(childItem);
    auto parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

DomItem * DomModel::item(const QModelIndex &index) const
{
    if(index.isValid())
    {
        auto item = static_cast<DomItem*>(index.internalPointer());
        return item;
    }

    return rootItem;
}

int DomModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(item(parent));

    return item(parent)->rowCount();
}

int DomModel::columnCount(const QModelIndex &parent) const
{
    Q_ASSERT(item(parent));

    return item(parent)->columnCount();
}

bool DomModel::hasChildren(const QModelIndex &index) const
{
    Q_ASSERT(item(index));

    return item(index)->node().childNodes().count();
}

bool DomModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DomItem *parentItem = item(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    parentItem->insertRows(position, rows);
    endInsertRows();

    return true;
}

bool DomModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DomItem *parentItem = item(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    parentItem->removeRows(position, rows);
    endRemoveRows();

    return true;
}

#include <QAbstractProxyModel>

QModelIndex DomModel::s_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    if(proxy == nullptr)
        return reinterpret_cast<const QAbstractProxyModel*>(index.model())->mapToSource(index);

    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapToSource(index);
}

QModelIndex DomModel::p_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapFromSource(index);
}

QAbstractProxyModel * DomModel::toProxy(QAbstractItemModel *model)
{
    return reinterpret_cast<QAbstractProxyModel*>(model);
}

DomItem * DomModel::toItem(const QModelIndex &index, bool source, QAbstractItemModel * proxy)
{
    auto _index = source ? index : s_index(index, proxy);

    return reinterpret_cast<DomItem *>(_index.internalPointer());
}

DomModel * DomModel::toModel(QAbstractItemModel *model_)
{
    return reinterpret_cast<DomModel *>(model_);
}
