//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CVARIABLE_H
#define EDITORSD_CVARIABLE_H

#include "../includes.h"
#include "../CDocumentation.h"
#include "../CAddData.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"


class CInterface;
class CResource;

/**
 * @brief  part of derived CInVar and so on.
 * @details source details in XML Format for IEC 61131-3 page 29
 */
class CVariable
{
public:
    explicit CVariable(CInterface *parent);
    CVariable(const CVariable &);
    CVariable(CVariable &&) noexcept;
    CVariable(const QDomNode &node, CInterface *parent);
    ~CVariable();

    CInterface * parent();
    void         set_parent(CInterface *parent);

    QDomNode    dom_node();

    CVariable&  operator=(const CVariable &rhs);

    [[nodiscard]] QString     type() const;
    void        set_type(const QString &type);

    [[nodiscard]] QString     name() const;
    [[nodiscard]] QString     full_name() const;
    void        set_name(const QString &name);

    [[nodiscard]] QString     address() const;
    void        set_addr(const QString &addr);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString &global_id);

    [[nodiscard]] QString     init_value() const;
    void        set_init_value(const QString &str);

    [[nodiscard]] QString     comment() const;
    void        set_comment(const QString &comment);

    [[nodiscard]] bool        is_empty() const;

    void        set_global_parent(CResource *resource);

    [[nodiscard]] bool          is_global() const;
    CResource     * resource();

private:
    CInterface * m_parent{nullptr};
    CResource  * m_glob_parent{nullptr};
    QString     m_attr_name{""};   // required
    QString     m_attr_addr{};
    QString     m_attr_global_id{};

    QString     m_type;           // EBaseTypes or other POUs
    QString     m_derived_name;
    QString     m_init_value;
    CDocumentation  m_doc;
    CAddData    m_add_data;
};


#endif //EDITORSD_CVARIABLE_H
