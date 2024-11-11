//
// Created by artem on 11/7/24.
//

#include "DBlock.h"

DBlock::DBlock(const s_init_block &init_block)
{
    m_type_name = QString::fromStdString(init_block.type_name);

    // TODO: define methods to find max local_id, this method could be static
    m_local_id = 0;

    for (auto &in : init_block.inputs)
    {
        auto * var = new CBlockVar();
        var->set_formal_param(in.name.c_str());
        m_in_vars->push_back(var);
    }

    for (auto &out : init_block.outputs)
    {
        auto * var = new CBlockVar();
        var->set_formal_param(out.name.c_str());
        m_out_vars->push_back(var);
    }

}

DBlock::~DBlock()
= default;
