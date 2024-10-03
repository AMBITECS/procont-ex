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

    static QString covertObjToString(const StructSt & structs)
    {
        QString result;
        result += QString("STRUCT") + "\n";
        for (const auto var : structs.vars)
        {
            result += "\t";
            result += Variable::covertObjToString(var);
        }
        result += "\t" + QString("END_STRUCT") + "\n";
        return result;
    }

    static StructSt TxtToObj(const QString& _vars_text)
    {
        StructSt result;
        QString vars_text = _vars_text;
        QTextStream varsStream(&vars_text);
        bool start_struct = false;
        while (true)
        {
            QString line = varsStream.readLine();

            if (line.isNull())
                break;
            else if ((line.contains("STRUCT")))
            {
                start_struct = true;
                break;
            } else if (line.contains("END_STRUCT"))
            {
                start_struct = false;
                break;
            }
            if (start_struct) {
                Variable variable;
                line.replace(" ", "");
                line.replace("\t", "");

                QStringList list_values = line.split(":=");

                if (list_values.size() > 1)
                {
                    QStringList list_types = list_values.at(0).split(":");
                    if (list_types.size() > 1)
                    {
                        variable.name = list_types.at(0);
                        variable.type = list_types.at(1);
                        variable.initialValue.simpleValue.value = list_values.at(1);
                        result.vars.append(variable);

                    } else {
                        variable.name = list_values.at(0);
                        variable.type = list_values.at(1);
                        result.vars.append(variable);
                    }
                } else {
                    QStringList list_types = list_values.at(0).split(":");
                    if (list_types.size() > 1) {
                        variable.name = list_types.at(0);
                        variable.type = list_types.at(1);
                        result.vars.append(variable);
                    }
                }
            }
        }

        return result;
    }

};
