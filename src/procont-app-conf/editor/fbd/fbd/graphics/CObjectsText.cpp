//
// Created by artem on 10/30/24.
//

#include <QFontMetrics>
#include "CObjectsText.h"

CObjectsText::CObjectsText()
= default;

CObjectsText::~CObjectsText()
= default;

QColor CObjectsText::color() const
{
    return m_color;
}

QString CObjectsText::text() const
{
    return m_text;
}

uint16_t CObjectsText::width() const
{
    return m_width;
}

uint16_t CObjectsText::height() const
{
    return m_height;
}

QPoint CObjectsText::pos() const
{
    return m_pos;
}

void CObjectsText::set_color(const QColor &color)
{
    m_color = color;
}

void CObjectsText::set_text(const QString &text)
{
    m_text = text;
    if (text == "???")
    {
        m_color = QColor(240, 200,200);
    }
    update_size();
}

void CObjectsText::set_pos(const QPoint &pos)
{
    m_pos = pos;
}

void CObjectsText::update_size()
{
    QFontMetrics fm(m_font);

    QSize sz = fm.size(Qt::TextSingleLine , m_text);
    m_width = sz.width();
    m_height = sz.height();

    m_rect.setRect(m_pos.x(), m_pos.y(), m_width, m_height);
}

QRect CObjectsText::text_rect() const
{
    return m_rect;
}
