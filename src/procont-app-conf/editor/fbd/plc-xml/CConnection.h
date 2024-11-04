//
// Created by artem on 10/22/24.
//

#ifndef EDITORSD_CCONNECTION_H
#define EDITORSD_CCONNECTION_H

#include "CPosition.h"
#include "CAddData.h"

/**
 * @brief XML Format for IEC 61131-3 page 33
 */
class CConnection
{
public:
    CConnection();
    CConnection(CConnection &&) noexcept;
    CConnection(const CConnection &other);
    explicit CConnection(const QDomNode &dom_node);
    ~CConnection();

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    [[nodiscard]] uint64_t        ref_local_id() const;
    void            set_re_local_id(const uint64_t &ref_local_id);

    [[nodiscard]] QString         formal_parameter() const;
    void            set_formal_param(const QString &formal_param);

    QList<CPosition*> *  positions();

    CPosition*      add_position(const float &x, const float &y);
    CPosition*      add_position(const CPosition & position);
    CPosition*      add_position(CPosition *position);

    [[nodiscard]] uint16_t        positions_count() const;

    CPosition*      position_at(const uint16_t &index);

    CPosition*      remove_position(const uint16_t &index);
    CPosition*      remove_position(const CPosition &position);
    CPosition*      remove_position(CPosition *position);
    CPosition*      remove_position(const float &x, const float &y);


    CAddData         *  add_data();

private:
    QString     m_global_id;
    QString     m_formal_param;
    uint64_t    m_ref_local_id{};

    QList<CPosition*>   * m_positions;
    CAddData    m_add_data{};
};


#endif //EDITORSD_CCONNECTION_H
