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
        QDomNode nodeArray = domNode.firstChild();
        ArraySt result;
        while(!nodeArray.isNull()) {
            QDomElement domElement = nodeArray.toElement();
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
            nodeArray = nodeArray.nextSibling();
        }
        return result;
    }

    static QString covertObjToString(const ArraySt & array_st)
    {
        QString result;

        result += QString("ARRAY") + "[" + array_st.dimension.lower +
                  QString("..") + array_st.dimension.upper + "]" + " OF " + array_st.baseType + "\n";
        return result;



        return result;
    }

};
