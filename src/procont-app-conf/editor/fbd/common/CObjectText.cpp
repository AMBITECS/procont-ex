//
// Created by artem on 10/30/24.
//

#include <QFontMetrics>
#include "CObjectText.h"

CObjectText::CObjectText()
= default;

CObjectText::~CObjectText()
= default;

QColor CObjectText::color() const
{
    return m_color;
}

QString CObjectText::text() const
{
    return m_text;
}

uint16_t CObjectText::width() const
{
    return m_width;
}

uint16_t CObjectText::height() const
{
    return m_height;
}

QPoint CObjectText::pos() const
{
    return m_pos;
}

void CObjectText::set_color(const QColor &color)
{
    m_color = color;
}

void CObjectText::set_text(const QString &text)
{
    m_text = text;

    update_size();
}

void CObjectText::set_pos(const QPoint &pos)
{
    m_pos = pos;
}

void CObjectText::update_size()
{
    QFontMetrics fm(m_font);

    QSize sz = fm.size(Qt::TextSingleLine , m_text);
    m_width = sz.width();
    m_height = sz.height();

    m_rect.setRect(m_pos.x(), m_pos.y(), m_width, m_height);
}

QRect CObjectText::text_rect() const
{
    return m_rect;
}
