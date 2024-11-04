//
// Created by artem on 27.10.24.
//

#ifndef XML_CBLOCKVAR_H
#define XML_CBLOCKVAR_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"

/**
 * @brief переменные внутри блока исходя из файла от IDE OpenPLC не соответствуют документации. Делаем на основе файла
 */
class CBlockVar
{
public:
    CBlockVar();
    CBlockVar(const CBlockVar & other);
    CBlockVar(const QDomNode & domNode);
    ~CBlockVar();

    QDomNode    dom_node() const;
    bool        is_empty() const;

    //CPosition   * position();
    QString     formal_parameter() const;
    void        set_formal_param(const QString &formal_param);
    CConnectionPointIn   * point_in();
    CConnectionPointOut  * point_out();

protected:

    QString m_formal_parameter;
    CConnectionPointIn  * m_point_in{nullptr};
    CConnectionPointOut * m_point_out{nullptr};
};


#endif //XML_CBLOCKVAR_H
