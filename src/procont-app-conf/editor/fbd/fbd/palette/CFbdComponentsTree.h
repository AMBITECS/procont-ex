
#ifndef EDITORSD_CFBDCOMPONENTSTREE_H
#define EDITORSD_CFBDCOMPONENTSTREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>


class CFbdComponentsTree
{
public:
    explicit CFbdComponentsTree(QTreeWidget *widget);
    ~CFbdComponentsTree();

    void build_tree();
    void clear_tree();


protected:

private:
    QTreeWidget *m_widget;

    void removeItem(QTreeWidgetItem *item);
};


#endif //EDITORSD_CFBDCOMPONENTSTREE_H
