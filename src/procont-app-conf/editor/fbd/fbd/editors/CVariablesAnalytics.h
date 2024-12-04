//
// Created by artem on 11/15/24.
//

#ifndef EDITORSD_CVARIABLESANALYTICS_H
#define EDITORSD_CVARIABLESANALYTICS_H

#include "../../plc-xml/CInterface.h"
#include "../graphics/CConnectorPin.h"
#include "../../plc-xml/common/CPou.h"
#include "../variables.h"
#include "CFilter.h"
#include "../../plc-xml/common/CUserType.h"
#include "../../plc-xml/common/types/CArray.h"
#include "../../../../iec/StandardLibrary.h"

class COglWorld;


struct s_tree_item
{
    uint16_t  id{0};
    uint16_t  id_parent{0};
    std::string name;
    std::string type;
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
    std::vector<s_tree_item>   query(CConnectorPin     * pin);

    /**
     * @brief returns editing diagram POU variables for object correct naming
     * @param [in] CDiagramObject* naming object
     * @return std::map<QString, EDefinedDataTypes> existing variables with types
     */
    std::vector<std::pair<QString, EDefinedDataTypes>> get_interface_variables();

    void    bind_pins(CDiagramObject *object);

    /** @brief найти и назначить новую переменную */
    bool find_target(const std::string &variable, CConnectorPin **pin, CVariable ** iface_var);


    void setup_block(CBlock *block);   //!< выяснить типы входов/выходов

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

private:

    COglWorld           * m_world;
    CPou                * m_diag_pou{nullptr};
    CInterface          * m_interface{nullptr};
    std::vector<CPou*>  * m_pou_array;
    QDomNode            * m_pous;
    std::vector<CUserType*> *m_types;
    StandardLibrary     * m_standard_library;


    void clear_pous();
    void define_variables_sets();  //!< сформировать структуры возможных источников данных для назначения на вход/выход блоков
    void clear_variable_sets();
    static void  copy_vars(QList<CVariable*> *variables, std::vector<std::pair<QString, EDefinedDataTypes>> *map);

    bool find_chine(CConnectorPin *&p_pin);
    bool find_input_data(CConnectorPin *pin);
    bool find_output_data(CConnectorPin *pin);
    bool find_in_out_data(CConnectorPin *pin);


    void collect_pins_data(std::vector<s_tree_item> &tree_items, CConnectorPin *pin);

    std::vector<s_tree_item> find_fbd_inputs_collection(CFbdContent *body_content, CConnectorPin *pin, uint16_t &id);

    std::vector<s_tree_item> find_fbd_outputs_collection(CFbdContent *body_content, CConnectorPin *pin, uint16_t &id);


    static bool check_variables(CBlockVar *pin, const int &dir, CInterface *iface);

    [[nodiscard]] QString get_comparable_type(const QString &mb_user_type);
    static QString     analyze_array(const QString &variable, CArray * user_type);

    static bool analyze_base_types(const EDefinedDataTypes &target_type, const EDefinedDataTypes &dragged_type,
                            const bool &is_strict_compliance);

    bool get_library_type_data(CBlock *block, const QString &standard_type_name);

    //CVariable* find_var(CBlockVar *pin, CInterface *standard_iface);
};


#endif //EDITORSD_CVARIABLESANALYTICS_H
