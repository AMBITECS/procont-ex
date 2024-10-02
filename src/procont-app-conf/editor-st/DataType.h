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
                        qDebug() << dataType.baseType.baseTypeName;
                        if(domElementBaseType.tagName() == "struct")
                        {
                            dataType.baseType.structs = StructSt::parseXML(nodeBaseType);
                        }
                        if(domElementBaseType.tagName() == "array")
                        {
                            dataType.baseType.array = ArraySt::parseXML(nodeBaseType);
                        }
                    }

                    nodeBaseType = nodeBaseType.nextSibling();
                }
            }
            //domNode = domNode.nextSibling();
        }


        return dataType;
    };
};


