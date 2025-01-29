//
// Created by artem on 10/23/24.
//

#include "CInline.h"

CInline::CInline()
= default;

CInline::CInline(const CInline &other)
{
    *this = other;
}

CInline::CInline(CInline &&other) noexcept
    : m_worksheet_name(std::move(other.m_worksheet_name))
    , m_global_id(std::move(other.m_global_id))
    , m_document(other.m_document)
    , m_add_data(std::move(other.m_add_data))
    , m_inline_type(other.m_inline_type)
    , m_inline_value(other.m_inline_value)
{}

CInline::CInline(const QDomNode &dom_node)
{
    if (dom_node.hasAttributes())
    {
        m_worksheet_name    = dom_node.attributes().namedItem("WorksheetName").toAttr().value();
        m_global_id         = dom_node.attributes().namedItem("globalId").toAttr().value();
    }

    m_add_data  = CAddData(dom_node.namedItem("addData"));
    m_document  = CDocumentation(dom_node.namedItem("documentation"));

    for (uint8_t i = 0; i < dom_node.childNodes().count(); ++i)
    {
        QDomNode child = dom_node.childNodes().at(i);

        if (!define_inline_type(child))
        {
            continue;
        }

        m_inline_value = child;
        break;
    }
}

CInline::~CInline()
= default;

CInline &CInline::operator=(const CInline &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_worksheet_name    = other.m_worksheet_name;
    m_global_id         = other.m_global_id;
    m_add_data          = other.m_add_data;
    m_document          = other.m_document;
    m_inline_type       = other.m_inline_type;
    m_inline_value      = other.m_inline_value;

    return *this;
}

QDomNode CInline::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("inline");

    if (!m_worksheet_name.isEmpty())
    {
        root.setAttribute("WorksheetName", m_worksheet_name);
    }

    if (!m_global_id.isEmpty())
    {
        root.setAttribute("globalId", m_global_id);
    }

    root.appendChild(m_inline_value);

    if (!m_add_data.is_empty())
    {
        root.appendChild(m_add_data.dom_node());
    }

    if(!m_document.is_empty())
    {
        root.appendChild(m_document.dom_node());
    }

    return root;
}

QString CInline::worksheet_name() const
{
    return m_worksheet_name;
}

void CInline::set_worksheet_name(const QString &name)
{
    m_worksheet_name = name;
}

QString CInline::global_id() const
{
    return m_global_id;
}

void CInline::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CAddData *CInline::add_data()
{
    return &m_add_data;
}

CDocumentation *CInline::documentation()
{
    return &m_document;
}

bool CInline::define_inline_type(const QDomNode &node)
{
    QString n_name = node.nodeName();

    int counter = 0;

    for (auto &name : body_types_names)
    {
        if (n_name == name)
        {
            m_inline_type = (EBodyType)counter;
            return true;
        }
        counter++;
    }

    return false;
}

bool CInline::is_empty() const
{
    bool  res   = m_worksheet_name.isEmpty() &&
                  m_global_id.isEmpty() &&
                  m_add_data.is_empty() &&
                  m_document.is_empty() &&
                  m_inline_type == BT_COUNT &&
                  !m_inline_value.hasAttributes();
    return res;
}
