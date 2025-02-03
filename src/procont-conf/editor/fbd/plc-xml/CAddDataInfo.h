//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CADDDATAINFO_H
#define EDITORSD_CADDDATAINFO_H

#include "CInfo.h"

/**
 * @refitem XML Formats for IEC 61131-3 Version 2.01 – Official Release page 22
 * @brief
 *      CAddDataInfo is the container for CInfo. May contains 0...INF of CInfo
 */
class CAddDataInfo
{
public:
    CAddDataInfo();
    CAddDataInfo(const CAddDataInfo  &);
    explicit CAddDataInfo(const QDomNode &node);
    CAddDataInfo(CAddDataInfo &&) noexcept;
    ~CAddDataInfo();

    [[nodiscard]] QDomNode    dom_node() const;

    QList<CInfo*>   * info_list();
    CInfo           * append_info(CInfo *info);
    CInfo           * remove_info(CInfo *info);
    CInfo           * remove_info(const uint16_t &index);
    void              clean();
    [[nodiscard]] bool   is_empty() const;

private:
    QList<CInfo*>   * m_info_list;
};


#endif //EDITORSD_CADDDATAINFO_H
