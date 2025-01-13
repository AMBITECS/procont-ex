#include "ProxyModel.h"

#include "DomModel.h"
#include "item/DomItem.h"
#include "undo/cundocommand_edit.h"

#include <QDebug>

ProxyModelTree_pou::ProxyModelTree_pou(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void ProxyModelTree_pou::setUndoStack(QUndoStack *undo_stack_)
{
    _m_undo_stack = undo_stack_;
}

bool ProxyModelTree_pou::setData(const QModelIndex &index, const QVariant &value_new_, int role)
{
    if (role != Qt::EditRole)
        return false;

    auto _value_old = index.data().toString(); _value_old = _value_old.remove(_value_old.indexOf('('), _value_old.length());

    if(_value_old == value_new_)
        return false;

    undoStack()->push(new CUndoCommand_edit_tree(this, index, _value_old, value_new_));

    return true;
}

bool ProxyModelTree_pou::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    DomItem *item = static_cast<DomItem*>(index.internalPointer());

    if(!item) return false;

    QDomNode node = item->node();

    return
        node.nodeName() != "xml" &&
        node.nodeName() != "fileHeader" &&
        node.nodeName() != "contentHeader" &&
        hasParent(node, "instances") == false &&
        hasParent(node, "dataType") == false &&
        // node.nodeName() != "dataTypes" &&
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

void ProxyModelTree_dev::setUndoStack(QUndoStack *undo_stack_)
{
    _m_undo_stack = undo_stack_;
}

bool ProxyModelTree_dev::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    if(index.data() == value)
        return false;

    undoStack()->push(new CUndoCommand_edit(this, index, index.data(), value));

    return true;
}

bool ProxyModelTree_dev::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    DomItem *item = static_cast<DomItem*>(index.internalPointer());

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

void ProxyModelTable_var::setUndoStack(QUndoStack *undo_stack_)
{
    _m_undo_stack = undo_stack_;
}

Qt::ItemFlags ProxyModelTable_var::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    auto _item = DomModel::toItem(index);

    Q_ASSERT(_item);

    Qt::ItemFlags flg = QAbstractItemModel::flags(index);

    if(_item->is_read_only())
        return flg;

    if(index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6 || index.column() == 7)
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

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString("   ");

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
        return item->data(role);
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

    if(index.data() == value)
        return false;

    auto _index = this->index(index.row(), 0, index.parent());
    auto _item = DomModel::toItem(_index);

    Q_ASSERT(_item);
    Q_ASSERT(undoStack());

    QDomNode _old = _item->node().cloneNode();

    undoStack()->push(new CUndoCommand_edit_table(this, index, index.data(), value, _item->node().toElement().attribute("name")));

    emit signal_variable_changed(_old, _item->node());

    return true;
}

ProxyModelTable_global::ProxyModelTable_global(QObject *parent)
    : ProxyModelTable_var(parent)
{
}

Qt::ItemFlags ProxyModelTable_global::flags(const QModelIndex &index) const
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
