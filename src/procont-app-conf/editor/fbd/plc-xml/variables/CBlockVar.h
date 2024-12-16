//
// Created by artem on 27.10.24.
//

#ifndef XML_CBLOCKVAR_H
#define XML_CBLOCKVAR_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"
#include "CVariable.h"


class CBlock;

enum EPinDirection
{
    PD_INPUT,
    PD_OUTPUT,
    PD_IN_OUT,
    PD_UNDEF
};

/**
 * @brief переменные внутри блока исходя из файла от IDE OpenPLC не соответствуют документации. Делаем на основе файла
 */
class CBlockVar
{
public:
    explicit CBlockVar(CBlock *parent = nullptr);
    CBlockVar(const CBlockVar & other);
    explicit CBlockVar(CBlock *parent, const QDomNode & domNode);
    ~CBlockVar();

    CBlock  *parent();
    void    set_parent(CBlock * block);
    CBlockVar & operator = (const CBlockVar &rhs);

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;
    [[nodiscard]] bool        is_negated() const;
    void                      set_negated(const bool &negated);

    [[nodiscard]] EEdge           edge_modifier() const;
    void    set_edge(const EEdge &edge_modifier);

    [[nodiscard]] EStorageMode    storage_modifier() const;
    void    set_storage_modifier(const EStorageMode &storage_modifier);

    [[nodiscard]] QString     formal_parameter() const;
    void        set_formal_param(const QString &formal_param);

    CConnectionPointIn   * point_in();
    CConnectionPointOut  * point_out();

    [[nodiscard]] EPinDirection   direction() const;
    void    set_direction(const EPinDirection &dir);

    [[nodiscard]] EDefinedDataTypes   type() const;
    [[nodiscard]] QString derived_type() const;
    void    set_type(const QString &type);

    CVariable   *  get_iface_variable();
    void           set_iface_variable(CVariable *var);

    [[nodiscard]] QString     constant_value() const;

    void        set_constant(const EDefinedDataTypes &type, const std::string &const_value);


protected:
    /// standard parameters
    QString m_formal_parameter;
    QString m_constant_value;

    QString             m_derived_type;
    CConnectionPointIn  * m_point_in{nullptr};
    CConnectionPointOut * m_point_out{nullptr};

    bool    m_is_negated{false};
    EEdge   m_edge_modifier{EEdge::EI_NONE};
    EStorageMode m_store_modifier{EStorageMode::SM_NONE};
    CAddData    * add_data;

    EDefinedDataTypes   m_type{EDefinedDataTypes::DDT_UNDEF};
    EPinDirection   m_direction{PD_UNDEF};

    /// extended parameters
    CVariable   * m_variable;
    CBlock *m_parent{nullptr};

    //std::vector<CBlockVar*> m_opposites;
    //CBlockVar   *m_opposite{nullptr};
};


#endif //XML_CBLOCKVAR_H
