
#ifndef EDITORSD_CFBDCOMPONENTSTREE_H
#define EDITORSD_CFBDCOMPONENTSTREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "../palette/palette.h"
#include "editor/fbd/plc-xml/common/CPou.h"

class CFbdComponentsTree
{
public:
    explicit CFbdComponentsTree(QTreeWidget *widget);
    ~CFbdComponentsTree();

    void build_tree(CPou *current_pou);
    void clear_tree();


protected:

private:
    QTreeWidget *m_widget;

    void removeItem(QTreeWidgetItem *item);
    QVector<s_comp_item> m_project_pou;

    void update_program_pous(CPou *current);

    void get_palette_roots(CPou *p_pou, QStringList &list, QVector<QVector<s_comp_item>> &list_1);
};


#endif //EDITORSD_CFBDCOMPONENTSTREE_H
