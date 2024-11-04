//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CINPUTVARIABLES_H
#define EDITORSD_CINPUTVARIABLES_H


#include "../includes.h"
#include "../CExpression.h"
#include "../CConnectionPointOut.h"
#include "../CPosition.h"
#include "../CDocumentation.h"

/**
 * @brief XML Format for IEC 61131-3 page 48
 */
class CInVariable
{
public:
    CInVariable();
    CInVariable(const CInVariable & other);
    explicit CInVariable(const QDomNode & dom_node);
    ~CInVariable();

    CInVariable & operator = (const CInVariable &rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] uint64_t        local_id() const;
    void            set_local_id(const uint64_t & local_id);

    [[nodiscard]] float           width() const;
    void            set_width(const float & width);

    [[nodiscard]] float           height() const;
    void            set_height(const float & height);

    [[nodiscard]] uint16_t        execution_order_id() const;
    void            set_exec_order_id(const uint16_t & exec_order);

    [[nodiscard]] bool            negated() const;
    void            set_negated(const bool & negated);

    [[nodiscard]] EEdge           edge() const;                                  //!< is edge rising or falling or none
    void            set_edge(const EEdge & edge_type);                           //!< set edge rising or falling or none

    [[nodiscard]] EStorageMode    storage_behaviour() const;                     //!< is behaviour set or reset or none
    void            set_storage_behaviour(const EStorageMode & behaviour_in);    //!< set behaviour set or reset or none

    [[nodiscard]] QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    [[nodiscard]] bool            is_empty() const;

    CPosition   *   position();
    CExpression *   expression();


    CConnectionPointOut * point_out();
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
    CConnectionPointOut m_point_out;
    CAddData        m_add_data;
    CDocumentation  m_documentation;
};

//----------------------------------------------------------------------------------------------------------------------
// CInputVariables -----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CInputVariables
{
public:
    CInputVariables();
    CInputVariables(const CInputVariables & other);
    CInputVariables(CInputVariables && other) noexcept;
    explicit CInputVariables(const QDomNode &dom_node);
    ~CInputVariables();

    [[nodiscard]] QDomNode        dom_node() const;
    [[nodiscard]] bool            is_empty() const;

    QList<CInVariable*> *   variables();
    void                    clean();

private:
    QList<CInVariable*> * m_variables;
};


#endif //EDITORSD_CINPUTVARIABLES_H
