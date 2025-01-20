//
// Created by artem on 12/7/24.
//

#include "CFbdActions.h"
#include "../../fbd/graphics/CFbdObject.h"

CFbdActions::CFbdActions(COglWorld *project_content)
{
    m_analytic_base = project_content;
}

CFbdActions::~CFbdActions()
= default;

void CFbdActions::connect_pins(CPin *dragged, CPin *target)
{
//    CPinIn * input = dragged->direction() == PD_INPUT ? dragged->input() : target->input();
//    CPinOut * output = target->direction() == PD_OUTPUT ? target->output() : dragged->output();
//
//    input->block_var()->set_iface_variable(nullptr);
//
//    uint64_t ref_id = output->parent()->local_id();
//    input->block_var()->point_in()->set_reference_id(ref_id);
//    input->block_var()->point_in()->set_formal_param(output->formal_param());
//    output->add_opposite(input);
}

void CFbdActions::disconnect_pins(CPin *pin0, CPin *pin1)
{

}

void CFbdActions::clear_connections(CPin *pin)
{

}

void CFbdActions::connect_pin_iface_variable(CPin *pin, CVariable *variable)
{

}

void CFbdActions::disconnect_pin_iface_var(CPin *pin)
{

}
