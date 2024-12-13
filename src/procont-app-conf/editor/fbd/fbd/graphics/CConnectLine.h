//
// Created by nechi on 29.11.2024.
//

#ifndef EDITORSD_CCONNECTLINE_H
#define EDITORSD_CCONNECTLINE_H

#include <QLine>
#include <QList>
#include <QColor>
#include "CPin.h"

#define  DIFFERENCE 2   //!< +- pixels for selecting line


class CConnectLine
{
public:
    CConnectLine(QPoint * ladder_tl, CPin * pin1, CPin *pin2);
    ~CConnectLine();

    QList<QLine>    * lines();
    QColor            color();

    /** @brief точного совпадения нет требуется: вертикалка +- 2 пикселя и горизонталка +- 2 пикселя */
    bool    is_clicked_on(const QPoint &pos);

    void    clear();
    void    add_line(const QLine &line);

    void    set_selected(const bool & is_selected);
    [[nodiscard]] bool    is_selected() const;

    void    set_warning(const bool &is_warning);
    [[nodiscard]] bool    is_warning() const;

    void    set_is_error(const bool & is_error);
    [[nodiscard]] bool    is_error() const;

    void    update_position();

    CPinIn *  get_pin_in();


private:
    QList<QLine>    * m_lines;
    QColor            m_base;
    QColor            m_warn;
    QColor            m_error;
    QColor            m_norm;
    QColor            m_selected;
    QPoint          * m_ladder_tl;
    QPoint            m_prev_ltl;

    bool     m_is_selected{false};
    bool     m_is_warn{false};
    bool     m_is_error{false};

    CPinIn * m_pin_in;
    CPinOut* m_pin_out;

    bool check_is_norm();
};


#endif //EDITORSD_CCONNECTLINE_H
