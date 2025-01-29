//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CADDDATA_H
#define EDITORSD_CADDDATA_H

#include "CData.h"

/**
 * @brief CAddData container to list any instances i.e. CData. This design is usually the result of poor architecture
 */
class CAddData
{
public:
    CAddData();
    CAddData(const CAddData &);
    // CAddData(CAddData &&) noexcept;
    explicit CAddData(const QDomNode &node);
    ~CAddData();

    CAddData&   operator=(const CAddData &rhs);
    [[nodiscard]] bool    is_empty() const;

    [[nodiscard]] QDomNode    dom_node() const;

    QList<CData*>   * data_list();
    CData   *   append_data(CData *data);
    CData   *   remove_data(CData *data);
    CData   *   remove_data(const uint16_t &index);
    void        clean();

private:
    QList<CData*>   * m_data_list;
};


#endif //EDITORSD_CADDDATA_H
