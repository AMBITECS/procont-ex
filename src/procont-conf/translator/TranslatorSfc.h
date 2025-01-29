#ifndef TRANSLATORSFC_H
#define TRANSLATORSFC_H

#include "TranslatorIec.h"

class TranslatorSFC : public TranslatorIEC
{
    Q_OBJECT
public:
    TranslatorSFC();
    void Code_STgenerator(T_POU_BODY_SFC _sfc, QString &text_);

protected:
    void Code_STgenerator(T_POU pou_, QString &text_) override;

protected:
    void parseItem(T_POU *pou_);
    void parseItem(T_POU_BODY_SFC *_sfc);

    void Transition_STcode(quint64 _index, QString &text_);
    void Step_STcode(T_POU_SFC_ITEM _step, QString &text_, bool _is_initial = false);

    bool itemIsTransition(quint32 _id);
    bool itemIsStep(quint32 _id);
    bool itemIsSelConvergence(quint32 _id);
    bool itemIsSelDivergence(quint32 _id);
    bool itemIsSimConvergence(quint32 _id);
    bool itemIsSimDivergence(quint32 _id);

    bool checkIsChainUsed(T_POU *pou_, quint64 _index_item);

protected:
    QMap<quint64, T_POU_SFC_ITEM> _m_transition_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_step_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_action_block_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_selConvergence_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_selDivergence_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_simConvergence_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_simDivergence_item;
    QMap<quint64, T_POU_SFC_ITEM> _m_jump_step_item;

    QVector<T_POU_ACTION>         _m_action;

    quint32  _m_SFC_inline_counter;
};

#endif // TRANSLATORSFC_H
