//
// Created by artem on 12/24/24.
//

#ifndef PROCONT_CLADDER_H
#define PROCONT_CLADDER_H

#include <QRect>
#include <QColor>
#include <QImage>

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

/** @brief протокласс ступеней на диаграммах */
class CLadder
{
    virtual ~CLadder();



};


#endif //PROCONT_CLADDER_H
