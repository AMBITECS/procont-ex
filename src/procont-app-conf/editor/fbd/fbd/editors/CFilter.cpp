//
// Created by nechi on 25.11.2024.
//

#include "CFilter.h"
#include <algorithm>
#include <regex>
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"


CFilter::CFilter(CVariablesAnalytics *var_analytics, const bool &case_insensitive)
{
    m_is_case_insensitive = case_insensitive;
    m_analytics = var_analytics;
}

CFilter::~CFilter()
= default;

bool CFilter::filter_string(const std::string &string, const int &flags)
{
    bool  service = true,
          base_type = true,
          naming = true,
          local_env = true,
          user_types = true,
          libary_type = true,
          pou_names = true;

    std::string compare_str = string;

    if (m_is_case_insensitive)
    {
        capitalize_word(compare_str);
    }

    if ((flags & ff_service_names) == ff_service_names || (flags & ff_all_flags) == ff_all_flags)
    {
        for (auto &word : service_words)
        {
            if (compare_str != word.toStdString())
            {
                continue;
            }
            service = false;
            break;
        }
    }

    if ((flags & ff_base_types) == ff_base_types  || (flags & ff_all_flags) == ff_all_flags)
    {
        QString compare = compare_str.c_str();
        for (auto &type : base_types_names)
        {
            if (type != compare)
            {
                continue;
            }
            base_type = false;
            break;
        }
    }

    if ((flags & ff_naming) == ff_naming  || (flags & ff_all_flags) == ff_all_flags)
    {
        const char *reg = "[a-zA-Z][a-zA-Z0-9_]*";
        naming =  std::regex_match(compare_str, std::regex(reg));
    }

    if ((flags & ff_local_env) == ff_local_env  || (flags & ff_all_flags) == ff_all_flags)
    {
        auto iface = m_analytics->local_pou_interface();
        for (auto &var : iface->all_variables())
        {
            std::string var_name = var->name().toStdString();

            if (m_is_case_insensitive)
            {
                capitalize_word(var_name);
            }

            if (compare_str != var_name)
            {
                continue;
            }
            local_env = false;
            break;
        }
    }

    if ((flags & ff_user_types) == ff_user_types  || (flags & ff_all_flags) == ff_all_flags)
    {
        for (auto &u_type : *m_analytics->user_types())
        {
            std::string utype_name = u_type->name().toStdString();

            if (m_is_case_insensitive)
            {
                capitalize_word(utype_name);
            }

            if (compare_str != utype_name)
            {
                continue;
            }

            user_types = false;
            break;
        }
    }

    if ((flags & ff_pou_names) == ff_pou_names  || (flags & ff_all_flags) == ff_all_flags)
    {
        for (auto &pou : *m_analytics->pou_array())
        {
            std::string  pou_name = pou->name().toStdString();

            if (m_is_case_insensitive)
            {
                capitalize_word(pou_name);
            }

            if (pou_name != compare_str)
            {
                continue;
            }
            pou_names = false;
            break;
        }
    }

    if ((flags & ff_library) == ff_library || (flags & ff_all_flags) == ff_all_flags)
    {
        auto lib = m_analytics->standard_library();
        for (auto name : lib->objects())
        {
            std::string comp_name = name.toStdString();
            if (m_is_case_insensitive)
            {
                capitalize_word(comp_name);
            }
            if (comp_name == compare_str)
            {
                libary_type = false;
                break;
            }
        }
    }

    return service && base_type && naming && local_env && user_types && pou_names && libary_type;
}

EDefinedDataTypes CFilter::get_type_from_const(const std::string &expression)
{
    const char * time_mask = "^(t#|time#){1}[\\d]+(ms|s|h|m){1}$/i";
    if (std::regex_match(expression, std::regex(time_mask)))
    {
        return DDT_TIME;
    }
    const char * date_mask_alien = R"(^(d#|date#){1}[\d]{4}-[\d]{2}-[\d]{2}$)";
    if (std::regex_match(expression, std::regex(date_mask_alien)))
    {
        return DDT_DATE;
    }

    const char * date_mask_rus = R"(^(d#|date#){1}[\d]{2}\.[\d]{2}\.[\d]{4}$)";
    if (std::regex_match(expression, std::regex(date_mask_rus)))
    {
        return DDT_DATE;
    }

    const char *real_mask = R"(^[+-]?((\d+[\.|\,]+\d+)|([\.|\,]+\d+))$)";
    if (std::regex_match(expression, std::regex(real_mask)))
    {
        return DDT_REAL;
    }

    const char * int_mask = "^[+|-]?[0-9]+$";
    if (std::regex_match(expression, std::regex(int_mask)))
    {
        return DDT_INT;
    }

    const char * uint_mask = "^[0-9]+$";
    if (std::regex_match(expression, std::regex(uint_mask)))
    {
        return DDT_UINT;
    }

    /// check if letters
    const char * not_str = "^\\D+$";
    if (std::regex_match(expression, std::regex(not_str)))
    {
        return DDT_STRING;
    }


    return DDT_UNDEF;
}


