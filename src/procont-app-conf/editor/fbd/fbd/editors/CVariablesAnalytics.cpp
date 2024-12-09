//
// Created by artem on 11/15/24.
//

#include "CVariablesAnalytics.h"
#include "../graphics/COglWorld.h"
#include "../../plc-xml/common/types/CAlias.h"
#include "../../plc-xml/common/types/CSubrange.h"


#include <vector>
#include <QFile>



CVariablesAnalytics::CVariablesAnalytics(COglWorld *world)
{
    m_world = world;
    m_pou_array = new std::vector<CPou*>();
    m_pous = new QDomNode(world->m_pou->sourceDomNode()->parentNode());
    m_types = new std::vector<CUserType*>();
    m_global_variables = new std::vector<CVariable*>();

    m_standard_library = StandardLibrary::instance();

    m_diagram_pou = m_world->m_pou;
    m_diagram_interface = m_diagram_pou->interface();

    update_arrays();
}

CVariablesAnalytics::~CVariablesAnalytics()
{
    clear_variable_sets();
    delete m_pou_array;
    delete m_pous;
    delete m_types;
    delete m_global_variables;

}

std::vector<s_tree_item> CVariablesAnalytics::query(CPin *pin)
{
    if (!pin)
    {
        return {};
    }

    std::vector<s_tree_item> tree_items;

    collect_pins_data(tree_items, pin);

    return tree_items;
}

std::vector<std::pair<QString, EDefinedDataTypes>> CVariablesAnalytics::get_interface_variables()
{
    std::vector<std::pair<QString, EDefinedDataTypes>> existing;

    copy_vars(m_diagram_interface->in_out_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->input_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->output_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->local_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->global_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->access_variables()->variables(), &existing);
    copy_vars(m_diagram_interface->external_variables()->variables(), &existing);

    return existing;
}

void CVariablesAnalytics::clear_pous()
{
    for (auto &item : *m_pou_array)
    {
        delete item;
    }
    m_pou_array->clear();
}

void CVariablesAnalytics::update_arrays()
{
    if (m_pous->isNull())
    {
        throw std::runtime_error("Can't work with empty QDomNode in 'void CVariablesAnalytics::update_arrays()'");
    }

    /// pous
    for (auto &pou : *m_pou_array)
        delete pou;
    m_pou_array->clear();

    int pous_amount = m_pous->childNodes().count();
    for (int i = 0; i < pous_amount; i++)
    {
        auto pou_node = m_pous->childNodes().at(i);

        auto pou_name = pou_node.attributes().namedItem(xmln::name).toAttr().value();
        if (pou_name == m_diagram_pou->name())
        {
            continue;
        }

        auto pou = new CPou(pou_node);
        m_pou_array->push_back(pou);
    }

    /// load user defined variables
    auto types = m_pous->parentNode();

    for (auto &item : *m_types)
        delete item;
    m_types->clear();

    // check node is "types" name
    if (types.nodeName() == (QString)xmln::types_node)
    {
        auto users_types = types.namedItem(xmln::datatypes);

        for (int i = 0; i < users_types.childNodes().count(); i++)
        {
            auto type = users_types.childNodes().at(i);
            auto utype = CUserType::get_user_type(type);
            auto user_type = CUserType::get_user_type(utype, &type);
            m_types->push_back(user_type);
        }
    }

    /// global variables
    m_global_variables->clear();
    for (auto &pou : *m_pou_array)
    {
        auto iface = pou->interface();

        for (auto &var : *iface->global_variables()->variables())
        {
            m_global_variables->push_back(var);
        }
    }
}

void CVariablesAnalytics::clear_variable_sets()
{
    clear_pous();
    for (auto &type : *m_types)
    {
        delete type;
    }
    m_types->clear();
}

void CVariablesAnalytics::copy_vars(QList<CVariable *> *variables,
                                    std::vector<std::pair<QString, EDefinedDataTypes>> *map)
{
    for (auto &var : *variables)
    {
        auto type = get_type_from_string(var->type().toStdString());
        map->emplace_back(var->name(), type);
    }
}

bool CVariablesAnalytics::find_input_data(CBlockVar *input)
{
    /// возможные варианты:<br>
    /// - пин пустой и ни к чему не привязан<br>
    /// - на пине сидит константа<br>- на пине графическая связь с другим блоком<br>
    /// - пин привязан к интерфейсной переменной<br>- пин привязан к глобальной переменной (сканить все POU на предмет
    ///   глобальных переменных)<br>- пин привязан к переменной из программного POU (пока не обрабатывается)<br>
    /// Эти варианты годны при выполнении одного из двух условий при reference_local_id > 0:<br>
    /// - в содержимом CBody находитсяCInVariable c соответствущим local_id от которой идёт связь на другие ресурсы (выше)<br>
    /// -в содержимом CBody находится CBlock с соответствующим local_id для графической связи

    //CBody * body = m_diagram_pou->bodies()->front();
    CInVariable *in_variable = nullptr;
    CInOutVariable *in_out_variable = nullptr;

    uint64_t pin_ref_id = input->ref_local_id();
    //QString formal_param = input->formal_parameter();

    /// 1. pin is empty. Returning
    if (pin_ref_id == 0)
    {
        return false;
    }

    /// ищем выполнения одного из двух условий: в теле CBody есть CInVariable или соединение с блоком
    bool is_var = m_diagram_pou->find_body_input_variable(pin_ref_id, &in_variable, &in_out_variable);

    /// если это условие не выполнилось, значит графическая связь с блоком
    if (!is_var)
    {
        CBlock *block = nullptr;
        CBlockVar * out_var = nullptr;
        bool res = m_diagram_pou->find_block_connecting_info(pin_ref_id, input->point_in()->formal_param(),
                                                             &block, &out_var);

        /// если и тут мимо - ошибка в проекте или в системе загрузки проекта
        if (!res)
        {
            throw std::runtime_error("none of 2 conditions are correct in 'bool CVariablesAnalytics::find_input_data(CPin *p_in)'");
        }

        /// надо где-то сохранить информацию для графического соединения и эту инфу можем сохранить либо в пине
        /// либо в CBlockVar пина, либо в каком-то специальном месте. Последнее приятнее чем мусорить в пине или в CBlockVar
        m_graph_connections.emplace_back(input, block, out_var);
        return true;
    }

    /// возможные варианты:<br>- в 'CInVariable' сидит константа<br>- в CInVariable сидит ссылка на интерфейсную
    /// переменную local interface, global variable or iface var of the program_pou<br>
    /// - в CInOutVariable сидит ссылка на что угодно с двух сторон. И наш input как-то относится к этому коню.
    /// Отдельная тема

    if (in_out_variable)
    {
        CBlockVar   * possible_block_var = nullptr;
        CVariable   * possible_iface_var = nullptr;

        bool in_out_done = m_diagram_pou->process_in_out(input, in_out_variable,
                                                         &possible_block_var,
                                                         &possible_iface_var);
        if (in_out_done)
        {
            if (possible_block_var)
            {
                m_graph_connections.emplace_back(input, possible_block_var->parent(), possible_block_var);
            }
            if (possible_iface_var)
            {
                input->set_iface_variable(possible_iface_var);
            }
            return true;
        }
    }

    if (get_input_source(input, in_variable))
    {
        return true;
    }

    std::string expr = in_variable->expression()->expression().toStdString();
    EDefinedDataTypes df_type = CFilter::get_type_from_const(expr);

    if (df_type == DDT_ANY_NUM)
    {
        return false;
    }

    input->set_constant(df_type, expr);
    return true;
}

void CVariablesAnalytics::collect_pins_data(std::vector<s_tree_item> &tree_items, CPin *pin)
{
    uint16_t  id = 1;
    std::vector<s_tree_item> items;
    std::vector<s_tree_item> items_v;

    CFilter filter(this);

    /// collecting interface variables
    for (auto &var : m_diagram_pou->interface()->all_variables())
    {
        if (var->name() == pin->parent()->instance_name())
        {
            continue;
        }

        if (filter.filter_string(var->type().toStdString(), ff_base_types | ff_user_types))
        {
            continue;
        }

        s_compare_types c_types;

        bool check = check_pin_compatibility(pin->type_name(),
                                             pin->type(),
                                             var->type(),
                                             get_type_from_string(var->type().toStdString()),
                                             c_types);

        if (!check)
        {
            continue;
        }

        s_tree_item item;
        item.id = id++;
        item.id_parent = 0;
        item.name = var->name().toStdString();
        item.type = var->type().toStdString();
        item.iface_variable = var;

        items.push_back(item);
    }

    /// collecting block's in/outs
    for (auto &body : *m_diagram_pou->bodies())
    {
        if (body->fbd_content())
        {
            if (pin->direction() == PD_INPUT)
            {
                items_v = find_fbd_outputs_collection(body->fbd_content(), pin, id);
            }
            if(pin->direction() == PD_OUTPUT)
            {
                items_v = find_fbd_inputs_collection(body->fbd_content(), pin, id);
            }
        }
    }

    items.insert(items.end(), items_v.begin(), items_v.end());
    tree_items.insert(tree_items.end(), items.begin(), items.end());
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_inputs_collection(CFbdContent * /*body_content*/,
                                                                         CPin *pin, uint16_t &id)
{

    std::vector<s_tree_item> tree_items;


    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &object : *ladder->draw_components())
        {
            if (object == pin->parent())
            {
                continue;
            }

            s_tree_item item;
            item.id = id++;
            item.id_parent = 0;

            auto stdName = object->instance_name().isEmpty() ? object->type_name() + QString::number(object->local_id())
                                                             : object->instance_name();

            item.name = stdName.toStdString();
            item.type = object->type_name().toStdString();

            tree_items.push_back(item);

            for (auto &connector : *object->pins())
            {
                if (connector->direction() != PD_INPUT)
                {
                    continue;
                }

                if (connector->is_connected())
                {
                    continue;
                }

                /// info about local pin type
                QString dragged_pin_type_name = pin->type() == DDT_DERIVED ? pin->type_name() :
                                                base_types_names[pin->type()];
                EDefinedDataTypes dragged_pin_type = pin->type();

                /// info about alien pin type
                QString target_pin_type_name = connector->type() == DDT_DERIVED ? connector->type_name() :
                                               base_types_names[connector->type()];
                EDefinedDataTypes target_pin_type = connector->type();

                s_compare_types compare_types;
                bool res = check_pin_compatibility(
                                    dragged_pin_type_name,
                                    dragged_pin_type,
                                    target_pin_type_name,
                                    target_pin_type,
                                    compare_types);

                if (!res)
                {
                    continue;
                }

                s_tree_item sub_item;

                sub_item.id = id++;
                sub_item.id_parent = item.id;
                sub_item.type = target_pin_type_name.toStdString();
                sub_item.name = connector->type_name().toStdString();
                sub_item.opposite_pin = connector;

                tree_items.push_back(sub_item);
            }
        }

    }

    return tree_items;
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_outputs_collection(CFbdContent * /*body_content*/,
                                                                          CPin *pin, uint16_t &id)
{
    std::vector<s_tree_item> tree_items;


    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &object : *ladder->draw_components())
        {
            if (object == pin->parent())
            {
                continue;
            }

            s_tree_item item;
            item.id = id++;
            item.id_parent = 0;

            auto stdName = object->instance_name().isEmpty() ? object->type_name() + QString::number(object->local_id())
                                                             : object->instance_name();

            item.name = stdName.toStdString();
            item.type = object->type_name().toStdString();

            tree_items.push_back(item);

            for (auto &connector : *object->pins())
            {
                if (connector->direction() == PD_INPUT)
                {
                    continue;
                }

                /// info about local pin type
                QString dragged_pin_type_name = pin->type() == DDT_DERIVED ? pin->type_name() :
                                                base_types_names[pin->type()];
                EDefinedDataTypes dragged_pin_type = pin->type();

                /// info about alien pin type
                QString target_pin_type_name = connector->type() == DDT_DERIVED ? connector->type_name() :
                                               base_types_names[connector->type()];
                EDefinedDataTypes target_pin_type = connector->type();

                s_compare_types compare_types;
                bool res = check_pin_compatibility(
                                dragged_pin_type_name,
                                dragged_pin_type,
                                target_pin_type_name,
                                target_pin_type,
                                compare_types);

                if (!res)
                {
                    continue;
                }

                s_tree_item sub_item;

                sub_item.id = id++;
                sub_item.id_parent = item.id;
                sub_item.type = target_pin_type_name.toStdString();
                sub_item.name = connector->pin_name().toStdString();
                sub_item.opposite_pin = pin;

                tree_items.push_back(sub_item);
            }
        }

    }

    return tree_items;
}

/*bool CVariablesAnalytics::find_target(const std::string &variable, CPin **pin, CVariable ** iface_var)
{
    /// define names
    auto pos = variable.find('.');
    auto target_name = variable.substr(0, pos);
    auto pin_name = variable.substr(pos + 1, variable.length()-1);

    /// search target in interface
    CFilter filter(this);

    for (auto &var : m_diagram_interface->all_variables())
    {
        if (filter.filter_string(var->type().toStdString(), FilterFlags::ff_base_types | ff_user_types))
        {
            continue;
        }

        if (var->name().toStdString() == variable)
        {
            *iface_var = var;
            return true;
        }
    }


    /// search target in the objects
    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &obj : *ladder->draw_components())
        {
            auto obj_name = obj->instance_name().isEmpty() ? obj->type_name() +
                    QString::number(obj->local_id()) : obj->instance_name();
            if (obj_name.toStdString() != target_name)
            {
                continue;
            }

            for (auto &connector : *obj->pins())
            {
                if (connector->pin_name().toStdString() != pin_name )
                {
                    continue;
                }
                *pin = connector;
                return true;
            }
        }
    }

    return false;
}*/

CInterface *CVariablesAnalytics::local_pou_interface()
{
    return m_diagram_interface;
}

std::vector<CUserType *> *CVariablesAnalytics::user_types()
{
    return m_types;
}

std::vector<CPou *> *CVariablesAnalytics::pou_array()
{
    return m_pou_array;
}

void CVariablesAnalytics::setup_block(CBlock *block)
{
    bool is_pou_data = false;
    /// define is source is POU
    for (auto &pou : *m_pou_array)
    {
        if (pou->is_empty() || pou->interface()->is_empty())
        {
            continue;
        }


        auto block_type = block->type_name();
        auto pou_name = pou->name();
        bool not_found = false;

        /// well it is our pou
        if (block_type == pou_name)
        {
            for (auto &pin : *block->input_variables())
            {
                if (!check_variables(pin, -1, pou->interface()))// -1 input; 0 - in-out; 1 - out
                    not_found = true;
            }

            for (auto &pin : *block->output_variables())
            {
                if (!check_variables(pin, 1, pou->interface()))// -1 input; 0 - in-out; 1 - out
                    not_found = true;
            }
            for (auto &pin : *block->in_out_variables())
            {
                if (!check_variables(pin, 0, pou->interface()))// -1 input; 0 - in-out; 1 - out
                    not_found = true;
            }

            /// if not found is wrong POU or my logic
            if (not_found)
            {
                throw std::runtime_error("logic broken in 'CVariablesAnalytics::setup_block'");
            }

            is_pou_data = true;
        }

        if (is_pou_data)
        {
            break;
        }
    }

    if (!is_pou_data)
    {
        /// well, it's library.
        for (auto &std_type : m_standard_library->objects())
        {
            if (std_type != block->type_name())
            {
                continue;
            }

            if (!get_library_type_data(block, std_type))
            {
                throw std::runtime_error("тогда что это может быть???");
            }
            break;
        }
    }

    /// in-outs and in into the single array
    std::vector<CBlockVar*> inputs;
    if (!block->in_out_variables()->empty())
    {
        inputs.insert(inputs.end(), block->in_out_variables()->begin(),
                      block->in_out_variables()->end());
    }
    if (!block->input_variables()->empty())
    {
        inputs.insert(inputs.end(), block->input_variables()->begin(),
                      block->input_variables()->end());
    }
    /// if here all pins has type. Lets define connection
    for (auto &in : inputs)
    {
        if (in->point_in()->is_empty())
        {
            continue;
        }

        if (!find_input_data(in))
        {
            throw std::runtime_error("connecting failed in 'void CVariablesAnalytics::setup_block(CBlock *block)'");
        }
    }
}

bool CVariablesAnalytics::check_variables(CBlockVar *pin, const int &dir, CInterface *iface)
{
    QList<CVariable*> *variables;
    switch (dir)
    {
        case -1:
            variables = iface->input_variables()->variables();
            break;
        case 1:
            variables = iface->output_variables()->variables();
            break;
        case 0:
            variables = iface->in_out_variables()->variables();
            break;
        default:
            return false;
    }

    if (!iface->return_type().isEmpty() && pin->direction() == PD_OUTPUT)
    {
        auto o_type = iface->return_type();
        pin->set_type(o_type);
        return true;
    }


    for (auto &var : *variables)
    {
        if (var->name() == pin->formal_parameter())
        {
            pin->set_type(var->type());
            return true;
        }
    }

    return false;
}

bool CVariablesAnalytics::check_pin_compatibility(const QString &dragged_pin_typename,
                                                  const EDefinedDataTypes &dragged_pin_type,
                                                  const QString &target_pin_typename,
                                                  const EDefinedDataTypes &target_pin_type,
                                                  s_compare_types & compare_types,  //!< что бы глянуть на экране, что к чему
                                                  const bool &strict_compliance)
{
    QString target_type_pin, dragged_type_pin;

    target_type_pin = target_pin_type == DDT_DERIVED ? get_comparable_type(target_pin_typename) : target_pin_typename;
    dragged_type_pin = dragged_pin_type == DDT_DERIVED ? get_comparable_type(dragged_pin_typename) : dragged_pin_typename;

    if (target_type_pin.isEmpty())
    {
        target_type_pin = target_pin_typename;
    }

    if (dragged_type_pin.isEmpty())
    {
        dragged_type_pin = dragged_pin_typename;
    }

    compare_types.target_type = target_type_pin;
    compare_types.dragged_type = dragged_type_pin;

    if (strict_compliance)
    {
        return target_type_pin == dragged_type_pin;
    }

    /// Ok. soft compliance of the base types or POUs

    /// и так если переменные базового типа
    auto target_var_type = get_type_from_string(target_type_pin.toStdString());
    auto dragged_var_type = get_type_from_string(dragged_type_pin.toStdString());



    if (target_var_type != DDT_UNDEF &&
        dragged_var_type != DDT_UNDEF)
    {
        return analyze_base_types(target_var_type,
                                  dragged_var_type,
                                  strict_compliance);
    }

    return target_type_pin == dragged_type_pin;
}

QString CVariablesAnalytics::get_comparable_type(const QString &mb_user_type)
{
    for (auto &user_type : *m_types)
    {
        if (user_type->name() == mb_user_type)
        {
            switch (user_type->type())
            {
                case UT_ALIAS:
                    return dynamic_cast<CAlias*>(user_type)->base_type_name();
                case UT_SUB_RANGE:
                    return dynamic_cast<CSubrange*>(user_type)->base_type_name();
                case UT_ENUM:
                    return base_types_names[DDT_INT];
                case UT_ARRAY:
                    return analyze_array(mb_user_type, dynamic_cast<CArray*>(user_type));
                case UT_STRUCT:
                    return user_type->name();
                case UT_UNDEF:
                case UT_COUNT:
                    break;
            }
        }
    }
    return {};
}

QString CVariablesAnalytics::analyze_array(const QString &variable, CArray *user_type)
{
    auto is_array_elem = variable.contains("[");
    if (!is_array_elem)
    {
        /// return as whole array
        return user_type->name();
    }

    /// return as array element of the array base type
    return user_type->base_type_name();
}

bool CVariablesAnalytics::analyze_base_types(const EDefinedDataTypes &target_type, const EDefinedDataTypes &dragged_type,
                                        const bool &is_strict_compliance)
{
    if (target_type == DDT_ANY || dragged_type == DDT_ANY)
    {
        return true;
    }



    if (target_type == dragged_type)
    {
        return true;
    }

    if (is_strict_compliance)
    {
        return target_type == dragged_type;
    }

    /// пограничные случаи
    if (target_type == DDT_STRING || target_type == DDT_WSTRING)
    {
        return dragged_type == DDT_STRING || dragged_type == DDT_WSTRING;
    }
    if (target_type == DDT_TIME || target_type == DDT_TOD)
    {
        return dragged_type == DDT_TIME || dragged_type == DDT_TOD;
    }
    if (target_type == DDT_DATE || target_type == DDT_DT)
    {
        return dragged_type == DDT_DATE || dragged_type == DDT_DT;
    }

    if (is_convertible_to_bool(target_type) && is_convertible_to_bool(dragged_type))
    {
        return true;
    }

    /// в целом приводимые типы
    if (is_convertible_to_any_num(target_type) && is_convertible_to_any_num(dragged_type))
    {
        if (target_type == DDT_ANY_NUM || dragged_type == DDT_ANY_NUM)
        {
            return true;
        }

        if (is_convertible_to_anyint(dragged_type) && is_convertible_to_anyint(target_type))
        {
            return true;
        }

        if (is_convertible_to_anyuint(dragged_type) && is_convertible_to_anyuint(target_type))
        {
            return true;
        }

        if (is_convertible_to_anyfloat(dragged_type) && is_convertible_to_anyfloat(target_type))
        {
            return true;
        }
    }
    return false;
}

bool CVariablesAnalytics::get_library_type_data(CBlock *block, const QString &standard_type_name)
{
    //bool  not_found = false;
    auto type_pou = m_standard_library->find_pou(standard_type_name);

    if (type_pou.isNull())
    {
        return false;
    }

    auto *pou = new CPou(type_pou);
    auto iface = pou->interface();

    if (iface->is_empty())
    {
        delete pou;
        return false;
    }

    int counter = 0;

    for (auto &in : *block->input_variables())
    {
        //auto var = find_var(in, iface);
        auto lib_var = iface->input_variables()->variables()->at(counter);

        in->set_formal_param(lib_var->name());
        in->set_type(lib_var->type());

        counter++;
    }

    counter = 0;

    /// if this is function - there is no outputs
    if (pou->type() == "function")
    {
        auto var = block->output_variables()->at(0);
        var->set_formal_param("out");
        var->set_type(iface->return_type());
        delete pou;

        return true;
    }

    for (auto &out : *block->output_variables())
    {
        //auto var = find_var(out, iface);
        auto lib_var = iface->output_variables()->variables()->at(counter);

        out->set_formal_param(lib_var->name());
        out->set_type(lib_var->type());

        counter++;
    }

    counter = 0;

    for (auto &in_out : *block->in_out_variables())
    {
        //auto var = find_var(in_out, iface);
        auto lib_var = iface->in_out_variables()->variables()->at(counter);

        in_out->set_formal_param(lib_var->name());
        in_out->set_type(lib_var->type());

        counter++;
    }

    return true;
}


CBlock CVariablesAnalytics::get_block(const QString &block_type_name)
{
    auto type_pou = m_standard_library->find_pou(block_type_name);

    if (type_pou.isNull())
    {
        return {};
    }

    CPou pou(type_pou);
    CBlock block = pou.get_block();

    return block;
}

bool CVariablesAnalytics::get_input_source(CBlockVar *block_var, CInVariable * in_variable)
{
    QString expression = in_variable->expression()->expression();//block_var->point_in()->expression();

    for (auto &var: m_diagram_pou->interface()->all_variables())
    {
        if (var->name() != expression)
        {
            continue;
        }
        /// есть таки iface_variable, значит не константа
        block_var->set_iface_variable(var);

        return true;
    }

    /// глянем в глобальных переменных
    for (auto &glob_var : *m_global_variables)
    {
        if (glob_var->name() != expression)
        {
            continue;
        }
        block_var->set_iface_variable(glob_var);
        return true;
    }

    /// осталось одно место: в интерфейсе программных POU
    for (auto pou : *m_pou_array)
    {
        if (pou->type() != "program" || pou->is_empty())
        {
            continue;
        }

        CInterface * iface = pou->interface();

        for (auto &iface_var : iface->all_variables())
        {
            if (iface_var->name() != expression)
            {
                continue;
            }

            block_var->set_iface_variable(iface_var);
            return true;
        }
    }
    return false;
}

bool CVariablesAnalytics::connect_pin(CPinIn *input, bool &found, CBlockVar ** opposite_out)
{
    /// connection data
    CBlockVar * some_input;
    CBlock    * opposite_block;
    found = false;

    if (m_graph_connections.empty())
    {
        return true;
    }

    for (auto &tup : m_graph_connections)
    {
        std::tie(some_input, opposite_block, *opposite_out) = tup;
        if (some_input == input->block_variable())
        {
            found = true;
            break;
        }
    }

    return false;
}

