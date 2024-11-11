#include "coglwidget.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QMenu>


#include "../variables.h"


COglWidget::COglWidget(s_ogl_startup * ogl_startup, QWidget *parent)
    : QOpenGLWidget(parent), m_vertical(ogl_startup->vertical), m_horizontal(ogl_startup->horizontal)
{
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    connect(m_vertical, &QScrollBar::valueChanged,
            this, &COglWidget::vertical_scroll_moved);
    connect(m_horizontal, &QScrollBar::valueChanged,
            this, &COglWidget::horizontal_scroll_moved);
    connect(this, &COglWidget::customContextMenuRequested,
            this, &COglWidget::slotCustomMenuRequested);


    m_paint_dev = dynamic_cast<QPaintDevice *>(this);
    m_style = new COglStyle();
    m_helper = new CGraphicsHelper(ogl_startup->node);

    m_is_editable = ogl_startup->is_editable;

    connect(this, &COglWidget::drag_moving,
            m_helper, &CGraphicsHelper::on_drag_move_event);
    connect(this, &COglWidget::scroll_bars_moving,
            m_helper, &CGraphicsHelper::scroll_bar_moved);
    connect(m_helper, &CGraphicsHelper::diagram_resized,
            this, &COglWidget::diagram_resized);

    m_ladders = m_helper->ladders();
    connect(m_helper, &CGraphicsHelper::on_project_loaded, this, &COglWidget::project_loaded);




    this->setAcceptDrops(m_is_editable);
}

COglWidget::~COglWidget()
{
    delete m_style;
    delete m_helper;
}

void
COglWidget::initializeGL()
{
    initializeOpenGLFunctions();


    s_color color = m_style->background();

    glClearColor(color.red, color.green, color.blue, color.alpha);
    glEnable(GL_ALPHA_TEST);

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

void COglWidget::resizeGL(int w, int h)
{
    //QOpenGLWidget::resizeGL(w, h);
    glViewport(0, 0, w, h);                 // установка площади обзора
    glMatrixMode(GL_PROJECTION);                // установка режима матрицы
    glLoadIdentity();                               // загрузка матрицы
    m_helper->resized(w, h);
    m_height = h;
    m_width  = w;
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
    draw_drag_bottom_upper();

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
        //m_start_move = event->pos();
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
    if (!m_is_editable)
    {
        event->ignore();
        return;
    }

    m_vertical_auto_rect = QRect();
    m_vertical_autoscroll = QImage();

    QString source = event->mimeData()->property(txt_vars::drag_source_prop).toString();

    if (source == txt_vars::drag_src_palette || source == txt_vars::drag_src_canvas)
    {
        m_helper->on_drop_event(event);
        update();
    }
    QWidget::dropEvent(event);
}

void COglWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (!m_is_editable)
    {
        event->ignore();
        return;
    }

    auto mime = event->mimeData();
    QString source = mime->property(txt_vars::drag_source_prop).toString();

    if (source == txt_vars::drag_src_palette)
    {
        event->acceptProposedAction();
        m_helper->on_drag_enter_event(event);
    }
    if (source == txt_vars::drag_src_canvas)
    {
        /// drag component
        if (mime->property(txt_vars::drag_obj_prop_name) == txt_vars::dragging_object)
        {
            event->acceptProposedAction();
            m_helper->on_drag_object_enter(event);
        }

        /// drag ladder
        if (mime->property(txt_vars::drag_obj_prop_name) == txt_vars::dragging_ladder)
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
    if (!m_is_editable)
    {
        event->ignore();
        return;
    }

    bool is_bottom_drag = false;
    bool is_top_drag = false;
    bool is_right_drag = false;
    bool is_left_drag = false;

    /// bottom autoscroll
    if (event->position().toPoint().y() >= m_height-20 &&
        m_vertical->isEnabled() && (m_vertical->sliderPosition() < m_vertical->maximum())
    )
    {
        is_bottom_drag = true;
        m_vertical_autoscroll = QImage(":/codesys/images/codesys/bottom_auto.png");
        m_vertical_auto_rect = QRect(0, m_height - 20, m_width, 20);
        m_vertical->setValue(m_vertical->value() + 5);
    }

    /// upper autoscroll
    if (event->position().toPoint().y() <= 20 &&
        m_vertical->isEnabled() && (m_vertical->sliderPosition() > 0)
    )
    {
        is_top_drag = true;
        m_vertical_autoscroll = QImage(":/codesys/images/codesys/upper_auto.png");
        m_vertical_auto_rect = QRect(0, 0, m_width, 20);
        m_vertical->setValue(m_vertical->value() - 5);
    }

    /// right autoscroll
    if (event->position().toPoint().x() > m_width - 20 &&
        m_horizontal->isEnabled() &&
        m_horizontal->value() < m_horizontal->maximum()
    )
    {
        is_right_drag = true;
        m_horizon_auto_rect = QRect(m_width-20, 0, 20, m_height);
        m_horizon_autoscroll = QImage(":/codesys/images/codesys/auto_right.png");
        //m_horizon_autoscroll.
        m_horizontal->setValue(m_horizontal->value() + 2);

    }
    /// left autoscroll
    if (event->position().toPoint().x() < 20 &&
            m_horizontal->isEnabled() &&
            m_horizontal->value() > 0
    )
    {
        is_left_drag = true;
        m_horizon_autoscroll = QImage(":/codesys/images/codesys/auto_left.png");
        m_horizon_auto_rect = QRect(0,0, 20, m_height);
        m_horizontal->setValue(m_horizontal->value() - 2);
    }

    if (!is_bottom_drag && !is_top_drag)
    {
        m_vertical_autoscroll = QImage();
        m_vertical_auto_rect = QRect();
    }

    if (!is_right_drag && !is_left_drag)
    {
        m_horizon_auto_rect = QRect();
        m_horizon_autoscroll = QImage();
    }

    QString source = event->mimeData()->property(txt_vars::drag_source_prop).toString();
    // event->mimeData()->property("element").toInt() == EG_CIRCUIT

    /// if drag object is our
    if (source == txt_vars::drag_src_palette || source == txt_vars::drag_src_canvas)
    {
        m_helper->on_drag_move_event(event);
        //emit drag_moving(event);
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
    m_vertical_autoscroll = QImage();
    m_vertical_auto_rect = QRect();
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

bool COglWidget::is_editable() const
{
    return m_is_editable;
}

void COglWidget::set_editable(const bool &editable)
{
    m_is_editable = editable;
}

void COglWidget::draw_drag_bottom_upper()
{
    QPainter mPainter(m_paint_dev);
    mPainter.beginNativePainting();
    mPainter.drawImage(m_vertical_auto_rect, m_vertical_autoscroll);
    mPainter.drawImage(m_horizon_auto_rect, m_horizon_autoscroll);
    mPainter.endNativePainting();
}

void COglWidget::slotCustomMenuRequested(const QPoint &pos)
{
    auto c_menu = new QMenu(this);

    m_helper->make_menu(this, c_menu, pos);

    c_menu->popup(this->mapToGlobal(pos));
}
