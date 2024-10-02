#pragma once

#include <QDomDocument>
#include <QList>
//#include "CommonStTypes.h"
#include <QDebug>

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
        QDomNode nodeArray0 = domNode.firstChild();
        QDomNode nodeArray = nodeArray0.firstChild();
        ArraySt result;
        while(!nodeArray.isNull()) {
            QDomElement domElement = nodeArray.toElement();
            if(!domElement.isNull()) {
                //qDebug() << domElement.tagName();
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
            nodeArray = nodeArray.nextSibling();
        }
        return result;
    }
};
