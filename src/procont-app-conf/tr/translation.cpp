#include "translation.h"

tr_str * tr_str::_m_instance = nullptr;

tr_str::tr_str()
{
    _m_strings["functionBlock"] = tr("functionBlock");
    _m_strings["function"] = tr("function");
    _m_strings["dataType"] = tr("dataType");
}

QString tr_str::ru(const QString &name_)
{
    if(_m_strings.contains(name_))
        return _m_strings.value(name_);

    return name_;
}

QString tr_str::en(const QString &name_)
{
    if(_m_strings.values().contains(name_))
        return _m_strings.key(name_);

    return name_;
}

tr_str * tr_str::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new tr_str;

    return _m_instance;
}
