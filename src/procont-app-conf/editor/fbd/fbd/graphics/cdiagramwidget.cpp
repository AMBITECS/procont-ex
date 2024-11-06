//
// Created by artem on 10/10/24.
//

#include "cdiagramwidget.h"
#include "ui_diagramwgt.h"
#include <QGridLayout>
#include "../palette/CFbdComponentsTree.h"
#include "../../general/QtDialogs.h"


CDiagramWidget::CDiagramWidget(const QDomNode &pou_node, CTreeObject * tree_object, const bool &is_editable, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    m_dom_node = new QDomNode(pou_node);
    m_st_widget = new CodeEditorWidget();

    s_ogl_startup startup;
    startup.tree = tree_object;
    startup.vertical = ui->oglVerticalScrollBar;
    startup.horizontal = ui->horizontalScrollBar;
    startup.node = m_dom_node;
    startup.is_editable = is_editable;
    startup.st_widget = m_st_widget;

    m_ogl_widget = new COglWidget(&startup);

    /// place ST-widget
    // {
    //     auto lo = new QGridLayout(ui->stWidget);
    //     lo->addWidget(m_st_widget);
    //     lo->setContentsMargins(0, 0, 0, 0);
    // }

    /// place OpenGL widget
    {
        auto lo = new QGridLayout(ui->oglWidget);
        lo->addWidget(m_ogl_widget);
        lo->setContentsMargins(0, 0, 0, 0);
    }

    m_tree_widget = tree_object;
    ui->diagramSplitter->setSizes({33333, 66667});

    build_tree();
}

CDiagramWidget::~CDiagramWidget()
{
    delete m_st_widget;
    delete m_ogl_widget;
    delete m_dom_node;

    CFbdComponentsTree tree_filler(m_tree_widget);
    tree_filler.clear_tree();

    delete ui;
}

void CDiagramWidget::build_tree()
{
    CFbdComponentsTree tree_filler(m_tree_widget);
    tree_filler.build_tree();
}

void CDiagramWidget::set_active()
{
    if (m_tree_widget->topLevelItemCount() == 0)
    {
        build_tree();
    }
}

void CDiagramWidget::diagram_updated()
{

}


