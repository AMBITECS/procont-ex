//
// Created by nechi on 25.11.2024.
//

#ifndef EDITORSD_CFILTER_H
#define EDITORSD_CFILTER_H

#include "../../plc-xml/includes.h"

class COglWorld;

/// for bitwise 'or' in parameter support
enum FilterFlags
{
    ff_service_names = 1,
    ff_base_types,
    ff_naming = 4,
    ff_local_env = 8,
    ff_user_types = 16,
    ff_pou_names = 32,
    ff_library = 64,
    ff_all_flags = 128
};

enum ETimeMeasure
{
    ET_HOUR,
    ET_MINUTE,
    ET_SEC,
    ET_MS,
    ET_COUNT
};

const std::string time_measere_str[ET_COUNT]
{
    "h",
    "m",
    "s",
    "ms"
};



class CVariablesAnalytics;

/**
 * @brief класс для фильтрации текста по параметрам:<br>
 * - совпадение со служебными словами<br>
 * - совпадение с базовыми типами<br>
 * - выполнение правил именования переменных<br>
 * - совпадение с имеющимися в интерфейсе переменными<br>
 * - совпадение с именами POU<br>
 * @attention
 * Использование класса "локальное", т.е. создали, отфильтровали, удалили (если не в цикле). Причина: создается копия проекта(!).
 * Размер программы это вам не это. Скорее всего изменю конструктор и в нём экземпляр CVariableAnalytics, там уже есть копия всего проекта
 */
class CFilter
{
public:
    //explicit CFilter(const bool & case_insensitive = true);
    CFilter() = delete;
    CFilter(const CFilter &) = delete;
    explicit CFilter(CVariablesAnalytics *var_analytics, const bool & case_insensitive = true);
    explicit CFilter(COglWorld *world, const bool & case_insensitive = true);
    ~CFilter();

    static EDefinedDataTypes get_type_from_const(const std::string &expression);

    /**
     * @brief register-independent type comparison is set in constructor. returns TRUE if OK - string could be new variable.
     * @code filter_string("sad", ff_naming | ff_local_env);
     */
    [[nodiscard]] bool    filter_string(const std::string &string, const int & flags);

    static void capitalize_word(std::string &word);

    /**
     *
     * @param[out] t_measure detected time measure (ms/s/h)
     * @param[in] time_str something like "T#451ms"
     * @param[out] is_err if translate error detected
     * @return uint16_t time value
     */
    static uint32_t time_to_int(ETimeMeasure & t_measure, const QString & time_str, bool * is_err = nullptr);

    static QString int_to_time(const ETimeMeasure & measure, uint16_t period);
    static ETimeMeasure time_meas_from_str(const std::string &meas_str);

private:
    bool    m_is_case_insensitive{true};
    CVariablesAnalytics *m_analytics;
    bool is_local_analytic;
};



static const QString service_words[32]
{
        "IF",
        "ELSEIF",
        "ELSE",
        "END_IF",
        "THEN",
        "EXIT",
        "FOR",
        "END_FOR",
        "TO",
        "DO",
        "WHILE",
        "END_WHILE",
        "UNTIL",
        "CASE",
        "END_CASE",
        "REPEAT",
        "END_REPEAT",
        "VAR",
        "END_VAR",
        "OF",
        "PROGRAM",
        "END_PROGRAM",
        "SEL",
        "mod",
        "OR",
        "AND",
        "XOR",
        "NOT",
        "FUNCTION_BLOCK",
        "FUNCTION",
        "VAR_INPUT",
        "VAR_OUTPUT"
};

#endif //EDITORSD_CFILTER_H
