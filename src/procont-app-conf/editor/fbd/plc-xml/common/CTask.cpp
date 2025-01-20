//
// Created by artem on 12/26/24.
//

#include "CTask.h"
#include "editor/fbd/fbd/editors/CFilter.h"

CTask::CTask(CResource *parent)
{
    m_parent = parent;
}

CTask::CTask(CResource *parent, const QDomNode &node)
{
    m_parent = parent;

    if (node.nodeName() == "task")
    {
        auto val = node.attributes().namedItem("name").toAttr().value();

        if (!val.isEmpty() && !val.isNull() && !val.isDetached())
        {
            m_name = val.toStdString();
        }

        m_priority = node.attributes().namedItem("priority").toAttr().value().toInt();
        QString inter = node.attributes().namedItem("interval").toAttr().value();

        ETimeMeasure time_mes;
        uint32_t  value;
        value = CFilter::time_to_int(time_mes, inter);

        switch (time_mes)
        {
            case ET_MS:
                m_period = value;
                break;
            case ET_SEC:
                m_period = value * 1000;
                break;
            case ET_MINUTE:
                m_period = value * 60000;
                break;
            case ET_HOUR:
                m_period = value * 60 * 60000;
                break;
            default:
                m_period = value;
        }
    }
}

CTask::CTask(const CTask &other)
= default;

CTask::~CTask()
= default;

QDomNode CTask::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("task");

    root.setAttribute("name", m_name.c_str());
    root.setAttribute("priority", m_priority);
    root.setAttribute("interval", CFilter::int_to_time(ETimeMeasure::ET_MS, m_period));

    return root;
}

uint32_t CTask::interval_millisec() const
{
    return m_period;
}

void CTask::set_interval(const uint32_t &millisec)
{
    m_period = millisec;
}

uint16_t CTask::priority() const
{
    return m_priority;
}

void CTask::set_priority(const uint16_t &priority)
{
    m_priority = priority;
}

QString CTask::name() const
{
    return  m_name.empty() ? "" : m_name.c_str();
}

void CTask::set_name(const QString &name)
{
    if (!name.isEmpty() && !name.isNull() && !name.isDetached())
    {
        m_name = name.toStdString();
    }
}

CResource *CTask::parent()
{
    return m_parent;
}
