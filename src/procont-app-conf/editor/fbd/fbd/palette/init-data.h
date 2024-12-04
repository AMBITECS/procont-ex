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

/*static s_init_block init[EPaletteElements::EP_ST]
{
    {},
    {},
    {},
    {},
    {},

    {EL_AND, "AND", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EL_OR, "OR", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EL_NOT, "NOT", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}, }, {{DDT_BOOL, "OUT"}}, {}},
    {EL_XOR, "XOR", "", {{DDT_BOOL, "IN1"}, {DDT_BOOL, "IN2"}}, {{DDT_BOOL, "OUT"}}, {}},

    {EM_ADD, "ADD", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_SUB, "SUB", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_MUL, "MUL", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_DIV, "DIV", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_EQ, "= (EQ)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_NE, "≠ (NE)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_LT, "< (LT)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_LE, "≤ (LE)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_GT, "> (GT)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EM_GE, "≥ (GE)", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}}, {{DDT_ANY_NUM, "OUT"}}, {}},

    {EO_SEL, "SEL", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}, {DDT_ANY_NUM, "IN3"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EO_MUX, "MUX", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}, {DDT_ANY_NUM, "IN3"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EO_LIMIT, "LIMIT", "", {{DDT_ANY_NUM, "IN1"}, {DDT_ANY_NUM, "IN2"}, {DDT_ANY_NUM, "IN3"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EO_MOVE, "MOVE", "", {{DDT_ANY_NUM, "IN2"}, {DDT_ANY_NUM, "IN3"}}, {{DDT_ANY_NUM, "OUT"}}, {}},
    {EO_CONV, "CONV", "", {{DDT_ANY_NUM, "IN2"}, {DDT_ANY_NUM, "IN3"}}, {{DDT_ANY_NUM, "OUT"}}, {}},

    {EF_R_TRIG, "R_TRIG", "???", {{DDT_BOOL, "IN1"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EF_F_TRIG, "F_TRIG", "???", {{DDT_BOOL, "IN1"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EF_RS, "RS", "???", {{DDT_BOOL, "IN1"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EF_SR, "SR", "???", {{DDT_BOOL, "IN1"}}, {{DDT_BOOL, "OUT"}}, {}},
    {EF_TON, "TON", "???", {{DDT_BOOL, "IN"}, {DDT_TIME, "PT"}}, {{DDT_BOOL, "Q"}, {DDT_TIME, "ET"}}, {}},
    {EF_TOF, "TOF", "???", {{DDT_BOOL, "IN"}, {DDT_TIME, "PT"}}, {{DDT_BOOL, "Q"}, {DDT_TIME, "ET"}}, {}},
    {EF_CTU, "CTU", "???", {{DDT_BOOL, "CU"}, {DDT_BOOL, "RESET"}, {DDT_WORD, "PV"}}, {{DDT_BOOL, "Q"}, {DDT_WORD, "CV"}}, {}},
    {EF_CTD, "CTD", "???", {{DDT_BOOL, "CU"}, {DDT_BOOL, "RESET"}, {DDT_WORD, "PV"}}, {{DDT_BOOL, "Q"}, {DDT_WORD, "CV"}}, {}}
    };*/

#endif //EDITORSD_INIT_DATA_H
