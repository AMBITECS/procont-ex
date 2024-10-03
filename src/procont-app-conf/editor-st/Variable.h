#pragma once

#include <QDomDocument>
#include <QList>
//#include "CommonStTypes.h"
#include "ArraySt.h"


enum ValueType
{
    SIMPLE_VALUE,
    ARRAY_VALUE,
};

struct SimpleValue
{
    QString value;
};

struct ArrayValue
{
    QList<SimpleValue> value;
};

struct InitialValue
{
    SimpleValue simpleValue;
    ArrayValue arrayValue;
};


class Variable
{
public:

    QString name;
    QString type;
    ArraySt arrayType;
    InitialValue initialValue;

    static Variable parseXML(const QDomElement &domElement)
    {
        QDomNode nodeVariable = domElement.firstChild();
        Variable variable;
        variable.name = domElement.attribute("name");
        while(!nodeVariable.isNull()) {
            QDomElement domElementVariable = nodeVariable.toElement();
            if (!domElementVariable.isNull()){

                if(domElementVariable.tagName() =="type"){
                    if (domElementVariable.firstChildElement().tagName() == QString("derived")){
                        variable.type = domElementVariable.firstChildElement().attribute("name");
                    } else {
                        variable.type = domElementVariable.firstChildElement().tagName();
                    }
                    if (variable.type == "array")
                    {
                        QDomNode nodeArray = nodeVariable.firstChild();
                        variable.arrayType = ArraySt::parseXML(nodeArray);
                    }
                }

                if(domElementVariable.tagName() =="initialValue"){
                    QDomNode nodeInitialValue = domElementVariable.firstChild();
                    while(!nodeInitialValue.isNull()) {
                        QDomElement domElementInitialValue = nodeInitialValue.toElement();
                        if (!domElementInitialValue.isNull()){
                            if(domElementInitialValue.tagName() =="simpleValue"){
                                InitialValue initialValue;
                                SimpleValue simpleValue;
                                simpleValue.value = domElementInitialValue.attribute("value");
                                initialValue.simpleValue = simpleValue;
                                variable.initialValue = initialValue;
                            }

                            if(domElementInitialValue.tagName() =="arrayValue"){
                                InitialValue initialValue;
                                ArrayValue arrayValue;
                                QDomNode nodeArrayValue = domElementInitialValue.firstChild();
                                while(!nodeArrayValue.isNull()) {
                                    QDomElement domElementArrayValue = nodeArrayValue.toElement();
                                    if (!domElementArrayValue.isNull()){
                                        if(domElementArrayValue.tagName() =="value"){
                                            QDomNode nodeValue = domElementArrayValue.firstChild();
                                            QDomElement domElementValue = nodeValue.toElement();
                                            if (domElementValue.tagName() == "simpleValue")
                                            {
                                                SimpleValue value;
                                                value.value = domElementValue.attribute("value");
                                                arrayValue.value.append(value);
                                            }
                                        }
                                    }
                                    nodeArrayValue = nodeArrayValue.nextSibling();
                                }
                                initialValue.arrayValue = arrayValue;
                                variable.initialValue = initialValue;
                            }
                        }
                        nodeInitialValue = nodeInitialValue.nextSibling();
                    }
                }
            }
            nodeVariable = nodeVariable.nextSibling();
        }

        return variable;
    }

    static QString covertObjToString(const Variable & variable)
    {
        QString result;
        if (variable.type == "array")
        {
            result += "\t" + variable.name + ": " + QString("ARRAY") + "[" + variable.arrayType.dimension.lower +
                      QString("..") + variable.arrayType.dimension.upper + "]" + " OF " + variable.arrayType.baseType + "\n";
            return result;
        }

        result += "\t" + variable.name + ": " + variable.type;

        if (variable.initialValue.simpleValue.value != "")
        {
            result += " := " + variable.initialValue.simpleValue.value + "\n";
        } else {
            result += "\n";
        }
        return result;
    }
};
