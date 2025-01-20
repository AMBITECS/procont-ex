//
// Created by artem on 12/24/24.
//

#ifndef PROCONT_CLADDER_H
#define PROCONT_CLADDER_H

#include <QRect>
#include <QColor>
#include <QImage>
#include "CDiagramObject.h"



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

class CBacking;


/** @brief протокласс ступеней на диаграммах */
class CLadder
{
public:
    CLadder(CBacking *backing);
    virtual ~CLadder();

    /// edit ladder
    CDiagramObject *    remove_object(CDiagramObject *object);
    CDiagramObject *    insert_object(CDiagramObject *object, const uint16_t &position);

    /// moving ladder on the canvas
    void    update_position();
    void    set_environment(CLadder *prev, CLadder *next);

    ///
    bool    is_cursor_here(const QPointF &position) const;
    bool    is_selected() const;
    bool    is_visible() const;
    void    set_selected();

    /// drawing
    QRectF& draw_rect();
    QImage& draw_image();
    QImage  drag_image();

protected:
    virtual void    resort() = 0;
    virtual void    update_image() = 0;

private:
    CBacking        * m_backing;
    QPointF         * m_hatch_tl;
    float           * m_scale_factor;

    QRectF            m_rect;
    QImage            m_draw_image;
};


#endif //PROCONT_CLADDER_H
