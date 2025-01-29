//
// Created by artem on 11/7/24.
//

#include "DBlock.h"

/*
extern uint16_t    max_local_id;

DBlock::DBlock(const s_init_block &init_block)
{
    m_type_name = QString::fromStdString(init_block.type_name);

    m_local_id = ++max_local_id;

    for (auto &in : init_block.inputs)
    {
        auto * var = new CBlockVar();
        var->set_formal_param(in.name.c_str());
        var->set_type(base_types_names[in.data_type]);
        m_in_vars->push_back(var);
    }

    for (auto &out : init_block.outputs)
    {
        auto * var = new CBlockVar();
        var->set_formal_param(out.name.c_str());
        var->set_type(base_types_names[out.data_type]);
        m_out_vars->push_back(var);
    }

    m_instance_name = init_block.inst_name.c_str();
}

DBlock::~DBlock()
= default;
*/