//
// Created by artem on 11/15/24.
//

#ifndef EDITORSD_CVARIABLESANALYTICS_H
#define EDITORSD_CVARIABLESANALYTICS_H

#include "editor/fbd/plc-xml/CInterface.h"
#include "CPou.h"
#include "editor/fbd/fbd/variables.h"
#include "editor/fbd/fbd/editors/CFilter.h"
#include "CUserType.h"
#include "editor/fbd/plc-xml/common/types/CArray.h"
#include "iec/StandardLibrary.h"
#include "editor/fbd/fbd/graphics/CPin.h"
#include "CProject.h"

class COglWorld;


struct s_tree_item
{
    uint16_t      id{0};
    uint16_t      id_parent{0};
    std::string   name;
    std::string   type;
    CVariable   * iface_variable{nullptr};
    CPin        * opposite_pin{nullptr};
    CBlock      * block{nullptr};
};

struct s_compare_types
{
    QString  dragged_type;
    QString  target_type;
};

/**
 * @brief Набор команд для манипуляций (поиск/сравнение и т.д.) с переменными или POU в проекте
 */
class CVariablesAnalytics
{
public:
    //static CVariablesAnalytics *   get_instance(const QDomNode &project_node);  //!< QDomNode соответствует тегу \<project xmlns="http...">
    explicit CVariablesAnalytics(COglWorld *world, const QString &pou_name);
    ~CVariablesAnalytics();

    // CPou *    set_current_pou(const QString &pou_name, COglWorld *world);
    /**
     * @brief returns all variable names that can be using for block connection
     * @param pin
     * @return
     */
    std::vector<s_tree_item>   query(CPin     * pin);

    /**
     * @brief returns editing diagram POU variables for object correct naming
     * @param [in] CDiagramObject* naming object
     * @return std::map<QString, EDefinedDataTypes> existing variables with types
     */
    std::vector<std::pair<QString, EDefinedDataTypes>> get_interface_variables();


    /** @brief выяснить типы входов/выходов */
    void setup_block(CBlock *block);

    /**
     * @brief проверка пинов на возможность соединения на предмет их типов. Если задано строгое соответствие,
     * то типы пинов должны быть одинаковы, иначе - подходящие
     */
    static bool  check_pin_compatibility(const QString &dragged_pin_typename, const EDefinedDataTypes &dragged_pin_type,
                                  const QString &target_pin_typename,  const EDefinedDataTypes &target_pin_type,
                                  s_compare_types & compare_types,     const bool &strict_compliance = false);

    CInterface  *  local_pou_interface();
    std::vector<CUserType*>* user_types();
    std::vector<CPou*> * pou_array();
    [[nodiscard]] CBlock  get_block_from_library(const QString &block_type_name) const;

    bool  connect_pin(CPinIn * input, bool &found, CBlockVar ** opposite_out);  //!< возврат true - означает системную или другую серьёзную ошибку
    bool load_connections();

    bool            remove_input_variable_by_id(const uint64_t &ref_id);
    CInVariable*    add_input_variable(CInVariable *in_variable);
    COutVariable*   add_out_variable(COutVariable * out_variable);
    COutVariable*   remove_out_bloc_by_iface_variable(CVariable *iface_var,
                                                      uint64_t &ref_id, const QString &out_formal_param);

    [[nodiscard]] bool connect_iface_var(CPinOut *pin_out, CVariable *iface_variable);
    // CVariable *     find_iface_var(const QString &var_name);

    StandardLibrary *       standard_library();
    CFbdObject  *       find_object(const QString &name);
protected:

private:

    COglWorld           * m_world;
    CPou                * m_diagram_pou;
    CInterface          * m_diagram_interface;
    std::vector<CPou*>  * m_pou_array;
    std::vector<CVariable*> * m_global_variables;
    std::vector<CUserType*> *m_types;
    StandardLibrary     * m_standard_library;

    std::vector<std::tuple<CBlockVar*, CBlock*, CBlockVar*>>  m_graph_connections;

    /**@brief эту команду необходимо расширить при реализации LD/SFC и прочее, а тип возврата сделать интерфейсом
     * или базовым классом */
    CFbdContent *  get_pou_content();

    // static void  copy_vars(std::vector<CVariable*> *variables, std::vector<std::pair<QString, EDefinedDataTypes>> *map);


    /** @brief обновить данные, которые с течением времени могли измениться */
    void update_arrays();


    void collect_pins_data(std::vector<s_tree_item> &tree_items, CPin *pin);

    std::vector<s_tree_item> find_fbd_inputs_collection(CPin *pin, uint16_t &id);

    std::vector<s_tree_item> find_fbd_outputs_collection(CPin *pin, uint16_t &id);

    [[nodiscard]] QString get_comparable_type(const QString &mb_user_type);
    static QString     analyze_array(const QString &variable, CArray * user_type);

    static bool analyze_base_types(const EDefinedDataTypes &target_type, const EDefinedDataTypes &dragged_type,
                            const bool &is_strict_compliance);
    CFbdObject *    find_object_by_id(const uint64_t & local_id);
    CVariable *get_iface_variable(const QString &name, QString &add_name);

    CPinOut *find_output(CBlockVar *p_var);

    void process_out_variables();
    void connect_inputs(CFbdObject *object);
};


#endif //EDITORSD_CVARIABLESANALYTICS_H
