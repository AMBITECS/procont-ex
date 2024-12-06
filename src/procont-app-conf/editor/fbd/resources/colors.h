//
// Created by artem on 12/6/24.
//

#ifndef PROCONT_COLORS_H
#define PROCONT_COLORS_H

#include <QColor>
#include <QApplication>

typedef struct s_base_diagram_colors
{
    QColor  diag_background;
    QColor  diag_text_def;
    QColor  diag_text_alternate;
    QColor  err_color;
}SDiagramBaseColors;

typedef struct
{
    QColor  rail;           //!< вертикальная часть ступени слева, которая складывается в сплошную шину
    QColor  ladder_number;  //!< того же цвета, что и шина
    QColor  grey_part;
    QColor  landing_strip;
    QColor  landing_brick;

    struct s_norm_colors
    {
        QColor  left_part;
        QColor  base_part;  //!< того же цвета, что и фон диаграммы
        QColor  block;
        QColor  block_inner_text;
    }normal;

    struct s_selected_colors
    {
        QColor  left_part;
        QColor  base_part;
        QColor  block;
        QColor  block_inner_text;
    }selected;
}SLadderColors;



/**
 * @brief устанавливает цвета диаграммы в зависимости от темы ОС.
 * Так же позволяет выставить вручную темную или светлую тему (в перспективе)
 */
class CDiagramColors
{
public:
    CDiagramColors();
    ~CDiagramColors();

    SLadderColors  ladder_colors();
    SDiagramBaseColors  base_colors();

    void    set_dark(){};
    void    set_light(){};

private:
    bool    is_dark_theme;
    void    update_colors();
    SDiagramBaseColors  m_base_colors;
    SLadderColors       m_ladder_colors;
};


#endif //PROCONT_COLORS_H
