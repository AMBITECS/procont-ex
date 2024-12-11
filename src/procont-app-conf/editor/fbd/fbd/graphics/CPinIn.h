//
// Created by artem on 12/7/24.
//

#ifndef PROCONT_CPININ_H
#define PROCONT_CPININ_H

#include "CPin.h"

class CPinIn : public CPin
{
public:
    CPinIn(CDiagramObject * parent, CBlockVar *base, QPoint * parent_tl);
    ~CPinIn() override;

    [[nodiscard]] bool    is_negated() const;
    void    set_negated(const bool  & negated);

    [[nodiscard]] bool    is_rising_edge() const;
    void    set_rising_edge(const bool & rising);

    [[nodiscard]] bool    is_falling_edge() const;
    void    set_falling_edge(const bool &falling);

    [[nodiscard]] bool        is_coil_set() const;
    void        set_coil_set(const bool &set);

    [[nodiscard]] bool        is_coil_reset() const;
    void        set_coil_reset(const bool &reset);

    [[nodiscard]] uint64_t    reference_local_id() const;


    /// операции соединения/разъединения
    CPinOut*    opposite();
    void        set_opposite_name(const bool &set_name);
    void        set_opposite(CPinOut *opposite);
    void        connect_pin(CPinOut *pin); //!< графическое соединение (если одна ступень)
    void        disconnect();
    void        connect_iface_variable(CVariable *variable);
    void        set_constant(const EDefinedDataTypes &type, const std::string &type_name);


private:
    QImage      m_img_negated;
    QImage      m_img_rising;
    QImage      m_img_falling;
    CPinOut   * m_opposite{nullptr};

    void update_condition();

};


#endif //PROCONT_CPININ_H
