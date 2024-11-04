//
// Created by artem on 10/20/24.
//

#include "CBody.h"

CBody::CBody()
{
    m_diagram = new QDomNode();
    m_add_data = new CAddData();
    m_document = new CDocumentation();
}

CBody::CBody(const CBody &other)
{
    m_diagram = new QDomNode(*other.m_diagram);
    m_add_data = new CAddData(*other.m_add_data);
    m_document = new CDocumentation(*other.m_document);
    m_worksheet_name = other.m_worksheet_name;
    m_global_ID = other.m_global_ID;
}

CBody::CBody(CBody &&other) noexcept
{
    m_diagram = other.m_diagram;
    m_add_data = other.m_add_data;
    m_document = other.m_document;

    other.m_diagram = nullptr;
    other.m_add_data = nullptr;
    other.m_document = nullptr;

    m_worksheet_name = other.m_worksheet_name;
    m_global_ID = other.m_global_ID;
}

CBody::CBody(const QDomNode &dom_node)
{
    if (dom_node.nodeName() != "body")
    {
        throw std::runtime_error("in 'CBody::CBody(const QDomNode &dom_node)' node is not body.");
    }
    m_worksheet_name = dom_node.attributes().namedItem("WorksheetName").toAttr().value();
    m_global_ID = dom_node.attributes().namedItem("globalId").toAttr().value();
    m_add_data = new CAddData(dom_node.namedItem("addData"));
    m_document = new CDocumentation(dom_node.namedItem("documentation"));
    m_diagram = new QDomNode(dom_node);

    /// process body
    define_diagram_type();
    switch (m_body_type) {
        case EBodyType::BT_FBD:
            m_fbd_content = new CFbdContent(m_diagram->firstChild());
            break;
        default:
            break;
    }
}

CBody::~CBody()
{
    if (!m_document)
    {
        return;
    }

    delete m_diagram;
    delete m_document;
    delete m_add_data;
    delete m_fbd_content;
}

QString CBody::worksheet_name() const
{
    return m_worksheet_name;
}

void CBody::set_worksheet_name(const QString & worksheet_name)
{
    m_worksheet_name = worksheet_name;
}

QString CBody::global_id() const
{
    return m_global_ID;
}

void CBody::set_global_id(const QString &glob_id)
{
    m_global_ID = glob_id;
}

CAddData *CBody::add_data()
{
    return m_add_data;
}

CDocumentation *CBody::documentation()
{
    return m_document;
}

EBodyType CBody::diagram_lang() const
{
    return m_body_type;
}

QString CBody::diagram_lang_str() const
{
    if (m_body_type == EBodyType::BT_COUNT)
    {
        return "UNDEF";
    }
    return body_types_names[m_body_type];
}

QDomNode CBody::diagram() const
{
    return *m_diagram;
}

QDomNode CBody::body_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("body");
    if (!m_worksheet_name.isEmpty())
    {
        root.setAttribute("WorksheetName", m_worksheet_name);
    }
    if (!m_global_ID.isEmpty())
    {
        root.setAttribute("globalId", m_global_ID);
    }

    if (!m_diagram->isNull())
    {
        root.appendChild(*m_diagram);
    }

    if (!m_add_data->is_empty())
    {
        root.appendChild(m_add_data->dom_node());
    }

    if (!m_document->is_empty())
    {
        root.appendChild(m_document->dom_node());
    }

    return root;
}

CFbdContent *CBody::fbd_content()
{
    return m_fbd_content;
}

CStContent *CBody::st_content()
{
    return m_st_content;
}

CLdContent *CBody::ld_content()
{
    return m_ld_content;
}

CCfcContent *CBody::cfc_content()
{
    return m_cfc_content;
}

CSfcContent *CBody::sfc_content()
{
    return m_sfc_content;
}

void CBody::add_fbd_diagram()
{
    delete m_fbd_content;
    m_fbd_content = new CFbdContent();
}

void CBody::define_diagram_type()
{
    if (!m_diagram->hasChildNodes()) {
        return;
    }

    QString d_type = m_diagram->firstChild().nodeName();

    int i = 0;
    m_body_type = EBodyType::BT_COUNT;

    for (auto &name : body_types_names)
    {
        if (name == d_type)
        {
            m_body_type = (EBodyType)i;
            break;
        }
        i++;
    }
}
