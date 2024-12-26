//
// Created by artem on 12/23/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CLdDiagram.h" resolved

#include "clddiagram.h"
#include "ui_clddiagram.h"

extern CProject *project;

CLdDiagram::CLdDiagram(const QDomNode &pou_node, CTreeObject * tree_object,
                       const bool &is_editable, QWidget *parent) :
        QWidget(parent), ui(new Ui::CLdDiagram)
{
    ui->setupUi(this);
    m_source_node = new QDomNode(pou_node);
    m_diagram_pou = nullptr;


    /// произведём анализ - возможно это POU уже есть в CProject, если нет - добавим
    define_diagram_pou(pou_node);

    /// create content of the diagram
    switch (m_diagram_language)
    {
        case BT_FBD:
            break;
        case BT_LD:
            break;
        default:
            // create empty and out
            break;
    }

    /// setup location
    this->setContentsMargins(0,0,0,0);
}

CLdDiagram::~CLdDiagram()
{
    delete ui;
}

void CLdDiagram::set_active()
{

}

QUndoStack *CLdDiagram::undo_stack()
{
    return nullptr;
}

QDomNode CLdDiagram::get_project_node(const QDomNode &node)
{
    if (node.isNull())
    {
        return {};
    }

    QDomNode parent = node.parentNode();
    QDomNode prj_node;

    while (!parent.isNull())
    {
        prj_node = parent;
        parent = parent.parentNode();
    }

    /// test prj_node
    if (prj_node.nodeName() != "project")
    {
        return {};
    }
    return prj_node;
}

void CLdDiagram::define_diagram_pou(const QDomNode &pou_node)
{

    if (project == nullptr)
    {
        QDomNode project_node = get_project_node(pou_node);
        CProject::get_instance(project_node); // no need to assign instance - it's global

        if (project->is_empty())
        {
            m_diagram_pou = new CPou(pou_node, project->types());
            project->types()->add_pou(m_diagram_pou);
        }
    }
    else
    {
        CPou local_pou(pou_node, project->types());
        QString pou_name = local_pou.name();
        m_diagram_pou = project->types()->find_pou_by_name(pou_name);

        if (!m_diagram_pou)
        {
            m_diagram_pou = new CPou(pou_node, project->types());
            project->types()->add_pou(m_diagram_pou);
        }
    }

    m_diagram_language = m_diagram_pou->body_type();
}
