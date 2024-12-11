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
    std::vector<CPin*>  * graphic_connections();
    std::vector<CVariable*> * iface_variables();
    void    remove_connection(CPinIn *opposite);
    void    remove_connection(CVariable * iface_var);
    int     outer_height() const;   //!< возвращает высоту занимаемую текстовым перечислением соединений
    int     outer_width() const;    //!< возвращает ширину занимаемую текстовым перечислением соединений

protected:


private:
    std::vector<CPin*>      * m_graphic_connections;
    std::vector<CVariable*> * m_iface_vars;
    COglWorld               * m_world;

    CObjectsText    make_outer_text(CVariable *variable);
    void            resort_outers();

};


#endif //PROCONT_CPINOUT_H
