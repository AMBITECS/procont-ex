//
// Created by artem on 10/10/24.
//

#include "cdiagramwidget.h"
#include "ui_diagramwgt.h"
#include <QGridLayout>
#include "../palette/CFbdComponentsTree.h"
#include <QTimer>


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


    m_ogl_widget = new COglWidget(&startup);

    connect(m_ogl_widget, &COglWidget::object_selected,
            this, &CDiagramWidget::diagram_object_is_selected);

    connect(m_ogl_widget, &COglWidget::set_current_pou,
            [this](CPou *pou){m_current_pou = pou; build_tree();});

    connect(m_ogl_widget, &COglWidget::instance_removed,
            [this](const QString &type, const QString &name){emit instance_removed(type, name); });
    connect(m_ogl_widget, &COglWidget::diagram_changed,
            this, &CDiagramWidget::diagram_has_changed);
    connect(m_ogl_widget, &COglWidget::undo_enabled, [this]()
            {emit this->undo_enabled();});
    connect(m_ogl_widget, &COglWidget::iface_var_new,
            [this](const QString &t, const QString &n)
            {emit interface_variable_new(t, n);});
    connect(m_ogl_widget, &COglWidget::iface_var_ren,
            [this](const QString &o, const QString &n)
            {emit interface_variable_rename(o, n);});

    /// place OpenGL widget
    {
        auto lo = new QGridLayout(ui->oglWidget);
        lo->addWidget(m_ogl_widget);
        lo->setContentsMargins(0, 0, 0, 0);
    }

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
    m_current_pou = m_ogl_widget->current_pou();
    if (m_current_pou)
    {
        CFbdComponentsTree tree_filler(m_tree_widget);
        tree_filler.build_tree(m_current_pou);
    }
}

void CDiagramWidget::set_active()
{
    build_tree();
}

void CDiagramWidget::update_interface(const QDomNode &node)
{
    // changing interface
    // emit change_interface();
}

QUndoStack *CDiagramWidget::undo_stack()
{
    return m_ogl_widget->undo_stack();
}

void CDiagramWidget::diagram_object_is_selected()
{
    emit object_selected();
}

void CDiagramWidget::delete_selected_object()
{
    m_ogl_widget->delete_selected();
}

void CDiagramWidget::diagram_has_changed(const QDomNode &node)
{
    emit changed_diagram(node);
}




