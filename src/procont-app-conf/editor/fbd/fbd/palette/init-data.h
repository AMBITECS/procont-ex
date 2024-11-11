//
// Created by artem on 11/7/24.
//

#ifndef EDITORSD_INIT_DATA_H
#define EDITORSD_INIT_DATA_H

#include "../../plc-xml/includes.h"
#include "palette.h"

struct s_init_variable
{
    EDefinedDataTypes   data_type{DDT_ENUM};
    std::string         name;
};

struct s_init_block
{
    EPaletteElements    element;
    std::string  type_name;
    std::string  inst_name;
    std::vector<s_init_variable>    inputs;
    std::vector<s_init_variable>    outputs;
    std::vector<s_init_variable>    in_outs;
};

static s_init_block init[EPaletteElements::EP_ST]
{
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {EL_AND_2IN, "AND", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EL_AND_3IN, "AND3", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}, {DDT_BOOL, "IN3"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EL_OR_2IN, "OR", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EL_OR_3IN, "OR3", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}, {DDT_BOOL, "IN3"}}, {{DDT_BOOL, "OUT"}}, {}}
    };

#endif //EDITORSD_INIT_DATA_H
