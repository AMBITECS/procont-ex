//
// Created by artem on 12.10.24.
//

#include "CFbdComponentsTree.h"
#include "../palette/palette.h"

CFbdComponentsTree::CFbdComponentsTree(QTreeWidget *widget)
{
    m_widget = widget;
}

CFbdComponentsTree::~CFbdComponentsTree()
= default;

void CFbdComponentsTree::build_tree()
{
    clear_tree();

    QStringList elements_groups;
    elements_groups << "Общее"
                    << "Логические операторы"
                    << "Мат. операторы"
                    << "Другие операторы"
                    << "Функциональные блоки";

    QVector<QVector<s_comp_item>> groups;
    groups  << general_data
            << logic_data
            << math_data
            << other_data
            << func_blocks_data;

    QVector<QTreeWidgetItem*>  top_level;
    for (const auto &group_name : elements_groups)
    {
        auto item = new QTreeWidgetItem(EP_FBD);
        item->setText(0, group_name);
        m_widget->addTopLevelItem(item);
        top_level.push_back(item);
    }


    int counter = 0;
    for (auto &top_item : top_level)
    {
        auto group = groups.at(counter);
        for (auto &s_item : group)
        {
            auto tree_item = new QTreeWidgetItem(top_item, 0);
            tree_item->setText(0, s_item.name);
            tree_item->setIcon(0, QIcon(element_images[s_item.element]));
            tree_item->setToolTip(0, s_item.hint);
            tree_item->setData(0, Qt::UserRole, s_item.element);
            top_item->addChild(tree_item);
        }
        counter++;
    }



    m_widget->expandAll();
}

void
CFbdComponentsTree::clear_tree()
{
    QTreeWidgetItem *item;
    item = m_widget->topLevelItem(0);
    while(item)
    {
        removeItem(item);
        item = m_widget->topLevelItem(0);
    }
}

void
CFbdComponentsTree::removeItem(QTreeWidgetItem *item)
{
    int count = item->childCount();
    if (count == 0)
    {
        delete item;
        return;
    }

    for(int i=0; i<count; i++)
    {
        QTreeWidgetItem * childitem = item-> child (0); // Delete subtraction
        removeItem(childitem);
    }
    delete item;
}
