

#ifndef EDITORSD_PALETTE_H
#define EDITORSD_PALETTE_H

#include <QString>
#include <QStringList>
#include <QIcon>
#include <QMap>

/** базовая конструкция палитры. эти значения - определения палитры
 * а так же индексы для доступа к дополнительным параметрам:<BR>
 * - иконки<BR>
 * - XML-наименования различных элементов<BR>
 * - XML-блоки различных элементов<BR>
 */
enum EPaletteElements
{
    EG_CIRCUIT,
    EG_RETURN,
    EG_GOTO,
    EG_LABEL,
    EG_EXECUTE,

    EL_AND,
    EL_OR,
    EL_NOT,
    EL_XOR,
    EL_SHL,
    EL_SHR,
    EL_ROR,
    EL_ROL,

    EM_ADD,
    EM_ADD_TIME,
    EM_SUB,
    EM_SUB_TIME,
    EM_MUL,
    EM_DIV,
    EM_EQ,
    EM_NE,
    EM_LT,
    EM_LE,
    EM_GT,
    EM_GE,
    EM_ABS,
    EM_SQRT,
    EM_LN,
    EM_LOG,
    EM_EXP,
    EM_SIN,
    EM_COS,
    EM_TAN,
    EM_ASIN,
    EM_ACOS,
    EM_ATAN,
    EM_MOD,
    EM_MAX,
    EM_MIN,

    EO_SEL,
    EO_MUX,
    EO_LIMIT,
    EO_MOVE,
    EO_CONV,

    EF_R_TRIG,
    EF_F_TRIG,
    EF_RS,
    EF_SR,
    EF_TON,
    EF_TOF,
    EF_CTU,
    EF_CTD,
    EF_PID,
    EF_RAMP,
    EF_HYSTERESIS,
    EF_SEMA,
    EF_INTEGRAL,
    EF_RTC,
    EF_TP,
    EF_TRUNC,
    EF_EXPT,

    EP_FBD,
    // здесь будут LD элементы
    // LD_CONTACT_NO
    // LD_CONTACT_NC
    // SFC, CFC...
    EP_ST,
    EP_LD2,
    EP_LD,
    EP_SFC,
    EP_CFC,
    E_COUNT
};

/// XML name and corresponding enum
static QMap<EPaletteElements, QString>  pou_item_names
{
        {EG_CIRCUIT, "CIRCUIT"},
        {EG_RETURN,"RETURN"},
        {EG_GOTO,"GOTO_LABEL"},
        {EG_LABEL, "LABEL"},
        {EG_EXECUTE,"EXECUTE"},

        {EL_AND,"AND"},
        {EL_OR,"OR"},
        {EL_NOT, "NOT"},
        {EL_XOR,"XOR"},
        {EL_SHL, "SHL"},
        {EL_SHR, "SHR"},
        {EL_ROR, "ROR"},
        {EL_ROL, "ROL"},

        {EM_ADD,"ADD"},
        {EM_ADD_TIME, "ADD_TIME"},
        {EM_SUB,"SUB"},
        {EM_SUB_TIME,"SUB_TIME"},
        {EM_MUL,"MUL"},
        {EM_DIV,"DIV"},
        {EM_EQ,"EQ"},
        {EM_NE,"NE"},
        {EM_LT,"LT"},
        {EM_LE,"LE"},
        {EM_GT,"GT"},
        {EM_GE,"GE"},
        {EM_ABS, "ABS"},
        {EM_SQRT, "SQRT"},
        {EM_LN, "LN"},
        {EM_LOG, "LOG"},
        {EM_EXP, "EXP"},
        {EM_SIN, "SIN"},
        {EM_COS, "COS"},
        {EM_TAN, "TAN"},
        {EM_ASIN, "ASIN"},
        {EM_ACOS, "ACOS"},
        {EM_ATAN, "ATAN"},
        {EM_MOD, "MOD"},
        {EM_MAX, "MAX"},
        {EM_MIN, "MIN"},


        {EO_SEL,"SEL"},
        {EO_MUX,"MUX"},
        {EO_LIMIT,"LIMIT"},
        {EO_MOVE,"MOVE"},
        {EO_CONV,"CONVERSION"},


        {EF_R_TRIG,"R_TRIG"},
        {EF_F_TRIG,"F_TRIG"},
        {EF_RS,"RS"},
        {EF_SR,"SR"},
        {EF_TON,"TON"},
        {EF_TOF,"TOF"},
        {EF_CTU,"CTU"},
        {EF_CTD,"CTD"},

        {EF_PID, "PID"},
        {EF_RAMP, "RAMP"},
        {EF_HYSTERESIS, "HYSTERESIS"},
        {EF_SEMA, "SEMA"},
        {EF_INTEGRAL, "INTEGRAL"},
        {EF_RTC, "RTC"},
        {EF_TP, "TP"},
        {EF_TRUNC, "TRUNC"},
        {EF_EXPT, "EXPT"},


        {EP_FBD,"FBD"},
        {EP_ST,"ST"},
        {EP_LD2,"LD2"},
        {EP_LD,"LD"},
        {EP_SFC,"SFC"},
        {EP_CFC,"CFC"}
};

///// XML name and corresponding enum
//static QMap<QString, EPaletteElements>  pou_icon_indexes
//{
//        {EG_CIRCUIT, "CIRCUIT"},
//        {EG_ELEMENT, "ELEMENT"},
//        {EG_ELEMENT_EN_ENO"ELEMENT_EN_ENO",},
//        {EG_VARIABLE"VARIABLE",},
//        {EG_TRANSFER"TRANSFER",},
//        {EG_RETURN"RETURN",},
//        {EG_ENTRANCE"ENTRANCE",},
//        {EG_NODE"NODE",},
//        {EG_EXECUTE"EXECUTE",},
//        {EL_AND_2IN"AND",},
//        {EL_AND_3IN"AND3",},
//        {EL_OR_2IN"OR",},
//        {EL_OR_3IN"OR3",},
//        {EL_XOR"XOR",},
//        {EM_ADD_2IN"ADD",},
//        {EM_ADD_3IN"ADD3",},
//        {EM_SUB"SUB",},
//        {EM_MUL"MUL",},
//        {EM_DIV"DIV",},
//        {EM_EQ"EQ",},
//        {EM_NE"NE",},
//        {EM_LT"LT",},
//        {EM_LE"LE",},
//        {EM_GT"GT",},
//        {EM_GE"GE",},
//        {EO_SEL"SEL",},
//        {EO_MUX"MUX",},
//        {EO_LIMIT"LIMIT",},
//        {EO_MOVE"MOVE",},
//        {EO_CONV"CONVERSION",},
//        {EF_R_TRIG"R_TRIG",},
//        {EF_F_TRIG"F_TRIG",},
//        {EF_RS"RS",},
//        {EF_SR"SR",},
//        {EF_TON"TON",},
//        {EF_TOF"TOF",},
//        {EF_CTU"CTU",},
//        {EF_CTD"CTD",},
//        {EP_FBD"FBD", },
//        {"ST", EP_ST},
//        {"LD2", EP_LD2},
//        {"LD", EP_LD},
//        {"SFC", EP_SFC},
//        {"CFC", EP_CFC}
//};

/// icons by index corresponding EPaletteElements
static  QString element_images[EPaletteElements::E_COUNT]
{
    ":/codesys/images/codesys/cirquit.png",
    ":/codesys/images/codesys/return.png",
    "goto.png",
    "label.png",
    ":/codesys/images/codesys/execute.png",

    ":/codesys/images/codesys/and_2_in.png",
    ":/codesys/images/codesys/or_2_in.png",
    "not.png",
    ":/codesys/images/codesys/xor.png",
    "shl.png",
    "shr.png",
    "ror.png",
    "rol.png",

    ":/codesys/images/codesys/add.png",
    "add_time.png",
    ":/codesys/images/codesys/sub.png",
    "sub_time.png",
    ":/codesys/images/codesys/mult.png",
    ":/codesys/images/codesys/div.png",
    ":/codesys/images/codesys/eq.png",
    ":/codesys/images/codesys/ne.png",
    ":/codesys/images/codesys/lt.png",
    ":/codesys/images/codesys/le.png",
    ":/codesys/images/codesys/gt.png",
    ":/codesys/images/codesys/ge.png",
    "EM_ABS",
    "EM_SQRT",
    "EM_LN",
    "EM_LOG",
    "EM_EXP",
    "EM_SIN",
    "EM_COS",
    "EM_TAN",
    "EM_ASIN",
    "EM_ACOS",
    "EM_ATAN",
    "EM_MOD",
    "EM_MAX",
    "EM_MIN",

    ":/codesys/images/codesys/sel.png",
    ":/codesys/images/codesys/mux.png",
    ":/codesys/images/codesys/limit.png",
    ":/codesys/images/codesys/move.png",
    ":/codesys/images/codesys/conv.png",

    ":/codesys/images/codesys/r_trig.png",
    ":/codesys/images/codesys/f_trig.png",
    ":/codesys/images/codesys/rs.png",
    ":/codesys/images/codesys/sr.png",
    ":/codesys/images/codesys/ton.png",
    ":/codesys/images/codesys/tof.png",
    ":/codesys/images/codesys/ctu.png",
    ":/codesys/images/codesys/ctd.png",

    "EF_PID",
    "EF_RAMP",
    "EF_HYSTERESIS",
    "EF_SEMA",
    "EF_INTEGRAL",
    "EF_RTC",
    "EF_TP",
    "EF_TRUNC",
    "EF_EXPT",


    ":/codesys/images/codesys/fbd.png",
    ":/codesys/images/codesys/st.png",
    ":/codesys/images/codesys/ld2.png",
    ":/codesys/images/codesys/ld.png",
    ":/codesys/images/codesys/sfc.png",
    ":/codesys/images/codesys/cfc.png"
};


/// palette groups content: EPaletteElements - is draggable, others are visible
struct s_comp_item
{
    EPaletteElements element;
    QString name;
    QString hint;
};


static QVector<s_comp_item> general_data
{
    {EPaletteElements::EG_CIRCUIT, "Цепь", "Новая пустая цепь"},
    {EPaletteElements::EG_RETURN, "Возврат", "Возврат из вызова POU"},
    {EPaletteElements::EG_GOTO, "Переход", "Переход к метке"},
    {EPaletteElements::EG_LABEL, "Метка", "Метка для перехода"},
    {EPaletteElements::EG_EXECUTE, "Выполнить", "Выполнение данного ST фрагмента"}
};

static QVector<s_comp_item> bitwise_operators
{
    {EPaletteElements::EL_AND, "AND", "Оператор AND"},
    {EPaletteElements::EL_OR, "OR", "Оператор OR"},
    {EPaletteElements::EL_NOT, "NOT", "Оператор NOT"},
    {EPaletteElements::EL_XOR, "XOR", "Оператор XOR"},
    {EPaletteElements::EL_SHL, "SHL", "Сдвиг влево"},
    {EPaletteElements::EL_SHR, "SHR", "Сдвиг вправо"},
    {EPaletteElements::EL_ROR, "ROR", "Цикл. сдвиг вправо"},
    {EPaletteElements::EL_ROL, "ROL", "Циклю сдвиг влево"}

};
static QVector<s_comp_item> math_data
{
    {EPaletteElements::EM_ADD, "ADD", "Сложение"},
    {EPaletteElements::EM_ADD_TIME, "ADD_TIME", "Сложение времени различного формата"},
    {EPaletteElements::EM_SUB, "SUB", "Вычитание"},
    {EPaletteElements::EM_SUB_TIME, "SUB_TIME", "Вычитание времени различного формата"},
    {EPaletteElements::EM_MUL, "MUL", "Умножение"},
    {EPaletteElements::EM_DIV, "DIV", "Деление"},
    {EPaletteElements::EM_EQ, "EQ", "Сравнение на 'равно'"},
    {EPaletteElements::EM_NE, "NE", "Сравнение на 'не равно'"},
    {EPaletteElements::EM_LT, "LT", "Сравнение на 'меньше'"},
    {EPaletteElements::EM_LE, "LE", "Сравнение на 'меньше или равно'"},
    {EPaletteElements::EM_GT, "GT", "Сравнение на 'больше'"},
    {EPaletteElements::EM_GE, "GE", "Сравнение на 'больше или равно'"},
    {EPaletteElements::EM_ABS, "ABS", "Предположу, что абсолютное значение std::abs()"},
    {EPaletteElements::EM_SQRT, "SQRT", "Квадратный корень"},
    {EPaletteElements::EM_LN, "LN", "Натуральный логарифм"},
    {EPaletteElements::EM_LOG, "LOG", "Десятичный логарифм"},
    {EPaletteElements::EM_EXP, "EXP", "Экспонента"},
    {EPaletteElements::EM_SIN, "SIN", "Синус"},
    {EPaletteElements::EM_COS, "COS", "Косинус"},
    {EPaletteElements::EM_TAN, "TAN", "Тангенс"},
    {EPaletteElements::EM_ASIN, "ASIN", "Арксинус"},
    {EPaletteElements::EM_ACOS, "ACOS", "Арккосинус"},
    {EPaletteElements::EM_ATAN, "ATAN", "Арктангенс"},
    {EPaletteElements::EM_MOD, "MOD", "Даже не спрашиваете про отличия MOD и ABS"},
    {EPaletteElements::EM_MAX, "MAX", "Выбор максимального значения"},
    {EPaletteElements::EM_MIN, "MIN", "Выбор минимального значения"},
    {EPaletteElements::EF_INTEGRAL, "INTEGRAL", "Интеграл (?)"}
};

static QVector<s_comp_item> other_data
{
    {EPaletteElements::EO_SEL, "SEL", "Двоичный селектор"},
    {EPaletteElements::EO_MUX, "MUX", "Расширяемый мультиплексор"},
    {EPaletteElements::EO_LIMIT, "LIMIT", "Оператор LIMIT"},
    {EPaletteElements::EO_MOVE, "MOVE", "Оператор MOVE"},
    {EPaletteElements::EO_CONV, "Конверсия", "Оператор конверсии"},
    {EPaletteElements::EF_SEMA, "SEMA", "Семафор"},
    {EPaletteElements::EF_RTC, "RTC", "Счётчик реального времени"},
    {EPaletteElements::EF_TP, "TP", "???"},
    {EPaletteElements::EF_TRUNC, "TRUNC", "Усечение"},
    {EPaletteElements::EF_EXPT, "EXPT", "???"},
};
static QVector<s_comp_item> func_blocks_data
{
    {EPaletteElements::EF_R_TRIG, "R_TRIG", "Функциональный блок обнаружения переднего фронта"},
    {EPaletteElements::EF_F_TRIG, "F_TRIG", "Функциональный блок обнаружения заднего фронта"},
    {EPaletteElements::EF_RS, "RS", "Однотригерный функциональный блок с доминантным RESET"},
    {EPaletteElements::EF_SR, "SR", "Однотригерный функциональный блок с доминантным SET"},
    {EPaletteElements::EF_TON, "TON", "Функциональный блок таймера с задержкой включения"},
    {EPaletteElements::EF_TOF, "TOF", "Функциональный блок таймера с задержкой выключения"},
    {EPaletteElements::EF_CTU, "CTU", "Суммирующий счётчик"},
    {EPaletteElements::EF_CTD, "CTD", "Обратный счётчик"},
    {EPaletteElements::EF_PID, "PID", "PID-регулятор с обр. связью"},
    {EPaletteElements::EF_RAMP, "RAMP", "???"},
    {EPaletteElements::EF_HYSTERESIS, "HYSTERESIS", "Петля гистерезиса"}
};

#include "components_palette.inc"

#endif //EDITORSD_PALETTE_H
