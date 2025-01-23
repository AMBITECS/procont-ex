//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CINFO_H
#define EDITORSD_CINFO_H

#include "includes.h"

/**
 * @refitem XML Formats for IEC 61131-3 Version 2.01 – Official Release page 22
 * @brief
 *  CInfo is a part of the addDataInfo.
 */

class CInfo
{
public:
    CInfo();
    CInfo(const CInfo &);
    CInfo(CInfo &&) noexcept;
    explicit CInfo(const QDomNode &node);
    ~CInfo();

    QDomNode    dom_node();

    QString     name() const;
    void     set_name(const QString &name);

    float       version() const;
    void        set_version(const float &version);

    QString     vendor() const;
    void        set_vendor(const QString &vendor);

    QString     description() const;
    void        set_description(const QString &description);


private:
    QString     m_name;
    float       m_version{0.1};
    QString     m_vendor;
    QString     m_description;
};


#endif //EDITORSD_CINFO_H
