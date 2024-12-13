//
// Created by artem on 11/15/24.
//

#include "CVariablesAnalytics.h"
#include "../graphics/COglWorld.h"
#include "../../plc-xml/common/types/CAlias.h"
#include "../../plc-xml/common/types/CSubrange.h"
#include "editor/fbd/fbd/graphics/CGrapchicsLogic.h"


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

    for (auto &var : m_diagram_interface->all_variables())
    {
        EDefinedDataTypes type = get_type_from_string(var->type().toStdString());
        existing.emplace_back(var->name(), type);
    }

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

bool CVariablesAnalytics::find_input_data()
{
    /// возможные варианты:<br>
    /// V- пин пустой и ни к чему не привязан<br>
    /// V- на пине сидит константа<br>
    /// V- на пине графическая связь с другим блоком<br>
    /// V- пин привязан к интерфейсной переменной<br>
    /// V- пин привязан к глобальной переменной (сканить все POU на предмет глобальных переменных)<br>
    /// V- пин привязан к CInOutVariable нашего CBody и тут возможна рекурсия<br>
    /// Эти варианты годны при выполнении одного из двух условий при reference_local_id > 0:<br>
    /// - в содержимом CBody находитсяCInVariable или CInOutVariable c соответствущим local_id от которой идёт связь на другие ресурсы (выше)<br>
    /// - в содержимом CBody находится CBlock с соответствующим local_id для графической связи

    CInVariable     * in_variable;
    CInOutVariable  * in_out_variable;
    COutVariable    * out_variable;

    auto content = get_pou_content();
    CGraphicsLogic graphics_logic;

    for (auto &ladder : *m_world->all_ladders())
    {
        for (auto &component : *ladder->draw_components())
        {
            for (auto &pin : *component->inputs())
            {
                in_variable = nullptr;
                in_out_variable = nullptr;
                out_variable = nullptr;

                CConnectionPointIn* point_in = pin->block_variable()->point_in();

                /// empty pin
                if (point_in->is_empty())
                {
                    continue;
                }

                uint64_t ref_id = point_in->ref_local_id();
                QString  in_formal = point_in->formal_param();

                /// suppose graphic connection
                if (!in_formal.isEmpty())
                {
                    CDiagramObject * item = find_object_by_id(ref_id);
                    CPinOut *out = item->get_output_by_name(in_formal);

                    CConnectLine *line = graphics_logic.add_new_line(pin, out);
                    if (line)
                    {
                        ladder->add_line(line);
                    }

                    continue;
                }

                /// Nope. It can be a long way through that damned standard OpenXML.
                s_variable_data var_data = content->get_var_by_local_id(ref_id);

                if (var_data.local_id != ref_id)
                {
                    continue;
                }

                switch (var_data.source) {
                    case PD_INPUT:
                        in_variable = static_cast<CInVariable*>(var_data.variable);
                        break;
                    case PD_IN_OUT:
                        in_out_variable = static_cast<CInOutVariable*>(var_data.variable);
                        break;
                    case PD_OUTPUT:
                        out_variable = static_cast<COutVariable*>(var_data.variable);
                        break;
                    default:
                        throw std::runtime_error("what this??? 'CFbdContent::comb_the_pou'");
                }

                if (!in_variable && in_out_variable &&out_variable)
                {
                    throw std::runtime_error("its impossible??? 'CFbdContent::comb_the_pou'");
                }

                /// suppose its iface variable from anywhere (local iface/global/program)

                if (in_out_variable)
                {
                    CBlockVar * possible_pin = nullptr;
                    std::vector<CVariable* > poss_iface_var;
                    auto res = m_diagram_pou->process_in_out(pin->block_variable(),
                                                              in_out_variable,
                                                              &possible_pin,
                                                              &poss_iface_var);
                    if (res && possible_pin)
                    {
                        auto out = find_output(possible_pin);

                        CConnectLine *line = graphics_logic.add_new_line(pin, out);
                        if (line)
                        {
                            ladder->add_line(line);
                        }

                        continue;
                    }

                    if (res && !poss_iface_var.empty())
                    {
                        pin->connect_iface_variable(poss_iface_var.front());

                        continue;
                    }
                }

                /// constant or iface var
                if (in_variable)
                {
                    QString var_express = in_variable->expression()->expression();

                    EDefinedDataTypes type = CFilter::get_type_from_const(var_express.toStdString());
                    if (type != EDefinedDataTypes::DDT_STRING && !var_express.isEmpty())
                    {
                        pin->set_constant(type, var_express.toStdString());
                        continue;
                    }

                    /// nope, some iface var
                    QString additional;
                    auto iface_var = get_iface_variable(var_express, additional);

                    if (iface_var)
                    {
                        pin->connect_iface_variable(iface_var);
                        continue;
                    }
                }
            }
        }
    }

    /// остались COutVariables
    process_out_variables();

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
                                                                         CPin *pin_out, uint16_t &id)
{
    CPinOut * out_pin = pin_out->output();
    std::vector<s_tree_item> tree_items;


    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &object : *ladder->draw_components())
        {
            if (object == out_pin->parent())
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

            //tree_items.push_back(item);
            std::vector<s_tree_item> complex_items;
            complex_items.push_back(item);


            for (auto &connector : *object->pins())
            {
                if (connector->direction() == PD_OUTPUT)
                {
                    continue;
                }

                if (connector->is_connected())
                {
                    continue;
                }

                /// info about local pin type
                QString dragged_pin_type_name = out_pin->type() == DDT_DERIVED ? out_pin->type_name() :
                                                base_types_names[out_pin->type()];
                EDefinedDataTypes dragged_pin_type = out_pin->type();

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
                sub_item.opposite_pin = connector;

                //tree_items.push_back(sub_item);
                complex_items.push_back(sub_item);
            }

            if (complex_items.size() > 1)
            {
                tree_items.insert(tree_items.end(), complex_items.begin(), complex_items.end());
            }
            else
            {
                auto unit = complex_items.front();
                s_compare_types compares;
                if (check_pin_compatibility(unit.type.c_str(),
                                            get_type_from_string(unit.type),
                                            QString::fromStdString(unit.type),
                                            get_type_from_string(unit.type),
                                            compares))
                {
                    tree_items.push_back(unit);
                }
            }
        }

    }

    return tree_items;
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_outputs_collection(CFbdContent * /*body_content*/,
                                                                          CPin *pin_in, uint16_t &id)
{
    std::vector<s_tree_item> tree_items;
    CPinIn * input_pin = pin_in->input();

    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &object : *ladder->draw_components())
        {
            if (object == input_pin->parent())
            {
                continue;
            }

            /// if POU then put it here with children
            std::vector<s_tree_item> complex_items;

            s_tree_item item;
            item.id = id++;
            item.id_parent = 0;

            auto stdName = object->instance_name().isEmpty() ? object->type_name() + QString::number(object->local_id())
                                                             : object->instance_name();

            item.name = stdName.toStdString();
            item.type = object->type_name().toStdString();
            item.block = object->block();

            complex_items.push_back(item);

            for (auto &connector : *object->pins())
            {
                if (connector->direction() == PD_INPUT)
                {
                    continue;
                }

                auto pin_out = connector->output();

                /// info about queried pin type
                QString dragged_pin_type_name = pin_in->type() == DDT_DERIVED ? pin_in->type_name() :
                                                base_types_names[pin_in->type()];
                EDefinedDataTypes dragged_pin_type = pin_in->type();

                /// info about alien pin type
                QString target_pin_type_name = pin_out->type() == DDT_DERIVED ? pin_out->type_name() :
                                               base_types_names[pin_out->type()];
                EDefinedDataTypes target_pin_type = pin_out->type();

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
                sub_item.opposite_pin = pin_out;

                complex_items.push_back(sub_item);
            }

            if (complex_items.size() > 1)
            {
                tree_items.insert(tree_items.end(), complex_items.begin(), complex_items.end());
            }
            else
            {
                auto unit = complex_items.front();
                s_compare_types compares;
                if (check_pin_compatibility(unit.type.c_str(),
                                            get_type_from_string(unit.type),
                                            QString::fromStdString(unit.type),
                                            get_type_from_string(unit.type),
                                            compares))
                {
                    tree_items.push_back(unit);
                }
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
    bool is_library = false;
    bool is_pous = false;
    CBlock templ_block;

    /// if block from the projects POU
    for (auto &pou : *m_pou_array)
    {
        if (pou->name() == block->type_name())
        {
            templ_block = pou->get_block();
            is_pous = true;
        }
    }

    if (!is_pous)
    {
        templ_block = get_block_from_library(block->type_name());

        if (!templ_block.is_empty())
        {
            is_library = true;
        }

    }

    if (!is_library && !is_pous)
    {
        fprintf(stderr, "FBD ERROR: block does not belong to either library or project\n");
        return;
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

CBlock CVariablesAnalytics::get_block_from_library(const QString &block_type_name) const
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

CDiagramObject * CVariablesAnalytics::find_object_by_id(const uint64_t &local_id)
{
    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &object : *ladder->draw_components())
        {
            if (object->block()->local_id() == local_id)
            {
                return object;
            }
        }
    }
    return nullptr;
}

CPinOut *CVariablesAnalytics::find_output(CBlockVar *p_var)
{
    uint64_t object_id = p_var->parent()->local_id();
    std::string  formal_param = p_var->formal_parameter().toStdString();

    CDiagramObject *object = find_object_by_id(object_id);

    if (!object)
    {
        return nullptr;
    }

    auto pin_out = object->get_output_by_name(p_var->formal_parameter());

    return pin_out;
}

CVariable *CVariablesAnalytics::get_iface_variable(const QString &name, QString &add_name)
{
    /// first - find in local iface
    auto var = m_diagram_interface->get_variable_by_name(name);
    if (var)
    {
        return var;
    }

    /// may be global?
    for (auto &glob: *m_global_variables)
    {
        if (glob->name() == name)
        {
            add_name = "GVL.";
            return glob;
        }
    }

    /// could be program?
    for (auto &pou : *m_pou_array)
    {
        if (pou == m_diagram_pou)
        {
            continue;
        }
        var = pou->interface()->get_variable_by_name(name);

        if (var)
        {
            add_name = pou->name() + ".";
            return var;
        }
    }

    return nullptr;
}

void CVariablesAnalytics::process_out_variables()
{
    auto content = get_pou_content();
    CConnectionPointIn *point_in;
    QString var_express;

    for (auto &out_var : *content->out_variables())
    {
        point_in = out_var->point_in();

        uint64_t ref_id = point_in->ref_local_id();
        var_express = out_var->expression()->expression();


        /// it could be block
        auto block = content->get_block_by_id(ref_id);

        if (block)
        {
            auto iface_var = m_diagram_interface->get_variable_by_name(var_express);
            auto out_formal = point_in->formal_param();

            if (iface_var->is_empty() || out_formal.isEmpty())
            {
                throw std::runtime_error("Here is block, but no iface_var or formal_param in 'CVariablesAnalytics::process_out_variables'");
            }

            CDiagramObject *obj = find_object_by_id(block->local_id());
            auto out = obj->get_output_by_name(out_formal);
            out->connect(iface_var);

            continue;
        }

        s_variable_data data = content->get_var_by_local_id(ref_id);

        if (data.local_id != ref_id)
        {
            //content->remove_data(data);
            continue;
        }

        if (data.source == PD_IN_OUT)
        {
            std::vector<CVariable*> iface_vars;

            if (!var_express.isEmpty())
            {
                auto item = m_diagram_interface->get_variable_by_name(var_express);
                if (item)
                {
                    iface_vars.push_back(item);
                }
            }

            CBlockVar * block_var = nullptr;
            auto *var = static_cast<CInOutVariable*>(data.variable);



            bool res = m_diagram_pou->recursive_find_front(var,
                                                           &block_var,
                                                           &iface_vars);
            if (res && block_var)
            {
                CDiagramObject *object = find_object_by_id(block_var->parent()->local_id());
                auto pin_out = object->get_output_by_name(block_var->formal_parameter());

                for (auto &i_var : iface_vars)
                {
                    pin_out->connect(i_var);
                }
                continue;
            }
        }
    }
}

