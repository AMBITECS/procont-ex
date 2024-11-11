//
// Created by nechi on 18.10.2024.
//

#ifndef EDITORSD_INCLUDES_H
#define EDITORSD_INCLUDES_H

#include <QDomDocument>
#include <QDomNode>
#include <QDateTime>
#include <QPoint>
#include <cmath>

#define  FLOAT_DIFF 0.0001  //!< максимальная разница между float, ДО которой float'ы могут считаться одинаковыми

/**
 * @brief   т.к. вещественые значения сравнивать некорректно из-за их машинного представления, когда float val = 4
 * может отражаться как 3,9999999999 и прочих чудесностей
 * @param val0
 * @param val1
 * @return is equal
 */
static bool     is_floats_equal(const float &val0, const float &val1)
{
    if (std::fabs(val0 - val1) >= FLOAT_DIFF)
    {
        return false;
    }

    return true;
}

enum  EEdge
{
    EI_NONE,
    EI_RISE,
    EI_FALL,
    EI_COUNT
};

static const QString edge_types_names[EI_COUNT]
{
    "none",
    "rising",
    "falling",
};

enum EStorageMode
{
    SM_NONE,
    SM_SET,
    SM_RESET,
    SM_COUNT
};

static const QString storage_behaviour_names[SM_COUNT]
{
    "none",
    "set",
    "reset"
};

static const QString bool_str[2]
{
    "false",
    "true"
};

enum  EPouType
{
    ePT_PROGRAM,
    ePT_FUNCTIONAL_BLOCK,
    ePT_FUNCTION,
    ePT_COUNT
};

static const QString pou_types_names[EPouType::ePT_COUNT]
{
    "program",
    "functionBlock",
    "function"
};

enum EBodyType
{
    BT_IL,
    BT_ST,
    BT_FBD,
    BT_LD,
    BT_SFC,
    BT_COUNT
};

static const QString body_types_names [EBodyType::BT_COUNT]
{
    "IL",
    "ST",
    "FBD",
    "LD",
    "SFC"
};

/**
 * base types of the system. Arrays, ranges, structs, enum and pointers are extended modifications of thees types
 */
enum EDefinedDataTypes
{
    DDT_BOOL,
    DDT_BYTE,
    DDT_WORD,
    DDT_DWORD,
    DDT_LWORD,
    DDT_SINT,
    DDT_INT,
    DDT_DINT,
    DDT_LINT,
    DDT_USINT,
    DDT_UINT,
    DDT_UDINT,
    DDT_ULINT,
    DDT_REAL,
    DDT_LREAL,
    DDT_TIME,
    DDT_DATE,
    DDT_DT,
    DDT_TOD,
    DDT_STRING,
    DDT_WSTRING,
    DDT_ENUM,           //!< граница базовых типов, больше смысла не имеет
    DDT_STRUCT,
    DDT_DERIVED,        //!< user defined or POU
    DDT_MODIFICATION,   //!< array, range or pointer
    DDT_UNDEF,
    DDT_COUNT
};

static const QString base_types_names[EDefinedDataTypes::DDT_COUNT]
{
    "BOOL",
    "BYTE",
    "WORD",
    "DWORD",
    "LWORD",
    "SINT",
    "INT",
    "DINT",
    "LINT",
    "USINT",
    "UINT",
    "UDINT",
    "ULINT",
    "REAL",
    "LREAL",
    "TIME",
    "DATE",
    "DT",
    "TOD",
    "STRING",
    "WSTRING",
    "ENUM",
    "STRUCT",
    "DERIVED",
    "MODIFICATION",
    "UNDEFINED"
};

static  EDefinedDataTypes  get_type_from_string(const std::string & type_s)
{
    int count = 0;
    for (auto &name : base_types_names)
    {
        if (name.toStdString() == type_s)
        {
            return (EDefinedDataTypes)count;
        }
        count++;
    }
    return DDT_UNDEF;
}

/** @brief последний индекс базового типа */
static const int base_type_last = EDefinedDataTypes::DDT_ENUM;

#endif //EDITORSD_INCLUDES_H
