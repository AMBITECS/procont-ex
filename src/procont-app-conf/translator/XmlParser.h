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

    bool setXmlFile(QString _xml_file);

    static bool parseUDT(const QDomNode &node_, T_UDT * data_);
    static bool parsePOU(const QDomNode &node_, T_POU * data_);
    static bool parseINSTANCES(const QDomNode &node_, T_INSTANCES * data_);

    bool UDT(quint32 _index, T_UDT *_udt);
    bool POU(quint32 _index, T_POU *_pou);
    bool INSTANCES(T_INSTANCES *_inst);

protected:
    bool readXmlFile();
    bool writeXmlFile();

    bool fileHeaderParser(QDomNode _node);
    bool contentHeaderParser(QDomNode _node);
    bool typesParser(QDomNode _node);
    bool instancesParser(QDomNode _node);

    static void checkPOUattr(QDomNode _node, T_POU *_pou);

    static void checkPOUinterface(QDomNode _node, T_POU *_pou);
    static void checkPOUbody(QDomNode _node, T_POU *_pou);
    static void checkPOUactions(QDomNode _node, T_POU *_pou);
    static void checkPOUdocumentation(QDomNode _node, T_POU *_pou);

    static void checkPOUinterfaceLocalVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceGlobalVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceInputVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceOutputVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceExternalVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceInOutVar(QDomNode _node, T_POU *_pou);
    static void checkPOUinterfaceTempVar(QDomNode _node, T_POU *_pou);

    static void checkPOUbodyFBD(QDomNode _node, T_POU *_pou);
    static void checkPOUbodyST(QDomNode _node, T_POU *_pou);
    static void checkPOUbodySFC(QDomNode _node, T_POU *_pou);
    static void checkPOUbodyIL(QDomNode _node, T_POU *_pou);
    static void checkPOUbodyLD(QDomNode _node, T_POU *_pou);

    static void checkPOUactionFBD(QDomNode _node, T_POU_ACTION *_action);
    static void checkPOUactionST(QDomNode _node, T_POU_ACTION *_action);
    static void checkPOUactionSFC(QDomNode _node, T_POU_ACTION *_action);
    static void checkPOUactionIL(QDomNode _node, T_POU_ACTION *_action);
    static void checkPOUactionLD(QDomNode _node, T_POU_ACTION *_action);

    static void checkPOUbodyFBD_block(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_in_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_out_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_in_out_var(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_connector(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_continuation(QDomNode _node, T_POU_FBD_ITEM *_item);
    static void checkPOUbodyFBD_comment(QDomNode _node, T_POU_FBD_ITEM *_item);

    static void checkPOUbodySFC_step(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_selection_divergence(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_selection_convergence(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_simultaneous_divergence(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_simultaneous_convergence(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_transition(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_action_block(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_jump_step(QDomNode _node, T_POU_SFC_ITEM *_item);
    static void checkPOUbodySFC_comment(QDomNode _node, T_POU_SFC_ITEM *_item);

    static void checkPOUbodyLD_block(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_in_var(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_out_var(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_in_out_var(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_connector(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_continuation(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_comment(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_contact(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_left_power_rail(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_right_power_rail(QDomNode _node, T_POU_LD_ITEM *_item);
    static void checkPOUbodyLD_coil(QDomNode _node, T_POU_LD_ITEM *_item);

    static bool checkRedifinitionBaseType(QDomNode _node, T_UDT *_udt);

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
