#include "ProxyModel.h"

#include "DomModel.h"

#include "item/DomItem.h"

#include <QDebug>

ProxyModelTree_pou::ProxyModelTree_pou(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool ProxyModelTree_pou::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    DomItem *item = static_cast<DomItem*>(index.internalPointer());
    // Q_ASSERT(item);
    if(!item) return false;
    QDomNode node = item->node();

    return
        node.nodeName() != "xml" &&
        node.nodeName() != "fileHeader" &&
        node.nodeName() != "contentHeader" &&
        hasParent(node, "instances") == false &&
        node.nodeName() != "dataTypes" &&
        hasParent(node, "pou") == false
        ;

    return true;
}

bool ProxyModelTree_pou::hasParent(const QDomNode &node, const QString &name) const
{
    QDomNode parent = node.parentNode();

    if(node.isNull())
        return false;

    if(parent.nodeName() == name)
        return true;

    return hasParent(parent, name);
}


int ProxyModelTree_pou::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

ProxyModelTree_dev::ProxyModelTree_dev(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool ProxyModelTree_dev::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    DomItem *item = static_cast<DomItem*>(index.internalPointer());
    // Q_ASSERT(item);
    if(!item) return false;
    QDomNode node = item->node();

    return
        node.nodeName() != "xml" &&
        node.nodeName() != "fileHeader" &&
        node.nodeName() != "contentHeader" &&
        hasParent(node, "types") == false &&
        hasParent(node, "globalVars") == false
        ;

    return true;
}

bool ProxyModelTree_dev::hasParent(const QDomNode &node, const QString &name) const
{
    QDomNode parent = node.parentNode();

    if(node.isNull())
        return false;

    if(parent.nodeName() == name)
        return true;

    return hasParent(parent, name);
}


int ProxyModelTree_dev::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

ProxyModelTable_var::ProxyModelTable_var(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

Qt::ItemFlags ProxyModelTable_var::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flg = QAbstractItemModel::flags(index);

    if(index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6 || index.column() == 7)
        return Qt::ItemIsEditable | flg;

    return flg;
}

QVariant ProxyModelTable_var::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case 1:
            return tr("Number");
        case 2:
            return tr("Type");
        case 3:
            return tr("Name");
        case 4:
            return tr("Address");
        case 5:
            return tr("Data type");
        case 6:
            return tr("Initial Value");
        case 7:
            return tr("Documentation");
        case 8:
            return tr("Attributes");
       default:
            break;
        }
    }

    return sourceModel()->headerData(section, orientation, role);
}

QVariant ProxyModelTable_var::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant{};

    QModelIndex source_index = mapToSource(index);
    DomItem *item = static_cast<DomItem*>(source_index.internalPointer());

    Q_ASSERT(item);

    switch(index.column())
    {
    case 1:
        return QString::number(index.row()+1);
    case 2:
        return item->node().nodeName();
    case 3:
        return item->data(role);
    case 4:
        return item->data(role);
    case 5:
        return item->data(role);
    case 6:
        return item->data(role);
    case 7:
        return item->data(role);
    case 8:
        return QVariant{};
    default:
        break;
    }

    return QVariant{};
}

bool ProxyModelTable_var::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    QModelIndex source_index = mapToSource(index);
    DomItem *item = static_cast<DomItem*>(source_index.internalPointer());

    Q_ASSERT(item);

    // qDebug() << __PRETTY_FUNCTION__ << item->data(Qt::DisplayRole) << item->parentItem()->data(Qt::DisplayRole);

    item->setData(value, role);

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return true;
}
