//
// Created by artem on 10/22/24.
//

#ifndef EDITORSD_CCONNECTOR_H
#define EDITORSD_CCONNECTOR_H

#include "includes.h"
#include "CPosition.h"
#include "CAddData.h"
#include "CDocumentation.h"
#include "CConnectionPointIn.h"


/**
 * @brief XML Format for IEC 61131-3 page 32
 */
class CConnector
{
public:
    CConnector();
    CConnector(const CConnector &);
    CConnector(CConnector &&) noexcept;
    explicit CConnector(const QDomNode &dom_node);
    ~CConnector();

    QDomNode    dom_node();

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

    [[nodiscard]] uint64_t    local_id() const;
    void        set_local_id(const uint64_t & local_id);

    [[nodiscard]] float       height() const;
    void        set_height(const float &height);

    [[nodiscard]] float       width() const;
    void        set_width(const float &width);

    [[nodiscard]] QString     global_id() const;
    void        set_global_id(const QString &glob_id);

    [[nodiscard]] float       pos_x() const;
    void        set_pos_x(const float &value);
    [[nodiscard]] float       pos_y() const;
    void        set_pos_y(const float &value);

    CConnectionPointIn *    connection_point_in();
    CAddData           *    add_data();
    CDocumentation     *    documentation();

    bool              is_empty() const;

private:
    QString           m_name;
    uint64_t          m_local_id{0};
    CPosition         m_position;
    CAddData          m_add_data;
    CDocumentation    m_documentation;
    float             m_height{0};
    float             m_width{0};
    QString           m_glob_id{};

    CConnectionPointIn  m_connection_input_point;
};


#endif //EDITORSD_CCONNECTOR_H
