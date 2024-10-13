#pragma once

#include <QDomDocument>
#include <QList>
#include "CommonStTypes.h"

enum textBlockType
{
    VARS,
    BODY,
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

    static QString getDataTypeText(const QDomNode& node);
    static QString getPouBodyText(const QDomNode& node);
    static QString getPouVarsText(const QDomNode& node);
    static QDomNode getPouNode(const QString& _text_vars, const QString&, const QDomNode &_parent);
    static QDomNode getDataTypeNode(const QString& _text_vars, const QString&, const QDomNode &_parent);

private:
    // xml to text
    void traverseNode(const QDomNode& node);
    QString convertDataToText();
    QString convertPouToText(const int index);
    void parsePOU(const QDomNode& node, QList<Pou> & pous);
    void parseDataTypes(const QDomNode& node, QList<DataType> & dataTypes);
    static void parseVariable(const QDomElement& domElementInterface, Interface& interface);
    // text to xml
    void convertTextToPou(const int index);



private:
    static void parsePouProgram(Pou & pou, QDomNode & domNode);
    //static Pou XmlToPOU(const QDomNode& node);
    //static Pou TxtToPOU(const QString& _text_vars, const QString& _text_body);
    //static QDomNode getPouNode(Pou _pou, const QDomNode &_parent);

private:
    QList<Pou> pous;
    QList<DataType> dataTypes;
    static QStringList types_list;
};
