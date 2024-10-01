#pragma once

#include <QDomDocument>
#include <QList>
#include "Variable.h"


class StructSt
{
public:
    QList<Variable> vars;
    static StructSt parseXML(QDomNode &nodeLocalVars)
    {
        StructSt result;
        QList<Variable> localVars;

        while(!nodeLocalVars.isNull()) {
            QDomElement domElementLocalVars = nodeLocalVars.toElement();
            if (!domElementLocalVars.isNull()){
                if(domElementLocalVars.tagName() =="variable"){
                    //QDomNode nodeVariable = domElementLocalVars.firstChild();
                    Variable variable = Variable::parseXML(domElementLocalVars);
                    localVars.append(variable);
                }
            }
            nodeLocalVars = nodeLocalVars.nextSibling();
        }
        result.vars = localVars;
        return result;
    }

};
