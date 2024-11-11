#pragma once

#include <QDomDocument>
#include <QList>
#include "Variable.h"
#include <QTextStream>


struct Interface
{
    QList<Variable> localVars;
    QList<Variable> inputVars;
    QList<Variable> outputVars;
    QString returnType;
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

    void setReturnType(QString type)
    {
        returnType = type;
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

    static Pou parseXML(const QDomNode &node)
    {
        QDomNode domNode =
            node.firstChild();
        Pou pou;
        pou.name = node.toElement().attribute("name");
        pou.pouType = node.toElement().attribute("pouType");
        // qDebug() << pou.pouType;
        while(!domNode.isNull()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.tagName() =="interface")
                {
                    QDomNode nodeInterface = domElement.firstChild();
                    Interface interface;
                    while(!nodeInterface.isNull()) {
                        QDomElement domElementInterface = nodeInterface.toElement();
                        if(!domElementInterface.isNull()) {
                            //if(domElementInterface.tagName() =="localVars" || domElementInterface.tagName() =="inputVars" || domElementInterface.tagName() =="outputVars")
                            //{
                            if(domElementInterface.tagName() == "returnType")
                            {
                                interface.setReturnType(domElementInterface.firstChildElement().tagName());
                                // qDebug() << "return type = " << interface.returnType;
                            } else {
                                parseVariable(domElementInterface, interface);
                            }
                        }
                        nodeInterface = nodeInterface.nextSibling();
                    }

                    pou.interface = interface;
                }

                if (domElement.tagName() =="body") {
                    if (!domElement.firstChildElement().isNull() && domElement.firstChildElement().tagName() == "ST"){
                        pou.body.value = domElement.firstChildElement().text();
                    }
                }

            }

            domNode = domNode.nextSibling();
        }
        return pou;
    }

    static void parseVariable(const QDomElement &domElementInterface, Interface& interface)
    {

        QDomNode nodeLocalVars = domElementInterface.firstChild();
        QList<Variable> localVars;

        while(!nodeLocalVars.isNull()) {
            QDomElement domElementLocalVars = nodeLocalVars.toElement();
            if (!domElementLocalVars.isNull()){
                if(domElementLocalVars.tagName() =="variable"){
                    //QDomNode nodeVariable = domElementLocalVars.firstChild();
                    Variable variable = Variable::parseXML(domElementLocalVars);
                    localVars.append(variable);

                }
                if(domElementInterface.tagName() =="localVars")
                {
                    interface.localVars = localVars;
                } else if (domElementInterface.tagName() =="inputVars")
                {
                    interface.inputVars = localVars;
                } else if (domElementInterface.tagName() =="outputVars")
                {
                    interface.outputVars = localVars;
                }

            }
            nodeLocalVars = nodeLocalVars.nextSibling();
        }

    }

    static QDomNode getNode(Pou _pou, const QDomNode &_parent, const QStringList & types_list)
    {
        QDomDocument document = _parent.ownerDocument();

        QDomElement pou_elem = document.createElement("pou");

        pou_elem.setAttribute("name", _pou.name);

        QDomElement interface_elem = document.createElement("interface");
        pou_elem.appendChild(interface_elem);

        QDomElement returnType_elem = document.createElement("returnType");
        QDomElement returnTypeValue_elem = document.createElement(_pou.interface.returnType);
        returnType_elem.appendChild(returnTypeValue_elem);
        interface_elem.appendChild(returnType_elem);

        QDomElement localVars_elem = document.createElement("localVars");
        interface_elem.appendChild(localVars_elem);
        for (const auto var : _pou.interface.localVars)
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
            localVars_elem.appendChild(variable_elem);
        }

        QDomElement inputVars_elem = document.createElement("inputVars");
        interface_elem.appendChild(inputVars_elem);
        for (const auto var : _pou.interface.inputVars)
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
            inputVars_elem.appendChild(variable_elem);
        }

        QDomElement outputVars_elem = document.createElement("outputVars");
        interface_elem.appendChild(outputVars_elem);
        for (const auto var : _pou.interface.outputVars)
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
            outputVars_elem.appendChild(variable_elem);
        }

        QDomText newNodeText = document.createCDATASection(_pou.body.value); newNodeText.setData(_pou.body.value);
        QDomElement xhtml_elem = document.createElement("xhtml:p");
        xhtml_elem.setAttribute("xmlns", "http://www.w3.org/1999/xhtml");
        xhtml_elem.appendChild(newNodeText);
        QDomElement ST_elem = document.createElement("ST");
        ST_elem.appendChild(xhtml_elem);
        QDomElement body_elem = document.createElement("body");
        body_elem.appendChild(ST_elem);
        pou_elem.appendChild(body_elem);

        return pou_elem;
    }

    static Pou TxtToObj(const QString& _vars_text, const QString& _body_text)
    {
        Pou pou;
        QString vars_text = _vars_text;
        QTextStream varsStream(&vars_text);
        QString varType = "";
        QString returnType = "";
        while (true)
        {
            QString line = varsStream.readLine();

            if (line.isNull())
                break;
            else {
                Variable variable;
                line.replace(" ", "");
                line.replace("\t", "");
                if (line.contains("FUNCTION"))
                {
                    QStringList list_types = line.split(":");
                    if (list_types.size() > 1)
                    {
                        pou.interface.setReturnType(list_types.at(1));

                    }
                }
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
};
