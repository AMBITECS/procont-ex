//
// Created by nechi on 25.11.2024.
//

#include "CFilter.h"
#include <algorithm>
#include <regex>
#include "CVariablesAnalytics.h"


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
          pou_names = true;

    std::string compare_str = string;

    if (m_is_case_insensitive)
    {
        capitalize_word(compare_str);
    }

    if ((flags & ff_service_names) == ff_service_names)
    {
        /*auto res = std::any_of(service_words->begin(),
                               service_words->end(),
                               [compare_str](const QString &word)
                                    {return compare_str == word.toStdString();});
        service = !res;*/
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

    if ((flags & ff_base_types) == ff_base_types)
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

    if ((flags & ff_naming) == ff_naming)
    {
        const char *reg = "[a-zA-Z][a-zA-Z0-9_]*";
        naming =  std::regex_match(compare_str, std::regex(reg));
    }

    if ((flags & ff_local_env) == ff_local_env)
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

    if ((flags & ff_user_types) == ff_user_types)
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

    if ((flags & ff_pou_names) == ff_pou_names)
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

    return service && base_type && naming && local_env && user_types && pou_names;
}

EDefinedDataTypes CFilter::get_type_from_const(const std::string &expression)
{
    /// check if letters
    const char * not_str = "\\D+";
    if (std::regex_match(expression, std::regex(not_str)))
    {
        return DDT_STRING;
    }

    const char * time_mask = "/^(T#)[0-9]+(ms|s|h|m)?$/i";
    if (std::regex_match(expression, std::regex(time_mask)))
    {
        return DDT_TIME;
    }
    const char * date_mask = "^[0-9]{2}(?:/|\\.)[0-9]{2}(?:/|\\.)[0-9]{4}$";
    if (std::regex_match(expression, std::regex(date_mask)))
    {
        return DDT_DATE;
    }

    const char *real_mask = R"([+-]?(([1-9]\d*\.\d*)|(0\.\d*[1-9]\d*)))";
    if (std::regex_match(expression, std::regex(real_mask)))
    {
        return DDT_REAL;
    }

    const char * int_mask = "(\\\\+|-)?[0-9]+";
    if (std::regex_match(expression, std::regex(int_mask)))
    {
        return DDT_INT;
    }

    const char * uint_mask = "[0-9]+";
    if (std::regex_match(expression, std::regex(uint_mask)))
    {
        return DDT_UINT;
    }

    return DDT_ANY_NUM;
}


