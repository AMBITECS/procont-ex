//
// Created by artem on 12/7/24.
//

#ifndef PROCONT_CFBDACTIONS_H
#define PROCONT_CFBDACTIONS_H

#include "../../fbd/graphics/CPin.h"

class COglWorld;

/**
 * @brief класс для отражения манипуляций c диаграммой в XML
 */
class CFbdActions
{
public:
    CFbdActions() = delete;
    CFbdActions(COglWorld * project_content);
    ~CFbdActions();

    static void    connect_pins(CPin *dragged, CPin * target);
    void    disconnect_pins(CPin *pin0, CPin * pin1);
    void    clear_connections(CPin *pin);
    void    connect_pin_iface_variable(CPin *pin, CVariable *variable);
    void    disconnect_pin_iface_var(CPin * pin);

protected:

private:
    COglWorld   * m_analytic_base;

};


#endif //PROCONT_CFBDACTIONS_H
