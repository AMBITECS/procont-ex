//
// Created by artem on 12/6/24.
//
#include "colors.h"
#include <QStyle>


CDiagramColors::CDiagramColors()
{
    m_base_colors.diag_background = QApplication::palette().color(QPalette::ColorRole::Base);
    m_base_colors.diag_text_def = QApplication::palette().color(QPalette::ColorRole::WindowText);
    //m_base_colors.diag_text_alternate = QApplication::palette().color(QPalette::ColorRole::HighlightedText);

    /// по базовым цветам делаем вывод о теме - тёмная или светлая
    QColor col = m_base_colors.diag_background;
    is_dark_theme = !(col.red() > 127 || col.green() > 127 || col.blue() > 127);

    update_colors();
}

CDiagramColors::~CDiagramColors()
= default;

void CDiagramColors::update_colors()
{
    /// эти и зимой и летом
    m_ladder_colors.rail = QColor(0, 128, 128);
    m_ladder_colors.ladder_number = QColor(0, 128, 128);
    m_ladder_colors.landing_brick = QColor(185,238,185);
    m_ladder_colors.landing_strip = QColor(239,192,136);
    m_ladder_colors.line_color = QColor(89,127,156);
    m_ladder_colors.line_selected = QColor(156,58,156);
    m_base_colors.out_pin_variable = QColor(177,107,49);

    /// тут надо аккуратней
    m_ladder_colors.normal.left_part = m_base_colors.diag_background;
    m_ladder_colors.normal.base_part = m_base_colors.diag_background;

    m_ladder_colors.normal.block = is_dark_theme ?
                                   QColor(116, 114, 147) :
                                   QColor(226, 234, 247);

    m_ladder_colors.normal.block_inner_text = is_dark_theme ?
                                              m_base_colors.diag_text_alternate :
                                              m_base_colors.diag_text_def;

    m_ladder_colors.grey_part = is_dark_theme ? QColor(240,240,240).darker(350) :
                                                QColor(240,240,240);

    m_ladder_colors.selected.left_part = is_dark_theme ?
                                         QColor(59,5,5) :
                                         QColor(247,226,234);

    m_ladder_colors.selected.base_part = is_dark_theme ?
                                         m_base_colors.diag_background.lighter(150) :
                                         QColor(255,255,224);
    m_ladder_colors.selected.block = QColor(80,176,243);
    m_ladder_colors.selected.block_inner_text = is_dark_theme ?
                                                m_base_colors.diag_text_alternate :
                                                m_base_colors.diag_text_def;
    m_base_colors.err_color = is_dark_theme ? QColor(187,63,91) : QColor(121,41,41);
}

SLadderColors CDiagramColors::ladder_colors()
{
    return m_ladder_colors;
}

SDiagramBaseColors CDiagramColors::base_colors()
{
    return m_base_colors;
}

