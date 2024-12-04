//
// Created by artem on 10/20/24.
//

#include "CAddData.h"

CAddData::CAddData()
{
    m_data_list = new QList<CData*>();
}

CAddData::CAddData(const CAddData &src)
{
    m_data_list = new QList<CData*>();

    for (auto &alien : *src.m_data_list)
    {
        auto data = new CData(*alien);
        m_data_list->push_back(data);
    }
}

/*
CAddData::CAddData(CAddData &&tmp) noexcept
{
    m_data_list = tmp.m_data_list;
    tmp.m_data_list = nullptr;
}
*/
CAddData::CAddData(const QDomNode &node)
{
    m_data_list = new QList<CData*>();

    if (node.isNull())
    {
        return;
    }

    if (node.nodeName() != "addData")
    {
        throw std::runtime_error("in 'CAddData::CAddData(const QDomNode &node)' wrong node name");
    }

    if (!node.hasChildNodes())
    {
        return;
    }

    for (uint16_t i = 0; i < node.childNodes().count(); ++i)
    {
        auto child = node.childNodes().at(i);
        auto data = new CData(child);
        m_data_list->push_back(data);
    }
}

CAddData::~CAddData()
{
    /*if (!m_data_list)
    {
        return;
    }*/

    if (!m_data_list->empty())
        clean();
    delete m_data_list;
}

QDomNode CAddData::dom_node() const
{
    QDomDocument doc;
    auto root = doc.createElement("addData");

    for (auto &data : *m_data_list)
    {
        root.appendChild(data->dom_node());
    }

    return root;
}

QList<CData *> *CAddData::data_list()
{
    return m_data_list;
}

CData *CAddData::append_data(CData *data)
{
    if (!data)
    {
        return nullptr;
    }

    m_data_list->push_back(data);
    return m_data_list->back();
}

CData *CAddData::remove_data(CData *data)
{
    if (!data)
    {
        return nullptr;
    }

    uint16_t counter = 0;


    for (auto &item : *m_data_list)
    {
        if (item == data)
        {
            m_data_list->erase(m_data_list->cbegin() + counter);
            return data;
        }

        counter++;
    }

    return nullptr;
}

CData *CAddData::remove_data(const uint16_t &index)
{
    if (index >= m_data_list->count())
    {
        return nullptr;
    }

    CData *rem = m_data_list->at(index);
    m_data_list->erase(m_data_list->cbegin() + index);
    return rem;
}

CAddData &
CAddData::operator=(const CAddData &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    clean();

    for (auto &item : *rhs.m_data_list)
    {
        m_data_list->emplaceBack(new CData(*item));
    }

    return *this;
}

bool CAddData::is_empty() const
{
    return m_data_list->isEmpty();
}

void CAddData::clean()
{
    for (auto &item : *m_data_list)
    {
        delete item;
    }
    m_data_list->clear();
}
