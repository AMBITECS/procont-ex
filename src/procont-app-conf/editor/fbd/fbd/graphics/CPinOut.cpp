//
// Created by artem on 12/7/24.
//

#include "CPinOut.h"
#include "CDiagramObject.h"
#include "CLadder.h"

CPinOut::CPinOut(CDiagramObject *parent, CBlockVar *base, QPoint *parent_tl) : CPin(parent, base, parent_tl)
{
    m_direction = PD_OUTPUT;

    m_img_norm = QImage(":/codesys/images/codesys/pin_output_norm.png");
    m_draw_image = m_img_norm;

    saturate();

    m_graphic_connections = new std::vector<CPin*>();
    m_iface_vars = new std::vector<CVariable*>();
    m_world = parent->parent()->parent();
}

CPinOut::~CPinOut()
{
    delete m_iface_vars;
    delete m_graphic_connections;
}

void CPinOut::connect(CPin *pin)
{
    if (!pin)
    {
        throw std::runtime_error("cant connect nullptr in 'void CPinOut::connect(CPin *pin)'");
    }

    for (auto &existing : *m_graphic_connections)
    {
        if (existing == pin)
        {
            return;
        }
    }

    m_is_connected = true;

    m_graphic_connections->push_back(pin);
}

void CPinOut::connect(CVariable *iface_var)
{
    if (!iface_var)
    {
        throw std::runtime_error("cant connect nullptr in 'void CPinOut::connect(CVariable *iface_var)'");
    }
    m_is_connected = true;
    m_iface_vars->push_back(iface_var);
}

std::vector<CPin *> * CPinOut::graphic_connections()
{
    return m_graphic_connections;
}

std::vector<CVariable *> *CPinOut::iface_variables()
{
    return m_iface_vars;
}

void CPinOut::remove_connection(CPinIn *opposite)
{

}

void CPinOut::remove_connection(CVariable *iface_var)
{

}

CObjectsText CPinOut::make_outer_text(CVariable *variable)
{
    
}

void CPinOut::resort_outers()
{

}
