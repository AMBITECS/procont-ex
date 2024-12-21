//
// Created by artem on 10/29/24.
//

#ifndef EDITORSD_CLADDER_H
#define EDITORSD_CLADDER_H


#include <QPoint>
#include <QRect>
#include <QImage>
#include <QDragMoveEvent>
#include "CDiagramObject.h"
#include "CObjectsText.h"
#include "../palette/palette.h"
#include "CConnectLine.h"
//#include "COglWorld.h"


#define  LEFT_WIDTH 50     //!< the width of the left rect
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

struct s_rects
{
    QRect   base{};
    QRect   left{};
    QRect   right{};
    QRect   divider{};
    QRect   field{};
    QRect   bottom{};
};

struct  s_colors
{
    QColor  def_left;//{255,255,255};
    QColor  def_right;//{255,255,255};
    QColor  selected_left;//{247,226,234};
    QColor  selected_right;//{255,255,224};
    QColor  divider;//{0, 128, 128};
    QColor  gray_field;//{240,240,240};
    QColor  gray_bottom;//{240,240,240};
    QColor  landing_brick;//{185,238,185};
    QColor  landing_strip;//{239,192,136};
};

struct s_images
{
    QImage  left{};
    QImage  right{};
    QImage  divider{};
    QImage  gray{};
    QImage  landing_brick{};
    QImage  landing_vertical{};
    QImage  bottom{};
    QImage  landing_bottom{};
};

class COglWorld;

class CLadder //: public QObject
{
    //Q_OBJECT
public:
    CLadder() = delete;
    CLadder(COglWorld *world, QPoint *hatch_top_left, QSize *hatch_size,
            CLadder *prev_ladder = nullptr, CLadder *next = nullptr);
    ~CLadder();

    /// change visible_ladders content
    CDiagramObject *    add_object(CBlock * object);
    COglWorld       * parent();

    /// change and update ladder position
    void    update_real_position(CLadder *sender = nullptr);
    void    update_relative_position();

    /// context
    void    set_previous(CLadder *ladder);
    void    set_next(CLadder *ladder);
    [[nodiscard]] bool    is_visible() const;     //!< is visible via hatch in the current position

    void    highlights_off();

    void    set_selected(const bool &is_selected);
    [[nodiscard]] bool    is_selected() const;
    [[nodiscard]] bool    is_clicked_here(const QPoint &pos) const;
    void    drag_object(QDragMoveEvent * event);


    [[nodiscard]] short   bottom_line_count() const;

    CConnectLine* add_line(CConnectLine *line);
    std::vector<CConnectLine*> * connecting_lines();
    CConnectLine* remove_line(CConnectLine *line);
    CConnectLine* remove_line(CPinIn * pin_input);


    [[nodiscard]] QPoint                real_bottom_right() const;
    QPoint *                            real_top_left();


    QVector<QPair<QRect*, QImage*>>   * draw_ladder();
    QVector<QPair<QRect, QImage>>       draw_highlights();
    QVector<CDiagramObject*>          * draw_components();
    std::vector<CObjectsText*>        * ladder_texts();
    [[nodiscard]] const uint16_t      * height();
    QRect                             * base_relative_rect();
    [[nodiscard]] uint16_t              number() const;

    void    resort();

    QImage       drag_image();
    CLadder   *  previous_ladder();
    CLadder   *  next_ladder();

    void    get_selected(const QPoint &point, s_selection *p_selection);
    void    refresh_graphic_connections();

protected:


private:
    CLadder     * m_previous{nullptr};
    CLadder     * m_next{nullptr};
    COglWorld   * m_parent;

    CObjectsText    * m_num_text;
    std::vector<CConnectLine*> * m_lines;

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

    QList<CDiagramObject*>          * m_objects;
    QVector<QPair<QRect, QImage>>     m_highlights;
    QVector<QPair<QRect*, QImage*>> * m_ladder_draw;
    std::vector<CObjectsText*>      * m_texts;

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
