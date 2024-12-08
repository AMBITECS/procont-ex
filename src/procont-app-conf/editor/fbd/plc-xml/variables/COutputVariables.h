//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_COUTPUTVARIABLES_H
#define EDITORSD_COUTPUTVARIABLES_H

#include "CVariable.h"
#include "../CConnectionPointIn.h"
#include "../CPosition.h"

/**
 * @brief this variable is located in the body's inner environment
 */
class COutVariable
{
public:
    COutVariable();
    COutVariable(const COutVariable & other);
    explicit COutVariable(const QDomNode &dom_node);
    ~COutVariable();

    COutVariable & operator=(const COutVariable & rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] uint64_t        local_id() const;
    void            set_local_id(const uint64_t & local_id);

    [[nodiscard]] uint64_t    reference_id() const;
    void        set_reference_id(const uint64_t &id);

    [[nodiscard]] float           width() const;
    void            set_width(const float & width);

    [[nodiscard]] float           height() const;
    void            set_height(const float & height);

    [[nodiscard]] uint16_t        execution_order_id() const;
    void            set_exec_order_id(const uint16_t & exec_order);

    [[nodiscard]] bool            negated() const;
    void            set_negated(const bool & negated);

    [[nodiscard]] EEdge           edge() const;                                  //!< is edge rising or falling or none
    void            set_edge(const EEdge & edge_type);                        //!< set edge rising or falling or none

    [[nodiscard]] EStorageMode    storage_behaviour() const;                     //!< is behaviour set or reset or none
    void            set_storage_behaviour(const EStorageMode & behaviour);    //!< set behaviour set or reset or none

    [[nodiscard]] QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    [[nodiscard]] bool            is_empty() const;

    CPosition   *   position();
    CExpression *   expression();

    QString         formal_parameter() const;
    void            set_formal_param(const QString &formal);


    CConnectionPointIn * point_in();
    CAddData            * add_data();
    CDocumentation      * documentation();


private:
    uint64_t        m_local_id{0};
    uint16_t        m_exec_order{0};
    float           m_width{0};
    float           m_height{0};
    QString         m_global_id;
    bool            m_negated{false};
    EEdge           m_edge{EEdge::EI_NONE};
    EStorageMode    m_storage{EStorageMode::SM_NONE};

    CPosition       m_position;
    CExpression     m_expression;
    CConnectionPointIn m_point_in;
    CAddData        m_add_data;
    CDocumentation  m_documentation;
};

class COutputVariables
{
public:
    COutputVariables();
    COutputVariables(const COutputVariables & other);
    COutputVariables(COutputVariables && other) noexcept;
    explicit COutputVariables(const QDomNode & dom_node);
    ~COutputVariables();

    [[nodiscard]] QDomNode        dom_node() const;
    [[nodiscard]] bool            is_empty() const;

    QList<COutVariable*> *   variables();
    void                    clean();

private:
    QList<COutVariable*>    * m_variables;

};


#endif //EDITORSD_COUTPUTVARIABLES_H
