//
// Created by artem on 29.10.24.
//

#ifndef EDITORSD_COGLWORLD_H
#define EDITORSD_COGLWORLD_H

#include <QPoint>
#include <QDragMoveEvent>
#include "QObject"
#include "CDiagramObject.h"
#include "CLadder.h"
#include "../../plc-xml/common/CPou.h"
#include "../palette/palette.h"


class CConnectorPin;
class CConnectLine;

/**
 * @brief any left mouse click will fill this struct
 */
struct s_selection
{
    CLadder * ladder{nullptr};
    CDiagramObject  * object{nullptr};
    CConnectorPin   * pin{nullptr};
    CConnectLine    * connection_line{nullptr};
    void reset()
    {
        ladder = nullptr;
        object = nullptr;
        pin    = nullptr;
        connection_line = nullptr;
    }
    bool empty() const
    {
        return !ladder && !object && !pin && !connection_line;
    }
};

/**
 * @brief this class represents all objects on the diagram world, QOpenGLWidget on the contrary is a small view hatch
 * through which we see the diagram world
 */
class COglWorld : public QObject
{
    Q_OBJECT

public:
    COglWorld() = delete;
    explicit COglWorld(CPou * pou, QPoint * hatch_pos);
    ~COglWorld() override;


    s_selection     get_selection(const QPoint &pos);

    std::vector<CLadder*>  * ladders();

    CLadder *   add_new_ladder();
    CLadder *   insert_new_ladder(CLadder *next);

    void        reset_all_highlights();
    s_selection *       get_selection();
    void        check_diagram_size();
    void insert_new_component(CLadder *p_ladder, const EPaletteElements &elements, const QPoint &pos);

signals:
    void    update_hatch();
    void    canvas_changed(const int &w, const int &h);

public slots:
    void    win_resized(const int & w, const int & h);
    void    view_hatch_moved(const QPoint & new_position); //!< the view hatch is panned or the scroll bar has moved
    void    mouse_clicked(const QPoint &pos);
    void    mouse_drag_over(QDragMoveEvent *event);
    void    shutdown_highlights();
    void    mouse_move(QMouseEvent * event);
    void    mouse_left_pressed(const QPoint &pos);
    void    insert_ladder(CLadder *dragged_ladder, CLadder *before);
    void    ladder_size_changed();

private slots:
    void    initial_shot();
    void    update_visible_ladders();

private:
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

    QSize        m_diagram_size{0,0};
    CConnectorPin   * m_drag_pin{nullptr};

    void    clear_ladders();
    QPoint  get_visible_range(const QPoint & pos);
    void load_project();
    void find_in_variable(CConnectorPin *&p_pin);
    CLadder * get_ladder(const unsigned long & id_ladder);

    bool find_out_var(CConnectorPin *p_pin, const uint64_t &block_id);

};


#endif //EDITORSD_COGLWORLD_H
