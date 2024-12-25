//
// Created by artem on 11/20/24.
//

#ifndef EDITORSD_CARRAY_H
#define EDITORSD_CARRAY_H

#include "../CUserType.h"
#include "../../includes.h"

class CArray : public  CUserType
{
public:
    CArray();
    CArray(const CArray &);
    explicit CArray(const QDomNode &);
    ~CArray() override;

    [[nodiscard]] QDomNode    dom_node() const override;

    [[nodiscard]] EDefinedDataTypes  base_type() const;
    [[nodiscard]] QString            base_type_name() const;
    void        set_base_type(const EDefinedDataTypes &type);
    void        set_base_type(const QString &type);

    [[nodiscard]] int         dimension_lower() const;
    void        set_dim_lower(const int &dimension);
    [[nodiscard]] int         dimension_upper() const;
    void        set_dim_upper(const int &upper);

private:
    EDefinedDataTypes   m_base_type{DDT_BOOL};

    int                 m_lower{0};
    int                 m_upper{0};

};


#endif //EDITORSD_CARRAY_H
