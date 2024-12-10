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

void CVariablesAnalytics::copy_vars(std::vector<CVariable *> *variables,
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
    /// - на пине сидит константа<br>
    /// - на пине графическая связь с другим блоком<br>
    /// - пин привязан к интерфейсной переменной<br>
    /// - пин привязан к глобальной переменной (сканить все POU на предмет глобальных переменных)<br>
    /// - пин привязан к переменной из программного POU (пока не обрабатывается)<br>
    /// - пин привязан к CInOutVariable нашего CBody и этут возможна рекрсия<br>
    /// Эти варианты годны при выполнении одного из двух условий при reference_local_id > 0:<br>
    /// - в содержимом CBody находитсяCInVariable или CInOutVariable c соответствущим local_id от которой идёт связь на другие ресурсы (выше)<br>
    /// - в содержимом CBody находится CBlock с соответствующим local_id для графической связи

    if (input->point_in()->is_empty())
    {
        return true;
    }

    /// этот id может ссылаться на любую переменную внутри POU (in/out/in-out var)
    uint64_t  some_id = input->point_in()->ref_local_id();

    /// suppose this is graphic connection to block
    auto block = m_diagram_pou->find_block_by_id(some_id);
    if (block)
    {
        auto out_var = block->get_output_by_name(input->point_in()->connections()->front()->formal_parameter());
        if (out_var)
        {
            input->set_opposite(out_var);
            return true;
        }
    }

    /// well its long way. Lets find var
    auto content = get_pou_content();
    auto var_data = content->get_var_by_local_id(some_id);

    if (var_data.local_id == some_id)
    {
        CInVariable * in_variable = nullptr;
        CInOutVariable * in_out_variable = nullptr;
        COutVariable * out_variable = nullptr;

        switch (var_data.source)
        {
            case PD_INPUT:
                in_variable = static_cast<CInVariable*>(var_data.variable);
                break;
            case PD_OUTPUT:
                out_variable = static_cast<COutVariable*>(var_data.variable);
                break;
            case PD_IN_OUT:
                in_out_variable = static_cast<CInOutVariable*>(var_data.variable);
            default:
                break;
        }

        if (in_variable || in_out_variable || out_variable)
        {
            return true;
        }
    }

    /// ok. Its a constant
    EDefinedDataTypes df_type = CFilter::get_type_from_const(input->point_in()->expression().toStdString());
    dfsad
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
    /// first of all - setup types of the block in-outs
    bool is_library = false;
    bool is_pous = false;
    CBlock templ_block;

    QDomNode inst = m_standard_library->find_pou(block->type_name());

    if (!inst.isNull())
    {
        templ_block = CBlock(inst);
        is_library = true;
    }

    if (!is_library)
    {
        for (auto &pou : *m_pou_array)
        {
            if (pou->name() == block->type_name())
            {
                templ_block = pou->get_block();
                is_pous = true;
            }
        }
    }

    if (!is_library && !is_pous)
    {
        throw std::runtime_error("Project error in 'CVariablesAnalytics::setup_block'");
    }

    block->normalize_block(templ_block);
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

CFbdContent *CVariablesAnalytics::get_pou_content()
{
    /// эту скромную строку потом нужно расширить для LD/SFC и прочее
    return m_diagram_pou->bodies()->front()->fbd_content();
}

