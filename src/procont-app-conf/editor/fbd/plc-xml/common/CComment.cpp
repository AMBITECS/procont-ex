//
// Created by artem on 10/26/24.
//

#include "CComment.h"

CComment::CComment()
= default;

CComment::CComment(const CComment &other)
= default;

CComment::CComment(const QDomNode &dom_node)
{
    m_local_id  = dom_node.attributes().namedItem("localId").toAttr().value().toULongLong();
    m_width     = dom_node.attributes().namedItem("width").toAttr().value().toFloat();
    m_height    = dom_node.attributes().namedItem("height").toAttr().value().toFloat();
    m_global_id = dom_node.attributes().namedItem("globalId").toAttr().value();

    m_position  = CPosition(dom_node.namedItem("position"));
    explode_content(dom_node.namedItem("content"));
    m_add_data  = CAddData(dom_node.namedItem("addData"));
    m_documentation = CDocumentation(dom_node.namedItem("documentation"));
}

CComment::~CComment()
= default;

CComment &CComment::operator=(const CComment &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    m_local_id = rhs.m_local_id;
    m_width= rhs.m_width;
    m_global_id = rhs.m_global_id;
    m_position = rhs.m_position;
    m_content = rhs.m_content;
    m_add_data = rhs.m_add_data;
    m_documentation = rhs.m_documentation;

    return *this;
}

QDomNode CComment::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("comment");
    root.appendChild(m_position.dom_node());
    root.appendChild(assemble_content());
    if (!m_add_data.is_empty())
        root.appendChild(m_add_data.dom_node());
    if (!m_documentation.is_empty())
        root.appendChild(m_documentation.dom_node());

    return root;
}

uint64_t CComment::local_id() const
{
    return m_local_id;
}

void CComment::set_local_id(const uint64_t &locId)
{
    m_local_id = locId;
}

float CComment::width() const
{
    return m_width;
}

void CComment::set_width(const float &width)
{
    m_width = width;
}

float CComment::height() const
{
    return m_height;
}

void CComment::set_height(const float &height)
{
    m_height = height;
}

QString CComment::global_id() const
{
    return m_global_id;
}

void CComment::set_global_id(const QString &glob_id)
{
    m_global_id = glob_id;
}

CPosition *CComment::position()
{
    return &m_position;
}

QString CComment::content() const
{
    return m_content;
}

void CComment::set_content(const QString &content)
{
    m_content = content;
}

CAddData *CComment::add_data()
{
    return &m_add_data;
}

CDocumentation *CComment::documentation()
{
    return &m_documentation;
}

void CComment::explode_content(const QDomNode &node)
{
    auto cdata = node.namedItem("xhtml:p").firstChild().toCDATASection();
    m_content = cdata.data();
}

QDomNode CComment::assemble_content() const
{
    QDomDocument doc;
    QDomElement element = doc.createElement("content");
    QDomElement xhtml = doc.createElement("xhtml:p");
    QDomCDATASection cdata = doc.createCDATASection("xhtml:p");
    cdata.setData(m_content);

    xhtml.appendChild(cdata);
    element.appendChild(xhtml);
    return element;
}
