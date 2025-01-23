//
// Created by artem on 10/23/24.
//

#include "CActionBlock.h"

CActionBlock::CActionBlock()
{
    m_actions = new QList<CAction*>();
}

CActionBlock::CActionBlock(const CActionBlock &other)
{
    m_actions = new QList<CAction*>(*other.m_actions);

    m_attr_global_id    = other.m_attr_global_id;
    m_attr_is_negated   = other.m_attr_is_negated;
    m_attr_width        = other.m_attr_width;
    m_attr_height       = other.m_attr_height;
    m_attr_exec_order   = other.m_attr_exec_order;
    m_position          = other.m_position;
    m_connection_point_in= other.m_connection_point_in;
    m_add_data          = other.m_add_data;
    m_document          = other.m_document;
}

CActionBlock::CActionBlock(CActionBlock &&other) noexcept
    : m_attr_global_id(std::move(other.m_attr_global_id))
{
    m_actions = other.m_actions;
    other.m_actions = nullptr;

    m_attr_is_negated   = other.m_attr_is_negated;
    m_attr_width        = other.m_attr_width;
    m_attr_height       = other.m_attr_height;
    m_attr_exec_order   = other.m_attr_exec_order;
    m_position          = other.m_position;
    m_connection_point_in= other.m_connection_point_in;
    m_add_data          = other.m_add_data;
    m_document          = other.m_document;
}

CActionBlock::CActionBlock(const QDomNode &dom_node)
{
    m_actions = new QList<CAction*>();

    m_attr_is_negated   = dom_node.attributes().namedItem("negated").toAttr().value().toInt();
    m_attr_global_id    = dom_node.attributes().namedItem("globalId").toAttr().value();
    m_attr_height       = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_attr_width        = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_attr_exec_order   = dom_node.attributes().namedItem("executionOrderId").toAttr().value().toLongLong();
    m_attr_local_id     = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();

    for (uint16_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);

        if (child.nodeName() == "position")
        {
            m_position = CPosition(child);
        }

        if (child.nodeName() == "connectionPointIn")
        {
            m_connection_point_in = CConnectionPointIn(child);
        }

        if (child.nodeName() == "action")
        {
            auto act = new CAction(child);
            m_actions->push_back(act);
        }

        if (child.nodeName() == "addData")
        {
            m_add_data = CAddData(child);
        }

        if (child.nodeName() == "documentation")
        {
            m_document = CDocumentation(child);
        }
    }
}

CActionBlock::~CActionBlock()
{
    if (!m_actions)
    {
        return;
    }

    for (auto &item : *m_actions)
    {
        delete item;
    }
    delete m_actions;
}

CActionBlock &CActionBlock::operator=(const CActionBlock &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete m_actions;
    m_actions = new QList<CAction*>(*other.m_actions);

    m_attr_global_id    = other.m_attr_global_id;
    m_attr_is_negated   = other.m_attr_is_negated;
    m_attr_width        = other.m_attr_width;
    m_attr_height       = other.m_attr_height;
    m_attr_exec_order   = other.m_attr_exec_order;
    m_position          = other.m_position;
    m_connection_point_in= other.m_connection_point_in;
    m_add_data          = other.m_add_data;
    m_document          = other.m_document;

    return *this;
}

QDomNode CActionBlock::dom_node() const
{
    return QDomNode();
}

uint64_t CActionBlock::local_id() const
{
    return 0;
}

void CActionBlock::set_local_id(const uint64_t &local_id)
{

}

bool CActionBlock::is_negated() const
{
    return false;
}

void CActionBlock::set_negated(const bool &negated)
{

}

float CActionBlock::width() const
{
    return 0;
}

void CActionBlock::set_width(const float &width)
{

}

float CActionBlock::height() const
{
    return 0;
}

void CActionBlock::set_height(const float &height)
{

}

uint64_t CActionBlock::exec_order_id() const
{
    return 0;
}

void CActionBlock::set_exec_order(const uint64_t &exec_order)
{

}

QString CActionBlock::global_id() const
{
    return QString();
}

void CActionBlock::set_global_id(const QString &glob_id)
{

}

QList<CAction *> *CActionBlock::actions()
{
    return nullptr;
}

CPosition *CActionBlock::position()
{
    return nullptr;
}

CAddData *CActionBlock::add_data()
{
    return nullptr;
}

CConnectionPointIn *CActionBlock::connection_point_in()
{
    return nullptr;
}

CDocumentation *CActionBlock::documentation()
{
    return nullptr;
}
