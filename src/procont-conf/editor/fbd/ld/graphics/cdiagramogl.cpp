#include "cdiagramogl.h"
#include "../../common/resources/colors.h"

CDiagramOgl::CDiagramOgl(QWidget *parent) : QOpenGLWidget(parent)
{

}

CDiagramOgl::~CDiagramOgl()
{

}

void CDiagramOgl::initializeGL()
{
    initializeOpenGLFunctions();

    CDiagramColors colors;
    auto bkg_col = colors.base_colors().diag_background;

    glColor bkg_color;
    bkg_color = {(float)bkg_col.red()/255.0f,
                 (float)bkg_col.green()/255.0f,
                 (float)bkg_col.blue()/255};

    glClearColor(bkg_color.r, bkg_color.g, bkg_color.b, 1.0f);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_LINE_SMOOTH);

    // тест глубины
    glEnable(GL_DEPTH_TEST);

    // glColor будет устанавливать свойства материала
    glEnable(GL_COLOR_MATERIAL);

    // разрешаем освещение
    glEnable(GL_LIGHTING);

    // включаем нулевую лампу
    glEnable(GL_LIGHT0);

    // разрешаем смешение цветов и "прозрачность"
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CDiagramOgl::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w, h);
}

void CDiagramOgl::paintGL()
{
    QOpenGLWidget::paintGL();
}

void CDiagramOgl::mouseDoubleClickEvent(QMouseEvent *e)
{
    QWidget::mouseDoubleClickEvent(e);
}

void CDiagramOgl::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void CDiagramOgl::wheelEvent(QWheelEvent *event)
{
    QWidget::wheelEvent(event);
}

void CDiagramOgl::dragEnterEvent(QDragEnterEvent *event)
{
    QWidget::dragEnterEvent(event);
}

void CDiagramOgl::dropEvent(QDropEvent *event)
{
    QWidget::dropEvent(event);
}

void CDiagramOgl::dragMoveEvent(QDragMoveEvent *event)
{
    QWidget::dragMoveEvent(event);
}

void CDiagramOgl::hatch_moved_x(const int &x)
{

}

void CDiagramOgl::hatch_moved_y(const int &y)
{

}

void CDiagramOgl::set_scale(const float &factor)
{

}

void CDiagramOgl::show_context_menu(const QPoint &pos)
{

}

void CDiagramOgl::set_scroll_bars(QScrollBar *horizontal, QScrollBar *vertical)
{
    m_vertical = vertical;
    m_horizon = horizontal;
}
