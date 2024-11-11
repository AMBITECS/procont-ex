//
// Created by artem on 27.10.24.
//

#ifndef XML_CBLOCKVAR_H
#define XML_CBLOCKVAR_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"

/**
 * @brief переменные внутри блока исходя из файла от IDE OpenPLC не соответствуют документации. Делаем на основе файла
 */
class CBlockVar
{
public:
    CBlockVar();
    CBlockVar(const CBlockVar & other);
    explicit CBlockVar(const QDomNode & domNode);
    ~CBlockVar();

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;
    [[nodiscard]] bool        is_negated() const;
    [[nodiscard]] EEdge           edge_modifier() const;
    void    set_edge(const EEdge &edge_modifier);

    [[nodiscard]] EStorageMode    storage_modifier() const;
    void    set_storage_modifier(const EStorageMode &storage_modifier);

    [[nodiscard]] QString     formal_parameter() const;
    void        set_formal_param(const QString &formal_param);
    CConnectionPointIn   * point_in();
    CConnectionPointOut  * point_out();

protected:

    QString m_formal_parameter;
    CConnectionPointIn  * m_point_in{nullptr};
    CConnectionPointOut * m_point_out{nullptr};
    bool    m_is_negated{false};
    EEdge   m_edge_modifier{EEdge::EI_NONE};
    EStorageMode m_store_modifier{EStorageMode::SM_NONE};
    EDefinedDataTypes   m_type{EDefinedDataTypes::DDT_UNDEF};

    CAddData    * add_data;



};


#endif //XML_CBLOCKVAR_H
