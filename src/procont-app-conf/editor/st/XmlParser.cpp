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
            traverseNode(domElement);
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
        project.appendChild(Pou::getNode(pou, project, types_list));

    xmlContent << document.toString();
}

QStringList XmlParser::getFilesNames()
{
    QStringList result;
    for (const auto & pou : pous)
    {
        result.append(pou.name);
    }
    for (const auto & dataType : dataTypes)
    {
        result.append(dataType.name);
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

void XmlParser::traverseNode(const QDomNode &node)
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
            if (domElement.tagName() == "dataType")
            {
                parseDataTypes(domNode, dataTypes);
            }
        }

        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

QString XmlParser::getPouBodyText(const QDomNode& node)
{
    if(node.isNotation())
        return {};

    if(node.nodeName() != "pou")
        return {};

    //return XmlToPOU(node).body.value + "\n";
    return Pou::parseXML(node).body.value + "\n";
}

QString XmlParser::getPouVarsText(const QDomNode& node)
{
    if(node.isNotation())
        return {};

    if(node.nodeName() != "pou")
        return {};

    QString result;

    //Pou pou = XmlToPOU(node);
    Pou pou = Pou::parseXML(node);

    if (pou.pouType == QString("program"))
    {
        result += "PROGRAM " + pou.name + "\n";
    }

    if (pou.pouType == QString("functionBlock"))
    {
        result += "FUNCTION_BLOCK " + pou.name + "\n";
    }

    if (pou.pouType == QString("function"))
    {
        result += "FUNCTION " + pou.name;

        if (pou.interface.returnType != QString(""))
        {
            result += " : " + pou.interface.returnType;
        }
        result += "\n";
    }

    if (!pou.interface.inputVars.empty())
    {
        result += QString("VAR_INPUT") + "\n";
        for (const auto & var : pou.interface.inputVars)
        {
            result += Variable::covertObjToString(var);
            /*
            result += "\t" + var.name + ": " + var.type;

            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
*/
        }
        result += QString("END_VAR") + "\n";
    }

    if (!pou.interface.outputVars.empty())
    {
        result += QString("VAR_OUTPUT") + "\n";
        for (const auto & var : pou.interface.outputVars)
        {
            result += Variable::covertObjToString(var);
            /*
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
*/
        }
        result += QString("END_VAR") + "\n";
    }

    if (!pou.interface.localVars.empty())
    {
        result += QString("VAR") + "\n";
        for (const auto & var : pou.interface.localVars)
        {
            result += Variable::covertObjToString(var);
            /*
            result += "\t" + var.name + ": " + var.type;
            if (var.initialValue.simpleValue.value != "")
            {
                result += " := " + var.initialValue.simpleValue.value + "\n";
            } else {
                result += "\n";
            }
*/
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
    return Pou::getNode(Pou::TxtToObj(_vars_text, _body_text), _parent, types_list);
}

QDomNode XmlParser::getDataTypeNode(const QString &_vars_text, const QString & _body_text, const QDomNode &_parent)
{
    return DataType::getNode(DataType::TxtToObj(_vars_text, _body_text), _parent, types_list);
}

void XmlParser::parsePOU(const QDomNode &node, QList<Pou> &pous)
{
    //pous.append(XmlToPOU(node));
    pous.append(Pou::parseXML(node));
}

void XmlParser::parseDataTypes(const QDomNode &node, QList<DataType> &dataTypes)
{
    dataTypes.append(DataType::parseXML(node));
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


QString XmlParser::getDataTypeText(const QDomNode &node)
{
    if(node.isNotation())
        return {};

    if(node.nodeName() != "dataType")
        return {};

    QString result;

    result += DataType::covertObjToString(DataType::parseXML(node));

    return result;
}
