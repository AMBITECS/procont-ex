//
// Created by artem on 10/29/24.
//

#ifndef EDITORSD_CCONNECTORPIN_H
#define EDITORSD_CCONNECTORPIN_H


#include <QImage>
#include "CObjectsText.h"
#include "../../plc-xml/variables/CBlockVar.h"
#include "../../plc-xml/variables/CInputVariables.h"
#include "../../plc-xml/variables/COutputVariables.h"

enum EPinDirection
{
    PD_INPUT,
    PD_OUTPUT
};

class CConnectorPin
{
public:
    CConnectorPin(CBlockVar* var, const EPinDirection &direction, QPoint * rel_tl);
    ~CConnectorPin();

    void    set_object_top_left(QPoint * top_left, const QPoint &rel_position);
    void    set_rel_position(const QPoint &pos);
    void    update_position();

    QImage  * image();
    QRect   * rect();
    std::vector<CObjectsText*> * texts();
    QPoint  * position();
    [[nodiscard]] bool    is_negated() const;
    void    set_negated(const bool &negated);
    [[nodiscard]] uint16_t inner_text_width() const;
    [[nodiscard]] uint16_t outer_text_width() const;
    [[nodiscard]] EPinDirection   direction() const;
    [[nodiscard]] uint64_t    ref_local_id() const;
    [[nodiscard]] QString     formal_param() const;
    void    set_in_variable(CInVariable * variable);
    void    set_out_variable(COutVariable * out);
    void    set_formal_param(const QString & formal);
    CBlockVar * block_var();


    void set_selected(const bool &selected);

private:
    QRect             m_rect;
    QImage            m_image;
    CObjectsText      m_formal_param;
    CObjectsText      m_expression;
    QPoint            m_pos;
    QPoint          * m_rel_obj_tp;
    EPinDirection     m_direction;
    CBlockVar       * m_variable;
    std::vector<CObjectsText*>  m_texts;
    bool              m_is_negated{false};
    CInVariable     * m_input_data{nullptr};
    COutVariable    * m_out_variable{nullptr};

    QRect             m_bound_rect{};


};


#endif //EDITORSD_CCONNECTORPIN_H
