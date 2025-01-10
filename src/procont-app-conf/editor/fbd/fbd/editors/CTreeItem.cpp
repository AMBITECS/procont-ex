//
// Created by nechi on 25.11.2024.
//

#include "CTreeItem.h"

#include <utility>

TreeItem::TreeItem(const s_tree_item &data, TreeItem *parentItem)
    : m_parentItem(parentItem)
{
    m_itemData = new s_tree_item(data);
}

TreeItem::~TreeItem()
{
    delete m_itemData;
}

void TreeItem::appendChild(TreeItem *child)
{
    child->set_parent(this);
    m_childItems.push_back(child);
}

TreeItem *TreeItem::child(int row)
{
    return row >= 0 && row < childCount() ? m_childItems.at(row) : nullptr;
}

int TreeItem::childCount() const
{
    return int(m_childItems.size());
}

int TreeItem::columnCount() const
{
    return 2;
}

QVariant TreeItem::data(int column) const
{
    return column == 0 ? m_itemData->name.c_str() : m_itemData->type.c_str();
}

int TreeItem::row() const
{
    if (m_parentItem == nullptr)
        return 0;

    const auto it = std::find_if(m_parentItem->m_childItems.cbegin(),
                                                  m_parentItem->m_childItems.cend(),
                                 [this](const TreeItem *treeItem) {
                                     return treeItem == this;
                                 });

    if (it != m_parentItem->m_childItems.cend())
        return static_cast<int>(std::distance(m_parentItem->m_childItems.cbegin(), it));

    Q_ASSERT(false); // should not happen
    return -1;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

s_tree_item *TreeItem::item()
{
    return m_itemData;
}

void TreeItem::set_parent(TreeItem *parent)
{
    m_parentItem = parent;
}


