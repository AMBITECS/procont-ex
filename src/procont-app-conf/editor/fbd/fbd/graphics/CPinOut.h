//
// Created by artem on 12/7/24.
//

#ifndef PROCONT_CPINOUT_H
#define PROCONT_CPINOUT_H

#include "CPin.h"

#define OUTER_SHIFT 2

class COglWorld;

class CPinOut : public CPin
{
public:
    CPinOut() = delete;
    CPinOut(CFbdObject * parent, CBlockVar *base, QPoint * parent_tl);
    ~CPinOut() override;

    /** @brief when loading project we have not create or edit any instances in XML - they are existing */
    void    load_project_connect(CPin *pin);
    /** @brief when loading project we have not create or edit any instances in XML - they are existing */
    void    load_project_connect(CVariable *iface_var);

    void    connect(CPin * pin);
    CVariable*    connect(CVariable * iface_var);
    void    disconnect(CPinIn *in, CPinIn *sender = nullptr);
    bool    disconnect(CVariable *iface_var);

    std::vector<CPinIn*>    * graphic_connections();
    std::vector<CVariable*> * iface_variables();

    void    refresh_connections();
    void    reset_connections();

    bool    is_pin_connected_to( CPinIn *in) const;
    bool    is_iface_var_connected_to(CVariable *variable);

    [[nodiscard]] int     outer_height() const;   //!< возвращает высоту занимаемую текстовым перечислением соединений
    [[nodiscard]] int     outer_width() const;    //!< возвращает ширину занимаемую текстовым перечислением соединений

protected:


private:
    std::vector<CPinIn*>    * m_graphic_connections;
    std::vector<CVariable*> * m_iface_vars;
    COglWorld               * m_world;
    QColor                    m_graph_color;
    QColor                    m_var_color;

    CObjectText*    make_outer_text(CVariable *variable);
    CObjectText*           make_outer_text(CPin *pin);

    CVariable*    disconnect_xml(CVariable *iface_var);

};


#endif //PROCONT_CPINOUT_H
