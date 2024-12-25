//
// Created by artem on 10/29/24.
//

#ifndef EDITORSD_CLADDER_H
#define EDITORSD_CLADDER_H


#include <QPoint>
#include <QRect>
#include <QImage>
#include <QDragMoveEvent>
#include "CFbdObject.h"
#include "editor/fbd/common/CObjectText.h"
#include "../palette/palette.h"
#include "CFbdConnectLine.h"
#include "editor/fbd/common/CLadder.h"


#define  LEFT_WIDTH 50      //!< the width of the left rect
#define  DIVIDER_WIDTH 3    //!< divider strip width
#define  GRAY_WIDTH  20     //!< gray field width
#define  DEF_HEIGHT 50      //!< empty ladder width
#define  HEIGHT_RESERVE 15  //!< addition to the calculated height for connections
#define  BOT_LANDING_HEIGHT 3
#define  OBJECTS_DISTANCE   40
#define  OBJECTS_TOP_SHIFT  30

#define def_bound_dist 5
#define def_lines_diff 5

class s_selection;



class COglWorld;

class CFbdLadder //: public QObject
{
    //Q_OBJECT
public:
    CFbdLadder() = delete;
    CFbdLadder(COglWorld *world, QPoint *hatch_top_left, QSize *hatch_size,
            CFbdLadder *prev_ladder = nullptr, CFbdLadder *next = nullptr);
    ~CFbdLadder();

    /// change visible_ladders content
    CFbdObject  * add_object(CBlock * object);
    COglWorld       * parent();

    /// change and update ladder position
    void    update_real_position(CFbdLadder *sender = nullptr);
    void    update_relative_position();

    /// context
    void    set_previous(CFbdLadder *ladder);
    void    set_next(CFbdLadder *ladder);
    [[nodiscard]] bool    is_visible() const;     //!< is visible via hatch in the current position

    void    highlights_off();

    void    set_selected(const bool &is_selected);
    [[nodiscard]] bool    is_selected() const;
    [[nodiscard]] bool    is_clicked_here(const QPoint &pos) const;
    void    drag_object(QDragMoveEvent * event);


    [[nodiscard]] short   bottom_line_count() const;

    CFbdConnectLine* add_line(CFbdConnectLine *line);
    std::vector<CFbdConnectLine*> * connecting_lines();
    CFbdConnectLine* remove_line(CFbdConnectLine *line);
    CFbdConnectLine* remove_line(CPinIn * pin_input);


    [[nodiscard]] QPoint                real_bottom_right() const;
    QPoint *                            real_top_left();


    QVector<QPair<QRect*, QImage*>>   * draw_ladder();
    QVector<QPair<QRect, QImage>>       draw_highlights();
    QVector<CFbdObject*>          * draw_components();
    std::vector<CObjectText*>        * ladder_texts();
    [[nodiscard]] const uint16_t      * height();
    QRect                             * base_relative_rect();
    [[nodiscard]] uint16_t              number() const;

    void    resort();

    QImage       drag_image();
    CFbdLadder   *  previous_ladder();
    CFbdLadder   *  next_ladder();

    void    get_selected(const QPoint &point, s_selection *p_selection);
    void    refresh_graphic_connections();

protected:


private:
    CFbdLadder     * m_previous{nullptr};
    CFbdLadder     * m_next{nullptr};
    COglWorld   * m_parent;

    CObjectText    * m_num_text;
    std::vector<CFbdConnectLine*> * m_lines;

    QPoint      * m_hatch_pos{nullptr};
    QSize       * m_hatch_size;

    bool          m_next_changed{false};
    bool          m_prev_changed{false};

    uint16_t      m_number{0};
    uint16_t      m_current_height{DEF_HEIGHT};
    uint16_t      m_current_width{};
    bool          m_is_selected{false};

    QPoint        m_relative_tl{0,0};
    short         m_bottom_lines{0};

    QList<CFbdObject*>          * m_objects;
    QVector<QPair<QRect, QImage>>     m_highlights;
    QVector<QPair<QRect*, QImage*>> * m_ladder_draw;
    std::vector<CObjectText*>      * m_texts;

    uint16_t    m_ladder_width{0};

    s_rects       m_abs_rects{};
    s_rects       m_relative{};
    s_colors      m_colors;
    s_images      m_images;

    QRect         m_ladder_landing{};
    QRect         m_base_rel;
    QImage        m_drag_image;

    [[nodiscard]] uint16_t    define_height() const;

    void fill_ladder_image();
    void show_landing_highlight();
    void show_brick();
};


#endif //EDITORSD_CLADDER_H
