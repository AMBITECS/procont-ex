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
    explicit CGraphicsHelper(COglWidget *ogl_widget, QDomNode * node);
    ~CGraphicsHelper() override;

    /// drag drop
    void    on_drop_event(QDropEvent *event);
    void    on_drag_enter_event(QDragEnterEvent *event);
    void    on_drag_exit(QDragLeaveEvent *event);
    void    on_drag_ladder_enter(QDragEnterEvent * event);
    void    on_drag_object_enter(QDragEnterEvent * event);
    void    on_drag_move_event(QDragMoveEvent *event);
    void    on_drag_pin(QDragMoveEvent *p_event);

    /// mouse
    void    on_mouse_released(const QPoint &pos);
    void    on_right_mouse_click(QMouseEvent *event);
    void    on_left_mouse_click(QMouseEvent *event);


    /// keyboard
    void    on_key_press_evt(QKeyEvent *event);
    void    on_key_released_event(QKeyEvent *event);


    /// others
    void    resized(const int &w, const int &h);
    std::vector<CLadder*>    * ladders();
    bool make_menu(COglWidget *p_widget, QMenu *p_menu, const QPoint &point);

    QUndoStack *    undo_stack();

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
    void    undo_enabled();
    void    mouse_dblClicked(QMouseEvent *evt);
    void    iface_var_new(const QString & type,     const QString & name);
    void    iface_var_rename(const QString & old_name, const QString & new_name);
    void    types_wrong(const QString &dragged_type, const QString &target_type,
                        const QPoint &pos, const bool &is_comparable);
    void    drag_complete();
    void    diagram_changed(const QDomNode &pou_node);
    void    instance_removed(const QString &type, const QString &name);
    void    set_current_pou(CPou *pou);



public slots:
    void    scroll_bar_moved(const QPoint & point);      //!< on scroll bar action
    void    diagram_sized(const int &w, const int &h);   //!< to scale scrollbars
    void    object_remove(CLadder *ladder, CDiagramObject *object);
    void    double_clicked(QMouseEvent *evt);
    void    drag_process_complete();



protected slots:
    void    project_complete();
    void    iface_new_var(const QString & type,     const QString & name);
    void    iface_ren_var(const QString & old_name, const QString & new_name);

protected:


private:
    std::vector<CLadder*>
                      * m_ladders;

    QDomNode          * m_pou_node;
    CPou              * m_pou;
    QPoint              m_hatch_tl{0,0};


    s_diagram_modes     m_modes;
    COglWorld         * m_graphics_world;

    CDiagramObject    * m_dragged_obj{nullptr};
    CPin              * m_dragged_pin{nullptr};
    CLadder           * m_object_source{nullptr};
    CLadder           * m_dragged_ladder{nullptr};
    COglWidget        * m_opengl_widget{nullptr};


    void make_object_menu(QMenu *p_menu, CDiagramObject *p_object, CLadder *p_ladder);
    void make_pin_menu(QMenu *p_menu, CPin * p_pin);
    void make_ladder_menu(QMenu *p_menu, CLadder *p_ladder);
    void object_cat(CLadder *p_ladder, CDiagramObject *p_object);
    void reset_dragged_objects();
};

#endif // CGRAPHICSHELPER_H
