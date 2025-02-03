#ifndef CDIAGRAMOGL_H
#define CDIAGRAMOGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QScrollBar>
#include "CBacking.h"


struct glColor
{
    float r{0};
    float g{0};
    float b{0};
    float a{1.0f};
};

class CDiagramOgl : public QOpenGLWidget , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit CDiagramOgl(QWidget *parent = nullptr);
    ~CDiagramOgl() override;
    void  set_scroll_bars(QScrollBar *horizontal, QScrollBar *vertical);

signals:

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mouseDoubleClickEvent( QMouseEvent * e ) override;
    void mousePressEvent(QMouseEvent *e) override;

    /// scrolling & zooming: wheel - Y scroll; <ctrl>+wheel = X scroll; <alt>+wheel=zooming
    void    wheelEvent(QWheelEvent *event) override;

    /// drag & drop
    void    dragEnterEvent(QDragEnterEvent *event) override;
    void    dropEvent(QDropEvent *event) override;
    void    dragMoveEvent(QDragMoveEvent *event) override;

protected slots:
    void    hatch_moved_x(const int &x);
    void    hatch_moved_y(const int &y);
    void    set_scale(const float & factor);
    void    show_context_menu(const QPoint &pos);

private:
    QPaintDevice    * m_paint_dev;
    CBacking        * m_backing{nullptr};

    QScrollBar      * m_horizon{nullptr};
    QScrollBar      * m_vertical{nullptr};

    QPointF           m_hatch_tl;
    QSizeF            m_hatch_size;
    float             m_scale_factor{1.0};

};

#endif // CDIAGRAMOGL_H
