//
// Created by artem on 10/20/24.
//

#include "CDocumentation.h"

CDocumentation::CDocumentation(const QDomNode &node)
{
    if (node.isNull())
    {
        return;
    }

    if (node.nodeName() != "documentation")
    {
        throw std::runtime_error("in 'CDocumentation::CDocumentation(const QDomNode &node)' wrong node name");
    }

    auto cdata = node.namedItem("xhtml:p").firstChild().toCDATASection();
    if (cdata.isCDATASection())
    {
        m_documentation = cdata.data();
    }
    else
    {
        m_documentation = node.firstChild().nodeValue();
    }
}

CDocumentation::CDocumentation()
= default;

CDocumentation::~CDocumentation()
= default;

QDomNode CDocumentation::dom_node() const
{
    if (m_documentation.isEmpty())
    {
        return {};
    }

    QDomDocument doc;
    QDomElement root = doc.createElement("documentation");

    auto xhtml = doc.createElement("xhtml:p");
    auto cdata = doc.createCDATASection("xhtml:p");
    cdata.setData(m_documentation);
    xhtml.appendChild(cdata);
    root.appendChild(xhtml);

    return root;
}

bool CDocumentation::is_empty() const
{
    return m_documentation.isEmpty();
}

CDocumentation::CDocumentation(const CDocumentation &other)
{
    m_documentation = other.m_documentation;
}

QString CDocumentation::documentation() const
{
    return m_documentation;
}

void CDocumentation::set_document(const QString &doc)
{
    m_documentation = doc;
}
