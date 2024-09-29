#include "XmlParser.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QApplication>
#include <QtAlgorithms>

QStringList XmlParser::types_list = {};

XmlParser::XmlParser() {}

void XmlParser::importFromXml(QString filename)
{
    pous.clear();
    QDomDocument domDoc;
    //QList<Pou> pous;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            traverseNode(domElement, pous);
        }
        file.close();
    }
}

void XmlParser::exportToXml(QString filename)
{
    QFile xmlFile(filename);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
        qDebug() << "Already opened or there is another issue";
        xmlFile.close();
    }
    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    //make the root element
    QDomElement project = document.createElement("project");
    //add it to document
    document.appendChild(project);

    for (const auto pou : pous)        
        project.appendChild(getPouNode(pou, project));

    xmlContent << document.toString();
}

QStringList XmlParser::getFilesNames()
{
    QStringList result;
    for (const auto & pou : pous)
    {
        result.append(pou.name);
    }
    return result;
}

QString XmlParser::getPouText(const int index)
{
    return convertPouToText(index);
}

QString XmlParser::getAllText()
{
    return convertDataToText();
}

QString XmlParser::getPouVarsText(const int index)
{
    QString result;



    result += "PROGRAM " + pous.at(index).name + "\n";

    if(!pous.at(index).interface.inputVars.empty())
    {
        result += QString("VAR_INPUT") + "\n";
        for (const auto & var : pous.at(index).interface.inputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    if(!pous.at(index).interface.outputVars.empty())
    {
        result += QString("VAR_OUTPUT") + "\n";
        for (const auto & var : pous.at(index).interface.outputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    if(!pous.at(index).interface.localVars.empty())
    {
        result += QString("VAR") + "\n";
        for (const auto & var : pous.at(index).interface.localVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    //result += QString("END_PROGRAM") + "\n";

    return result;
}

QString XmlParser::getPouBodyText(const int index)
{
    QString result;

    if (pous.at(index).body.value != "")
    {
        //result += "PROGRAM " + pous.at(index).name + "\n";
        result += pous.at(index).body.value + "\n";
        //result += QString("END_PROGRAM") + "\n";
    }

    return result;
}

QList<Pou> *XmlParser::getPous()
{
    return &pous;
}

void XmlParser::traverseNode(const QDomNode &node, QList<Pou> &pous)
{
    QDomNode domNode =
        node.firstChild();
    while(!domNode.isNull()) {
        QDomElement domElement = domNode.toElement();
        if(!domElement.isNull()) {
            if(domElement.tagName() =="pou")
            {
                parsePOU(domNode, pous);
            }
        }

        traverseNode(domNode, pous);
        domNode = domNode.nextSibling();
    }
}

QString XmlParser::getPouBodyText(const QDomNode& node)
{
    if(node.isNotation())
        return {};

    if(node.nodeName() != "pou")
        return {};

    return XmlToPOU(node).body.value + "\n";
}

QString XmlParser::getPouVarsText(const QDomNode& node)
{
    if(node.isNotation())
        return {};

    if(node.nodeName() != "pou")
        return {};

    QString result;

    Pou pou = XmlToPOU(node);

    if (pou.pouType == QString("program"))
    {
        result += "PROGRAM " + pou.name + "\n";
    }

    if (pou.pouType == QString("functionBlock"))
    {
        result += "FUNCTION_BLOCK " + pou.name + "\n";
    }

    if (!pou.interface.inputVars.empty())
    {
        result += QString("VAR_INPUT") + "\n";
        for (const auto & var : pou.interface.inputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    if (!pou.interface.outputVars.empty())
    {
        result += QString("VAR_OUTPUT") + "\n";
        for (const auto & var : pou.interface.outputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    if (!pou.interface.localVars.empty())
    {
        result += QString("VAR") + "\n";
        for (const auto & var : pou.interface.localVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    return result;
}

QString XmlParser::convertDataToText()
{
    QString result;

    for (const auto & pou : pous)
    {
        result += "PROGRAM " + pou.name + "\n";

        if (!pou.interface.localVars.empty())
        {
            result += QString("VAR") + "\n";
            for (const auto & var : pou.interface.localVars)
            {
                result += "\t" + var.name + ": " + var.type;
                if (var.initialValue.simpleValue.value != "")
                {
                    result += " := " + var.initialValue.simpleValue.value + "\n";
                } else {
                    result += "\n";
                }
            }
            result += QString("END_VAR") + "\n";
        }

        if (!pou.interface.inputVars.empty())
        {
            result += QString("VAR_INPUT") + "\n";
            for (const auto & var : pou.interface.inputVars)
            {
                result += "\t" + var.name + ": " + var.type;
                if (var.initialValue.simpleValue.value != "")
                {
                    result += " := " + var.initialValue.simpleValue.value + "\n";
                } else {
                    result += "\n";
                }
            }
            result += QString("END_VAR") + "\n";
        }

        if (!pou.interface.outputVars.empty())
        {
            result += QString("VAR_OUTPUT") + "\n";
            for (const auto & var : pou.interface.outputVars)
            {
                result += "\t" + var.name + ": " + var.type;
                if (var.initialValue.simpleValue.value != "")
                {
                    result += " := " + var.initialValue.simpleValue.value + "\n";
                } else {
                    result += "\n";
                }
            }
            result += QString("END_VAR") + "\n";
        }
        if (pou.body.value != "")
        {
            result += pou.body.value + "\n";
        }
        result += QString("END_PROGRAM") + "\n";
    }
    //out << result << "\n";

    //file.close();
    return result;
}

QString XmlParser::convertPouToText(const int index)
{
    QString result;

    result += "PROGRAM " + pous.at(index).name + "\n";

    if (!pous.at(index).interface.localVars.empty())
    {
        result += QString("VAR") + "\n";
        for (const auto & var : pous.at(index).interface.localVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }
    if (!pous.at(index).interface.inputVars.empty())
    {
        result += QString("VAR_INPUT") + "\n";
        for (const auto & var : pous.at(index).interface.inputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }
    if (!pous.at(index).interface.outputVars.empty())
    {
        result += QString("VAR_OUTPUT") + "\n";
        for (const auto & var : pous.at(index).interface.outputVars)
        {
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
        }
        result += QString("END_VAR") + "\n";
    }

    if (pous.at(index).body.value != "")
    {
        result += pous.at(index).body.value + "\n";
    }
    result += QString("END_PROGRAM") + "\n";

    return result;
}

QDomNode XmlParser::getPouNode(const QString& _vars_text, const QString& _body_text, const QDomNode &_parent)
{
    return getPouNode(TxtToPOU(_vars_text, _body_text), _parent);
}

QDomNode XmlParser::getPouNode(Pou _pou, const QDomNode &_parent)
{
    QDomDocument document = _parent.ownerDocument();

    QDomElement pou_elem = document.createElement("pou");

    pou_elem.setAttribute("name", _pou.name);

    QDomElement interface_elem = document.createElement("interface");
    pou_elem.appendChild(interface_elem);

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

Pou XmlParser::TxtToPOU(const QString& _vars_text, const QString& _body_text)
{
    Pou pou;
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
        }
    }
    pou.body.value = body;

    return pou;
}

Pou XmlParser::XmlToPOU(const QDomNode &node)
{
    QDomNode domNode =
        node.firstChild();
    Pou pou;
    pou.name = node.toElement().attribute("name");
    pou.pouType = node.toElement().attribute("pouType");

    parsePouProgram(pou, domNode);

    return pou;
}

void XmlParser::parsePOU(const QDomNode &node, QList<Pou> &pous)
{
    pous.append(XmlToPOU(node));
}

void XmlParser::parseVariable(const QDomElement &domElementInterface, Interface& interface)
{

        QDomNode nodeLocalVars = domElementInterface.firstChild();
        QList<Variable> localVars;

        while(!nodeLocalVars.isNull()) {
            QDomElement domElementLocalVars = nodeLocalVars.toElement();
            if (!domElementLocalVars.isNull()){
                if(domElementLocalVars.tagName() =="variable"){
                    QDomNode nodeVariable = domElementLocalVars.firstChild();
                    Variable variable;
                    variable.name = domElementLocalVars.attribute("name");
                    while(!nodeVariable.isNull()) {
                        QDomElement domElementVariable = nodeVariable.toElement();
                        if (!domElementVariable.isNull()){

                            if(domElementVariable.tagName() =="type"){
                                if (domElementVariable.firstChildElement().tagName() == QString("derived")){
                                    variable.type = domElementVariable.firstChildElement().attribute("name");
                                } else {
                                    variable.type = domElementVariable.firstChildElement().tagName();
                                }
                            }

                            if(domElementVariable.tagName() =="initialValue"){
                                QDomNode nodeInitialValue = domElementVariable.firstChild();
                                InitialValue initialValue;
                                while(!nodeInitialValue.isNull()) {
                                    QDomElement domElementInitialValue = nodeInitialValue.toElement();
                                    if (!domElementInitialValue.isNull()){
                                        if(domElementInitialValue.tagName() =="simpleValue"){
                                            SimpleValue simpleValue;
                                            simpleValue.value = domElementInitialValue.attribute("value");
                                            initialValue.simpleValue = simpleValue;
                                            variable.initialValue = initialValue;
                                        }
                                    }
                                    nodeInitialValue = nodeInitialValue.nextSibling();
                                }
                            }

                        }
                        nodeVariable = nodeVariable.nextSibling();
                    }
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

void XmlParser::parsePouProgram(Pou &pou, QDomNode &domNode)
{
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
                            parseVariable(domElementInterface, interface);

                       //}

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
}

void XmlParser::typesFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "NOt file open!!!!";
        return;
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            types_list << QString::fromUtf8(line.trimmed());
    }

    types_list.sort();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
}
