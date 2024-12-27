//
// Created by nechi on 25.11.2024.
//

#include "CFilter.h"
#include <algorithm>
#include <regex>
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"
#include "editor/fbd/fbd/graphics/COglWorld.h"


CFilter::CFilter(CVariablesAnalytics *var_analytics, const bool &case_insensitive)
{
    m_is_case_insensitive = case_insensitive;
    m_analytics = var_analytics;
    is_local_analytic = false;
}

CFilter::CFilter(COglWorld *world, const bool &case_insensitive)
{
    m_is_case_insensitive = case_insensitive;
    m_analytics = new CVariablesAnalytics(world, world->current_pou()->name());
    is_local_analytic = true;
}

CFilter::~CFilter()
{
    if (is_local_analytic)
    {
        delete m_analytics;
    }
}

bool CFilter::filter_string(const std::string &string, const int &flags)
{
    bool  service = true,
          base_type = true,
          naming = true,
          local_env = true,
          user_types = true,
          library_type = true,
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
        for (auto &name : lib->objects())
        {
            std::string comp_name = name.toStdString();
            if (m_is_case_insensitive)
            {
                capitalize_word(comp_name);
            }
            if (comp_name == compare_str)
            {
                library_type = false;
                break;
            }
        }
    }

    return service && base_type && naming && local_env && user_types && pou_names && library_type;
}

EDefinedDataTypes CFilter::get_type_from_const(const std::string &expression)
{
    std::regex time_mask("^(t#|time#){1}[0-9]+(ms|s|h|m){1}$", std::regex_constants::icase);
    if (std::regex_match(expression, std::regex(time_mask)))
    {
        return DDT_TIME;
    }
    std::regex date_mask_alien("(^(d#|date#){1}[0-9]{4}-[0-9]{2}-[0-9]{2}$)", std::regex_constants::icase);
    if (std::regex_match(expression, std::regex(date_mask_alien)))
    {
        return DDT_DATE;
    }

    std::regex date_mask_rus(R"(^(d#|date#){1}[0-9]{2}\.[0-9]{2}\.[0-9]{4}$)", std::regex_constants::icase);
    if (std::regex_match(expression, std::regex(date_mask_rus)))
    {
        return DDT_DATE;
    }

    std::regex real_mask(R"(^[+-]?(([0-9]+[\.|,]{1}[0-9]+)|([\.|,]{1}[0-9]+))$)");
    if (std::regex_match(expression, std::regex(real_mask)))
    {
        return DDT_REAL;
    }

    std::regex int_mask("^[+|-]?[0-9]+$");
    if (std::regex_match(expression, std::regex(int_mask)))
    {
        return DDT_INT;
    }

    std::regex uint_mask("^[0-9]+$");
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

    return DDT_DERIVED;
}

uint32_t CFilter::time_to_int(ETimeMeasure &t_measure, const QString &time_str, bool * is_err)
{
    if (is_err)
    {
        *is_err = false;
    }
    /// explode text
    std::string text = time_str.toStdString();

    size_t f_digit_pos = text.find('#');

    size_t l_digit_pos = text.length();
    for (auto riter = text.rbegin(); riter < text.rend(); riter++)
    {
        l_digit_pos--;

        if (!std::isdigit(*riter))
        {
            continue;
        }
        break;
    }

    std::string val_str = text.substr(f_digit_pos + 1, (l_digit_pos - f_digit_pos));
    std::string measure_str = text.substr(l_digit_pos + 1, text.length());

    ETimeMeasure t_mes =time_meas_from_str(measure_str);
    int  period_value = stoi(val_str);

    if (t_mes == ETimeMeasure::ET_COUNT)
    {
        if (is_err)
            *is_err = true;
        return 0;
    }

    t_measure = t_mes;

    return period_value;
}

ETimeMeasure CFilter::time_meas_from_str(const std::string &meas_str)
{
    std::string str_cap = meas_str;
    CFilter::capitalize_word(str_cap);
    std::string meas_cap = str_cap;
    int counter = 0;

    for (auto &str : time_measere_str)
    {
        str_cap = str;
        CFilter::capitalize_word(str_cap);

        if (str_cap == meas_cap)
        {
            return (ETimeMeasure)counter;
        }

        counter++;
    }

    return ETimeMeasure::ET_COUNT;
}

QString CFilter::int_to_time(const ETimeMeasure & measure, uint16_t period)
{
    return QString();
}

void inline CFilter::capitalize_word(std::string &word)
{
    for (auto &sym : word)
    {
        sym = static_cast<char>(std::toupper(sym));
    }
}


