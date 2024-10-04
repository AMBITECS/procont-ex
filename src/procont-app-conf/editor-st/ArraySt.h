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

    static ArraySt TxtToObj(const QString& line_input)
    {
        ArraySt result;
        QString line = line_input;

        if (line.isNull())
            return result;
        else if ((line.contains("ARRAY")))
        {

            line.replace(" ", "");
            line.replace("\t", "");

            QStringList list_values = line.split(":=");

            if (list_values.size() > 1)
            {
                QStringList list_types = list_values.at(0).split(":");
                if (list_types.size() > 1)
                {
                    QString dim_lower = list_types.at(1).mid(list_types.at(1).indexOf('[') + 1, list_types.at(1).indexOf('[') - 1).split("..").at(0);
                    QString dim_upper = list_types.at(1).mid(list_types.at(1).indexOf('[') + 1, list_types.at(1).indexOf('[') - 1).split("..").at(0);
                    result.dimension.lower = dim_lower;
                    result.dimension.upper = dim_upper;
                    result.baseType = list_types.at(1).split("OF").at(1);

                    qDebug() << "baseName: " << result.baseType << ", dimension lower: " << result.dimension.lower << ", dimension upper: " << result.dimension.upper;
                }
            }
        }
        return result;
    }

};


