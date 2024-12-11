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


/**
 * @brief  part of derived CInVar and so on.
 * @details source details in XML Format for IEC 61131-3 page 29
 */
class CVariable
{
public:
    CVariable();
    CVariable(const CVariable &);
    CVariable(CVariable &&) noexcept;
    explicit CVariable(const QDomNode &node);
    ~CVariable();

    QDomNode    dom_node();

    CVariable&  operator=(const CVariable &rhs);

    [[nodiscard]] QString     type() const;
    void        set_type(const QString &type);

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

    [[nodiscard]] QString     address() const;
    void        set_addr(const QString &addr);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString &global_id);

    [[nodiscard]] QString     init_value() const;
    void        set_init_value(const QString &str);

    QString     comment() const;
    void        set_comment(const QString &comment);

    //[[nodiscard]] CConnectionPointIn * connection_point_in() const;
    //[[nodiscard]] CConnectionPointOut* connection_point_out() const;

    bool        is_empty() const;

private:
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
