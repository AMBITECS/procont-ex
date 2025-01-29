//
// Created by artem on 12/6/24.
//

#ifndef PROCONT_CPIN_H
#define PROCONT_CPIN_H

#include <QImage>
#include "editor/fbd/common/CObjectText.h"
#include "../../plc-xml/variables/CBlockVar.h"
#include "../../plc-xml/variables/CInputVariables.h"
#include "../../plc-xml/variables/COutputVariables.h"
#include "../../plc-xml/fbd/CBlock.h"
#include <QApplication>


class CFbdObject;
class CFbdLadder;
class CPinIn;
class CPinOut;

class CPin
{
public:

    virtual ~CPin();

    /// base data
    CFbdObject   *  parent();
    CBlockVar * block_variable();

    /// to avoid dynamic_cast<CPinXXX>(pin)
    CPinIn *    input();    //!< in case of direction input - returns CPinIn, otherwise - nullptr
    CPinOut*    output();   //!< in case of direction output - returns CPinOut, otherwise - nullptr

    /// drawing object
    QImage  * image();
    QRect   * rect();
    std::vector<CObjectText*> * texts();
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
    [[nodiscard]] bool        is_pin_at_pos(const QPoint &pos) const;
    [[nodiscard]] bool        is_connected() const;

    /// tech data for drawing parent
    [[nodiscard]] uint16_t    pin_name_width() const;     //!< ширина текста, находящегося "внутри" родителя
    /** @brief ширина текста, находящегося вне родителя (наименование связи). Для выходного пина - максимальная
     * ширина из имеющихся */
    [[nodiscard]] uint16_t    outer_text_width() const;


    [[nodiscard]] QString     name() const;
    [[nodiscard]] QString     name_full() const;  //!< with parent name
    void    set_pin_name(const QString & formal);

    [[nodiscard]] QString     type_name() const;
    [[nodiscard]] EDefinedDataTypes type() const;
    void        set_type(const QString &type);



protected:
    CPin(CFbdObject* parent, CBlockVar* var, QPoint * parent_tl);

    CBlockVar       * m_block_variable;
    CFbdObject  * m_parent;

    static void    saturate(QImage *image);

    /// drawing data
    QPoint            m_pos;
    QPoint          * m_relative_parent_tp;
    QRect             m_rect;
    QRect             m_bound_rect{};

    QImage            m_draw_image;
    QImage            m_def_image;
    QImage            m_img_not_selected;
    QImage            m_img_selected;
    QImage            m_img_error;


    QFont             m_font{QApplication::font()};
    CObjectText    * m_pin_name;
    CObjectText    * m_outer_text;

    std::vector<CObjectText*>  * m_texts;
    std::vector<CObjectText*>  * m_outer_texts;
    std::vector<CObjectText*>  * m_outs_graphics;    //!< графические соединения в буквенном выражении


    bool              m_is_selected{false};
    bool              m_is_error{false};
    bool              m_is_connected{false};
    EPinDirection     m_direction{PD_UNDEF};
    QSize             m_out_texts_size;

    CFbdLadder           * m_current_ladder{nullptr};
    CFbdLadder           * m_prev_ladder{nullptr};

    void resort_outers();
    QString  make_pin_text(CPin *pin);
    bool    check_compatibility(const QString &type_name);
};


#endif //PROCONT_CPIN_H
