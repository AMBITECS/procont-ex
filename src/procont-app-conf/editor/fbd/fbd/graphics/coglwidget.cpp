#include "coglwidget.h"
#include "../palette/palette.h"

#include <QMouseEvent>
#include <QMimeData>
#include <GL/glu.h>
#include <QPainter>


COglWidget::COglWidget(s_ogl_startup * ogl_startup, QWidget *parent)
    : QOpenGLWidget(parent), m_vertical(ogl_startup->vertical), m_horizontal(ogl_startup->horizontal)
{
    connect(m_vertical, &QScrollBar::valueChanged, this, &COglWidget::vertical_scroll_moved);
    connect(m_horizontal, &QScrollBar::valueChanged, this, &COglWidget::horizontal_scroll_moved);

    m_paint_dev = dynamic_cast<QPaintDevice *>(this);
    m_style = new COglStyle();
    m_helper = new CGraphicsHelper(ogl_startup->node, ogl_startup->st_widget);

    connect(this, &COglWidget::scroll_bars_moving,
            m_helper, &CGraphicsHelper::scroll_bar_moved);
    connect(m_helper, &CGraphicsHelper::diagram_resized,
            this, &COglWidget::diagram_resized);

    m_ladders = m_helper->ladders();
    connect(m_helper, &CGraphicsHelper::on_project_loaded, this, &COglWidget::project_loaded);

    this->setAcceptDrops(true);
}

COglWidget::~COglWidget()
{
    delete m_style;
    delete m_helper;
}

void
COglWidget::initializeGL()
{
    //QOpenGLWidget::initializeGL();
    if (!m_funcGL)
    {
        m_funcGL = QOpenGLContext::currentContext()->functions();
    }

    s_color color = m_style->background();

    m_funcGL->glClearColor(color.red, color.green, color.blue, color.alpha);
    m_funcGL->glEnable(GL_ALPHA_TEST);

    // тест глубины
    m_funcGL->glEnable(GL_DEPTH_TEST);

    // glColor будет устанавливать свойства материала
    m_funcGL->glEnable(GL_COLOR_MATERIAL);

    // разрешаем освещение
    m_funcGL->glEnable(GL_LIGHTING);

    // включаем нулевую лампу
    m_funcGL->glEnable(GL_LIGHT0);

    // разрешаем смешение цветов и "прозрачность"
    m_funcGL->glEnable(GL_BLEND);
    m_funcGL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void COglWidget::resizeGL(int w, int h)
{
    //QOpenGLWidget::resizeGL(w, h);
    glViewport(0, 0, w, h);                 // установка площади обзора
    //glViewport(m_X_scroll, m_Y_scroll, w, h);
    glMatrixMode(GL_PROJECTION);            // установка режима матрицы
    glLoadIdentity();                       // загрузка матрицы
    //gluLookAt(x,y+height,z,x-sin(angleX/180*PI),y+height+(tan(angleY/180*PI)),z-cos(angleX/180*PI), 0, 1, 0);
    m_helper->resized(w, h);
    height = h;
    QOpenGLWidget::resizeGL(w, h);
    update();
    //repaint();
}

void
COglWidget::paintGL()
{
    //QOpenGLWidget::paintGL();
    // base drawing cycle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_ladders();
}

void
COglWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}

void
COglWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        m_helper->on_right_mouse_click(event);
    }

    if (event->button() == Qt::LeftButton)
    {
        m_start_move = event->pos();
        m_helper->on_left_mouse_click(event);
    }

    update();
    QWidget::mousePressEvent(event);
}

void
COglWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_helper->mouse_moving(event);

    QWidget::mouseMoveEvent(event);
    this->update();
}

void
COglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_helper->on_mouse_released(event->pos());
    QWidget::mouseReleaseEvent(event);
}

void
COglWidget::keyPressEvent(QKeyEvent *evt)
{
    m_helper->on_key_press_evt(evt);
    QWidget::keyPressEvent(evt);
}

void
COglWidget::keyReleaseEvent(QKeyEvent *evt)
{
    m_helper->on_key_released_event(evt);
    QWidget::keyReleaseEvent(evt);
}

void
COglWidget::dropEvent(QDropEvent *event)
{
    m_helper->on_drop_event(event);
    update();
    QWidget::dropEvent(event);
}

void COglWidget::dragEnterEvent(QDragEnterEvent *event)
{
    auto mime = event->mimeData();
    if (mime->property("palette").toInt() == 1)
    {
        event->acceptProposedAction();
        m_helper->on_drag_enter_event(event);
    }
    if (mime->property("source").toString() == "canvas")
    {
        /// drag component
        if (mime->property("object") == "object")
        {
            event->acceptProposedAction();
            m_helper->on_drag_object_enter(event);
        }

        /// drag ladder
        if (mime->property("object") == "ladder")
        {
            event->acceptProposedAction();
            m_helper->on_drag_ladder_enter(event);
        }
    }
    QWidget::dragEnterEvent(event);
    this->update();
}

void
COglWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->property("element").toInt() == EG_CIRCUIT)
    {
        //m_helper->on_drag_new_node(event->position().toPoint());
        m_helper->on_drag_move_event(event);
    }
    else
    {
        m_helper->on_drag_move_event(event);
    }
    QWidget::dragMoveEvent(event);
    update();
}

void COglWidget::vertical_scroll_moved(int position)
{
    m_Y_scroll = position * m_vertical->pageStep();
    QPoint point(m_X_scroll, m_Y_scroll);
    emit scroll_bars_moving(point);
    repaint();
}

void COglWidget::horizontal_scroll_moved(int position)
{
    m_X_scroll = position * m_horizontal->pageStep();
    QPoint point(m_X_scroll, m_Y_scroll);
    emit scroll_bars_moving(point);
    repaint();
}

void COglWidget::draw_ladders()
{
    QPainter mPainter(m_paint_dev);
    mPainter.beginNativePainting();
    mPainter.setFont(QFont("Helvetica", 8));

    for (auto &ladder : *m_ladders) // later need to change all ladders to ladders buffer
    {
        /// draw ladder without objects and its text with highlights
        for (auto  &pair : *ladder->draw_ladder())
        {
            mPainter.drawImage(*pair.first, *pair.second);
        }

        /// draw ladders text
        for (auto &item : *ladder->ladder_texts())
        {
            mPainter.setPen(item->color());
            mPainter.drawText(item->pos(), item->text());
        }



        /// draw ladders highlights
        for (auto &hl : ladder->draw_highlights())
        {
            mPainter.drawImage(hl.first, hl.second);
        }

        /// draw objects
        for (auto &object : *ladder->draw_components())
        {
            mPainter.drawImage(*object->rect(), *object->image());
            //mPainter.drawImage(object->bound_rect(), object->bound_image());

            /// draw text
            for (auto &text : *object->texts())
            {
                mPainter.setPen(text->color());
                mPainter.drawText(text->pos().x(), text->pos().y(), text->text());
            }

            /// draw pins
            for (auto &pin : *object->pins())
            {
                mPainter.drawImage(*pin->rect(), *pin->image());

                for (auto &txt : *pin->texts())
                {
                    mPainter.setPen(txt->color());
                    mPainter.drawText(txt->pos(), txt->text());
                }
            }

            /// draw objects highlights
            for (const auto& hl : *object->highlights())
            {
                mPainter.drawImage(hl.first, hl.second);
            }
        }
    }
    mPainter.endNativePainting();   
}

void COglWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_helper->on_drag_exit(event);
    //QWidget::dragLeaveEvent(event);
    update();
}

void
COglWidget::project_loaded()
{
    //m_helper->resized(this->width(), this->height);
    update();
}

void COglWidget::diagram_resized(const int &w, const int &h)
{
    m_vertical->setEnabled(h > this->size().height());
    m_horizontal->setEnabled(w > this->size().width());

    if (!m_vertical->isEnabled() && !m_horizontal->isEnabled())
    {
        return;
    }

    if (m_vertical->isEnabled())
    {
        m_vertical->setMaximum((h / m_vertical->pageStep()) - m_vertical->pageStep());
    }

    if (m_horizontal->isEnabled())
    {
        m_horizontal->setMaximum(w / m_horizontal->pageStep() - m_horizontal->pageStep());
    }
}
