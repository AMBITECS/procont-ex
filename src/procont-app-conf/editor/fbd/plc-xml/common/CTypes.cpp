//
// Created by artem on 12/16/24.
//

#include "CTypes.h"
#include "types/CArray.h"
#include "types/CAlias.h"
#include "types/CEnum.h"
#include "types/CSubrange.h"
#include "types/CStruct.h"
#include "editor/fbd/fbd/editors/CFilter.h"

CTypes::CTypes()
{
    m_user_types = new std::vector<CUserType*>();
    m_pous       = new std::vector<CPou*>();
}

CTypes::CTypes(const CTypes &src)
{
    m_user_types = new std::vector<CUserType*>();
    m_pous       = new std::vector<CPou*>();

    *this = src;
}

CTypes::CTypes(const QDomNode &node)
{
    m_user_types = new std::vector<CUserType*>();
    m_pous       = new std::vector<CPou*>();

    /// check node
    if (node.nodeName() != xmln::project_types)
    {
        return;
    }

    /// User types
    auto data_types_node = node.namedItem("dataTypes");

    for (int i = 0; i < data_types_node.childNodes().count(); i++)
    {
        auto ut_node = data_types_node.childNodes().at(i);
        auto ut_type = CUserType::get_user_type(ut_node);
        CUserType *uType = CUserType::get_user_type(ut_type, &ut_node);
        m_user_types->push_back(uType);
    }

    /// existing pous
    auto pous_node = node.namedItem("pous");

    for (int i = 0; i < pous_node.childNodes().count(); i++)
    {
        auto pou_node = pous_node.childNodes().at(i);
        auto pou = new CPou(pou_node);
        m_pous->push_back(pou);
    }
}

CTypes::~CTypes()
{
    for (auto &item : *m_pous)
    {
        delete item;
    }
    for (auto &item : *m_user_types)
    {
        delete item;
    }

    delete m_pous;
    delete m_user_types;
}

CTypes &CTypes::operator=(const CTypes &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    for (auto &ut : *m_user_types)
    {
        delete ut;
    }
    m_user_types->clear();

    CArray      *array, *n_array;
    CAlias      *alias, *n_alias;
    CEnum       *a_enum, *n_enum;
    CStruct     *a_struct, *n_struct;
    CSubrange   *a_subrange, *n_subrange;

    for (auto &ut : *rhs.m_user_types)
    {
        switch (ut->type()) {
            case EUserTypes::UT_ARRAY:
                array = dynamic_cast<CArray*>(ut);
                n_array = new CArray(*array);
                m_user_types->push_back(n_array);
                break;
            case EUserTypes::UT_ALIAS:
                alias = dynamic_cast<CAlias*>(ut);
                n_alias = new CAlias(*alias);
                m_user_types->push_back(n_alias);
                break;
            case EUserTypes::UT_ENUM:
                a_enum = dynamic_cast<CEnum*>(ut);
                n_enum = new CEnum(*a_enum);
                m_user_types->push_back(n_enum);
                break;
            case EUserTypes::UT_STRUCT:
                a_struct = dynamic_cast<CStruct*>(ut);
                n_struct = new CStruct(*a_struct);
                m_user_types->push_back(n_struct);
                break;
            case EUserTypes::UT_SUB_RANGE:
                a_subrange = dynamic_cast<CSubrange*>(ut);
                n_subrange = new CSubrange(*a_subrange);
                m_user_types->push_back(n_subrange);
                break;
            default:
                continue;
        }
    }

    for (auto &alien_pou : *rhs.m_pous)
    {
        auto pou = new CPou(*alien_pou);
        m_pous->push_back(pou);
    }

    return *this;
}

QDomNode CTypes::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement(xmln::project_types);

    /// user types
    auto types_node = doc.createElement("dataTypes");

    if (!m_user_types->empty())
    {
        for (auto &ut : *m_user_types)
        {
            types_node.appendChild(ut->dom_node());
        }
    }
    root.appendChild(types_node);

    /// POUs
    auto pous_node = doc.createElement("pous");

    if (!m_pous->empty())
    {
        for (auto &pou : *m_pous)
        {
            pous_node.appendChild(pou->dom_node());
        }
    }
    root.appendChild(pous_node);

    return root;
}

std::vector<CUserType *> *CTypes::user_types()
{
    return m_user_types;
}

std::vector<CPou *> *CTypes::pous()
{
    return m_pous;
}

CPou *CTypes::add_pou(const QString &pou_name)
{
    std::string pou_item_name = pou_name.toStdString();
    CFilter::capitalize_word(pou_item_name);

    for (auto &pou : *m_pous)
    {
        std::string name = pou->name().toStdString();
        CFilter::capitalize_word(name);

        if (pou_item_name == name)
        {
            return nullptr;
        }
    }

    auto pou = new CPou();
    pou->set_name(pou_name);
    m_pous->push_back(pou);

    return m_pous->back();
}

CPou *CTypes::add_pou(CPou *pou)
{
    if (!pou)
    {
        return nullptr;
    }

    m_pous->push_back(pou);
    return m_pous->back();
}

CPou *CTypes::add_pou(const QDomNode &pou_node)
{
    if (pou_node.isNull())
    {
        return nullptr;
    }

    auto pou = new CPou(pou_node);
    m_pous->push_back(pou);

    return m_pous->back();
}

CPou *CTypes::find_pou_by_name(const QString &pou_name)
{
    std::string pou_item_name = pou_name.toStdString();
    CFilter::capitalize_word(pou_item_name);

    for (auto &pou : *m_pous)
    {
        std::string p_name = pou->name().toStdString();
        CFilter::capitalize_word(p_name);

        if (p_name == pou_item_name)
        {
            return pou;
        }
    }
    return nullptr;
}

CPou *CTypes::remove_pou(CPou *pou)
{
    if (!pou)
    {
        return nullptr;
    }

    int counter = 0;
    for (auto &item : *m_pous)
    {
        if (item == pou)
        {
            m_pous->erase(m_pous->begin() + counter);
            return pou;
        }
        counter++;
    }
    return nullptr;
}

CUserType *CTypes::add_user_type(const EUserTypes &user_type)
{
    switch (user_type) {
        case EUserTypes::UT_ARRAY:
            m_user_types->emplace_back(new CArray());
            break;
        case EUserTypes::UT_ALIAS:
            m_user_types->emplace_back(new CAlias());
            break;
        case EUserTypes::UT_ENUM:
            m_user_types->emplace_back(new CEnum());
            break;
        case EUserTypes::UT_STRUCT:
            m_user_types->emplace_back(new CStruct());
            break;
        case EUserTypes::UT_SUB_RANGE:
            m_user_types->emplace_back(new CSubrange());
            break;
        default:
            return nullptr;
    }
    return m_user_types->back();
}

CUserType *CTypes::add_user_type(const QDomNode &node)
{
    if (node.isNull())
    {
        return nullptr;
    }
    QDomNode d_node = node;
    auto ut = CUserType::get_user_type(node);
    auto user_type = CUserType::get_user_type(ut, &d_node);

    m_user_types->push_back(user_type);
    return m_user_types->back();
}

CUserType *CTypes::find_user_type_by_name(const QString &name)
{
    if (name.isNull() || name.isEmpty())
    {
        return nullptr;
    }

    std::string item_name = name.toStdString();
    CFilter::capitalize_word(item_name);

    for (auto &ut : *m_user_types)
    {
        std::string type_name = ut->name().toStdString();
        CFilter::capitalize_word(type_name);

        if (type_name == item_name)
        {
            return ut;
        }
    }

    return nullptr;
}

CUserType *CTypes::remove_user_type(CUserType *user_type)
{
    if (!user_type)
    {
        return nullptr;
    }

    int counter = 0;

    for (auto &ut : *m_user_types)
    {
        if (ut == user_type)
        {
            m_user_types->erase(m_user_types->begin() + counter);
            return user_type;
        }
        counter++;
    }
    return nullptr;
}

bool CTypes::is_empty() const
{
    return m_pous->empty() && m_user_types->empty();
}
