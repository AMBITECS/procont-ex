//
// Created by nechi on 29.11.2024.
//

#include <QRect>
#include "CFbdConnectLine.h"
#include "../../resources/colors.h"
#include "CPinIn.h"

CFbdConnectLine::CFbdConnectLine(QPoint * ladder_tl, CPin * pin1, CPin *pin2)
{
    CDiagramColors colors;

    m_lines = new QList<QLine>();
    m_error = QColor(255, 25, 91);
    m_warn  = QColor(222,217,80);
    m_selected = colors.ladder_colors().line_selected;
    m_norm = colors.ladder_colors().line_color;
    m_ladder_tl = ladder_tl;
    m_prev_ltl = *ladder_tl;
    m_base = m_norm;

    m_pin_in = pin1->direction() == PD_INPUT ? pin1->input() : pin2->input();
    m_pin_out = pin1->direction() == PD_OUTPUT ? pin1->output() : pin2->output();
}

CFbdConnectLine::~CFbdConnectLine()
{
    delete m_lines;
}

QList<QLine> *CFbdConnectLine::lines()
{
    return m_lines;
}

bool CFbdConnectLine::is_clicked_on(const QPoint &pos)
{
    QRect rect;

    for (auto &line : *m_lines)
    {
        /// if vertical
        if (line.p1().x() == line.p2().x())
        {
            rect = QRect(line.p1().x()-DIFFERENCE, line.p1().y(),
                         DIFFERENCE * 2 + 1, line.dy());

            if (rect.contains(pos))
            {
                return true;
            }
        }
        /// horizontal
        if (line.p1().y() == line.p2().y())
        {
            rect = QRect(line.p1().x(), line.p1().y()-DIFFERENCE,
                         line.dx(), DIFFERENCE * 2 + 1);

            if (rect.contains(pos))
            {
                return true;
            }
        }
    }

    return false;
}

void CFbdConnectLine::set_selected(const bool &is_selected)
{
    m_is_selected = is_selected;

    if (is_selected)
    {
        m_base = m_selected;
    }
    check_is_norm();
}

bool CFbdConnectLine::is_selected() const
{
    return m_is_selected;
}

void CFbdConnectLine::set_warning(const bool &is_warning)
{
    m_is_warn = is_warning;
    if (is_warning)
    {
        m_base = m_warn;
    }
    check_is_norm();
}

bool CFbdConnectLine::is_warning() const
{
    return m_is_warn;
}

void CFbdConnectLine::set_is_error(const bool &is_error)
{
    m_is_error = is_error;
    if (is_error)
    {
        m_base = m_error;
    }
    check_is_norm();
}

bool CFbdConnectLine::is_error() const
{
    return m_is_error;
}

QColor CFbdConnectLine::color()
{
    return m_base;
}

bool CFbdConnectLine::check_is_norm()
{
    if (!m_is_error && !m_is_warn && !m_is_selected)
    {
        m_base = m_norm;
    }
    return true;
}

void CFbdConnectLine::update_position()
{
    QPoint diff = *m_ladder_tl - m_prev_ltl;

    for (auto &line : *m_lines)
    {
        line.setP1(line.p1() + diff);
        line.setP2(line.p2() + diff);
    }

    m_prev_ltl = *m_ladder_tl;
}

void CFbdConnectLine::add_line(const QLine &line)
{
    m_lines->push_back(line);
}

void CFbdConnectLine::clear()
{
    m_lines->clear();
}

CPinIn *CFbdConnectLine::get_pin_in()
{
    return m_pin_in;
}

