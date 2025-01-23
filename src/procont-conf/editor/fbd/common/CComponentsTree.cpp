//
// Created by artem on 12.10.24.
//

#include "CComponentsTree.h"
#include "editor/fbd/plc-xml/common/CProject.h"

extern CProject *project;

CComponentsTree::CComponentsTree(QTreeWidget *widget)
{
    m_widget = widget;
}

CComponentsTree::~CComponentsTree()
= default;

void CComponentsTree::build_tree(CPou *current_pou)
{
    clear_tree();

    update_program_pous(current_pou);

    QStringList elements_groups;
    QVector<QVector<s_comp_item>> groups;

    get_palette_roots(current_pou, elements_groups, groups);


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
            auto tree_item = new QTreeWidgetItem();
            tree_item->setText(0, s_item.name);
            tree_item->setIcon(0, QIcon(element_images[s_item.element]));
            tree_item->setToolTip(0, s_item.hint);
            tree_item->setData(0, Qt::UserRole, s_item.element);
            top_item->addChild(tree_item);
        }
        counter++;
    }



    m_widget->expandAll();
    m_widget->setItemsExpandable(true);
}

void
CComponentsTree::clear_tree()
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
CComponentsTree::removeItem(QTreeWidgetItem *item)
{
    if (!item)
    {
        return;
    }

    int count = item->childCount();
    if (count == 0)
    {
        delete item;
        return;
    }

    for(int i=0; i<count; i++)
    {
        QTreeWidgetItem * child_item = item->child(i);
        removeItem(child_item);
    }

    delete item;
}

void CComponentsTree::update_program_pous(CPou *current)
{
    m_project_pou . clear();

    for (auto &pou : *project->types()->pous())
    {
        if (pou == current || pou->type_name() == "program")
        {
            continue;
        }

        s_comp_item item;
        item.name = pou->name();
        item.hint = item.name + " " + pou->type_name();

        EPaletteElements element;

        if (pou->type() == BT_FBD)
            element = EPaletteElements::EP_FBD;
        if (pou->type() == BT_LD)
            element = EPaletteElements::EP_LD;
        /*if (pou->body_type() == BT_IL)
            element = EPaletteElements::EP_IL;*/
        if (pou->type() == BT_ST)
            element = EPaletteElements::EP_ST;
        if (pou->type() == BT_SFC)
            element = EPaletteElements::EP_SFC;

        item.element = element;

        m_project_pou.push_back(item);
    }
}

void CComponentsTree::get_palette_roots(CPou *p_pou, QStringList &list, QVector<QVector<s_comp_item>> &list_1)
{
    if (p_pou->type() == BT_FBD)
    {
        list << "Общее"
                        << "Логические операторы"
                        << "Мат. операторы"
                        << "Другие операторы"
                        << "Функциональные блоки";
        if (!m_project_pou.empty())
            list << "Проектные POU";

        list_1 << general_data
               << bitwise_operators
               << math_data
               << other_data
               << func_blocks_data
               << m_project_pou;
    }

    if (p_pou->type() == BT_LD)
    {
        list << "Логические операторы"
             << "Мат. операторы"
             << "Функциональные блоки"
             << "Проектные POU";

        list_1 << bitwise_operators
               << math_data
               << func_blocks_data
               << m_project_pou;
    }
}
