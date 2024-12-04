//
// Created by artem on 10/30/24.
//

#ifndef EDITORSD_COBJECTSTEXT_H
#define EDITORSD_COBJECTSTEXT_H


#include <QColor>
#include <QPoint>
#include <QFont>

class CObjectsText
{
public:
    CObjectsText();
    ~CObjectsText();

    [[nodiscard]] QColor      color() const;
    void                      set_color(const QColor &color);

    [[nodiscard]] QString     text() const;
    void                      set_text(const QString &text);

    [[nodiscard]] uint16_t    width() const;
    [[nodiscard]] uint16_t    height() const;

    [[nodiscard]] QPoint      pos() const;
    void                      set_pos(const QPoint &pos);

    QRect                     text_rect() const;

private:
    QColor  m_color;
    QString m_text;
    QPoint  m_pos;
    uint16_t m_width{0};
    uint16_t m_height{0};
    QFont    m_font{"Helvetica", 8};
    QRect    m_rect;

    void  update_size();
};


#endif //EDITORSD_COBJECTSTEXT_H
