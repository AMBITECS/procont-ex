//
// Created by artem on 10/20/24.
//

#include "CAddDataInfo.h"

CAddDataInfo::CAddDataInfo()
{
    m_info_list = new QList<CInfo*>();
}

CAddDataInfo::CAddDataInfo(const CAddDataInfo &src)
{
    m_info_list = new QList<CInfo*>(*src.m_info_list);
}

CAddDataInfo::CAddDataInfo(const QDomNode &node)
{
    m_info_list = new QList<CInfo*>();

    if (!node.hasChildNodes())
    {
        return;
    }

    for (int ind = 0; ind < node.childNodes().count(); ++ind)
    {
        auto child = node.childNodes().at(ind);

        auto info = new CInfo(child);
        m_info_list->push_back(info);
    }
}

CAddDataInfo::CAddDataInfo(CAddDataInfo && tmp) noexcept
{
    m_info_list = tmp.m_info_list;
    tmp.m_info_list = nullptr;
}

CAddDataInfo::~CAddDataInfo()
{
    if (!m_info_list)
    {
        return;
    }

    clean();
    delete m_info_list;
}

QDomNode CAddDataInfo::dom_node() const
{
    QDomDocument doc;
    auto elem = doc.createElement("addDataInfo");

    for (auto &child : *m_info_list)
    {
        auto dom_child = child->dom_node();
        elem.appendChild(dom_child);
    }

    return elem;
}

QList<CInfo *> *CAddDataInfo::info_list()
{
    return m_info_list;
}

CInfo *CAddDataInfo::append_info(CInfo *info)
{
    if (info)
    {
        m_info_list->push_back(info);
    }
    return info;
}

CInfo *CAddDataInfo::remove_info(CInfo *info)
{
    int counter = 0;
    for (auto &item : *m_info_list)
    {
        if (item == info)
        {
            m_info_list->erase(m_info_list->begin() + counter);
            return info;
        }
        counter++;
    }

    return nullptr;
}

CInfo *CAddDataInfo::remove_info(const uint16_t &index)
{
    if (index >= m_info_list->count())
    {
        return nullptr;
    }

    CInfo   * for_delete = m_info_list->at(index);
    m_info_list->erase(m_info_list->begin() + index);

    return for_delete;
}

void CAddDataInfo::clean()
{
    for (auto &item : *m_info_list)
    {
        delete item;
    }
    m_info_list->clear();
}

bool CAddDataInfo::is_empty() const
{
    return m_info_list->isEmpty();
}
