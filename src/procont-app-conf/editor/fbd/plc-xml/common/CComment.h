//
// Created by artem on 10/26/24.
//

#ifndef EDITORSD_CCOMMENT_H
#define EDITORSD_CCOMMENT_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CAddData.h"
#include "../CDocumentation.h"

/**
 * @brief The element “comment” is used to store arbitrary text strings, which are not associated with a graphic
 * location. They are for example presented inside a dialog box/dialog window within the GUI.
 * “comment” elements are sparsely used in language elements.
 * @note
 *  XML Format for IEC 61131-3 page 30
 */
class CComment
{
public:
    CComment();
    CComment(const CComment &other);
    explicit CComment(const QDomNode &dom_node);
    ~CComment();

    CComment & operator=(const CComment & rhs);

    QDomNode        dom_node() const;

    uint64_t        local_id() const;
    void            set_local_id(const uint64_t &loc_id);
    float           width() const;
    void            set_width(const float & width);
    float           height() const;
    void            set_height(const float & height);
    QString         global_id() const;
    void            set_global_id(const QString & glob_id);

    CPosition   *   position();
    QString         content() const;
    void            set_content(const QString & content);
    CAddData   *    add_data();
    CDocumentation* documentation();

private:
    uint64_t    m_local_id{0};
    float       m_height{0};
    float       m_width{0};
    QString     m_global_id;
    CPosition   m_position;
    QString     m_content;
    CAddData    m_add_data;
    CDocumentation m_documentation;

    void explode_content(const QDomNode &node);

    QDomNode assemble_content() const;
};


#endif //EDITORSD_CCOMMENT_H
