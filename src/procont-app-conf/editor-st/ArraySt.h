#pragma once

#include <QDomDocument>
#include <QList>
//#include "CommonStTypes.h"

struct Dimension
{
    QString lower;
    QString upper;

};

class ArraySt
{
public:

    QString baseType;
    Dimension dimension;

    static ArraySt parseXML(QDomNode &domNode)
    {
        ArraySt result;
        while(!domNode.isNull()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.tagName() =="dimension"){
                    result.dimension.lower = domElement.attribute("lower");
                    result.dimension.upper = domElement.attribute("upper");
                }
                if(domElement.tagName() =="baseType"){
                    if (domElement.firstChildElement().tagName() == QString("derived")){
                        result.baseType = domElement.firstChildElement().attribute("name");
                    } else {
                        result.baseType = domElement.firstChildElement().tagName();
                    }
                }

            }
            domNode = domNode.nextSibling();
        }
        return result;
    }
};
