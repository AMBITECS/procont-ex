#ifndef TRANSLATORFBD_H
#define TRANSLATORFBD_H

#include "XmlParser.h"

#include "TranslatorIec.h"

class TranslatorFBD : public TranslatorIEC
{
public:
    TranslatorFBD();

protected:
    void ProgramCode_Program_STgenerator(T_POU &pou_, QString &text_) override;
    void ProgramCode_Function_STgenerator(T_POU &pou_, QString &text_) override;
    void ProgramCode_FunctionBlock_STgenerator(T_POU &pou_, QString &text_) override;

protected:
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
    QMultiMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_execution_order_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_FBD_generator_item;
};

#endif // TRANSLATORFBD_H
