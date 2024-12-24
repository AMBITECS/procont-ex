//
// Created by artem on 12/16/24.
//

#include "CProject.h"

CProject *  project{nullptr};

CProject *CProject::get_instance(const QDomNode &project_node)
{
    inst_count++;
    if (!project)
    {
        project = new CProject(project_node);
    }
    return project;
}

CProject::CProject()
{
    m_types = new CTypes(this);
}

CProject::CProject(const CProject &src)
{
    m_types = new CTypes(*src.m_types);

    m_company_name = src.m_company_name;
    m_content_header_name = src.m_content_header_name;
    m_version = src.m_version;
    m_project_name = src.m_project_name;
    m_creation_dt = src.m_creation_dt;
    m_modification_dt = src.m_modification_dt;

    m_xmlns = src.m_xmlns;
    m_xmlns_xsd = src.m_xmlns_xsd;
    m_xmlns_xhtml = src.m_xmlns_xhtml;
    m_xmlns_ns1 = src.m_xmlns_ns1;
}

CProject::CProject(const QDomNode &project_node)
{
    if (project_node.isNull())
    {
        m_types = new CTypes(this);
        return;
    }

    m_xmlns = project_node.attributes().namedItem("xmlns").toAttr().value();
    m_xmlns_xsd = project_node.attributes().namedItem("xmlns:xsd").toAttr().value();
    m_xmlns_xhtml = project_node.attributes().namedItem("xmlns:xhtml").toAttr().value();
    m_xmlns_ns1 = project_node.attributes().namedItem("xmlns:ns1").toAttr().value();

    QDomNode file_header = project_node.namedItem("fileHeader");
    if (!file_header.isNull())
    {
        process_file_header(file_header);
    }


    QDomNode content_header = project_node.namedItem("contentHeader");
    if (!content_header.isNull())
    {
        process_content_header(content_header);
    }


    QDomNode types = project_node.namedItem("types");
    if (!types.isNull())
    {
        m_types = new CTypes(types, this);
    }
    else
    {
        m_types = new CTypes(this);
    }


    //QDomNode instances = project_node.namedItem("instances");
}

CProject::~CProject()
{
    delete m_types;
    project = nullptr;
}

CTypes *CProject::types()
{
    return m_types;
}

//CContentHeader *CProject::content_header()
//{
//    return nullptr;
//}

QString CProject::company_name() const
{
    return m_company_name;
}

void CProject::set_company_name(const QString &name)
{
    m_company_name = name;
}

QString CProject::product_name() const
{
    return m_project_name;
}

void CProject::set_product_name(const QString &name)
{
    m_project_name = name;
}

QDateTime CProject::creation_date_time() const
{
    return m_creation_dt;
}

void CProject::set_creation_dt(const QDateTime &date_time)
{
    m_creation_dt = date_time;
}

QDateTime CProject::modification_date_time() const
{
    return m_modification_dt;
}

void CProject::set_modification_dt(const QDateTime &date_time)
{
    m_modification_dt = date_time;
}

QString CProject::project_version() const
{
    return m_version;
}

void CProject::set_project_version(const QString &version)
{
    m_version = version;
}

void CProject::process_file_header(const QDomNode &node)
{
    m_company_name = node.attributes().namedItem("companyName").toAttr().value();
    m_project_name = node.attributes().namedItem("productName").toAttr().value();
    m_version      = node.attributes().namedItem("productVersion").toAttr().value();
    QString creat_dt  = node.attributes().namedItem("creationDateTime").toAttr().value();

    m_creation_dt = QDateTime::fromString(creat_dt);
}

void CProject::process_content_header(const QDomNode &node)
{
    m_content_header_name = node.attributes().namedItem("name").toAttr().value();
    QString mod_dt = node.attributes().namedItem("modificationDateTime").toAttr().value();
    m_modification_dt = QDateTime::fromString(mod_dt);
}

QDomNode CProject::dom_node() const
{
    QDomDocument doc;
    QDomElement root = doc.createElement("project");
    root.setAttribute("xmlns", m_xmlns);
    root.setAttribute("xmlns:xsd", m_xmlns_xsd);
    root.setAttribute("xmlns:xhtml", m_xmlns_xhtml);
    root.setAttribute("xmlns:ns1", m_xmlns_ns1);

    QDomElement file_header;
    file_header.setAttribute("companyName", m_company_name);
    file_header.setAttribute("productName", m_project_name);
    file_header.setAttribute("productVersion", m_version);
    file_header.setAttribute("creationDateTime", m_creation_dt.toString());
    root.appendChild(file_header);

    QDomElement content_header;
    QDomNode coord_info = doc.createElement("coordinateInfo");
    content_header.setAttribute("name", m_content_header_name);
    content_header.setAttribute("modificationDateTime", m_modification_dt.toString());
    content_header.appendChild(coord_info);
    root.appendChild(content_header);

    if (!m_types->is_empty())
    {
        root.appendChild(m_types->dom_node());
    }

    return root;
}

void CProject::Delete()
{
    inst_count--;
    if (inst_count > 1)
    {
        return;
    }
    delete this;
}

bool CProject::is_empty() const
{
    return m_types->is_empty();
}


