//
// Created by nechi on 15.10.2024.
//

#ifndef EDITORSD_COMPONENTS_INC
#define EDITORSD_COMPONENTS_INC

enum EBaseTypes
{
    ET_BOOL,
    ET_SINT,
    ET_INT,
    ET_DINT,
    ET_LINT,
    ET_USINT,
    ET_UINT,
    ET_UDINT,
    ET_ULINT,
    ET_BYTE,
    ET_WORD,
    ET_DWORD,
    ET_LWORD,
    ET_REAL,
    ET_LREAL,
    ET_TIME,
    ET_DATE,
    ET_TIME_OF_DAY,
    ET_DATE_AND_TIME,
    ET_STRING,
    ET_ANY_BIT,
    ET_ANY_NUM,
    ET_ANY_DATE,
    ET_ANY_INT,
    ET_ANY_REAL,
    ET_VARIANT,
    ET_COUNT
};

static QString baseTypesNames[ET_COUNT]
{
        "BOOL",
        "SINT",
        "INT",
        "DINT",
        "LINT",
        "USINT",
        "UINT",
        "UDINT",
        "ULINT",
        "BYTE",
        "WORD",
        "DWORD",
        "LWORD",
        "REAL",
        "LREAL",
        "TIME",
        "DATE",
        "TIME_OF_DAY",
        "DATE_AND_TIME",
        "STRING",
        "ANY_BIT",
        "ANY_NUM",
        "ANY_DATE",
        "ANY_INT",
        "ANY_REAL"
};

/// XML constructions corresponding to standard palette elements like AND, MUL etc.
static QString xml_constrictions[EPaletteElements::E_COUNT]
{

};



#endif //EDITORSD_COMPONENTS_INC
