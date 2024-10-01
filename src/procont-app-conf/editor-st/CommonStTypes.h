#pragma once

#include <QString>
#include <QList>
#include "Variable.h"
#include "StructSt.h"
#include "ArraySt.h"

enum PouType
{
    program,
    functionalBlock,
};


/*
struct SimpleValue
{
    QString value;
};

struct InitialValue
{
    SimpleValue simpleValue;
};

struct Variable
{
    QString name;
    QString type;
    InitialValue initialValue;
};
*/

struct Interface
{
    QList<Variable> localVars;
    QList<Variable> inputVars;
    QList<Variable> outputVars;

    void setVar(Variable var, QString varType = QString("VAR"))
    {
        if (varType == "VAR")
        {
            setVariable(var);
        } else if (varType == "VAR_INPUT")
        {
            setInputVariable(var);
        } else if (varType == "VAR_OUTPUT")
        {
            setOutputVariable(var);
        }
    }

    void setVariable(Variable var)
    {
        for (auto index = 0; index < localVars.size(); ++index)
        {
            if (localVars.at(index).name == var.name)
            {
                localVars[index] = var;
                return;
            }
        }
        localVars.append(var);
    }

    void setInputVariable(Variable var)
    {
        for (auto index = 0; index < inputVars.size(); ++index)
        {
            if (inputVars.at(index).name == var.name)
            {
                inputVars[index] = var;
                return;
            }
        }
        inputVars.append(var);
    }

    void setOutputVariable(Variable var)
    {
        for (auto index = 0; index < outputVars.size(); ++index)
        {
            if (outputVars.at(index).name == var.name)
            {
                outputVars[index] = var;
                return;
            }
        }
        outputVars.append(var);
    }
};

struct Body
{
    QString value;
};

struct Pou
{
    QString name;
    Interface interface;
    Body body;
    QString pouType;
};

struct BaseType
{
    QString baseType;
};

struct BaseTypeStruct : public BaseType
{
    StructSt structs;
};

struct BaseTypeArray : public BaseType
{
    ArraySt array;
};

struct DataType
{
    BaseType baseType;
};

struct DataTypes
{
    QList<DataType> dataTypes;
};



