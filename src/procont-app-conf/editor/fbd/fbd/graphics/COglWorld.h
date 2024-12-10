//
// Created by artem on 29.10.24.
//

#ifndef EDITORSD_COGLWORLD_H
#define EDITORSD_COGLWORLD_H

#include <QPoint>
#include <QDragMoveEvent>
#include <QUndoStack>
#include "QObject"
#include "CDiagramObject.h"
#include "CLadder.h"
#include "../../plc-xml/common/CPou.h"
#include "../palette/palette.h"
#include "editor/fbd/fbd/editors/CVariablesAnalytics.h"


class CPin;
class CConnectLine;
class COglWidget;
class CEditors;

// undo/redo pres
class CAddNewLadder;
class CInsertNewLadder;
class CInsertNewObject;
class CMoveObject;
class CInsertLadder;

/**
 * @brief any left mouse click will fill this struct
 */
struct s_selection
{
    CLadder * ladder{nullptr};
    CDiagramObject  * object{nullptr};
    CPin   * pin{nullptr};
    CConnectLine    * connection_line{nullptr};
    void reset()
    {
        ladder = nullptr;
        object = nullptr;
        pin    = nullptr;
        connection_line = nullptr;
    }
    [[nodiscard]] bool empty() const
    {
        return !ladder && !object && !pin && !connection_line;
    }
};

/**
 * @brief this class represents all objects on the diagram world, QOpenGLWidget on the contrary is a small view hatch
 * through which we see the diagram world. For this class only all objects are accessible. That's why here
 * is going basic job
 */
class COglWorld : public QObject
{
    Q_OBJECT


public:
    COglWorld() = delete;
    explicit COglWorld(COglWidget * openGLwidget, CPou * pou, QPoint * hatch_pos);
    ~COglWorld() override;


    s_selection     get_selection(const QPoint &pos);  //!< searches selected objects
    s_selection *   selected();                        //!<  returns active selection (in function above)
    std::vector<CLadder*>  * ladders(); //!< returns VISIBLE ladders to show them in QOpenGL

    QUndoStack *    undo_stack();

    /// here are commands which has to be undo/redo. Note we have to know indexes of objects objects and indexes
    /// of inserted one
    CLadder *         add_new_ladder();                 /// index of the inserting is result->number()-1
    CLadder *         insert_new_ladder(CLadder *next); /// index of the inserting is result->number()-1
    CDiagramObject  * insert_new_component(CLadder *p_ladder, const EPaletteElements &elements, const QPoint &pos);
    void              insert_ladder(CLadder *dragged_ladder, CLadder *before);
    bool              move_object(CLadder * source, CLadder *destination, CDiagramObject *object, const QPoint &pos);
    void              check_diagram_size();
    bool              check_pins_to_connection(CPin *target_pin, s_compare_types &comparable_types);
    void              connect_pins(CPin *dragged_pin, CPin *target_pin);

signals:
    void    update_hatch();
    void    canvas_changed(const int &w, const int &h);     //!< signal for enable/disable/scale QScrollBars.
    void    undo_enabled();
    void    iface_var_new(const QString & typeName, const QString & varName);
    void    iface_var_rename(const QString & old, const QString &last);
    void    drag_complete();


public slots:
    void    win_resized(const int & w, const int & h);
    void    view_hatch_moved(const QPoint & new_position); //!< the view hatch is panned or the scroll bar has moved
    void    shutdown_highlights();
    void    mouse_move(QMouseEvent * event);
    void    mouse_left_pressed(const QPoint &pos);
    void    mouse_dblClicked(QMouseEvent *evt);
    void    pin_variable_rename();

//    void    ladder_size_changed();

protected slots:
    void    iface_new_var(const QString & type,     const QString & name);
    void    iface_rename( const QString & old_name, const QString & new_name);
    void    load_later();
    void    update_visible_ladders();

    friend  CAddNewLadder;
    friend  CInsertNewLadder;
    friend  CInsertNewObject;
    friend  CMoveObject;
    friend  CInsertLadder;
    friend  CVariablesAnalytics;

private:
    QUndoStack  * m_undo_stack;

    uint16_t      m_hatch_width{0};   //!< ширина смотрового люка
    uint16_t      m_hatch_height{0};  //!< высота смотрового люка
    QSize         m_hatch_size;
    QPoint      * m_hatch_topLeft{nullptr}; //!< top-left смотрового люка
    CPou        * m_pou;
    s_selection   m_selection;

    EBodyType     m_diagram_type;
    CFbdContent * m_fbd_content{nullptr};

    std::vector<CLadder*>     * m_ladders;
    std::vector<CLadder*>     * m_visible_ladders;
    QPoint       m_mouse_pressed{};

    CEditors    * m_editors;

    QSize        m_diagram_size{0,0};
    CPin   * m_drag_pin{nullptr};

    void    clear_ladders();
    QPoint  get_visible_range(const QPoint & pos);
    void    load_project();
    CLadder * get_ladder(const unsigned long & id_ladder);
    void    check_local_id(const uint16_t &local_id);  //!< if loaded items local_id > global variable increase global
    void    init_projects_instances();


};


#endif //EDITORSD_COGLWORLD_H
