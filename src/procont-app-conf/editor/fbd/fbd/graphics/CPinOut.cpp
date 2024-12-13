//
// Created by artem on 12/7/24.
//

#include <QFontMetrics>
#include "CPinOut.h"
#include "CDiagramObject.h"
#include "CLadder.h"
#include "../../resources/colors.h"

CPinOut::CPinOut(CDiagramObject *parent, CBlockVar *base, QPoint *parent_tl) : CPin(parent, base, parent_tl)
{
    m_direction = PD_OUTPUT;

    m_img_norm = QImage(":/codesys/images/codesys/pin_output_norm.png");
    m_draw_image = m_img_norm;

    saturate();

    m_graphic_connections = new std::vector<CPinIn*>();
    m_iface_vars = new std::vector<CVariable*>();
    m_world = parent->parent()->parent();

    CDiagramColors colors;
    m_graph_color = colors.ladder_colors().line_color;
    m_var_color = colors.base_colors().out_pin_variable;
}

CPinOut::~CPinOut()
{
    delete m_iface_vars;
    delete m_graphic_connections;
}

void CPinOut::connect(CPin *pin)
{
    if (!pin || pin->direction() == PD_OUTPUT)
    {
        throw std::runtime_error("cant connect nullptr in 'void CPinOut::connect(CPin *pin)'");
    }

    CPinIn *in = pin->input();

    for (auto &existing : *m_graphic_connections)
    {
        if (existing == in)
        {
            return;
        }
    }

    m_is_connected = true;

    if (pin->parent()->parent() != m_parent->parent())
    {
        auto txt_block = make_outer_text(pin);
        txt_block->set_color(m_graph_color);
        m_outer_texts->push_back(txt_block);

        resort_outers();
    }

    m_graphic_connections->push_back(in);
    refresh_connections();
}

void CPinOut::connect(CVariable *iface_var)
{
    if (!iface_var)
    {
        throw std::runtime_error("cant connect nullptr in 'void CPinOut::connect(CVariable *iface_var)'");
    }
    m_is_connected = true;

    auto txt = make_outer_text(iface_var);
    txt->set_color(m_var_color);
    m_outer_texts->push_back(txt);

    m_iface_vars->push_back(iface_var);

    refresh_connections();
}

std::vector<CPinIn *> * CPinOut::graphic_connections()
{
    return m_graphic_connections;
}

std::vector<CVariable *> *CPinOut::iface_variables()
{
    return m_iface_vars;
}

CObjectsText *CPinOut::make_outer_text(CVariable *variable)
{
    auto text = new CObjectsText();
    text->set_text(variable->name());

    return  text;
}

int CPinOut::outer_height() const
{
    return m_out_texts_size.height();
}

int CPinOut::outer_width() const
{
    return m_out_texts_size.width();
}

void CPinOut::refresh_connections()
{
    for (auto &item : *m_outer_texts)
    {
        delete item;
    }
    m_outer_texts->clear();

    for (auto &iface : *m_iface_vars)
    {
        auto txt = make_outer_text(iface);
        txt->set_color(m_var_color);
        m_outer_texts->push_back(txt);
    }

    for (auto &pin : *m_graphic_connections)
    {
        if (pin->parent()->parent() == m_parent->parent())
        {
            continue;
        }

        auto txt = make_outer_text(pin);
        txt->set_color(m_graph_color);
        m_outer_texts->push_back(txt);
    }

    resort_outers();
}

CObjectsText *CPinOut::make_outer_text(CPin *pin)
{
    auto txt_block = new CObjectsText();
    txt_block->set_text(make_pin_text(pin));
    return txt_block;
}

void CPinOut::disconnect(CPinIn *in)
{
    int counter = 0;
    for (auto &input : *m_graphic_connections)
    {
        if (in == input)
        {
            m_graphic_connections->erase(m_graphic_connections->begin() + counter);
            refresh_connections();
            return;
        }
        counter++;
    }
}

void CPinOut::disconnect(CVariable *iface_var)
{
    int counter = 0;
    for (auto &i_var : *m_iface_vars)
    {
        if (i_var == iface_var)
        {
            m_iface_vars->erase(m_iface_vars->begin() + counter);
            refresh_connections();
            return;
        }
        counter++;
    }
}


