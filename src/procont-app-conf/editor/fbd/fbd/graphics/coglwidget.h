#ifndef COGLWIDGET_H
#define COGLWIDGET_H

#include <QOpenGLWidget>
#include <QScrollBar>
#include <QOpenGLFunctions>
#include <QDomNode>
//#include <QOpenGLFunctions_4_1_Core>

#include "cgraphicshelper.h"
#include "COglStyle.h"
#include "editor/fbd/general/ctreeobject.h"


struct s_ogl_startup
{
    QDomNode    * node{nullptr};
    CTreeObject * tree{nullptr};
    QScrollBar  * vertical{nullptr};
    QScrollBar  * horizontal{nullptr};
    bool          is_editable{false};
};

class COglWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit COglWidget(s_ogl_startup * ogl_startup, QWidget *parent = nullptr);
    ~COglWidget() override;

    QUndoStack *    undo_stack();

signals:
    void  scroll_bars_moving(const QPoint & newPos);
    void  drag_moving(QDragMoveEvent *event);
    void  diagram_changed(const QDomNode & node);
    void  undo_enabled();           //!< for update undo/redo interface for enabled
    void  mouse_dblClicked(QMouseEvent *evt);
    void    iface_var_new(const QString & type,     const QString & name);
    void    iface_var_ren(const QString & old_name, const QString & new_name);

protected:
    bool    eventFilter(QObject *target, QEvent *event) override;

    /// open GL
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    /// context
    void showEvent( QShowEvent* event ) override;
    [[nodiscard]] bool is_editable() const;
    void set_editable(const bool &editable);
    void mouseDoubleClickEvent(QMouseEvent * dblEvent) override; //!< for manage variables and link lines
    void wheelEvent(QWheelEvent *event) override;

    /// mouse
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    /// keyboard
    void keyPressEvent(QKeyEvent *evt) override;
    void keyReleaseEvent(QKeyEvent *evt) override;

    /// drag & drop
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
public slots:
    void  drag_complete();  //!< когда процесс Drag&Drop закончился с любым исходом

protected slots:
    void  vertical_scroll_moved(int position);
    void  horizontal_scroll_moved(int position);
    void  project_loaded();
    void  diagram_resized(const int &w, const int &h);
    void  slotCustomMenuRequested(const QPoint &pos);
    void  iface_new_var(const QString & type,     const QString & name);
    void  iface_ren_var(const QString & old_name, const QString & new_name);
    void  show_wrong_types(const QString &dragged, const QString &target, const QPoint &pos, const bool &is_comparable);
protected:


private:
    std::vector<CLadder*>   * m_ladders;
    CGraphicsHelper         * m_helper;
    QScrollBar              * m_vertical;
    QScrollBar              * m_horizontal;

    QPaintDevice            * m_paint_dev;
    COglStyle               * m_style;

    int                   m_X_scroll{0};
    int                   m_Y_scroll{0};
    int                   m_height{0};
    int                   m_width{0};
    bool                  m_is_editable{true};

    /// drag autoscroll
    QImage                m_vertical_autoscroll;
    QRect                 m_vertical_auto_rect;
    QImage                m_horizon_autoscroll;
    QRect                 m_horizon_auto_rect;

    /// wrong types - message about not comparable variables types, when try to graphic connect them
    QImage  m_wrong_type_img;
    QRect   m_wrong_type_rect;
    QString m_wrong_type_text;
    QFont   m_message_font;
    QFont   m_diagram_font;

    void draw_ladders();
    void draw_drag_bottom_upper();
    //void make_wrong_message(const QString &dragged, const QString &target, const QPoint &pos, const bool &is_comparable);

    void draw_type_message();
};


#endif // COGLWIDGET_H

