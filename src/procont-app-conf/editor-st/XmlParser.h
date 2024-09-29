#pragma once

#include <QDomDocument>
#include <QList>

enum PouType
{
    program,
    functionalBlock,
};

struct SimpleValue
{
    QString value;
};

struct InitialValue
{
    SimpleValue simpleValue;
};

struct Variable
{
    QString name;
    QString type;
    InitialValue initialValue;
};

struct Interface
{
    QList<Variable> localVars;
    QList<Variable> inputVars;
    QList<Variable> outputVars;

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
};

class XmlParser/* : QObject*/
{
public:
    XmlParser();
    void importFromXml(QString filename);
    void exportToXml(QString filename);
    QStringList getFilesNames();
    QString getPouText(const int index);
    QString getAllText();
    QString getPouVarsText(const int index);
    QString getPouBodyText(const int index);
    QList<Pou>* getPous();

    static void typesFromFile(const QString &fileName);

    static QString getPouBodyText(const QDomNode& node);
    static QString getPouVarsText(const QDomNode& node);
    static QDomNode getPouNode(const QString& _text_vars, const QString&, const QDomNode &_parent);

private:
    // xml to text
    void traverseNode(const QDomNode& node, QList<Pou> & pous);
    QString convertDataToText();
    QString convertPouToText(const int index);
    void parsePOU(const QDomNode& node, QList<Pou> & pous);
    static void parseVariable(const QDomElement& domElementInterface, Interface& interface);
    // text to xml
    void convertTextToPou(const int index);
    static void parsePouProgram(Pou & pou, QDomNode & domNode);


private:
    static Pou XmlToPOU(const QDomNode& node);
    static Pou TxtToPOU(const QString& _text_vars, const QString& _text_body);
    static QDomNode getPouNode(Pou _pou, const QDomNode &_parent);

private:
    QList<Pou> pous;
    static QStringList types_list;
};
