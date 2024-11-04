#ifndef TRANSLATORST_H
#define TRANSLATORST_H


#include "TranslatorIec.h"

class TranslatorST : public TranslatorIEC
{
    Q_OBJECT
public:
    TranslatorST();
    void Code_STgenerator(T_POU_BODY_ST _st, QString &text_);

protected:
    void Code_STgenerator(T_POU pou_, QString &text_) override;
};

#endif // TRANSLATORST_H
