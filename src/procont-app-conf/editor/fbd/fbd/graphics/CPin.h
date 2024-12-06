//
// Created by artem on 12/6/24.
//

#ifndef PROCONT_CPIN_H
#define PROCONT_CPIN_H

#include <QImage>
#include "CObjectsText.h"
#include "../../plc-xml/variables/CBlockVar.h"
#include "../../plc-xml/variables/CInputVariables.h"
#include "../../plc-xml/variables/COutputVariables.h"
#include "../../plc-xml/fbd/CBlock.h"


class CDiagramObject;

class CPin
{
public:
    CPin(CDiagramObject* parent, CBlockVar* var);
    virtual ~CPin();

    /// base data
    CDiagramObject   *  parent();
    CBlockVar        *  pin_base_variable();

    /// drawing object
    QImage  * image();
    QRect   * rect();
    std::vector<CObjectsText*> * texts();
    QPoint  * position();

    /// update object coordinates
    void    set_rel_position(const QPoint &pos);
    void    update_position();

    /// object condition
    [[nodiscard]] bool        is_selected() const;
    void                      set_selected(const bool &selected);
    [[nodiscard]] bool        is_error_state() const;
    void                      set_error(const bool & is_error);
    [[nodiscard]] EPinDirection   direction() const;

    /// tech data for drawing parent
    [[nodiscard]] uint16_t    pin_name_width() const;     //!< ширина текста, находящегося "внутри" родителя
    /** @brief ширина текста, находящегося вне родителя (наименование связи). Для выходного пина - максимальная
     * ширина из имеющихся */
    [[nodiscard]] uint16_t    outer_text_width() const;

    /// configure pin
    [[nodiscard]] uint64_t    ref_local_id() const;        //!< id на который ссылается этот pin при имеющейся связи
    void    set_reference_id(const uint64_t &ref_id);

    [[nodiscard]] QString     pin_name() const;
    void    set_pin_name(const QString & formal);

    [[nodiscard]] QString     type_name() const;
    [[nodiscard]] EDefinedDataTypes type() const;
    void        set_type(const QString &type);

    void        clear_connections();

protected:
    CBlockVar       * m_block_variable;
    CDiagramObject  * m_parent;

    /// drawing data
    QPoint            m_pos;
    QPoint          * m_relative_parent_tp;
    QRect             m_rect;
    QImage            m_draw_image;
    QImage            m_img_norm;
    QImage            m_img_selected;
    QImage            m_img_error;

    bool              m_is_selected{false};
    bool              m_is_error{false};
    EPinDirection     m_direction{PD_UNDEF};

};


#endif //PROCONT_CPIN_H
