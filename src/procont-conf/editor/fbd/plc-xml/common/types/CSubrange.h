//
// Created by artem on 11/21/24.
//

#ifndef EDITORSD_CSUBRANGE_H
#define EDITORSD_CSUBRANGE_H

#include "../CUserType.h"
#include "../../includes.h"

class CSubrange : public CUserType
{
public:
    CSubrange();
    CSubrange(const CSubrange &);
    explicit CSubrange(const QDomNode &);
    ~CSubrange() override;

    [[nodiscard]] QDomNode dom_node() const override;

    [[nodiscard]] int     lower() const;
    void    set_lower(const int &lower);

    [[nodiscard]] int upper() const;
    void set_upper(const int &upper);

    [[nodiscard]] EDefinedDataTypes   base_type() const;
    [[nodiscard]] QString       base_type_name() const;
    void    set_base_type(const QString &base_type_name);
    void    set_base_type(const EDefinedDataTypes &base_type);

private:
    EDefinedDataTypes   m_base_type{DDT_UNDEF};
    QString             m_base_type_name;
    int     m_lower{0};
    int     m_upper{0};

    QString m_init_val;
};


#endif //EDITORSD_CSUBRANGE_H
