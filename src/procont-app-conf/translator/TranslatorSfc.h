#ifndef TRANSLATORSFC_H
#define TRANSLATORSFC_H

#include "XmlParser.h"

#include "TranslatorIec.h"

class TranslatorSFC : public TranslatorIEC
{
public:
    TranslatorSFC();

protected:
    void ProgramCode_Program_STgenerator(T_POU &pou_, QString &text_) override;
    void ProgramCode_Function_STgenerator(T_POU &pou_, QString &text_) override;
    void ProgramCode_FunctionBlock_STgenerator(T_POU &pou_, QString &text_) override;

protected:
    void parseSFCitem(const T_POU &pou_);

    void AllVarSFC_STgenerator(T_POU &pou_, QString &text_);

    void TransactionSFC_STcode(T_POU_SFC_ITEM _transaction, QString &text_);
    void InitialStepSFC_STcode(T_POU_SFC_ITEM _step, QString &text_);
    void StepSFC_STcode(T_POU_SFC_ITEM _step, QString &text_);

protected:
    QVector<T_POU_SFC_ITEM> _m_pou_SFC_transition_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_pou_SFC_all_item;

    quint32  _m_SFC_inline_counter;
    quint32  _m_SFC_localId_start;
};

#endif // TRANSLATORSFC_H
