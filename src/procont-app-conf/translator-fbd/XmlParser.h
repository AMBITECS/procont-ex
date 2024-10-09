#ifndef XMLPARSER_H
#define XMLPARSER_H

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include <QFile>
#include <QDir>
#include <QVector>
#include <QDomDocument>

#include "GlobalType.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#define ARRAY_SIZE(a) int(sizeof(a) / sizeof(a[0]))

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class PLCopenXmlParser
{
public:
    explicit PLCopenXmlParser() = default;

public:
    static bool parseUDT(const QDomNode &node_, T_UDT * data_);
    static bool parsePOU(const QDomNode &node_, T_POU * data_);
    static bool parseINSTANCES(const QDomNode &node_, T_INSTANCES * data_);

protected:

    static void checkPOUattr(QDomNode _node, T_POU *_pou);

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

    static bool checkRedifinitionBaseType(QDomNode _node, T_UDT *_udt);
};

#endif // XMLPARSER_H
