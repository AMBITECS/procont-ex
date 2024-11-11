#ifndef CGRAPHICSHELPER_H
#define CGRAPHICSHELPER_H

#include <QVector>
#include "CLadder.h"
#include "../palette/palette.h"
#include "../../plc-xml/fbd/CFbdContent.h"
#include "../../plc-xml/common/CPou.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QImage>
#include <QWidget>
#include <QDomNode>
#include "COglWorld.h"



struct s_diagram_modes
{
    bool    is_panning{false};
    bool    is_multiselect{false};
    bool    is_read_only{false};
};

class COglWidget;

class CGraphicsHelper : public QWidget
{
    Q_OBJECT



public:
    explicit CGraphicsHelper(QDomNode * node);
    ~CGraphicsHelper() override;

    /// drag drop
    void    on_drop_event(QDropEvent *event);
    void    on_drag_enter_event(QDragEnterEvent *event);
    void    on_drag_move_event(QDragMoveEvent *event);
    void    on_drag_exit(QDragLeaveEvent *event);
    void    on_drag_ladder_enter(QDragEnterEvent * event);
    void    on_drag_object_enter(QDragEnterEvent * event);

    /// mouse
    void    on_mouse_released(const QPoint &pos);
    void    on_move_object(QDragMoveEvent *event);
    void    on_move_ladder(QDragMoveEvent *event);
    void    on_right_mouse_click(QMouseEvent *event);
    void    on_left_mouse_click(QMouseEvent *event);

    /// keyboard
    void    on_key_press_evt(QKeyEvent *event);
    void    on_key_released_event(QKeyEvent *event);

    /// others
    void    resized(const int &w, const int &h);
    std::vector<CLadder*>    * ladders();
    bool make_menu(COglWidget *p_widget, QMenu *p_menu, const QPoint &point);


    /// signals and slots
signals:
    void    canvas_resized(const int &w, const int &h);
    void    mouse_clicked(const QPoint &pos);
    void    mouse_left_pressed(const QPoint &pos);
    void    mouse_drag_over(QDragMoveEvent *event);
    void    mouse_moving(QMouseEvent *event);
    void    hatch_moving(const QPoint & point);      //!< in pan mode
    void    scroll_bars_moving(const QPoint & pos);
    void    on_drag_new_node(const QPoint &pos);
    void    on_project_loaded();
    void    shutdown_highlights();
    void    diagram_resized(const int &w, const int &h);


public slots:
    void    scroll_bar_moved(const QPoint & point);      //!< on scroll bar action
    void    diagram_sized(const int &w, const int &h);   //!< to scale scrollbars
    void    object_remove(CLadder *ladder, CDiagramObject *object);
protected slots:
    void    project_complete();

protected:

private:
    std::vector<CLadder*>
                      * m_ladders;

    QDomNode          * m_pou_node;
    CPou              * m_pou;
    QPoint              m_hatch_tl{0,0};
    int m_w{0}, m_h{0};

    s_diagram_modes     m_modes;
    COglWorld         * m_graphics_world;

    CDiagramObject    * m_dragged_obj{nullptr};
    CDiagramObject    * m_clip_object{nullptr};
    CLadder           * m_object_source{nullptr};
    CLadder           * m_dragged_ladder{nullptr};

    void make_object_menu(QMenu *p_menu, CDiagramObject *p_object, CLadder *p_ladder);
    void make_pin_menu(QMenu *p_menu, CConnectorPin * p_pin);
    void make_ladder_menu(QMenu *p_menu, CLadder *p_ladder);
    void object_cat(CLadder *p_ladder, CDiagramObject *p_object);
};

#endif // CGRAPHICSHELPER_H
