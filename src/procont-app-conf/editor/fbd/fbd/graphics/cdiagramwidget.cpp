//
// Created by artem on 10/10/24.
//

#include "cdiagramwidget.h"
#include "ui_diagramwgt.h"
#include <QGridLayout>
#include "../../common/CComponentsTree.h"
#include <QTimer>
// igor'
#include "main/MainWindow.h"
#include <QUndoGroup>
#include <QFile>
#include "../../plc-xml/common/CInstances.h"

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

    /// user clicked on the diagram, i'm in focus
    connect(m_ogl_widget, &COglWidget::user_clicked, [this](){
        undo_stack()->setActive();
        emit user_clicked(); 
    });

    /// diagram_object_is_selected
    connect(m_ogl_widget, &COglWidget::object_selected,
            this, &CDiagramWidget::diagram_object_is_selected);

    connect(m_ogl_widget, &COglWidget::set_current_pou,
            [this](CPou *pou){m_current_pou = pou; build_tree();});

    /// interface variable instance has been removed
    connect(m_ogl_widget, &COglWidget::instance_removed,
            [this](const QString &type, const QString &name)
            {emit instance_removed(type, name); });

    /// diagram has been changed, take QDomNode
    connect(m_ogl_widget, &COglWidget::diagram_changed,
            this, &CDiagramWidget::diagram_has_changed);

    /// For now you can use undo/redo hmm... is it necessary?
    connect(m_ogl_widget, &COglWidget::undo_enabled, [this]()
            {emit this->undo_enabled();});

    /// The new variable instance has to be added to the interface
    connect(m_ogl_widget, &COglWidget::iface_var_new,
            [this](const QString &t, const QString &n)
            {emit interface_variable_new(t, n);});

    /// This variable instance renamed in the diagram
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

    // igor'
    MainWindow::instance()->undoGroup()->addStack(undo_stack());
}

CDiagramWidget::~CDiagramWidget()
{
    delete m_ogl_widget;
    delete m_dom_node;

    CComponentsTree tree_filler(m_tree_widget);
    tree_filler.clear_tree();

    delete ui;
}

void CDiagramWidget::build_tree()
{
    m_current_pou = m_ogl_widget->current_pou();
    if (m_current_pou)
    {
        CComponentsTree tree_filler(m_tree_widget);
        tree_filler.build_tree(m_current_pou);
    }
}

void CDiagramWidget::set_active()
{
    build_tree();
}

void CDiagramWidget::update_interface(const QDomNode &node)
{
    if (!m_current_pou)
    {
        qDebug() << "m_current_pou is nullptr";
        return;
    }

    //save_to_file(node);

    auto *pou = new CPou(node, m_current_pou->parent());
    auto iface = pou->interface();

    if (!iface->is_empty())
    {
        m_current_pou->set_interface(iface);
    }

    delete pou;
}

QUndoStack *CDiagramWidget::undo_stack()
{
    return m_ogl_widget->undo_stack();
}

void CDiagramWidget::diagram_object_is_selected()
{
    // igor'
    undo_stack()->setActive();
    emit object_selected();
}

void CDiagramWidget::delete_selected_object()
{
    m_ogl_widget->delete_selected();
}

void CDiagramWidget::diagram_has_changed(const QDomNode &node)
{
    if (node.isNull())
    {
        return;
    }
    // igor'
    undo_stack()->setActive();

    //save_to_file(node);

    emit changed_diagram(node);
}

void CDiagramWidget::save_to_file( const QDomNode &node )
{
    QFile outFile( "fbd_diag.xml" );
    if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );
        return;
    }

    QDomDocument document;
    QDomElement root = document.createElement("wrapper");
    root.appendChild(node);
    document.appendChild(root);

    QTextStream stream( &outFile );
    stream << document.toString();

    outFile.close();
}




