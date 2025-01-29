//
// Created by artem on 10/23/24.
//

#ifndef EDITORSD_CINLINE_H
#define EDITORSD_CINLINE_H

#include "../includes.h"
#include "../CAddData.h"
#include "../CDocumentation.h"


/**
 * @brief These are part of the common objects because their scope is beyond SFC (action, actionBlock, inline are the same)
 */
class CInline
{
public:
    CInline();
    CInline(const CInline &other);
    CInline(CInline && other) noexcept;
    explicit CInline(const QDomNode &dom_node);
    ~CInline();

    CInline& operator=(const CInline &other);

    QDomNode        dom_node() const;

    QString     worksheet_name() const;
    void        set_worksheet_name(const QString &name);

    QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    CAddData *  add_data();
    CDocumentation  *   documentation();

    bool        is_empty() const;

    // TODO: выяснить что такое ppx:LI/ppx:ST/ppx:FBD... сделать их и загнать их либо в std::variant либо в enum

private:
    QString         m_worksheet_name;
    QString         m_global_id;
    CAddData        m_add_data;
    CDocumentation  m_document;
    EBodyType       m_inline_type{BT_COUNT};
    QDomNode        m_inline_value;

    bool        define_inline_type(const QDomNode &node);
};


#endif //EDITORSD_CINLINE_H
