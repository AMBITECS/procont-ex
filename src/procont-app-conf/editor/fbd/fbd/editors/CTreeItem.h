//
// Created by nechi on 25.11.2024.
//

#ifndef EDITORSD_CTREEITEM_H
#define EDITORSD_CTREEITEM_H


#include <QVariantList>
#include "CVariablesAnalytics.h"


class TreeItem
{
public:
    explicit TreeItem(s_tree_item data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    [[nodiscard]] int childCount() const;
    [[nodiscard]] int columnCount() const;
    [[nodiscard]] QVariant data(int column) const;
    [[nodiscard]] int row() const;
    TreeItem *parentItem();
    void    set_parent(TreeItem *parent);

    s_tree_item *   item();

private:
    std::vector<TreeItem*> m_childItems;
    s_tree_item * m_itemData;
    TreeItem    * m_parentItem{nullptr};
};


#endif //EDITORSD_CTREEITEM_H
