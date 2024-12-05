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

    m_standard_library = StandardLibrary::instance();

    define_variables_sets();
}

CVariablesAnalytics::~CVariablesAnalytics()
{
    clear_variable_sets();
    delete m_pou_array;
    delete m_pous;
    delete m_types;
    //delete m_standard_library;
}

std::vector<s_tree_item> CVariablesAnalytics::query(CConnectorPin *pin)
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

    copy_vars(m_interface->in_out_variables()->variables(), &existing);
    copy_vars(m_interface->input_variables()->variables(), &existing);
    copy_vars(m_interface->output_variables()->variables(), &existing);
    copy_vars(m_interface->local_variables()->variables(), &existing);
    copy_vars(m_interface->global_variables()->variables(), &existing);
    copy_vars(m_interface->access_variables()->variables(), &existing);
    copy_vars(m_interface->external_variables()->variables(), &existing);

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

void CVariablesAnalytics::define_variables_sets()
{
    m_diag_pou = m_world->m_pou;

    /// load user defined variables
    if (!m_pous->isNull())
    {
        auto types = m_pous->parentNode();

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
    }


    /// get pou instances
    if (!m_pous->isNull())
    {
        int pous_amount = m_pous->childNodes().count();
        for (int i = 0; i < pous_amount; i++)
        {
            auto pou_node = m_pous->childNodes().at(i);

            auto pou_name = pou_node.attributes().namedItem(xmln::name).toAttr().value();
            if (pou_name == m_diag_pou->name())
            {
                continue;
            }

            auto pou = new CPou(pou_node);
            m_pou_array->push_back(pou);
        }
    }

    /// interface instance;
    m_interface = m_diag_pou->interface();

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

void CVariablesAnalytics::bind_pins(CDiagramObject *object)
{
    for (auto &pin : *object->pins())
    {
        find_chine(pin);
    }
}

bool CVariablesAnalytics::find_chine(CConnectorPin *&p_pin)
{
    if (m_diag_pou->bodies()->empty())
    {
        throw std::runtime_error("not prepared data in 'CVariablesAnalytics::find_chine'");
    }

    /// search output variables in the body if connection by VARIABLE (not graphics)
    switch (p_pin->direction())
    {
        case PD_INPUT:
            if (find_input_data(p_pin))
            {
                return true;
            }
            break;
        case PD_OUTPUT:
            if (find_output_data(p_pin))
            {
                return true;
            }
            break;
        case PD_IN_OUT:
            /*if (find_in_out_data(p_pin))
            {
                return true;
            }*/
            break;
        default:
            return false;
    }

    /// we are here. It means graphics connection between blocks
    auto pin_ref_id = p_pin->ref_local_id();
    auto body = m_diag_pou->bodies()->front();

    for (auto &block : *body->fbd_content()->blocks())
    {
        if (block->local_id() != pin_ref_id)
        {
            continue;
        }

        /// find our output
        std::string inp_expr = p_pin->block_var()->point_in()->formal_param().toStdString();
        CFilter::capitalize_word(inp_expr);
        for (auto &block_var : *block->output_variables())
        {
            auto var_express = block_var->formal_parameter().toStdString();
            CFilter::capitalize_word(var_express);
            if (var_express != inp_expr)
            {
                continue;
            }

            QString pin_text = block->instance_name().isEmpty() ? block->type_name() + "_" + QString::number(block->local_id()) :
                               block->instance_name();
            pin_text += "." + block_var->formal_parameter();
            pin_text = "";
            p_pin->set_graphic_base(block->local_id(), block_var, pin_text);
            return true;
        }

        ///< hmm. block is found, but output is none. I think it is library from beremiz and project from OpenPLC
        fprintf(stderr, "Block is found, but no output was found in 'CVariablesAnalytics::find_chine'\n");
        throw std::runtime_error("Block is found, but no output was found in 'CVariablesAnalytics::find_chine'");
    }

    /// empty pin
    return false;
}

bool CVariablesAnalytics::find_input_data(CConnectorPin *pin)
{
    auto body = m_diag_pou->bodies()->front();
    auto pin_ref_id = pin->ref_local_id();

    bool is_constant = true;

    for (auto &in : *body->fbd_content()->inVariables())
    {
        auto in_local_id = in->local_id();
        if (in_local_id != pin_ref_id)
        {
            continue;
        }

        /// наличие в пине in_variable и отсутствие iface_variable означает что in_variable - константа
        pin->set_in_variable(in);

        QString expression = in->expression()->expression();

        for (auto &var: m_diag_pou->interface()->all_variables())
        {
            if (var->name() != expression)
            {
                continue;
            }
            /// есть таки iface_variable, значит не константа
            pin->set_iface_variable(var);
            is_constant = false;
        }

        if (!is_constant)
        {
            return true;
        }

        std::string expr = in->expression()->expression().toStdString();
        auto df_type = CFilter::get_type_from_const(expr);
        pin->set_type(base_types_names[df_type]);
    }
    return false;
}

bool CVariablesAnalytics::find_output_data(CConnectorPin *pin)
{
    auto body = m_diag_pou->bodies()->front();

    uint64_t block_id = pin->parent()->block()->local_id();
    QString  pin_formal = pin->formal_param();

    for (auto &out_var : *body->fbd_content()->out_variables())
    {
        uint64_t var_ref_id = out_var->point_in()->ref_local_id();
        QString  var_formal_param = out_var->formal_parameter();

        if (var_ref_id == block_id && var_formal_param == pin_formal)
        {
            pin->set_out_variable(out_var);
            return true;
        }
    }
    return false;
}

void CVariablesAnalytics::collect_pins_data(std::vector<s_tree_item> &tree_items, CConnectorPin *pin)
{
    uint16_t  id = 1;
    std::vector<s_tree_item> items;
    std::vector<s_tree_item> items_v;

    CFilter filter(this);

    /// collecting interface variables
    for (auto &var : m_diag_pou->interface()->all_variables())
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

        bool check = check_pin_compatibility(pin->derived_type(),
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

        items.push_back(item);
    }

    /// collecting block's in/outs
    for (auto &body : *m_diag_pou->bodies())
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
                                                                         CConnectorPin *pin, uint16_t &id)
{
// TODO: later select only needed outputs, not all
    //auto pin_type = pin->type();

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
                QString dragged_pin_type_name = pin->type() == DDT_DERIVED ? pin->derived_type() :
                                                base_types_names[pin->type()];
                EDefinedDataTypes dragged_pin_type = pin->type();

                /// info about alien pin type
                QString target_pin_type_name = connector->type() == DDT_DERIVED ? connector->derived_type() :
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
                sub_item.name = connector->formal_param().toStdString();

                tree_items.push_back(sub_item);
            }
        }

    }

    return tree_items;
}

std::vector<s_tree_item> CVariablesAnalytics::find_fbd_outputs_collection(CFbdContent * /*body_content*/,
                                                                          CConnectorPin *pin, uint16_t &id)
{
    // TODO: later select only needed outputs, not all
    //auto pin_type = pin->type();

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
                QString dragged_pin_type_name = pin->type() == DDT_DERIVED ? pin->derived_type() :
                                                base_types_names[pin->type()];
                EDefinedDataTypes dragged_pin_type = pin->type();

                /// info about alien pin type
                QString target_pin_type_name = connector->type() == DDT_DERIVED ? connector->derived_type() :
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
                sub_item.name = connector->formal_param().toStdString();

                tree_items.push_back(sub_item);
            }
        }

    }

    return tree_items;
}

bool CVariablesAnalytics::find_target(const std::string &variable, CConnectorPin **pin, CVariable ** iface_var)
{
    /// define names
    auto pos = variable.find('.');
    auto target_name = variable.substr(0, pos);
    auto pin_name = variable.substr(pos + 1, variable.length()-1);

    /// search target in interface
    CFilter filter(this);

    for (auto &var : m_interface->all_variables())
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
                if (connector->formal_param().toStdString() != pin_name )
                {
                    continue;
                }
                *pin = connector;
                return true;
            }
        }
    }

    return false;
}

CInterface *CVariablesAnalytics::local_pou_interface()
{
    return m_interface;
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
    /// for single usage only
    {
        QStringList lib_pous = m_standard_library->objects();
//
        QFile file("lib_pous.txt");
        file.open(QIODevice::WriteOnly);
//
        QTextStream qout(&file);
//
        for (auto &txt: lib_pous)
        {
            qout << txt << "\n";
        }
//
        file.close();
    }

    bool is_object_pou = false;
    /// define source: libraries, POU
    for (auto &pou : *m_pou_array)
    {
        if (pou->is_empty() || pou->interface()->is_empty())
        {
            continue;
        }

        /// well it is our pou
        auto o_type = block->type_name();
        auto p_name = pou->name();
        bool not_found = true;

        if (o_type == p_name)
        {
            for (auto &pin : *block->input_variables())
            {
                check_variables(pin, -1, pou->interface());
            }

            for (auto &pin : *block->output_variables())
            {
                check_variables(pin, 1, pou->interface());
            }
            for (auto &pin : *block->in_out_variables())
            {
                check_variables(pin, 0, pou->interface());
            }

//            if (not_found) // -1 input; 0 - in-out; 1 - out
//            {
//                throw std::runtime_error("logic broken in 'CVariablesAnalytics::setup_block'");
//            }

            is_object_pou = true;
            break;
        }
    }

    if (is_object_pou)
        return;

    /// well, it's library. Not available now (later)
    for (auto &std_type : m_standard_library->objects())
    {
        if (std_type == block->type_name())
        {
            if (!get_library_type_data(block, std_type))
            {
                throw std::runtime_error("тогда что это может быть???");
            }
        }
    }
    //    if (!is_object_pou)
//    {
//        for (auto &pin : *block->pins())
//        {
//            pin->set_type("ANY_NUM");
//        }
//    }

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

//CVariable* CVariablesAnalytics::find_var(CBlockVar *pin, CInterface *standard_iface)
//{
//    for (auto &var : standard_iface->all_variables())
//    {
//        if (var->name() == pin->formal_parameter())
//        {
//            pin->set_iface_variable(var);
//            return var;
//        }
//    }
//    return nullptr;
//}

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
