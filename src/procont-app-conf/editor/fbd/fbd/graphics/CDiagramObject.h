//
// Created by artem on 10/29/24.
//

#ifndef EDITORSD_CDIAGRAMOBJECT_H
#define EDITORSD_CDIAGRAMOBJECT_H


#include <QImage>
#include "CConnectorPin.h"
#include "CObjectsText.h"
#include "../../plc-xml/fbd/CBlock.h"
#include "CConnectorPin.h"

#define TOP_SHIFT 40
#define PIN_SHIFT 20
#define NAME_SHIFT 5
#define BOTTOM_SHIFT 10

class CDiagramObject
{
public:
    CDiagramObject(QPoint * ladder_top_left, CBlock *block);
    ~CDiagramObject();

    void    set_ladders_top_left(QPoint * ltl, const QPoint & pos);

    QRect   * rect();
    QImage  * image();
    std::vector<std::pair<QRect, QImage>>  * highlights();

    std::vector<CConnectorPin*> * pins();
    std::vector<CObjectsText*>  * texts();


    [[nodiscard]] bool  switch_highlights(const QPoint &pos);
    void  set_relative_pos(const int &x, const int &y);
    void  update_rel_position(QPoint * relative_tl = nullptr);
    [[nodiscard]] QRect   bound_rect() const;
    [[nodiscard]] QImage  bound_image() const;
    void  set_selected(const bool & selected);
    bool  is_selected() const;
    QImage  drag_image() const;
    void draw_drag_image();
    uint64_t local_id() const;

private:
    QPoint  * m_ladder_relative_tl;
    QPoint    m_top_left;


    CBlock  * m_block;
    CObjectsText    m_type_name;
    CObjectsText    m_var_name;
    QSize           m_size;

    QImage          m_image;
    QImage          m_bound_img;
    QRect           m_rect;
    QRect           m_bounds;
    bool            m_is_selected{false};
    QColor          m_color_norm{226, 234, 247};
    QColor          m_color_sel{80,176,243};
    QColor          m_color_curr{m_color_norm};
    QImage          m_drag_image;

    bool            bound_complete{false};


    int m_rel_x{0};
    int m_rel_y{0};

    std::vector<CConnectorPin*>  * m_inputs;
    std::vector<CConnectorPin*>  * m_outputs;
    std::vector<CObjectsText*>     m_texts;
    std::vector<std::pair<QRect, QImage>>  * m_highlights;
    std::vector<CConnectorPin*> * m_pins;

    void build_block();
    void define_size();

    void define_bound();
    void draw_bound_rect();

    void locate_pins();
};


#endif //EDITORSD_CDIAGRAMOBJECT_H
