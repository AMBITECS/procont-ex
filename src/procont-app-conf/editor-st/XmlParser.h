#pragma once

#include <QDomDocument>
#include <QList>

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
    // text to xml
    void convertTextToPou(const int index);

private:
    static Pou XmlToPOU(const QDomNode& node);
    static Pou TxtToPOU(const QString& _text_vars, const QString& _text_body);
    static QDomNode getPouNode(Pou _pou, const QDomNode &_parent);

private:
    QList<Pou> pous;
    static QStringList types_list;
};
