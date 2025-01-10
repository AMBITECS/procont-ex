//
// Created by nechi on 19.11.2024.
//

#ifndef EDITORSD_CUSERTYPE_H
#define EDITORSD_CUSERTYPE_H

#include <QDomNode>
#include "editor/fbd/fbd/variables.h"


enum EUserTypes
{
    UT_ENUM,
    UT_ARRAY,
    UT_STRUCT,
    UT_ALIAS,
    UT_SUB_RANGE,
    UT_UNDEF,
    UT_COUNT
};

static const char *UserTypeName[UT_COUNT]
{
    "enum",
    "array",
    "struct",
    "alias",
    "subrangeSigned",
    "undefined"
};

class CUserType
{
public:
    CUserType() = default;
    CUserType(const CUserType &) = delete;
    CUserType(CUserType &&) = delete;
    virtual ~CUserType() = default;

    static CUserType * get_user_type(const EUserTypes &type, QDomNode *node = nullptr);
    static EUserTypes  get_user_type(const QDomNode &dom_node);

    [[nodiscard]] virtual QDomNode    dom_node() const = 0;

    [[nodiscard]] EUserTypes  type() const;
    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

protected:
    QString     m_name;
    EUserTypes  m_type{UT_UNDEF};

};


#endif //EDITORSD_CUSERTYPE_H
