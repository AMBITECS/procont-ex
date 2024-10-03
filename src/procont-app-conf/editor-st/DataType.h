#pragma once

#include <QDomDocument>
#include <QList>
#include "Variable.h"
#include <QTextStream>
#include "StructSt.h"
#include <QDebug>

struct BaseType
{
    QString baseTypeName;
    StructSt structs;
    ArraySt array;
};


struct DataType
{
    QString name;
    BaseType baseType;
    static DataType parseXML(const QDomNode &node)
    {
        QDomNode domNode =
            node.firstChild();
        DataType dataType;
        dataType.name = node.toElement().attribute("name");
        while(!domNode.isNull()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.tagName() =="baseType")
                {
                    QDomNode nodeBaseType = domElement.firstChild();
                    QDomElement domElementBaseType = nodeBaseType.toElement();
                    if(!domElementBaseType.isNull()){
                        dataType.baseType.baseTypeName = domElementBaseType.tagName();
                        if(domElementBaseType.tagName() == "struct")
                        {
                            QDomNode nodeStruct = nodeBaseType.firstChild();
                            dataType.baseType.structs = StructSt::parseXML(nodeStruct);
                        }
                        if(domElementBaseType.tagName() == "array")
                        {
                            //QDomNode nodeArray = nodeBaseType.firstChild();
                            dataType.baseType.array = ArraySt::parseXML(nodeBaseType);
                        }
                    }

                    nodeBaseType = nodeBaseType.nextSibling();
                }
            }
            domNode = domNode.nextSibling();
        }
        return dataType;
    };

    static QString covertObjToString(const DataType & dataType)
    {
        QString result;

        result += QString("TYPE") + "\n";
        result += "\t" + dataType.name + QString(" : ");

        if(dataType.baseType.baseTypeName == "struct")
        {
            result += StructSt::covertObjToString(dataType.baseType.structs);
        } else if (dataType.baseType.baseTypeName == "array")
        {
            result += ArraySt::covertObjToString(dataType.baseType.array);
            //result += dataType.baseType.array.

        } else
        {
            result += dataType.baseType.baseTypeName + "\n";
        }
        result += QString("END_TYPE");

        return result;
    }

    static QDomNode getNode(DataType _dataType, const QDomNode &_parent, const QStringList & types_list)
    {
        QDomDocument document = _parent.ownerDocument();

        QDomElement elem = document.createElement("dataType");

        elem.setAttribute("name", _dataType.name);

        QDomElement baseType_elem = document.createElement("baseType");
        elem.appendChild(baseType_elem);

        if (!_dataType.baseType.structs.vars.empty())
        {
            QDomElement struct_elem = document.createElement("struct");
            baseType_elem.appendChild(struct_elem);
            for (const auto var : _dataType.baseType.structs.vars)
            {
                QDomElement variable_elem = document.createElement("variable");
                variable_elem.setAttribute("name", var.name);
                QDomElement type_elem = document.createElement("type");

                if (types_list.contains(var.type))
                {
                    QDomElement type_name_elem = document.createElement("type_name_elem");
                    type_name_elem.setTagName(var.type);
                    type_elem.appendChild(type_name_elem);
                    variable_elem.appendChild(type_elem);

                    QDomElement initialValue_elem = document.createElement("initialValue");
                    QDomElement simpleValue_elem = document.createElement("simpleValue");
                    simpleValue_elem.setAttribute("value", var.initialValue.simpleValue.value);
                    initialValue_elem.appendChild(simpleValue_elem);
                    variable_elem.appendChild(initialValue_elem);
                } else {
                    QDomElement derived_elem = document.createElement("derived");
                    derived_elem.setAttribute("name", var.type);
                    type_elem.appendChild(derived_elem);
                    variable_elem.appendChild(type_elem);
                }
                struct_elem.appendChild(variable_elem);
            }
        }

        if (_dataType.baseType.baseTypeName == "array")
        {
            QDomElement array_elem = document.createElement("array");
            baseType_elem.appendChild(array_elem);
            QDomElement dimension_elem = document.createElement("dimension");
            dimension_elem.setAttribute("lower", _dataType.baseType.array.dimension.lower);
            dimension_elem.setAttribute("upper", _dataType.baseType.array.dimension.upper);
            array_elem.appendChild(dimension_elem);

            QDomElement baseType_elem_0 = document.createElement("baseType");
            if (types_list.contains(_dataType.baseType.array.baseType))
            {
                QDomElement type_name_elem = document.createElement("type_name_elem");
                type_name_elem.setTagName(_dataType.baseType.array.baseType);
                baseType_elem_0.appendChild(type_name_elem);
                array_elem.appendChild(baseType_elem_0);
            }
        }

        return elem;
    }

/*
    static DataType TxtToObj(const QString& _vars_text, const QString& _body_text)
    {
        DataType result;
        QString vars_text = _vars_text;
        QTextStream varsStream(&vars_text);
        QString varType = "";
        while (true)
        {
            QString line = varsStream.readLine();

            if (line.isNull())
                break;
            else {
                Variable variable;
                line.replace(" ", "");
                line.replace("\t", "");
                if (line.contains("VAR_INPUT"))
                {
                    varType = "VAR_INPUT";
                } else if (line.contains("VAR_OUTPUT"))
                {
                    varType = "VAR_OUTPUT";
                } else if (line.contains("VAR"))
                {
                    varType = "VAR";
                }
                QStringList list_values = line.split(":=");

                if (list_values.size() > 1)
                {
                    QStringList list_types = list_values.at(0).split(":");
                    if (list_types.size() > 1)
                    {
                        variable.name = list_types.at(0);
                        variable.type = list_types.at(1);
                        variable.initialValue.simpleValue.value = list_values.at(1);
                        pou.interface.setVar(variable, varType);

                    } else {
                        variable.name = list_values.at(0);
                        variable.type = list_values.at(1);
                        pou.interface.setVar(variable, varType);
                    }
                } else {
                    QStringList list_types = list_values.at(0).split(":");
                    if (list_types.size() > 1) {
                        variable.name = list_types.at(0);
                        variable.type = list_types.at(1);
                        pou.interface.setVar(variable, varType);
                    }
                }
            }
        }

        QString body_text = _body_text;
        QTextStream bodyStream(&body_text);
        QString body;
        while (true)
        {
            QString line = bodyStream.readLine();

            if (line.isNull())
                break;
            else {
                body += line + "\n";
            }        Pou pou;
        }
        pou.body.value = body;

        return pou;
    }
*/

};


