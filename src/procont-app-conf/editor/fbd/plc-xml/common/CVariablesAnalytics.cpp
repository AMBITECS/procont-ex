//
// Created by artem on 11/15/24.
//

#include "CVariablesAnalytics.h"
#include "editor/fbd/fbd/graphics/COglWorld.h"
#include "editor/fbd/plc-xml/common/types/CAlias.h"
#include "editor/fbd/plc-xml/common/types/CSubrange.h"
#include "editor/fbd/fbd/graphics/CGrapchicsLogic.h"


#include <vector>
#include <QFile>

extern  uint16_t    max_local_id;
extern CProject *project;

CVariablesAnalytics::CVariablesAnalytics(COglWorld *world ,const QString &pou_name)
{
    m_diagram_pou = project->types()->find_pou_by_name(pou_name);
    if (m_diagram_pou)
    {
        m_diagram_interface = m_diagram_pou->interface();
    }
    m_world = world;
    m_pou_array         = project->types()->pous();
    m_types             = project->types()->user_types();
    m_global_variables  = new std::vector<CVariable*>();
    m_standard_library = StandardLibrary::instance();

    /// global variables left
    update_global_vars();
}

CVariablesAnalytics::~CVariablesAnalytics()
{

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

std::vector<std::pair<QString, EDefinedDataTypes>> CVariablesAnalytics::get_diag_interface_variables()
{
    std::vector<std::pair<QString, EDefinedDataTypes>> existing;

    for (auto &var : m_diagram_interface->all_variables())
    {
        EDefinedDataTypes type = get_type_from_string(var->type().toStdString());
        existing.emplace_back(var->name(), type);
    }

    return existing;
}

void CVariablesAnalytics::update_global_vars()
{
    for (auto &config : *project->instances()->configurations())
    {
        for (auto &res : *config->resources())
        {
            for (auto item : *res->global_vars()->variables())
            {
                m_global_variables->push_back(item);
            }
        }
    }
}

bool CVariablesAnalytics::load_connections()
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

    for (auto &ladder : *m_world->all_ladders())
    {
        for (auto &component : *ladder->draw_components())
        {
            connect_inputs(component);
        }
    }

    /// остались COutVariables
    process_out_variables();

    return true;
}

void CVariablesAnalytics::connect_inputs(CFbdObject *object)
{
    CBlockVar       * block_var;
    CConnection     * in_connection;
    CFbdConnectLine * line;
    CPinOut         * out;
    CGraphicsLogic    logic;
    CInVariable     * inVar;
    CVariable       * iface_var;


    CFbdContent* content = get_pou_content();

    for (auto &in : *object->inputs())
    {
        block_var = in->block_variable();

        /// pin is empty
        if (block_var->point_in()->connections()->isEmpty())
        {
            continue;
        }

        in_connection = block_var->point_in()->connections()->front();

        /// undefined error
        if (in_connection->ref_local_id() == 0)
        {
            continue;
        }


        /// graphic connection
        if (!in_connection->formal_parameter().isEmpty())
        {
            auto diag_obj = find_object_by_id(in_connection->ref_local_id());

            if(!diag_obj)
            {
                continue;
            }

            out = diag_obj->get_output_by_name(in_connection->formal_parameter());
            if (!out)
            {
                continue;
            }

            line = logic.add_new_line(in, out);

            if (line)
            {
                in->parent()->parent()->add_line(line);

            }

            in->load_project_connect_pin(out);
            out->load_project_connect(in);

            continue;
        }

        /// interface variable connection or constant
        if (in_connection->formal_parameter().isEmpty())
        {
            auto ref_id = in_connection->ref_local_id();

            if (ref_id == 0)
            {
                continue;
            }

            inVar = find_inVariable_by_id(ref_id);
            if (!inVar)
            {
                fprintf(stderr, "Logic broken: can't find CInVariable with id=%lu\n", ref_id);
                continue;
            }

            QString expression =inVar->expression()->expression();

            iface_var = find_variable_by_name(expression);

            /// interface variable. No matter local/global/prog POUs
            if (iface_var)
            {
                in->connect_iface_variable(iface_var);
            }

            /// constant
            auto type = CFilter::get_type_from_const(expression.toStdString());

            if (type < DDT_STRING)
            {
                in->set_constant(type, expression.toStdString());
            }

            fprintf(stderr, "Logic broken: can't find anything by ref_id=%lu and expression=%s\n",
                    ref_id, expression.toStdString().c_str());
        }
    }
}

void CVariablesAnalytics::collect_pins_data(std::vector<s_tree_item> &tree_items, CPin *pin)
{
    uint16_t  id = 1;
    std::vector<s_tree_item> items;
    std::vector<s_tree_item> items_v;
    QString var_name;

    CFilter filter(this);

    /// collecting interface variables from all correct pous
    for (auto &pou : *project->types()->pous())
    {
        if (pou->type_name() != "program" && pou != m_diagram_pou)
        {
            continue;
        }

        for (auto &var : pou->interface()->all_variables())
        {
            if (var->name() == pin->parent()->instance_name())
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

            if (pin->direction() == PD_OUTPUT)
            {
                if (pin->output()->is_iface_var_connected_to(var))
                {
                    continue;
                }
            }

            if (pou != m_diagram_pou)
            {
                var_name = pou->name() + "." + var->name();
            }
            else
            {
                var_name = var->name();
            }

            s_tree_item item;
            item.id = id++;
            item.id_parent = 0;
            item.name = var_name.toStdString();
            item.type = var->type().toStdString();
            item.iface_variable = var;

            items.push_back(item);
        }
    }


    /// collecting block's in/outs
    if (pin->direction() == PD_INPUT)
    {
        items_v = find_fbd_outputs_collection(pin, id);
    }
    if(pin->direction() == PD_OUTPUT)
    {
        items_v = find_fbd_inputs_collection(pin, id);
    }

    items.insert(items.end(), items_v.begin(), items_v.end());
    tree_items.insert(tree_items.end(), items.begin(), items.end());
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_inputs_collection(CPin *pin_out, uint16_t &id)
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

            std::vector<s_tree_item> complex_items;
            complex_items.push_back(item);

            CPinOut *pinOut = pin_out->output();
            for (auto &connector : *object->inputs())
            {
                if (connector->direction() == PD_OUTPUT)
                {
                    continue;
                }

                if (connector->is_connected())
                {
                    continue;
                }

                if (pinOut->is_pin_connected_to(connector))
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
                sub_item.name = connector->name().toStdString();
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
                                            pin_out->type_name(),
                                            pin_out->type(),
                                            compares))
                {
                    tree_items.push_back(unit);
                }
            }
        }

    }

    return tree_items;
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_outputs_collection(CPin *pin_in, uint16_t &id)
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
                sub_item.name = connector->name().toStdString();
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
                                            pin_in->type_name(),
                                            pin_in->type(),
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
    CBlock templ_block(nullptr);

    /// if block from the projects POU
    for (auto &pou : *m_pou_array)
    {
        if (pou->name() == block->type_name())
        {
            templ_block = pou->get_block();
            templ_block.set_parent(m_world->m_pou->bodies()->front());
            is_pous = true;
        }
    }

    if (!is_pous)
    {
        templ_block = get_block_from_library(block->type_name());
        templ_block.set_parent(m_world->m_pou->bodies()->front());

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
    compare_types.target_type = target_pin_typename;
    compare_types.dragged_type = dragged_pin_typename;

    if (dragged_pin_typename == target_pin_typename)
    {
        return true;
    }

    if (dragged_pin_type == DDT_ANY || target_pin_type == DDT_ANY)
    {
/*        if (dragged_pin_type == DDT_ANY && target_pin_type < DDT_DERIVED)
        {
            return true;
        }

        if(target_pin_type == DDT_ANY && dragged_pin_type < DDT_DERIVED)
        {
            return true;
        }
*/
        return true;
    }

    if (dragged_pin_type == DDT_ANY_NUM || target_pin_type == DDT_ANY_NUM)
    {
        if (dragged_pin_type == DDT_ANY_NUM)
        {
            return is_convertible_to_any_num(target_pin_type);
        }

        if (target_pin_type == DDT_ANY_NUM)
        {
            return is_convertible_to_any_num(dragged_pin_type);
        }

        return false;
    }

    if (dragged_pin_type == EDefinedDataTypes::DDT_DERIVED &&
        target_pin_type == EDefinedDataTypes::DDT_DERIVED)
    {
        return dragged_pin_typename == target_pin_typename;
    }

    if (dragged_pin_type == EDefinedDataTypes::DDT_UNDEF &&
        target_pin_type == EDefinedDataTypes::DDT_UNDEF)
    {
        return dragged_pin_typename == target_pin_typename;
    }

    if (dragged_pin_type == EDefinedDataTypes::DDT_DERIVED ||
        target_pin_type == EDefinedDataTypes::DDT_DERIVED)
    {
        return false;
    }

    if ( is_convertible_to_anyint(dragged_pin_type) && is_convertible_to_anyint(target_pin_type) )
    {
        return true;
    }

    if ( is_convertible_to_anyfloat(dragged_pin_type) && is_convertible_to_anyfloat(target_pin_type) )
    {
        return true;
    }

    if ( is_convertible_to_bool(dragged_pin_type) && is_convertible_to_bool(target_pin_type) )
    {
        return true;
    }

    return false;
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
        return CBlock{nullptr};
    }

    auto lib_pou = new CPou(type_pou, project->types());

    CBlock block = lib_pou->get_block();
    block.set_parent(m_world->m_pou->bodies()->front());

    delete lib_pou;

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

CFbdObject * CVariablesAnalytics::find_object_by_id(const uint64_t &local_id)
{
    if (!m_world)
    {
        return nullptr;
    }
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

    CFbdObject *object = find_object_by_id(object_id);

    if (!object)
    {
        return nullptr;
    }

    auto pin_out = object->get_output_by_name(p_var->formal_parameter());

    return pin_out;
}

void CVariablesAnalytics::process_out_variables()
{
    auto content = get_pou_content();
    CConnectionPointIn *point_in;
    QString var_name;

    for (auto &out_var : *content->out_variables())
    {
        var_name = out_var->expression()->expression();

        point_in = out_var->point_in();

        for (auto &connection : *point_in->connections())
        {
            uint64_t block_id = connection->ref_local_id();
            QString block_out_name = connection->formal_parameter();

            auto block = content->get_block_by_id(block_id);

            /// it could be block
            if (block)
            {
                auto iface_var = m_diagram_interface->get_variable_by_name(var_name);
                auto out_formal = connection->formal_parameter();

                if (iface_var->is_empty() || out_formal.isEmpty())
                {
                    //throw std::runtime_error("Here is block, but no iface_var or formal_param in 'CVariablesAnalytics::process_out_variables'");
                    return;
                }

                CFbdObject *obj = find_object_by_id(block->local_id());
                auto out = obj->get_output_by_name(block_out_name);
                out->connect(iface_var);
                continue;
            }

            /// или это может быть CInOutVariable
            s_variable_data data = content->get_var_by_local_id(block_id);

            if (data.local_id != block_id)
            {
                //TODO: content->remove_data(data); - not critical but remove trash
                continue;
            }

            if (data.source == PD_IN_OUT)
            {
                std::vector<CVariable*> iface_vars;

                if (!var_name.isEmpty())
                {
                    auto item = m_diagram_interface->get_variable_by_name(var_name);
                    if (item)
                    {
                        iface_vars.push_back(item);
                    }
                }

                std::vector<CBlockVar *> block_variables;
                auto *var = static_cast<CInOutVariable*>(data.variable);



                bool res = m_diagram_pou->recursive_find_in_out_top(var,
                                                                    &block_variables,
                                                                    &iface_vars);
                if (res && !block_variables.empty())
                {
                    for (auto &block_var : block_variables)
                    {
                        CFbdObject *object = find_object_by_id(block_var->parent()->local_id());
                        auto pin_out = object->get_output_by_name(block_var->formal_parameter());

                        for (auto &i_var : iface_vars)
                        {
                            pin_out->connect(i_var);
                        }
                    }
                    continue;
                }
            }

        }
    }
}

bool CVariablesAnalytics::remove_input_variable_by_id(const uint64_t &ref_id)
{
    auto content = get_pou_content();
    auto var = content->remove_in_variable_ny_id(ref_id);
    if (!var)
        return false;

    delete var;
    return true;
}

CInVariable* CVariablesAnalytics::add_input_variable(CInVariable *in_variable)
{
    if (in_variable)
    {
        auto content = get_pou_content();
        content->inVariables()->push_back(in_variable);
        return in_variable;
    }
    return nullptr;
}

COutVariable * CVariablesAnalytics::add_out_variable(COutVariable *out_variable)
{
    if (out_variable)
    {
        auto content = get_pou_content();
        content->out_variables()->push_back(out_variable);
        return out_variable;
    }
    return nullptr;
}

COutVariable *CVariablesAnalytics::remove_out_bloc_by_iface_variable(CVariable *iface_var, uint64_t &ref_id, const QString &out_formal_param)
{
    if (!iface_var)
    {
        return nullptr;
    }

    /// логика: если в outVariable есть только одно соединение, то возвращаем её для удаления или для дальнейшей вставки,
    /// при этом ref_id становится равным 0, если же в outVariable много соединений, находим и удаляем наше соединение,
    /// при этом ref_id становится больше 0. Удалять такую outVariable нельзя

    auto content = get_pou_content();
    int counter = 0;
    int conn_counter;

    for (auto &out_var : *content->out_variables())
    {
        if (out_var->expression()->expression() != iface_var->name())
        {
            continue;
        }
        conn_counter = 0;

        auto point_in = out_var->point_in();

        for (auto &conn : *point_in->connections())
        {
            if (conn->ref_local_id() == ref_id && conn->formal_parameter() == out_formal_param)
            {
                if (point_in->connections()->size() == 1)
                {
                    ref_id = 0;
                    content->out_variables()->erase(content->out_variables()->cbegin() + counter);
                    return out_var;
                }
                else
                {
                    point_in->connections()->erase(point_in->connections()->cbegin() + conn_counter);
                    delete conn;
                    ref_id = conn_counter;
                    return out_var;
                }
            }
            conn_counter++;
        }
        counter++;
    }
    return nullptr;
}

bool CVariablesAnalytics::connect_iface_var(CPinOut *pin_out, CVariable *iface_variable)
{
    /// возможно найдём существующий outVariable
    auto content = get_pou_content();
    COutVariable *out_var = content->find_output_var_by_iface_name(iface_variable->name());

    auto connection = new CConnection();

    connection->set_formal_param(pin_out->name());
    connection->set_ref_local_id(pin_out->parent()->local_id());


    if (out_var)
    {
        /// check we are absent
        for (auto &conn : *out_var->point_in()->connections())
        {
            if (conn->ref_local_id() == pin_out->parent()->local_id() && conn->formal_parameter() == pin_out->name())
            {
                delete connection;
                return false;
            }
        }

        /// lets connect
        out_var->point_in()->connections()->push_back(connection);
        return true;
    }


    out_var = new COutVariable(m_world->current_pou()->bodies()->front());
    out_var->set_local_id(++max_local_id);
    out_var->point_in()->connections()->push_back(connection);
    out_var->expression()->set_expression(iface_variable->name());

    content->out_variables()->push_back(out_var);
    return true;
}

//CVariable *CVariablesAnalytics::find_iface_var(const QString &var_name)
//{
//    QString ext_name;
//    return get_iface_variable(var_name, ext_name);
//}

StandardLibrary *CVariablesAnalytics::standard_library()
{
    return m_standard_library;
}

CFbdObject *CVariablesAnalytics::find_object( const QString &name )
{
    QString obj_name, obj_id_name;

    for (auto &ladder : *m_world->m_ladders)
    {
        for (auto &obj : *ladder->draw_components())
        {
            obj_name = obj->instance_name().isEmpty() ? obj->type_name() : obj->instance_name();
            obj_id_name = obj_name;
            if (obj->instance_name().isEmpty())
            {
                obj_id_name = obj_name + QString::number(obj->local_id());
            }

            if (obj_name == name || obj_id_name == name)
            {
                return obj;
            }
        }
    }
    return nullptr;
}

CVariable *CVariablesAnalytics::find_variable_by_name(const QString &name)
{
    /// possible places: current interface, global variables, program pous

    CInterface *local_iface = local_pou_interface();
    CPou    * current_pou = m_world->current_pou();

    /// local variables
    for (auto &var : local_iface->all_variables())
    {
        if (var->name() == name)
        {
            return var;
        }
    }

    /// program pous variables
    for (auto &pou : *project->types()->pous())
    {
        if (pou == current_pou || pou->type_name() != "program")
        {
            continue;
        }

        for (auto &var : pou->interface()->all_variables())
        {
            if (var->name() == name)
            {
                return var;
            }
        }
    }

    /// global variables
    for (auto &glob : *m_global_variables)
    {
        if (glob->name() == name)
        {
            return glob;
        }
    }
    return nullptr;
}

CInVariable *CVariablesAnalytics::find_inVariable_by_id(const uint64_t &ref_id)
{
    for (auto &body : *m_diagram_pou->bodies())
    {
        for (auto &invar : *body->fbd_content()->inVariables())
        {
            if (invar->local_id() == ref_id)
            {
                return invar;
            }
        }
    }
    return nullptr;
}





