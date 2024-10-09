#ifndef FBDTRANSLATOR_H
#define FBDTRANSLATOR_H

#include <QString>
#include <QVector>

#include "XmlParser.h"

class FbdTranslator
{
public:
    explicit FbdTranslator() = default;

public:
    static QString getSTCode_types(const QDomNode &node_);
    static QString getSTCode_instances(const QDomNode &node_);

public:
    QString getSTCode_pou(const QDomNode &node_);

protected:
    static QString getSTCode_type(const QDomNode &node_);
    static QString UDT_STgenerator(const T_UDT &udt_);
    static QString INSTANCES_STgenerator(const T_INSTANCES &inst_);
    QString POU_STgenerator(const T_POU &pou_);

    void Block_STgenerator(T_POU_FBD_ITEM_SHORT _block, QString &text_);
    void Func_STgenerator(T_POU_FBD_ITEM_SHORT _func, QString &text_);
    void Var_STgenerator(T_POU_FBD_ITEM_SHORT _var, QString &text_);

protected:
    QString getTypeByVar(const T_POU &pou_, QString _var_name);

    void parseItem(const T_POU &pou_);

    void prepareConnectContinuation();
    QString prepareLocalVar(const T_POU &pou_);
    void prepareBlock();
    void prepareFuncTempVar();
    void prepareFunc();
    void prepareVar();
    void prepareVarType();

    bool itemIsBlock(quint32 _id);
    bool itemIsFunc(quint32 _id);
    bool itemIsInVar(quint32 _id);
    bool itemIsOutVar(quint32 _id);
    bool itemIsInOutVar(quint32 _id);
    bool itemIsConnect(quint32 _id);
    bool itemIsContinuation(quint32 _id);

    quint32 linkConnect(quint32 _connect_id);

protected:
    QMap<quint64, T_POU_FBD_ITEM> _m_pou_item;

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_block_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_func_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_in_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_in_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_connect_item;

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_continuation_item;

    QMultiMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_execution_order_item;

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_generator_item;
};

#endif // FBDTRANSLATOR_H
