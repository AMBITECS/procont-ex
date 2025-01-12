//
// Created by artem on 1/9/25.
//

#ifndef PROCONT_CCOIL_H
#define PROCONT_CCOIL_H

#include <QDomNode>
#include "../includes.h"
#include "editor/fbd/plc-xml/CPosition.h"
#include "editor/fbd/plc-xml/CConnectionPointIn.h"
#include "editor/fbd/plc-xml/CConnectionPointOut.h"
#include "editor/fbd/plc-xml/variables/CVariable.h"

class CBody;

class CCoil
{
public:
    CCoil();
    CCoil(const CCoil &);
    explicit CCoil(CBody *parent);
    CCoil(CBody *parent, const QDomNode &node);
    virtual ~CCoil();

    CBody   * parent();
    void      set_parent(CBody *parent);

    [[nodiscard]] QDomNode  dom_node() const;

    [[nodiscard]] uint64_t  local_id() const;
    void      set_local_id(const uint64_t &local_id);

    void      set_height(const float &height);
    [[nodiscard]] float     height() const;

    void      set_width(const float & width);
    [[nodiscard]] float     width() const;

    [[nodiscard]] uint32_t  execution_order() const;
    void      set_execution_order(const uint32_t & order);

    void      set_negated(const bool & negated);
    [[nodiscard]] bool      is_negated() const;

    void      set_edge(const EEdge &edge_modifier);
    [[nodiscard]] EEdge     edge_modifier() const;

    void      set_storage(const EStorageMode & storage_modifier);
    [[nodiscard]] EStorageMode storage_modifier() const;

    [[nodiscard]] QString   global_id() const;
    void      set_global_id(const QString & glob_id);

    CPosition   * position();
    CConnectionPointIn  * connection_point_in();
    CConnectionPointOut * connection_point_out();
    CVariable           * variable();
    CAddData            * add_data();
    CDocumentation      * documentation();

protected:
    CBody               * m_parent;
    CPosition           * m_position;
    CConnectionPointIn  * m_connection_point_in;
    CConnectionPointOut * m_connection_point_out;
    CVariable           * m_variable;
    CAddData            * m_add_data;
    CDocumentation      * m_documentation;

    std::string     m_global_id{};
    EStorageMode    m_storage{EStorageMode::SM_NONE};
    EEdge           m_edge{EEdge::EI_NONE};
    bool            m_negated{false};
    uint32_t        m_execution_order{0};
    float           m_width{0};
    float           m_height{0};
    uint64_t        m_local_id{0};

};


#endif //PROCONT_CCOIL_H
