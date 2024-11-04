#ifndef TRANSLATORFBD_H
#define TRANSLATORFBD_H

#include "TranslatorIec.h"

class TranslatorFBD : public TranslatorIEC
{
    Q_OBJECT
public:
    TranslatorFBD();
    void Code_STgenerator(T_POU_BODY_FBD _fbd, QString &text_);

protected:
    void Code_STgenerator(T_POU pou_, QString &text_) override;

protected:
    void parseItem(T_POU *pou_);
    void parseItem(T_POU_BODY_FBD *_fbd);

    void prepareConnectContinuation();
    void prepareBlock();
    void prepareFuncTempVar();
    void prepareFunc();
    void prepareVar();
    void prepareVarType();

    void Block_STcode(T_POU_FBD_ITEM_SHORT _block, QString &text_);
    void Func_STcode(T_POU_FBD_ITEM_SHORT _func, QString &text_);
    void Var_STcode(T_POU_FBD_ITEM_SHORT _var, QString &text_);

    bool itemIsBlock(quint32 _id);
    bool itemIsFunc(quint32 _id);
    bool itemIsInVar(quint32 _id);
    bool itemIsOutVar(quint32 _id);
    bool itemIsInOutVar(quint32 _id);
    bool itemIsConnect(quint32 _id);
    bool itemIsContinuation(quint32 _id);

    quint32 linkConnect(quint32 _connect_id);

protected:
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_in_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_in_out_var_item;

    QMap<quint64, T_POU_FBD_ITEM>       _m_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_block_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_func_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_connect_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_continuation_item;

    QMultiMap<quint64, T_POU_FBD_ITEM_SHORT> _m_execution_order_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_generator_item;
};

#endif // TRANSLATORFBD_H
