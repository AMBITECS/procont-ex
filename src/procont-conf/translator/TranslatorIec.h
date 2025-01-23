#ifndef TRANSLATORIEC_H
#define TRANSLATORIEC_H

#include <QObject>
#include "GlobalType.h"

class TranslatorIEC : public QObject
{
    Q_OBJECT
public:
    TranslatorIEC();

public:
    static QString getSTCode_types(const QDomNode &node_);

    static QString getSTCode_instances(const QDomNode &node_);

    QString getSTCode_pou(const QDomNode &node_);

protected:
    static QString getSTCode_type(const QDomNode &node_);
    static QString UDT_STgenerator(T_UDT *udt_);

    static QString INSTANCES_STgenerator(T_INSTANCES *inst_);

    virtual void Code_STgenerator(T_POU pou_, QString &text_) = 0;

protected:
    void AllVar_STgenerator(T_POU *pou_, QString &text_);
    void prepareAllRetainVar(T_POU *pou_, QString &);
    void prepareAllNonRetainVar(T_POU *pou_, QString &);
    void prepareAllConstantVar(T_POU *pou_, QString &);

    static QString getTypeByVar(const T_POU *pou_, QString _var_name);
};

#endif // TRANSLATORIEC_H
