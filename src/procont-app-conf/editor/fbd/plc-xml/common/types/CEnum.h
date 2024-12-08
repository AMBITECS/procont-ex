//
// Created by nechi on 19.11.2024.
//

#ifndef EDITORSD_CENUM_H
#define EDITORSD_CENUM_H

#include "../CUserType.h"

class CEnum : public CUserType
{
public:
    CEnum();
    CEnum(const CEnum &);
    explicit CEnum(const QDomNode &node);
    CEnum(CEnum &&) noexcept;
    ~CEnum() override;

    bool  add_value(const std::string &value);
    void  remove_value(const std::string &value);

    [[nodiscard]] QDomNode    dom_node() const;

    std::vector<std::string> * values();

private:
    std::vector<std::string>    * m_values;
    int  find_value(const std::string & value);
};


#endif //EDITORSD_CENUM_H
