//
// Created by artem on 10/29/24.
//

#ifndef EDITORSD_CDIAGRAMOBJECT_H
#define EDITORSD_CDIAGRAMOBJECT_H


#include <QImage>
#include "CPin.h"
#include "CObjectsText.h"
#include "../../plc-xml/fbd/CBlock.h"
#include "CPinIn.h"
#include "CPinOut.h"

#define TOP_SHIFT 40
#define PIN_SHIFT 20
#define NAME_SHIFT 5
#define BOTTOM_SHIFT 10

class CLadder;

enum    EPinTypes
{
    EPT_ANY,        //!< ANY/ANY_NUM
    EPT_ANY_CON,    //!< ANY_INT/ANY_REAL/ANY_BOOL
    EPT_CONCRETE   //!< REAL/INT/...user type.. POU_type
};

class CDiagramObject
{
public:
    CDiagramObject(CLadder *ladder, CBlock *block);
    ~CDiagramObject();

    /**
     * @brief   sitting up objects position in the ladder when insert, create or moved with ladder change.
     * @param[in] ladder_rtl    relative top-left of the ladder
     * @param[in] rtl_shift     top-left of the objects body shifted from the ladder_rtl
     */
    void    set_ladders_relative_top_left(CLadder *ladder, const QPoint & rtl_shift);

    /**
     * @brief using when ladder has moved
     */
    void    update_position();
    /**
     * @brief creating object is consist of 3 stages:<br>1. create itself and define base size<br>2. setup
     * in/out variables<br>3. and this function - setup it bound rect after setup variables ONLY<br> only after thees stages object could
     * be located correctly
     */
    void    update_bound_rect();

    /// to draw
    QRect   * rect();
    QImage  * image();
    std::vector<std::pair<QRect, QImage>>  * highlights();
    std::vector<CPin*> * pins();
    std::vector<CPinOut*> * outputs();
    std::vector<CPinIn*> * inputs();
    std::vector<CObjectsText*>  * texts();

    [[nodiscard]] QRect   bound_text_rect() const;
    [[nodiscard]] QRect   bound_graph_rect() const; //!< границы образуемые графическими соединениями
    [[nodiscard]] QImage  bound_image() const;
    [[nodiscard]] QImage drag_image(const bool &is_transparent = false);

    /** @brief if opposite pins on other ladder convert graphic connections to text descriptions */
    void refresh_graphic_connections();

    [[nodiscard]] bool  switch_highlights(const QPoint &pos);
    void  set_selected(const bool & selected);

    [[nodiscard]] bool  is_selected() const;

    [[nodiscard]] uint64_t    local_id() const;
    [[nodiscard]] QString     instance_name() const;
    void                      set_instance_name(const QString &name);
    [[nodiscard]] QString     type_name() const;
    [[nodiscard]] EDefinedDataTypes         type() const;

    CLadder * parent();
    CBlock  * block();

    CPinOut * get_output_by_name(const QString & formal);

    CObjectsText *  inst_text();

private:
    friend CPin;
    friend CPinIn;
    friend CPinOut;


    CBlock  * m_block;
    CObjectsText    m_type_name;
    CObjectsText    m_instance_name;
    QSize           m_size;
    QSize           m_bound_size;

    QImage          m_image;
    QImage          m_bound_img;
    bool            m_is_selected{false};
    QColor          m_color_norm;//{226, 234, 247};
    QColor          m_color_sel;//{80,176,243};
    QColor          m_color_curr;//{m_color_norm};

    bool            bound_complete{false};

    /// coordinates of this object
    int           m_rel_x{0};
    int           m_rel_y{0};
    QPoint        m_base_shift;         //!< сдвиг компонента относительно top-left ступени
    QPoint      * m_ladder_relative_tl; //!< top-left ступени
    int           m_text_bound_shift{0};
    int           m_graph_bound_shift{0};

    QRect         m_rect;
    QRect         m_text_bounds;
    QRect         m_graph_bounds; //!< граница образуемая графическими соединениями

    std::vector<CPinIn*>  * m_inputs;
    std::vector<CPinOut*>  * m_outputs;
    std::vector<CObjectsText*>     m_texts;
    std::vector<std::pair<QRect, QImage>>  * m_highlights;
    std::vector<CPin*> * m_pins;
    EPinTypes     m_pin_types{EPT_ANY};

    EDefinedDataTypes   m_primary_type;
    bool          m_set_type_done{false};

    void define_size();
    // void draw_bound_rect();
    void locate_pins();
    void  update_rel_position(QPoint * relative_tl = nullptr);

    CLadder *m_parent;

    void update_block_data();

    void    im_connected(const QString &type, CPin *pin);
    void    im_disconnected(CPin *pin);

    static EPinTypes define_is_concrete_types(const EDefinedDataTypes &type);

    void set_all_pins_any_concrete(const EDefinedDataTypes &types);
};


#endif //EDITORSD_CDIAGRAMOBJECT_H
