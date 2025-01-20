//
// Created by nechi on 19.11.2024.
//

#ifndef EDITORSD_CSTRUCT_H
#define EDITORSD_CSTRUCT_H

#include "../CUserType.h"
#include "../../variables/CVariable.h"

class CStruct : public CUserType
{
public:
    CStruct();
    CStruct(const CStruct &);
    CStruct(CStruct &&) noexcept;
    explicit CStruct(const QDomNode &node);
    ~CStruct() override;

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] QDomNode  dom_node() const override;

    void  add_variable(const std::string &name, const EDefinedDataTypes &var_type, const std::string &init_value);
    void  remove_value(const std::string &name);

    std::vector<CVariable*> * variables();

private:
    std::vector<CVariable*> * m_variables;

};


#endif //EDITORSD_CSTRUCT_H
