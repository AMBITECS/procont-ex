//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CBODY_H
#define EDITORSD_CBODY_H

#include "../includes.h"
#include "../CAddData.h"
#include "../CDocumentation.h"

#include "../fbd/CFbdContent.h"

class CLdContent;
class CSfcContent;
class CCfcContent;
class CStContent;

/**
 * @brief XML Format for IEC 61131-3 page 25. Set of diff variables and objects with instructions on IEC-lang
 * after creating LD and so on, `m_diagram` as QDomNode will be replaced with diagram-interface
 */
class CBody
{
public:
    CBody();
    CBody(const CBody & other);
    CBody(CBody && other) noexcept;
    explicit CBody(const QDomNode &dom_node);
    ~CBody();

    [[nodiscard]] QString         worksheet_name() const;
    void            set_worksheet_name(const QString & worksheet_name);
    [[nodiscard]] QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    CAddData     *  add_data();
    CDocumentation* documentation();

    [[nodiscard]] EBodyType       diagram_lang() const; //!< enum diagram type
    [[nodiscard]] QString         diagram_lang_str() const; //!< text diagram type

    [[nodiscard]] QDomNode        diagram() const;      //!< unparsed diagram
    [[nodiscard]] QDomNode        body_node() const;    //!< assembled from members domNode

    CFbdContent     * fbd_content();
    CFbdContent * add_fbd_diagram();    //!< not working yet
    CStContent      * st_content();         //!< not working yet
    CLdContent      * ld_content();         //!< not working yet
    CCfcContent     * cfc_content();        //!< not working yet
    CSfcContent     * sfc_content();        //!< not working yet



private:
    QString     m_worksheet_name;
    QString     m_global_ID;
    CFbdContent * m_fbd_content{nullptr};
    CStContent  * m_st_content{nullptr};
    CLdContent  * m_ld_content{nullptr};
    CCfcContent * m_cfc_content{nullptr};
    CSfcContent * m_sfc_content{nullptr};

    /// body's children
    EBodyType         m_body_type{BT_COUNT};  //!< main child-container for body itself. required
    CAddData        * m_add_data{nullptr};    //!< additional data. optional
    CDocumentation  * m_document{nullptr};
    QDomNode        * m_diagram;

    void define_diagram_type();
};


#endif //EDITORSD_CBODY_H
