//
// Created by artem on 29.10.24.
//

#ifndef EDITORSD_COGLWORLD_H
#define EDITORSD_COGLWORLD_H

#include <QPoint>
#include <QDragMoveEvent>
#include <QUndoStack>
#include "QObject"
#include "CFbdObject.h"
#include "CFbdLadder.h"
#include "../../plc-xml/common/CPou.h"
#include "../palette/palette.h"
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"


class CPin;
class CFbdConnectLine;
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
    CFbdLadder * ladder{nullptr};
    CFbdObject  * object{nullptr};
    CPin   * pin{nullptr};
    CFbdConnectLine    * connection_line{nullptr};
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
    std::vector<CFbdLadder*>  * visible_ladders();        //!< returns VISIBLE visible_ladders to show them in QOpenGL
    std::vector<CFbdLadder*>  * all_ladders();

    QUndoStack *    undo_stack();

    /// here are commands which has to be undo/redo. Note we have to know indexes of objects objects and indexes
    /// of inserted one
    CFbdLadder *         add_new_ladder();                 //!< index of the inserting is result->number()-1
    CFbdLadder *         insert_new_ladder(CFbdLadder *next); //!< index of the inserting is result->number()-1
    CFbdObject  * insert_new_component(CFbdLadder *p_ladder, const EPaletteElements &elements, const QString &pou_name,
                                           const QPoint &pos);
    void              insert_ladder(CFbdLadder *dragged_ladder, CFbdLadder *before);
    bool              move_object(CFbdLadder * source, CFbdLadder *destination, CFbdObject *object, const QPoint &pos);
    void              erase_object(CFbdObject *object);
    void              connect_pins(CPin *dragged_pin, CPin *target_pin);
    void              text_based_connecting_pin(CPin *selected_pin);

    void              check_diagram_size();
    bool              check_pins_to_connection(CPin *target_pin, s_compare_types &comparable_types);
    CPou            * current_pou();
signals:
    void    update_hatch();
    void    canvas_changed(const int &w, const int &h);     //!< signal for enable/disable/scale QScrollBars.
    void    undo_enabled();
    void    iface_var_new(const QString & typeName, const QString & varName);
    void    iface_var_rename(const QString & old, const QString &last);
    void    drag_complete();
    void    diagram_changed(const QDomNode &node);
    void    instance_removed(const QString &type, const QString &name);
    void    set_current_pou(CPou *pou);


public slots:
    void    win_resized(const int & w, const int & h);
    void    view_hatch_moved(const QPoint & new_position); //!< the view hatch is panned or the scroll bar has moved
    void    shutdown_highlights();
    void    mouse_move(QMouseEvent * event);
    void    mouse_left_pressed(const QPoint &pos);
    void    mouse_dblClicked(QMouseEvent *evt);
    void    pin_variable_rename();
    void    iface_new_var(const QString & type,     const QString & name);
    void    iface_rename( const QString & old_name, const QString & new_name);
    void    load_later();
    void    update_visible_ladders();
    void    convert_to_XML();

protected:
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
    QSize         m_diagram_size{0,0};
    QPoint        m_mouse_pressed{};

    s_selection   m_selection;

    EBodyType     m_diagram_type;
    CFbdContent * m_fbd_content{nullptr};
    CPou        * m_pou;

    std::vector<CFbdLadder*>     * m_ladders;
    std::vector<CFbdLadder*>     * m_visible_ladders;

    CEditors    * m_editors;

    CPin        * m_drag_pin{nullptr};

    void    clear_ladders();
    QPoint  get_visible_range(const QPoint & pos);
    void    load_project();
    CFbdLadder * get_ladder(const unsigned long & id_ladder);
    static void    check_local_id(const uint16_t &local_id);  //!< if loaded items local_id > global variable increase global
    void    init_projects_instances();


};


#endif //EDITORSD_COGLWORLD_H
