//
// Created by artem on 11/15/24.
//

#ifndef EDITORSD_CVARIABLESANALYTICS_H
#define EDITORSD_CVARIABLESANALYTICS_H

#include "../../plc-xml/CInterface.h"
#include "../../plc-xml/common/CPou.h"
#include "../variables.h"
#include "CFilter.h"
#include "../../plc-xml/common/CUserType.h"
#include "../../plc-xml/common/types/CArray.h"
#include "../../../../iec/StandardLibrary.h"
#include "editor/fbd/fbd/graphics/CPin.h"

class COglWorld;


struct s_tree_item
{
    uint16_t  id{0};
    uint16_t  id_parent{0};
    std::string name;
    std::string type;
    CVariable   * iface_variable{nullptr};
    CPin *  opposite_pin{nullptr};
};

struct s_compare_types
{
    QString  dragged_type;
    QString  target_type;
};

class CVariablesAnalytics
{
public:
    explicit CVariablesAnalytics(COglWorld * world);
    ~CVariablesAnalytics();

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

    /// find pin connections
//    void    bind_pins(CPin *pin);

    /** @brief найти и назначить новую переменную */
    //bool find_target(const std::string &variable, CPin **pin, CVariable ** iface_var);

    /** @brief выяснить типы входов/выходов а если на входе висит соединение, то и его распутаем */
    void setup_block(CBlock *block);

    /**
     * @brief проверка пинов на возможность соединения на предмет их типов. Если задано строгое соответствие,
     * то типы пинов должны быть одинаковы, иначе - подходящие
     */
    bool  check_pin_compatibility(const QString &dragged_pin_typename, const EDefinedDataTypes &dragged_pin_type,
                                  const QString &target_pin_typename,  const EDefinedDataTypes &target_pin_type,
                                  s_compare_types & compare_types,     const bool &strict_compliance = false);

    CInterface  *  local_pou_interface();
    std::vector<CUserType*>* user_types();
    std::vector<CPou*> * pou_array();
    CBlock  get_block(const QString &block_type_name);

    bool  connect_pin(CPinIn * input, bool &found, CBlockVar ** opposite_out);  //!< возврат true - означает системную или другую серьёзную ошибку
    bool find_input_data();
private:

    COglWorld           * m_world;
    CPou                * m_diagram_pou{nullptr};
    CInterface          * m_diagram_interface{nullptr};
    std::vector<CPou*>  * m_pou_array;
    std::vector<CVariable*> * m_global_variables;
    QDomNode            * m_pous;
    std::vector<CUserType*> *m_types;
    StandardLibrary     * m_standard_library;

    std::vector<std::tuple<CBlockVar*, CBlock*, CBlockVar*>>  m_graph_connections;

    CFbdContent *  get_pou_content();
    void clear_pous();
    void clear_variable_sets();
    static void  copy_vars(std::vector<CVariable*> *variables, std::vector<std::pair<QString, EDefinedDataTypes>> *map);




    /** @brief обновить данные, которые с течением времени могли измениться */
    void update_arrays();


    void collect_pins_data(std::vector<s_tree_item> &tree_items, CPin *pin);

    std::vector<s_tree_item> find_fbd_inputs_collection(CFbdContent *body_content, CPin *pin, uint16_t &id);

    std::vector<s_tree_item> find_fbd_outputs_collection(CFbdContent *body_content, CPin *pin, uint16_t &id);

    [[nodiscard]] QString get_comparable_type(const QString &mb_user_type);
    static QString     analyze_array(const QString &variable, CArray * user_type);

    static bool analyze_base_types(const EDefinedDataTypes &target_type, const EDefinedDataTypes &dragged_type,
                            const bool &is_strict_compliance);
    CDiagramObject *    find_object_by_id(const uint64_t & local_id);
    CVariable *get_iface_variable(const QString &name, QString &add_name);

    CPinOut *find_output(CBlockVar *p_var);

    void process_out_variables();
};


#endif //EDITORSD_CVARIABLESANALYTICS_H
