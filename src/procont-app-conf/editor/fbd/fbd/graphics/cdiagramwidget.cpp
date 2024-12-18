//
// Created by artem on 10/10/24.
//

#include "cdiagramwidget.h"
#include "ui_diagramwgt.h"
#include <QGridLayout>
#include "../palette/CFbdComponentsTree.h"
#include "editor/fbd/resources/colors.h"

CDiagramWidget::CDiagramWidget(const QDomNode &pou_node, CTreeObject * tree_object, const bool &is_editable, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    m_dom_node = new QDomNode(pou_node);

    s_ogl_startup startup;
    startup.tree = tree_object;
    startup.vertical = ui->oglVerticalScrollBar;
    startup.horizontal = ui->horizontalScrollBar;
    startup.node = m_dom_node;
    startup.is_editable = is_editable;

    /// define diagram colors
    CDiagramColors colors; //!<3 и всё ))

    m_ogl_widget = new COglWidget(&startup);


    /*connect(tree_object, &CTreeObject::dragging_complete,
            m_ogl_widget, &COglWidget::drag_complete);*/
    connect(m_ogl_widget, &COglWidget::undo_enabled, [this](){emit this->undo_enabled();});
    connect(m_ogl_widget, &COglWidget::iface_var_new,
            [this](const QString &t, const QString &n){emit interface_variable_new(t, n);});
    connect(m_ogl_widget, &COglWidget::iface_var_ren,
            [this](const QString &o, const QString &n){emit interface_variable_rename(o, n);});

    /// place OpenGL widget
    {
        auto lo = new QGridLayout(ui->oglWidget);
        lo->addWidget(m_ogl_widget);
        lo->setContentsMargins(0, 0, 0, 0);
    }

    connect(m_ogl_widget, &COglWidget::diagram_changed, this, &CDiagramWidget::updated_diagram);

    m_tree_widget = tree_object;
    ui->diagramSplitter->setSizes({33333, 66667});
}

CDiagramWidget::~CDiagramWidget()
{
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

void CDiagramWidget::updated_diagram()
{
    emit changed_diagram(*m_dom_node);
}

void CDiagramWidget::updated_interface(const QDomNode &node)
{
    // changing interface
    emit changed_interface();
}

QUndoStack *CDiagramWidget::undo_stack()
{
    return m_ogl_widget->undo_stack();
}




