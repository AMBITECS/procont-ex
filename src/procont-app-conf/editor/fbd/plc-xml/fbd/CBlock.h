//
// Created by artem on 10/24/24.
//

#ifndef EDITORSD_CBLOCK_H
#define EDITORSD_CBLOCK_H

#include "../includes.h"
#include "../CPosition.h"
#include "../variables/CInputVariables.h"
#include "../variables/CInOutVariables.h"
#include "../variables/COutputVariables.h"
#include "../CAddData.h"
#include "../CDocumentation.h"
#include "../variables/CBlockVar.h"

#define  INS "inputs"
#define  OUTS "outputs"

/**
 * XML Format for IEC 61131-3 page 47
 */
class CBlock
{
public:
    CBlock();
    CBlock(const CBlock & other);
    CBlock(CBlock && other) noexcept;
    explicit CBlock(const QDomNode &dom_node);
    virtual ~CBlock();

    CBlock& operator=(const CBlock &block);

    [[nodiscard]] QDomNode        dom_node() const;

    [[nodiscard]] bool            is_empty() const;

    [[nodiscard]] uint64_t            local_id() const;
    void                set_local_id(const uint64_t & local_id);
    [[nodiscard]] float               width() const;
    void                set_width(const float &width);
    [[nodiscard]] float               height() const;
    void                set_height(const float  &height);
    [[nodiscard]] QString             type_name() const;
    void                set_type_name(const QString & type_name);
    [[nodiscard]] QString             instance_name() const;
    void                set_instance_name(const QString &instance_name);
    [[nodiscard]] uint16_t            execution_order_id() const;
    void                set_exec_order_id(const uint16_t & order_id);
    [[nodiscard]] QString             global_id() const;
    void                set_global_id(const QString & glob_id);

    CPosition   *       position();
    QList<CBlockVar*> *   input_variables();
    QList<CBlockVar*> *   in_out_variables();
    QList<CBlockVar*> *   output_variables();

    CAddData        *   add_data();
    CDocumentation  *   documentation();

    /** @brief block при загрузке проекта не имеет типов входов/выходов а сейчас всё будет хорошо */
    bool    normalize_block(const CBlock &n_block);

    CBlockVar * get_output_by_name(const QString &name);


protected:
    uint64_t          m_local_id{0};
    float             m_width{0};
    float             m_height{0};
    QString           m_type_name;
    QString           m_instance_name;
    uint16_t          m_exec_order{0};
    QString           m_global_id;

    CPosition         m_position;
    QList<CBlockVar*> * m_in_vars;
    QList<CBlockVar*> * m_in_out_vars;
    QList<CBlockVar*>* m_out_vars;
    CAddData          m_add_data;
    CDocumentation    m_documentation;

    std::vector<EDefinedDataTypes>  m_inputs;
    std::vector<EDefinedDataTypes>  m_outputs;

    void
    extract_vars(const QString &direction,
                 const QDomNode &node);
    void extract_params();

    void extract_pin_params(const std::string &direction, const std::string &types_string);
};


#endif //EDITORSD_CBLOCK_H
