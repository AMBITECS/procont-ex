//
// Created by nechi on 19.11.2024.
//

#include "CUserType.h"
#include "types/CEnum.h"
#include "types/CStruct.h"
#include "types/CArray.h"
#include "types/CAlias.h"
#include "types/CSubrange.h"

CUserType *CUserType::get_user_type(const EUserTypes &type, QDomNode *node)
{
    switch (type)
    {
        case EUserTypes::UT_ENUM:
            return dynamic_cast<CUserType*>(node == nullptr ? new CEnum() : new CEnum(*node));
        case EUserTypes::UT_STRUCT:
            return dynamic_cast<CUserType*>(node == nullptr? new CStruct() : new CStruct(*node));
        case EUserTypes::UT_ARRAY:
            return dynamic_cast<CUserType*>(node == nullptr ? new CArray() : new CArray(*node));
        case EUserTypes::UT_ALIAS:
            return dynamic_cast<CUserType*>(node == nullptr ? new CAlias() : new CAlias(*node));
        case EUserTypes::UT_SUB_RANGE:
            return dynamic_cast<CUserType*>(node == nullptr ? new CSubrange() : new CSubrange(*node));
        default:
            return nullptr;
    }
}

EUserTypes CUserType::type() const
{
    return m_type;
}

QString CUserType::name() const
{
    return m_name;
}

void CUserType::set_name(const QString &name)
{
    m_name = name;
}

EUserTypes CUserType::get_user_type(const QDomNode &dom_node)
{
    if (dom_node.isNull())
    {
        return EUserTypes::UT_UNDEF;
    }

    /// т.к. у этого недостандарта в пользовательских типах не предусмотрен тэг "alias" или хоть что-то, что говорило бы,
    /// что у нас нода типа "псевдоним", приходится делать так:
    auto bt = dom_node.namedItem(xmln::base_type);
    auto type_name = bt.firstChild().nodeName();

    int counter = 0;
    for (auto &name : UserTypeName)
    {
        if ((QString)name == type_name)
        {
            return (EUserTypes)counter;
        }
        counter++;
    }
    return EUserTypes::UT_ALIAS;
}
