#ifndef XMLPARSER_H
#define XMLPARSER_H

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include <QObject>
#include <QFile>
#include <QDir>
#include <QVector>
#include <QDomDocument>

#include "GlobalType.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#define ARRAY_SIZE(a) int(sizeof(a) / sizeof(a[0]))

typedef bool(*PROJECT_SECTION_PARSER)(QDomNode _node);

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct{
    QString _name;
}T_PROJECT_SECTION_NAME;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class PLCopenXmlParser : public QObject
{
    Q_OBJECT
public:
    explicit PLCopenXmlParser(QObject *parent = nullptr);

public:
    static bool parsePOU(const QDomNode &node_, T_POU * data_);

public:
    bool setXmlFile(QString _xml_file);
    bool setNode(const QDomNode & node_);

    bool POU(quint32 _index, T_POU *_pou);
    bool UDT(quint32 _index, T_UDT *_udt);
    bool INSTANCES(T_INSTANCES *_inst);

protected:
    bool readXmlFile();
    bool writeXmlFile();

    bool fileHeaderParser(QDomNode _node);
    bool contentHeaderParser(QDomNode _node);
    bool typesParser(QDomNode _node);
    bool instancesParser(QDomNode _node);

    void checkPOUattr(QDomNode _node, T_POU *_pou);

    static void checkPOUinterface(QDomNode _node, T_POU *_pou);
    static void checkPOUbody(QDomNode _node, T_POU *_pou);
    static void checkPOUdocumentation(QDomNode _node, T_POU *_pou);

    static void checkPOUinterfaceLocalVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceGlobalVar(QDomNode _node, T_POU *_pou);

    static void checkPOUbodyFBD(QDomNode _node, T_POU *_pou);
    static void checkPOUbodyST(QDomNode _node, T_POU *_pou);
    static void checkPOUbodySFC(QDomNode _node, T_POU *_pou);

    static void checkPOUbodyFBD_block(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_in_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_out_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_in_out_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_connector(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_continuation(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_comment(QDomNode _node, T_POU_FBD_ITEM *_item);

    bool checkRedifinitionBaseType(QDomNode _node, T_UDT *_udt);

protected:
    QString         _m_xml_file;
    QFile           _m_file;

    QDomDocument    _m_doc;

    QDomNode        _m_pou_node;
    QDomNode        _m_user_data_type_node;
    QDomNode        _m_instances_node;

protected:
    T_PROJECT_SECTION_NAME PROJECT_SECTION_NAME[10];
};

#endif // XMLPARSER_H
