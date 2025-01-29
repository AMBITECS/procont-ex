//
// Created by artem on 10/22/24.
//

#include "CConnection.h"

CConnection::CConnection()
{
    m_positions = new QList<CPosition*>();
}

CConnection::CConnection(CConnection &&tmp) noexcept
    :   m_formal_param(std::move(tmp.m_formal_param))
    ,   m_global_id(std::move(tmp.m_global_id))
    ,   m_add_data(tmp.m_add_data)
    ,   m_ref_local_id(tmp.m_ref_local_id)
{
    m_positions = tmp.m_positions;
    tmp.m_positions = nullptr;
}

CConnection::CConnection(const CConnection &other)
{
    m_positions = new QList<CPosition*>();

    for (auto &alien : *other.m_positions)
    {
        auto pos = new CPosition(*alien);
        m_positions->push_back(pos);
    }

    m_formal_param = other.m_formal_param;
    m_global_id = other.m_global_id;
    m_add_data = other.m_add_data;
    m_ref_local_id = other.m_ref_local_id;
}

CConnection::CConnection(const QDomNode &dom_node)
{
    m_positions = new QList<CPosition*>();

    m_ref_local_id = dom_node.attributes().namedItem("refLocalId").toAttr().value().toLongLong();
    m_formal_param = dom_node.attributes().namedItem("formalParameter").toAttr().value();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    auto list = dom_node.childNodes();
    for (auto i = 0; i < list.count(); ++i)
    {
        auto child = list.at(i);

        if (child.nodeName() == "position")
        {
            m_positions->emplace_back(new CPosition(child));
        }

        if (child.nodeName() == "addData")
        {
            m_add_data = CAddData(child);
        }
    }
}

CConnection::~CConnection()
{
    if (m_positions == nullptr)
    {
        return;
    }

    for (auto &item : *m_positions)
    {
        delete item;
    }
    delete m_positions;
}

QDomNode CConnection::dom_node() const
{
    QDomDocument    doc;
    auto root = doc.createElement("connection");

    QString ref_id = QString::number(m_ref_local_id);
    root.setAttribute("refLocalId", ref_id);
    root.setAttribute("formalParameter", m_formal_param);

    if (!m_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_global_id);
    }

    for (auto &item : *m_positions)
    {
        root.appendChild(item->dom_node());
    }

    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }

    return root;
}

QString CConnection::global_id() const
{
    return m_global_id;
}

void CConnection::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

uint64_t CConnection::ref_local_id() const
{
    return m_ref_local_id;
}

void CConnection::set_ref_local_id(const uint64_t &ref_local_id)
{
    m_ref_local_id = ref_local_id;
}

QString CConnection::formal_parameter() const
{
    return m_formal_param;
}

void CConnection::set_formal_param(const QString &formal_param)
{
    m_formal_param = formal_param;
}

QList<CPosition *> *CConnection::positions()
{
    return m_positions;
}

CPosition *CConnection::add_position(const float &x, const float &y)
{
    m_positions->emplace_back(new CPosition(x, y));
    return m_positions->back();
}

CPosition *CConnection::add_position(const CPosition &position)
{
    m_positions->emplace_back(new CPosition(position));
    return m_positions->back();
}

CPosition *CConnection::add_position(CPosition *position)
{
    m_positions->push_back(position);
    return position;
}

uint16_t CConnection::positions_count() const
{
    return m_positions->count();
}

CPosition *CConnection::position_at(const uint16_t &index)
{
    if (index >= m_positions->count())
    {
        return nullptr;
    }

    return m_positions->at(index);
}

CPosition *CConnection::remove_position(const uint16_t &index)
{
    if (index >= m_positions->count())
    {
        return nullptr;
    }

    CPosition *trash = m_positions->at(index);
    m_positions->erase(m_positions->cbegin() + index);

    return trash;
}

CPosition *CConnection::remove_position(const CPosition &position)
{
    uint16_t counter = 0;
    for (auto &pos : *m_positions)
    {
        if (*pos == position)
        {
            auto trash = m_positions->at(counter);
            m_positions->erase(m_positions->cbegin() + counter);
            return trash;
        }

        counter++;
    }
    return nullptr;
}

CPosition *CConnection::remove_position(CPosition *position)
{
    uint16_t  counter = 0;

    for (auto &pos : *m_positions)
    {
        if (pos == position)
        {
            auto trash = m_positions->at(counter);
            m_positions->erase(m_positions->cbegin() + counter);
            return trash;
        }
        counter++;
    }
    return nullptr;
}

CPosition *CConnection::remove_position(const float &x, const float &y)
{
    auto trash = CPosition(x, y);

    int counter = 0;
    for (auto &item : *m_positions)
    {
        if (*item == trash)
        {
            auto res = m_positions->at(counter);
            m_positions->erase(m_positions->cbegin() + counter);
            return res;
        }
        counter++;
    }
    return nullptr;
}

CAddData *CConnection::add_data()
{
    return &m_add_data;
}
