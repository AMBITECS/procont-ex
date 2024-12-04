//
// Created by artem on 11/21/24.
//

#ifndef EDITORSD_CALIAS_H
#define EDITORSD_CALIAS_H

#include "../CUserType.h"
#include "../../includes.h"

class CAlias : public CUserType
{
public:
    CAlias();
    CAlias(const CAlias &);
    explicit CAlias(const QDomNode &);
    ~CAlias() override;

    QDomNode    dom_node() const;

    EDefinedDataTypes   base_type() const;
    QString             base_type_name() const;
    void    set_base_type(const QString &base_type_name);
    void    set_base_type(const EDefinedDataTypes &base_type);

private:
    EDefinedDataTypes   m_base_type{DDT_UNDEF};

};


#endif //EDITORSD_CALIAS_H
