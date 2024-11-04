

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
    EG_ELEMENT,
    EG_ELEMENT_EN_ENO,
    EG_VARIABLE,
    EG_TRANSFER,
    EG_RETURN,
    EG_ENTRANCE,
    EG_NODE,
    EG_EXECUTE,
    EL_AND_2IN,
    EL_AND_3IN,
    EL_OR_2IN,
    EL_OR_3IN,
    EL_XOR,
    EM_ADD_2IN,
    EM_ADD_3IN,
    EM_SUB,
    EM_MUL,
    EM_DIV,
    EM_EQ,
    EM_NE,
    EM_LT,
    EM_LE,
    EM_GT,
    EM_GE,
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
static QMap<QString, EPaletteElements>  pou_icon_indexes
{
    {"CIRCUIT",EG_CIRCUIT},
    {"CIRCUIT",EG_ELEMENT},
    {"ELEMENT_EN_ENO",EG_ELEMENT_EN_ENO},
    {"VARIABLE",EG_VARIABLE},
    {"TRANSFER",EG_TRANSFER},
    {"RETURN",EG_RETURN},
    {"ENTRANCE",EG_ENTRANCE},
    {"NODE",EG_NODE},
    {"EXECUTE",EG_EXECUTE},
    {"AND",EL_AND_2IN},
    {"AND3",EL_AND_3IN},
    {"OR",EL_OR_2IN},
    {"OR3",EL_OR_3IN},
    {"XOR",EL_XOR},
    {"ADD",EM_ADD_2IN},
    {"ADD3",EM_ADD_3IN},
    {"SUB",EM_SUB},
    {"MUL",EM_MUL},
    {"DIV",EM_DIV},
    {"EQ",EM_EQ},
    {"NE",EM_NE},
    {"LT",EM_LT},
    {"LE",EM_LE},
    {"GT",EM_GT},
    {"GE",EM_GE},
    {"SEL",EO_SEL},
    {"MUX",EO_MUX},
    {"LIMIT",EO_LIMIT},
    {"MOVE",EO_MOVE},
    {"CONVERSION",EO_CONV},
    {"R_TRIG",EF_R_TRIG},
    {"F_TRIG",EF_F_TRIG},
    {"RS",EF_RS},
    {"SR",EF_SR},
    {"TON",EF_TON},
    {"TOF",EF_TOF},
    {"CTU",EF_CTU},
    {"CTD",EF_CTD},
    {"FBD", EP_FBD},
    {"ST", EP_ST},
    {"LD2", EP_LD2},
    {"LD", EP_LD},
    {"SFC", EP_SFC},
    {"CFC", EP_CFC}
};

/// icons by index corresponding EPaletteElements
static  QString element_images[EPaletteElements::E_COUNT]
{
    ":/codesys/images/codesys/cirquit.png",
    ":/codesys/images/codesys/element.png",
    ":/codesys/images/codesys/element_en_eno.png",
    ":/codesys/images/codesys/variable.png",
    ":/codesys/images/codesys/transfer.png",
    ":/codesys/images/codesys/return.png",
    ":/codesys/images/codesys/entrance.png",
    ":/codesys/images/codesys/node.png",
    ":/codesys/images/codesys/execute.png",
    ":/codesys/images/codesys/and_2_in.png",
    ":/codesys/images/codesys/and_3_in.png",
    ":/codesys/images/codesys/or_2_in.png",
    ":/codesys/images/codesys/or_3_in.png",
    ":/codesys/images/codesys/xor.png",
    ":/codesys/images/codesys/add.png",
    ":/codesys/images/codesys/add_3.png",
    ":/codesys/images/codesys/sub.png",
    ":/codesys/images/codesys/mult.png",
    ":/codesys/images/codesys/div.png",
    ":/codesys/images/codesys/eq.png",
    ":/codesys/images/codesys/ne.png",
    ":/codesys/images/codesys/lt.png",
    ":/codesys/images/codesys/le.png",
    ":/codesys/images/codesys/gt.png",
    ":/codesys/images/codesys/ge.png",
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
    {EPaletteElements::EG_ELEMENT, "Элемент", "Пустой элемент"},
    {EPaletteElements::EG_ELEMENT_EN_ENO, "Элемент с EN/ENO", "Пустой элемент с EN/ENO"},
    {EPaletteElements::EG_VARIABLE, "Присваивание", "Новое присваивание или расширение существующего присваивания"},
    {EPaletteElements::EG_TRANSFER, "Переход", "Переход к метке"},
    {EPaletteElements::EG_RETURN, "Возврат", "Возврат из вызова POU"},
    {EPaletteElements::EG_ENTRANCE, "Вход", "Вход как расширение оператора, такого как AND, OR, ..."},
    {EPaletteElements::EG_NODE, "Ветвь", "Элемент ветвь для разделения потока сигналов"},
    {EPaletteElements::EG_EXECUTE, "Выполнить", "Выполнение данного ST фрагмента"}
};

static QVector<s_comp_item> logic_data
{
    {EPaletteElements::EL_AND_2IN, "AND", "Логический оператор AND с двумя входами"},
    {EPaletteElements::EL_AND_3IN, "AND с 3 входами", "Логический оператор AND с тремя входами"},
    {EPaletteElements::EL_OR_2IN, "OR", "Логический оператор OR с двумя входами"},
    {EPaletteElements::EL_OR_3IN, "OR с тремя входами", "Логический оператор OR с тремя входами"},
    {EPaletteElements::EL_XOR, "XOR", "Логический оператор XOR с двумя входами"}
};
static QVector<s_comp_item> math_data
{
    {EPaletteElements::EM_ADD_2IN, "ADD (2 входа)", "Сложение (ADD) с двумя входами"},
    {EPaletteElements::EM_ADD_3IN, "ADD (3 входа)", "Сложение (ADD) с тремя входами"},
    {EPaletteElements::EM_SUB, "SUB", "Вычитание"},
    {EPaletteElements::EM_MUL, "MUL", "Умножение"},
    {EPaletteElements::EM_DIV, "DIV", "Деление"},
    {EPaletteElements::EM_EQ, "EQ", "Сравнение на 'равно'"},
    {EPaletteElements::EM_NE, "NE", "Сравнение на 'не равно'"},
    {EPaletteElements::EM_LT, "LT", "Сравнение на 'меньше'"},
    {EPaletteElements::EM_LE, "LE", "Сравнение на 'меньше или равно'"},
    {EPaletteElements::EM_GT, "GT", "Сравнение на 'больше'"},
    {EPaletteElements::EM_GE, "GE", "Сравнение на 'больше или равно'"}
};

static QVector<s_comp_item> other_data
{
    {EPaletteElements::EO_SEL, "SEL", "Двоичный селектор"},
    {EPaletteElements::EO_MUX, "MUX", "Расширяемый мультиплексор"},
    {EPaletteElements::EO_LIMIT, "LIMIT", "Оператор LIMIT"},
    {EPaletteElements::EO_MOVE, "MOVE", "Оператор MOVE"},
    {EPaletteElements::EO_CONV, "Конверсия", "Оператор конверсии"}
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
    {EPaletteElements::EF_CTD, "CTD", "Обратный счётчик"}
};

#include "components_palette.inc"

#endif //EDITORSD_PALETTE_H
