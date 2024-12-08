//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CINOUTVARIABLES_H
#define EDITORSD_CINOUTVARIABLES_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CExpression.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"
#include "../CDocumentation.h"


/**
 * @brief  XML Format for IEC 61131-3 page 50
 */
class CInOutVariable
{
public:
    CInOutVariable();
    CInOutVariable(const CInOutVariable & other);
    explicit CInOutVariable(const QDomNode & dom_node);
    ~CInOutVariable();

    CInOutVariable & operator=(const CInOutVariable & rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] uint64_t        local_id() const;
    void            set_local_id(const uint64_t & local_id);

    uint64_t    reference_local_id() const;
    void        set_reference_local_id(const uint64_t &ref_id);

    [[nodiscard]] float           width() const;
    void            set_width(const float & width);

    [[nodiscard]] float           height() const;
    void            set_height(const float & height);

    [[nodiscard]] uint16_t        execution_order_id() const;
    void            set_exec_order_id(const uint16_t & exec_order);

    [[nodiscard]] bool            negated_in() const;
    void            set_negated_in(const bool & negated);

    [[nodiscard]] EEdge           edge_in() const;                                  //!< is edge rising or falling or none
    void            set_edge_in(const EEdge & edge_in_type);                        //!< set edge rising or falling or none

    [[nodiscard]] EStorageMode    storage_behaviour_in() const;                     //!< is behaviour set or reset or none
    void            set_storage_behaviour_in(const EStorageMode & behaviour_in);    //!< set behaviour set or reset or none

    [[nodiscard]] bool            negated_out() const;
    void            set_negated_out(const bool &negated_out);

    [[nodiscard]] EEdge           edge_out() const;                                 //!< is edge rising or falling or none
    void            set_edge_out(const EEdge &edge);                                //!< set edge rising or falling or none

    [[nodiscard]] EStorageMode    storage_behaviour_out() const;                    //!< is behaviour set or reset or none
    void            set_storage_behaviour_out(const EStorageMode & behaviour_out);  //!< set behaviour set or reset or none

    [[nodiscard]] QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    [[nodiscard]] bool            is_empty() const;

    CPosition   *   position();
    CExpression *   expression();

    CConnectionPointIn  * point_in();
    CConnectionPointOut * point_out();
    CAddData            * add_data();
    CDocumentation      * documentation();

private:
    uint64_t        m_local_id{0};
    uint16_t        m_exec_order{0};
    float           m_width{0};
    float           m_height{0};
    QString         m_global_id;
    bool            m_negated_in{false};
    bool            m_negated_out{false};
    EEdge           m_edge_in{EEdge::EI_NONE};
    EEdge           m_edge_out{EEdge::EI_NONE};
    EStorageMode    m_storage_in{EStorageMode::SM_NONE};
    EStorageMode    m_storage_out{EStorageMode::SM_NONE};

    CPosition       m_position;
    CExpression     m_expression;
    CConnectionPointIn  m_point_in;
    CConnectionPointOut m_point_out;
    CAddData        m_add_data;
    CDocumentation  m_documentation;

};


class CInOutVariables
{
public:
    CInOutVariables();
    CInOutVariables(const CInOutVariables & other);
    CInOutVariables(CInOutVariables && other) noexcept;
    explicit CInOutVariables(const QDomNode & dom_node);
    ~CInOutVariables();

    CInOutVariables & operator = (const CInOutVariables & rhs);

    [[nodiscard]] QDomNode        dom_node() const;

    QList<CInOutVariable*>  * in_out_variables();

    bool        is_empty() const;

    void        clean();

private:
    QList<CInOutVariable*>  * m_variables;
};


#endif //EDITORSD_CINOUTVARIABLES_H
