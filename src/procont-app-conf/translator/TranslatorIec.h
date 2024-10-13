#ifndef TRANSLATORIEC_H
#define TRANSLATORIEC_H

#include "XmlParser.h"

class TranslatorIEC
{
public:
    TranslatorIEC();

public:
    static QString getSTCode_types(const QDomNode &node_);

    static QString getSTCode_instances(const QDomNode &node_);

    QString getSTCode_pou(const QDomNode &node_);

protected:
    static QString getSTCode_type(const QDomNode &node_);
    static QString UDT_STgenerator(const T_UDT &udt_);

    static QString INSTANCES_STgenerator(const T_INSTANCES &inst_);

    void Program_STgenerator(T_POU &pou_, QString &text_);

    void ProgramCode_STgenerator(T_POU &pou_, QString &text_);

    virtual void ProgramCode_Program_STgenerator(T_POU &pou_, QString &text_);
    virtual void ProgramCode_Function_STgenerator(T_POU &pou_, QString &text_);
    virtual void ProgramCode_FunctionBlock_STgenerator(T_POU &pou_, QString &text_);

    void parseFBDitem(const T_POU &pou_);

    void AllVarFBD_STgenerator(T_POU &pou_, QString &text_);
    void prepareAllRetainVar(T_POU &pou_, QString &);
    void prepareAllNonRetainVar(T_POU &pou_, QString &);
    void prepareAllConstantVar(T_POU &pou_, QString &);

    static QString getTypeByVar(const T_POU &pou_, QString _var_name);

protected:

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_in_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_in_out_var_item;

    QMap<quint64, T_POU_FBD_ITEM>       _m_pou_FBD_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_block_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_func_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_connect_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_continuation_item;
};

#endif // TRANSLATORIEC_H
