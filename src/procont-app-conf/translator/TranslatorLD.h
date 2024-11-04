#ifndef TRANSLATORLD_H
#define TRANSLATORLD_H


#include "TranslatorIec.h"

class TranslatorLD : public TranslatorIEC
{
    Q_OBJECT
public:
    TranslatorLD();
    void Code_STgenerator(T_POU_BODY_LD _ld, QString &text_);

protected:
    void Code_STgenerator(T_POU pou_, QString &text_) override;

protected:
    void parseItem(T_POU *pou_);
    void parseItem(T_POU_BODY_LD *_ld);

    void prepareConnectContinuation();
    void prepareBlock();
    void prepareFuncTempVar();
    void prepareFunc();
    void prepareVar();
    void prepareVarType();
    void prepareModificators();

    void Block_STcode(T_POU_LD_ITEM _block, QString &text_);
    void Func_STcode(T_POU_LD_ITEM _func, QString &text_);
    void Var_STcode(T_POU_LD_ITEM _var, QString &text_);

    bool itemIsBlock(quint32 _id);
    bool itemIsFunc(quint32 _id);
    bool itemIsInVar(quint32 _id);
    bool itemIsOutVar(quint32 _id);
    bool itemIsInOutVar(quint32 _id);
    bool itemIsConnect(quint32 _id);
    bool itemIsContinuation(quint32 _id);
    bool itemIsLeftPowerRail(quint32 _id);
    bool itemIsRightPowerRail(quint32 _id);
    bool itemIsContact(quint32 _id);
    bool itemIsCoil(quint32 _id);
    bool itemIsModifContact(quint32 _id);
    bool itemIsModifCoil(quint32 _id);

    quint32 linkConnect(qint32 _connect_id);
    quint32 linkContinuation(qint32 _connect_id, qint32 _new_connect_id);
    qint32 checkBlockConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var);
    qint32 checkFuncConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var);
    qint32 checkVarConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var);
    QString checkCoilConnectionChain(qint32 _var_id, qint32 &_next_id, QString _coil_type);

protected:
    QMap<quint64, T_POU_LD_ITEM>        _m_in_var_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_out_var_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_in_out_var_item;

    QMap<quint64, T_POU_LD_ITEM>        _m_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_block_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_func_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_connector_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_continuation_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_left_power_rail_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_right_power_rail_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_contact_item;
    QMap<quint64, T_MODIFICATOR>        _m_contact_modificator_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_coil_item;
    QMap<quint64, T_MODIFICATOR>        _m_coil_modificator_item;

    QMultiMap<quint64, T_POU_LD_ITEM>   _m_execution_order_item;
    QMap<quint64, T_POU_LD_ITEM>        _m_generator_item;
};

#endif // TRANSLATORLD_H
