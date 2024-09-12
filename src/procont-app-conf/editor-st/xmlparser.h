#pragma once
#include <QObject>
#include <QDomDocument>

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
};

class XmlParser : QObject
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
    void typesFromFile(const QString &fileName);


private:
    // xml to text
    void traverseNode(const QDomNode& node, QList<Pou> & pous);
    QString convertDataToText();
    QString convertPouToText(const int index);
    void parsePOU(const QDomNode& node, QList<Pou> & pous);

    // text to xml
    void convertTextToPou(const int index);



private:
    QList<Pou> pous;
    QStringList types_list;
};
