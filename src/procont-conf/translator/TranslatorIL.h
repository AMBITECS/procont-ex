#ifndef TRANSLATORIL_H
#define TRANSLATORIL_H


#include "TranslatorIec.h"

class TranslatorIL : public TranslatorIEC
{
    Q_OBJECT
public:
    TranslatorIL();
    void Code_STgenerator(T_POU_BODY_IL _il, QString &text_);

protected:
    void Code_STgenerator(T_POU pou_, QString &text_) override;

};

#endif // TRANSLATORIL_H
