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
    CPinOut(CDiagramObject * parent, CBlockVar *base, QPoint * parent_tl);
    ~CPinOut() override;

    void    connect(CPin * pin);
    void    connect(CVariable * iface_var);
    void    disconnect(CPinIn *in);
    void    disconnect(CVariable *iface_var);

    std::vector<CPinIn*>    * graphic_connections();
    std::vector<CVariable*> * iface_variables();

    void    refresh_connections();

    [[nodiscard]] int     outer_height() const;   //!< возвращает высоту занимаемую текстовым перечислением соединений
    [[nodiscard]] int     outer_width() const;    //!< возвращает ширину занимаемую текстовым перечислением соединений

protected:


private:
    std::vector<CPinIn*>    * m_graphic_connections;
    std::vector<CVariable*> * m_iface_vars;
    COglWorld               * m_world;
    QColor                    m_graph_color;
    QColor                    m_var_color;

    CObjectsText*    make_outer_text(CVariable *variable);
    CObjectsText*    make_outer_text(CPin *pin);


};


#endif //PROCONT_CPINOUT_H
