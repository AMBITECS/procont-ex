//
// Created by artem on 12/23/24.
//

#ifndef PROCONT_CLDDIAGRAM_H
#define PROCONT_CLDDIAGRAM_H

#include <QWidget>
#include <QUndoStack>
#include <QDomNode>
#include "editor/fbd/general/ctreeobject.h"
#include "editor/fbd/plc-xml/common/CProject.h"
#include "graphics/COpenGlDiagram.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CLdDiagram;
}
QT_END_NAMESPACE

class CLdDiagram : public QWidget
{
Q_OBJECT

public:
    explicit CLdDiagram(const QDomNode &pou_node, CTreeObject * tree_object,
                        const bool &is_editable = true, QWidget *parent = nullptr);

    ~CLdDiagram() override;

    void  set_active();
    QUndoStack *    undo_stack();

signals:
    void    changed_diagram(const QDomNode & node);
    void    undo_enabled();
    void    interface_variable_new(const QString &type, const QString &name);
    void    interface_variable_rename(const QString &old_name, const QString &new_name);
    void    instance_removed(const QString &type, const QString &name);

private:
    Ui::CLdDiagram  * ui;
    QDomNode        * m_source_node;
    CPou            * m_diagram_pou;
    EBodyType         m_diagram_language{EBodyType::BT_COUNT};

    QDomNode get_project_node(const QDomNode &node);
    void     define_diagram_pou(const QDomNode &pou_node);
};


#endif //PROCONT_CLDDIAGRAM_H
