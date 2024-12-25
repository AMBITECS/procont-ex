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
#include <regex>

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
    EPT_PROGRAM,
    EPT_FUNCTIONAL_BLOCK,
    EPT_FUNCTION,
    EPT_COUNT
};

static const QString pou_types_names[EPouType::EPT_COUNT]
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

static EBodyType body_type_from_string(const QString &str)
{
    int counter = 0;
    for (auto &name : body_types_names)
    {
        if (name == str)
        {
            return (EBodyType)counter;
        }
        counter++;
    }
    return EBodyType::BT_COUNT;
}

/**
 * base types of the system. Arrays, ranges, structs, enum and pointers are extended modifications of thees types
 */
enum EDefinedDataTypes
{
    DDT_BOOL,
    DDT_ANY_BIT,
    DDT_SINT,
    DDT_INT,
    DDT_DINT,
    DDT_LINT,
    DDT_ANY_INT,
    DDT_USINT,
    DDT_UINT,
    DDT_UDINT,
    DDT_ULINT,
    DDT_ANY_UINT,
    DDT_REAL,
    DDT_LREAL,
    DDT_ANY_REAL,
    DDT_ANY_NUM,
    DDT_TIME,
    DDT_DATE,
    DDT_DT,
    DDT_TOD,
    DDT_STRING,
    DDT_WSTRING,
    DDT_ENUM,           //!< граница базовых типов, больше смысла не имеет
    DDT_BYTE,
    DDT_WORD,
    DDT_DWORD,
    DDT_LWORD,
    DDT_ANY,
    DDT_DERIVED,        //!< user defined or POU
    DDT_UNDEF,
    DDT_COUNT
};

static const QString base_types_names[EDefinedDataTypes::DDT_COUNT]
{
    "BOOL",
    "ANY_BIT",
    "SINT",
    "INT",
    "DINT",
    "LINT",
    "ANY_INT",
    "USINT",
    "UINT",
    "UDINT",
    "ULINT",
    "ANY_UINT",
    "REAL",
    "LREAL",
    "ANY_REAL",
    "ANY_NUM",
    "TIME",
    "DATE",
    "DT",
    "TOD",
    "STRING",
    "WSTRING",
    "ENUM",
    "BYTE",
    "WORD",
    "DWORD",
    "LWORD",
    "ANY",
    "DERIVED",
    "UNDEFINED"
};

static EDefinedDataTypes  get_type_from_string(const std::string & type_s)
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
    return DDT_DERIVED;
}


/** @brief последний индекс базового типа */
static const int base_type_last = EDefinedDataTypes::DDT_ENUM;

static bool  is_convertible_to_anyint(const EDefinedDataTypes &type)
{
    return (type >= DDT_SINT && type <= DDT_ANY_UINT) || (type == DDT_ENUM);
}

static bool is_convertible_to_anyuint(const EDefinedDataTypes &type)
{
    return type >= DDT_USINT && type <= DDT_ANY_UINT;
}

static bool is_convertible_to_anyfloat(const EDefinedDataTypes &type)
{
    return type >= DDT_REAL && type <= DDT_ANY_REAL;
}

static bool is_convertible_to_any_num(const EDefinedDataTypes &type)
{
    return (type >= DDT_SINT && type <= DDT_ANY_NUM) || (type == DDT_ENUM);
}

static bool is_convertible_to_bool(const EDefinedDataTypes &type)
{
    return type <= DDT_ANY_BIT;
}

#endif //EDITORSD_INCLUDES_H
