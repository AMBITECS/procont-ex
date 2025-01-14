#include "translation.h"

#include <QDebug>

tr_str * tr_str::_m_instance = nullptr;

tr_str::tr_str()
{
    _m_strings_ru["functionBlock"] = tr("functionBlock");
    _m_strings_ru["functionBlock#1"] = tr("functionBlock#1");
    _m_strings_ru["function"] = tr("function");
    _m_strings_ru["function#1"] = tr("function#1");
    _m_strings_ru["dataType"] = tr("dataType");
    _m_strings_ru["dataType#1"] = tr("dataType#1");
    _m_strings_ru["dataTypes"] = tr("dataTypes");
    _m_strings_ru["pous"] = tr("pous");
    _m_strings_ru["pou"] = tr("pou");
    _m_strings_ru["program"] = tr("program");
    _m_strings_ru["program#1"] = tr("program#1");
    _m_strings_ru["variable"] = tr("variable");
    _m_strings_ru["User defined"] = tr("User defined");
    _m_strings_ru["Standard Function Blocks"] = tr("Standard Function Blocks");
    _m_strings_ru["Standard IEC Functions"] = tr("Standard IEC Functions");
    _m_strings_ru["Additional Function Blocks"] = tr("Additional Function Blocks");

    _m_strings_letter["functionBlock"] = "function block";
    _m_strings_letter["functionBlock#1"] = "Function block";
    _m_strings_letter["function"] = "function";
    _m_strings_letter["function#1"] = "Function";
    _m_strings_letter["dataType"] = "data type";
    _m_strings_letter["dataType#1"] = "Data type";
    _m_strings_letter["program"] = tr("program");
    _m_strings_letter["program#1"] = tr("Program");
}

QString tr_str::ru(const QString &word_en_, eTranslateLetters letter_)
{
    if(auto _word = word_en_+letterToStr(letter_) ; _m_strings_ru.contains(_word))
        return _m_strings_ru.value(_word);

    return word_en_;
}

QString tr_str::en(const QString &word_ru_)
{   
    if(_m_strings_ru.values().contains(word_ru_))
    {
        auto _word_en = _m_strings_ru.key(word_ru_);
        for(const auto & i : _m_letterKeywords)
        {
            _word_en = _word_en.remove(i);
            _word_en.squeeze();
        }
        return _word_en;
    }

    return word_ru_;
}

QString tr_str::letter(const QString &word_en_, eTranslateLetters letter_)
{
    if(auto _word = word_en_+letterToStr(letter_) ; _m_strings_letter.contains(_word))
        return _m_strings_letter.value(_word);

    return word_en_;
}

QString tr_str::letterToStr(eTranslateLetters letter_)
{
    switch(letter_)
    {
    case eTranslateLetters::eTL_Lowercase: return QString(); break;
    case eTranslateLetters::eTL_Capital: return "#1"; break;
    case eTranslateLetters::eTL_Uppercase: return "#2"; break;
    default: return QString(); break;
    }

    return QString();
}

tr_str * tr_str::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new tr_str;

    return _m_instance;
}
