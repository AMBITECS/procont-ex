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
#include "../../plc-xml/fbd/CBlock.h"

struct graphic_base
{
    uint64_t  block_local_id{0};
    CBlockVar *block_var{nullptr};
};

class CDiagramObject;

class CConnectorPin
{
public:
    CConnectorPin(CBlockVar* var, CDiagramObject* parent, const EPinDirection &direction, QPoint * obj_tl);
    ~CConnectorPin();

    void    set_rel_position(const QPoint &pos);
    void    update_position();

    QImage  * image();
    QRect   * rect();
    std::vector<CObjectsText*> * texts();
    QPoint  * position();
    [[nodiscard]] bool        is_selected() const;
    [[nodiscard]] uint16_t inner_text_width() const;
    [[nodiscard]] uint16_t outer_text_width() const;
    [[nodiscard]] EPinDirection   direction() const;
    [[nodiscard]] uint64_t    ref_local_id() const;

    [[nodiscard]] QString     formal_param() const;
    void    set_formal_param(const QString & formal);

    void    set_in_variable(CInVariable * variable);
    void    set_iface_variable(CVariable * var);
    void    set_out_variable(COutVariable * out);

    CBlockVar * block_var();
    CDiagramObject * parent();

    [[nodiscard]] bool    is_negated() const;
    void    set_negated(const bool &negated);

    [[nodiscard]] EEdge    edge_modifier() const;
    void            set_edge_modifier(const EEdge & edge);

    [[nodiscard]] EDefinedDataTypes   type() const;
    [[nodiscard]] QString     derived_type() const;
    void        set_type(const QString &type);

    void set_selected(const bool &selected);

    /// for all pins
    [[nodiscard]] bool    is_empty() const;
    void    reset_connections();

    /// for output pins
    void    remove_opposite(CConnectorPin * opposite);
    void    add_opposite(CConnectorPin * opposite);
    std::vector<CConnectorPin*> * opposites();

    /// for input pins
    CConnectorPin * opposite_pin();
    void        set_opposite_pin(CConnectorPin *opposite_pin);


    [[nodiscard]] bool    is_connected() const; //!< is connected to anything. Actual for inputs. For outputs returns false always.

    void    set_graphic_base(const uint64_t &local_id, const CBlockVar *bloc_out, const QString &pin_label); //!< базовые данные для графического соединения
    graphic_base *  graphic_connection_base();

    [[nodiscard]] bool    pin_here(const QPoint &pos) const;

    void    set_opposite_name(const bool &set_name);

private:
    QPoint            m_pos;
    QPoint          * m_rel_obj_tp;

    QRect             m_rect;
    QImage            m_image;
    QImage            m_norm_img;
    QImage            m_selected_img;

    CObjectsText      m_pin_name;
    CObjectsText      m_outer_text;
    EPinDirection     m_direction;
    CBlockVar       * m_variable;
    CDiagramObject  * m_parent;



    std::vector<CObjectsText*>
                      m_texts;

    bool              m_is_negated{false};
    EEdge             m_edge_modifier{EEdge::EI_NONE};
    bool              m_is_selected{false};

    CConnectorPin   * m_opposite_pin{nullptr};
    std::vector<CConnectorPin*> * m_out_connections;    //!< if this pin is output

    //CVariable   m_iface_variable;
    //CVariable         m_iface_var;
    //CInVariable     * m_input_data{nullptr};
    //COutVariable    * m_out_variable{nullptr};

    /// base for graphics connection
    graphic_base m_graphic_conn_base;

    EDefinedDataTypes   m_type{DDT_ANY_NUM};
    QString             m_derived_type;

    QRect             m_bound_rect{};

    void            saturate_image();   // make 'selected' image
};


#endif //EDITORSD_CCONNECTORPIN_H
