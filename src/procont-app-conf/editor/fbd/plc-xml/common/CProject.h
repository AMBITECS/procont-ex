//
// Created by artem on 12/16/24.
//

#ifndef PROCONT_CPROJECT_H
#define PROCONT_CPROJECT_H

#include "editor/fbd/plc-xml/includes.h"
#include "CTypes.h"

class CContentHeader;
static int inst_count{0}; //!< счётчик вызовов

/**
 * @brief парсит почти весь проект и хранит в более-менее читаемом виде. @attention не парсится тэг \<instances>
 */
class CProject
{
public:
    static CProject * get_instance(const QDomNode &project_node);
    void Delete();

    [[nodiscard]] QDomNode    dom_node() const;

    CTypes  * types();
    //CContentHeader * content_header(){ return nullptr;}

    [[nodiscard]] QString     company_name() const;
    void        set_company_name(const QString &name);

    [[nodiscard]] QString     product_name() const;
    void        set_product_name(const QString &name);

    [[nodiscard]] QDateTime   creation_date_time() const;
    void        set_creation_dt(const QDateTime &date_time);

    [[nodiscard]] QDateTime   modification_date_time() const;
    void        set_modification_dt(const QDateTime &date_time);

    [[nodiscard]] QString     project_version() const;
    void        set_project_version(const QString &version);

    bool        is_empty() const;
protected:
    CProject();
    CProject(const CProject &);
    explicit CProject(const QDomNode &project_node);
    ~CProject();
private:
    CTypes      * m_types;
    QString       m_company_name{"Unnamed"};
    QString       m_content_header_name{"Unnamed"};
    QString       m_version{};
    QString       m_project_name{"Unnamed"};
    QDateTime     m_creation_dt{};
    QDateTime     m_modification_dt{};

    QString       m_xmlns{};
    QString       m_xmlns_xsd{};
    QString       m_xmlns_xhtml{};
    QString       m_xmlns_ns1{};


    void process_file_header(const QDomNode &node);

    void process_content_header(const QDomNode &node);
};


#endif //PROCONT_CPROJECT_H
