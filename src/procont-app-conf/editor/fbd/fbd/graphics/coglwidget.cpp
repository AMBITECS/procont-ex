#include "coglwidget.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QMenu>
#include <QApplication>
#include "editor/fbd/common/general/QtDialogs.h"
#include "editor/fbd/common/resources/colors.h"


COglWidget::COglWidget(s_ogl_startup * ogl_startup, QWidget *parent)
    : QOpenGLWidget(parent), m_vertical(ogl_startup->vertical), m_horizontal(ogl_startup->horizontal)
{
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    installEventFilter(this);

    connect(m_vertical, &QScrollBar::valueChanged,
            this, &COglWidget::vertical_scroll_moved);

    connect(m_horizontal, &QScrollBar::valueChanged,
            this, &COglWidget::horizontal_scroll_moved);

    connect(this, &COglWidget::customContextMenuRequested,
            this, &COglWidget::slotCustomMenuRequested);


    m_diagram_font = QFont("Helvetica", 8);
    m_diagram_font.setStyle(QApplication::font().style());

    m_message_font = QApplication::font();
    m_message_font.setStyle(QApplication::font().style());
    QFontMetrics fm(m_message_font);

    m_wrong_type_img = QImage(QSize(fm.height(), 2), QImage::Format_ARGB32);
    m_wrong_type_img.fill(QColor(119, 36, 49));

    if (!ogl_startup->node ||
         ogl_startup->node->isNull() ||
         ogl_startup->node->parentNode().isNull())
    {
        QtDialogs::alarm_user("Переданная структура QDomNode пуста, либо в ней нет родительских структур\n"
                              "Продолжение нормальной работы невозможно.");
        return;
    }


    m_paint_dev = dynamic_cast<QPaintDevice *>(this);

    m_helper = new CGraphicsHelper(this, ogl_startup->node);

    connect(m_helper, &CGraphicsHelper::object_selected,
            [this](){ emit object_selected(); });

    connect (m_helper, &CGraphicsHelper::set_current_pou,
             [this](CPou* pou){m_current_pou = pou; emit set_current_pou(pou);});
    connect(m_helper, &CGraphicsHelper::diagram_changed,
            [=](const QDomNode &node){emit diagram_changed(node);});
    connect(m_helper, &CGraphicsHelper::instance_removed,
            [=](const QString &type, const QString &name){emit instance_removed(type, name); });
    connect(m_helper, &CGraphicsHelper::drag_complete, this, &COglWidget::drag_complete);
    connect(m_helper, &CGraphicsHelper::iface_var_new, this, &COglWidget::iface_new_var);
    connect(m_helper, &CGraphicsHelper::iface_var_rename, this, &COglWidget::iface_ren_var);
    connect(m_helper, &CGraphicsHelper::undo_enabled, [this](){emit this->undo_enabled();});
    connect(this, &COglWidget::mouse_dblClicked, m_helper, &CGraphicsHelper::double_clicked);
    connect(m_helper, &CGraphicsHelper::on_project_loaded, this, &COglWidget::project_loaded);
    connect(m_helper, &CGraphicsHelper::types_wrong, this, &COglWidget::show_wrong_types);

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

    make_gradient_images();
}

COglWidget::~COglWidget()
{
    //delete m_style;
    delete m_helper;
}

void
COglWidget::initializeGL()
{
    initializeOpenGLFunctions();

    CDiagramColors colors;
    float r, g, b;
    colors.base_colors().diag_background.getRgbF(&r, &g, &b);

    glClearColor(r,
                 g,
                 b,
                 1.0f);

    glEnable(GL_ALPHA_TEST);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_ladders();
    draw_drag_bottom_upper();
    draw_type_message();
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
    m_wrong_type_rect = {};
    m_wrong_type_text = "";
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

    /// reset possible autoscroll gradients
    m_vertical_auto_rect = QRect();
    m_vert_top_autoscroll = QImage();
    m_horizon_auto_rect = {};
    m_horiz_right_autoscroll = {};
    m_wrong_type_rect = QRect();
    m_wrong_type_text = "";

    QString source = event->mimeData()->property(txt_vars::drag_source_prop).toString();

    if (source == txt_vars::drag_src_palette || source == txt_vars::drag_src_canvas)
    {
        m_helper->on_drop_event(event);
        repaint();
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

    m_wrong_type_rect = QRect();

    const QMimeData * mime = event->mimeData();
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
        }

        /// drag ladder
        if (mime->property(txt_vars::drag_obj_prop_name) == txt_vars::dragging_ladder)
        {
            event->acceptProposedAction();
        }

        if (mime->property(txt_vars::drag_obj_prop_name) == txt_vars::drag_pin)
        {
            event->acceptProposedAction();
        }


        m_helper->on_drag_enter_event(event);
    }

    if (source != txt_vars::drag_src_palette &&
        source != txt_vars::drag_src_canvas)
    {
        event->ignore();
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
    bool is_top_drag    = false;
    bool is_right_drag  = false;
    bool is_left_drag   = false;

    /// define drag source. If source is palette - autoscroll off
    auto mime = event->mimeData();


    /// enabling or disabling autoscroll
    if (mime->property(txt_vars::drag_source_prop).toString() != txt_vars::drag_src_palette)
    {
        /// bottom autoscroll
        if (event->position().toPoint().y() >= m_height-20 &&
            m_vertical->isEnabled() && (m_vertical->sliderPosition() < m_vertical->maximum())
                )
        {
            is_bottom_drag = true;
            m_vert_top_autoscroll = m_vert_bottom_templ;
            m_vertical_auto_rect = QRect(0, m_height - 40, m_width, 40);
            m_vertical->setValue(m_vertical->value() + 5);
        }

        /// upper autoscroll
        if (event->position().toPoint().y() <= 20 &&
            m_vertical->isEnabled() && (m_vertical->sliderPosition() > 0)
                )
        {
            is_top_drag = true;
            m_vert_top_autoscroll = m_vert_top_templ;
            m_vertical_auto_rect = QRect(0, 0, m_width, 40);
            m_vertical->setValue(m_vertical->value() - 5);
        }

        /// right autoscroll
        if (event->position().toPoint().x() > m_width - 20 &&
            m_horizontal->isEnabled() &&
            m_horizontal->value() < m_horizontal->maximum()
                )
        {
            is_right_drag = true;
            m_horizon_auto_rect = QRect(m_width-40, 0, 40, m_height);
            m_horiz_right_autoscroll = m_horiz_right_templ;
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
            m_horiz_right_autoscroll = m_horiz_left_templ;
            m_horizon_auto_rect = QRect(0,0, 40, m_height);
            m_horizontal->setValue(m_horizontal->value() - 2);
        }

        if (!is_bottom_drag && !is_top_drag)
        {
            m_vert_top_autoscroll = QImage();
            m_vertical_auto_rect = QRect();
        }

        if (!is_right_drag && !is_left_drag)
        {
            m_horizon_auto_rect = QRect();
            m_horiz_right_autoscroll = QImage();
        }
    }


    QString source = event->mimeData()->property(txt_vars::drag_source_prop).toString();
    // event->mimeData()->property("element").toInt() == EG_CIRCUIT

    /// if drag object is our
    if (source == txt_vars::drag_src_palette || source == txt_vars::drag_src_canvas)
    {
        m_wrong_type_rect = QRect();
        m_wrong_type_text = "";

        m_helper->on_drag_move_event(event);
    }

    QWidget::dragMoveEvent(event);
    update();
}

void COglWidget::vertical_scroll_moved(int position)
{
    if (position >= m_vertical->maximum())
    {
        return;
    }

    m_Y_scroll = position * m_vertical->pageStep();
    QPoint point(m_X_scroll, m_Y_scroll);
    emit scroll_bars_moving(point);
    repaint();
}

void COglWidget::horizontal_scroll_moved(int position)
{
    if (position >= m_horizontal->maximum())
    {
        return;
    }

    m_X_scroll = position * m_horizontal->pageStep();
    QPoint point(m_X_scroll, m_Y_scroll);
    emit scroll_bars_moving(point);
    repaint();
}

void COglWidget::draw_ladders()
{
    QPainter mPainter(m_paint_dev);
    mPainter.setFont(m_diagram_font);
    mPainter.beginNativePainting();


    for (auto &ladder : *m_ladders) // later need to change all ladders to visible_ladders buffer
    {
        /// draw ladder without objects and its text with highlights
        for (auto  &pair : *ladder->draw_ladder())
        {
            mPainter.drawImage(*pair.first, *pair.second);
        }

        /// draw visible_ladders text
        for (auto &item : *ladder->ladder_texts())
        {
            mPainter.setPen(item->color());
            mPainter.drawText(item->pos(), item->text());
        }



        /// draw visible_ladders highlights
        for (auto &hl : ladder->draw_highlights())
        {
            mPainter.drawImage(hl.first, hl.second);
        }

        /// draw objects
        for (auto &object : *ladder->draw_components())
        {
            mPainter.drawImage(*object->rect(), *object->image());
            //mPainter.drawImage(object->bound_text_rect(), object->bound_image());

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

        /// draw connecting lines
        auto def_color = mPainter.pen().color();
        for (auto &lines : *ladder->connecting_lines())
        {
            mPainter.setPen(lines->color());
            mPainter.drawLines(*lines->lines());
        }
        mPainter.setPen(def_color);
    }

    mPainter.endNativePainting();
}

void COglWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_vert_top_autoscroll = QImage();
    m_vertical_auto_rect = QRect();
    m_helper->on_drag_exit(event);
    //QWidget::dragLeaveEvent(event);
    update();
}

void
COglWidget::project_loaded()
{
    update();
    //repaint();
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
    mPainter.drawImage(m_vertical_auto_rect, m_vert_top_autoscroll);
    mPainter.drawImage(m_horizon_auto_rect, m_horiz_right_autoscroll);
    mPainter.endNativePainting();
}

void COglWidget::slotCustomMenuRequested(const QPoint &pos)
{
    auto c_menu = new QMenu(this);
    m_helper->make_menu(this, c_menu, pos);

    c_menu->popup(this->mapToGlobal(pos));
}

QUndoStack *COglWidget::undo_stack()
{
    return m_helper->undo_stack();
}

void COglWidget::mouseDoubleClickEvent(QMouseEvent *dblEvent)
{
    emit mouse_dblClicked(dblEvent);
}

void COglWidget::iface_new_var(const QString &type, const QString &name)
{
    emit iface_var_new(type, name);
}

void COglWidget::iface_ren_var(const QString &old_name, const QString &new_name)
{
    emit iface_var_ren(old_name, new_name);
}

void COglWidget::show_wrong_types(const QString &dragged, const QString &target, const QPoint &pos, const bool &is_comparable)
{
    QString delim = is_comparable ? " -> " : " <> "; //" ≠ ";
    if (dragged == target)
    {
        delim = " : ";
    }

    m_wrong_type_text = dragged + delim + target;

    if (dragged == "один")
    {
        m_wrong_type_text = "Занято!";
    }

#ifdef NDEBUG
    if (is_comparable)
    {
        m_wrong_type_text = "";
        m_wrong_type_rect = {};
        return;
    }
#endif

    QFontMetrics fm(m_message_font);
    int w = fm.size(Qt::TextSingleLine, m_wrong_type_text).width();
    int h = fm.size(Qt::TextSingleLine, m_wrong_type_text).height();
    m_wrong_type_rect = QRect({pos.x(), pos.y() - 30}, QSize(w, h));
    is_comparable ? m_wrong_type_img.fill(QColor(43,120,36)) : m_wrong_type_img.fill(QColor(119, 36, 49) );
}

void COglWidget::draw_type_message()
{
    QPainter mPainter(m_paint_dev);
    mPainter.setRenderHint(QPainter::TextAntialiasing);//Antialiasing);
    //mPainter.setRenderHint(QPainter::RenderHint::TextAntialiasing);//HighQualityAntialiasing);
    mPainter.beginNativePainting();

    mPainter.drawImage(m_wrong_type_rect, m_wrong_type_img);
    mPainter.setPen(Qt::yellow);
    mPainter.drawRect(m_wrong_type_rect);

    mPainter.setPen(QColor(Qt::white));
    mPainter.drawText(m_wrong_type_rect, Qt::AlignCenter, m_wrong_type_text);


    mPainter.endNativePainting();
}

void COglWidget::drag_complete()
{
    m_wrong_type_text = "";
    m_wrong_type_rect = {};
}

bool COglWidget::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto keyEvent = dynamic_cast<QKeyEvent*>(event);

        /// Ctrl+Z
        if (keyEvent->key() == Qt::Key_Z &&
            keyEvent->modifiers().testFlag((Qt::ControlModifier)))
        {
            if (m_helper->undo_stack()->canUndo())
            {
                m_helper->undo_stack()->undo();
            }
            return true;
        }

        /// Ctrl+shift + Z
        if (keyEvent->key() == Qt::Key_Z &&
            keyEvent->modifiers().testFlag((Qt::ControlModifier)) &&
            keyEvent->modifiers().testFlag(Qt::ShiftModifier))
        {
            if (m_helper->undo_stack()->canRedo())
            {
                m_helper->undo_stack()->redo();
            }
            return true;
        }
    }

    return QObject::eventFilter(target, event);
}

void COglWidget::wheelEvent(QWheelEvent *event)
{
    int delta_y = event->angleDelta().y() / 10;
    if (delta_y < 0)
    {
        delta_y = std::abs(delta_y);
    }
    else
    {
        delta_y = -delta_y;
    }

    if (event->modifiers() & Qt::ControlModifier)
    {
        m_horizontal->setValue(m_horizontal->value() + delta_y);
    }
    else
    {
        if (m_vertical->isEnabled())
        {
            m_vertical->setValue(m_vertical->value() + delta_y);
        }
    }

    // event->accept();
}

CPou *COglWidget::current_pou()
{
    return m_current_pou;
}

void COglWidget::make_gradient_images()
{
    CDiagramColors colors;

    QColor transparent, solid;

    transparent = colors.base_colors().diag_background;
    transparent.setAlpha(0);

    solid   = colors.base_colors().diag_background;

    QPainter painter;

    /// vertical top autoscroll
    {
        m_vert_top_templ = QImage({QSize(1, 40)}, QImage::Format_ARGB32);
        m_vert_top_templ.fill(transparent);

        painter.begin(&m_vert_top_templ);

        QLinearGradient gr(0, 0, 0, 40);
        gr.setColorAt(0, solid);
        gr.setColorAt(1, transparent);
        painter.fillRect(QRect(0,0,1,40), gr);

        painter.end();
    }

    /// vertical bottom autoscroll
    {
        m_vert_bottom_templ = QImage({QSize(3, 40)}, QImage::Format_ARGB32);
        m_vert_bottom_templ.fill(transparent);

        painter.begin(&m_vert_bottom_templ);

        QLinearGradient gr(0, 0, 0, 40);
        gr.setColorAt(0, transparent);
        gr.setColorAt(1, solid);
        painter.fillRect(QRect(0, 0, 3, 40), gr);

        painter.end();
    }

    /// horizontal right autoscroll
    {
        m_horiz_right_templ = QImage({QSize(40, 1)}, QImage::Format_ARGB32);
        m_horiz_right_templ.fill(transparent);

        painter.begin(&m_horiz_right_templ);

        QLinearGradient gr(0, 0, 40, 0);
        gr.setColorAt(0, transparent);
        gr.setColorAt(1, solid);
        painter.fillRect(QRect(0,0,40,1), gr);

        painter.end();
    }

    {
        m_horiz_left_templ = QImage(QSize(40,1), QImage::Format_ARGB32);
        m_horiz_left_templ.fill(transparent);

        painter.begin(&m_horiz_left_templ);

        QLinearGradient gr(0,0,40,0);
        gr.setColorAt(0, solid);
        gr.setColorAt(1, transparent);
        painter.fillRect(QRect(0,0,40,1), gr);

        painter.end();
    }

}

void COglWidget::delete_selected()
{
    m_helper->remove_selected_object();
}
