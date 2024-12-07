#include "StandardLibrary.h"

#include <QObject>

#include <QDebug>

StandardLibrary * StandardLibrary::_m_instance = nullptr;
QMap<QString, ILibrary *> StandardLibrary::_m_libs;

StandardLibrary::~StandardLibrary()
{
    for(auto i : _m_libs)
        delete i;

    if(_m_instance != nullptr)
        delete _m_instance;
}

StandardLibrary * StandardLibrary::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new StandardLibrary;

    return _m_instance;
}

// void StandardLibrary::test()
// {
//     qDebug() << StandardLibrary::instance()->contents_type("datatype"); // no such type
//     qDebug() << StandardLibrary::instance()->contents_type("datatype0"); // type present
//     qDebug() << StandardLibrary::instance()->find_type("datatype").toElement().attribute("name"); // no such type
//     qDebug() << StandardLibrary::instance()->find_type("datatype0").toElement().attribute("name"); // type present
//     qDebug() << StandardLibrary::instance()->contents_pou("POU"); // no such pou
//     qDebug() << StandardLibrary::instance()->contents_pou("TON"); // pou present
//     qDebug() << StandardLibrary::instance()->find_pou("POU").toElement().attribute("name"); // no such pou
//     qDebug() << StandardLibrary::instance()->find_pou("TON").toElement().attribute("name"); // pou present
// }

const QString StandardLibrary::filePath() const
{
    return {};
}

QString StandardLibrary::version() const
{
    return {};
}

void StandardLibrary::load()
{
    auto name_ = "Standard Function Blocks";
    _m_libs.insert(name_, new ILibrary(name_, ":/lib/lib/StandardFunctionBlocks.xml"));
    name_ = "Additional Function Blocks";
    _m_libs.insert(name_, new ILibrary(name_, ":/lib/lib/AdditionalFunctionBlocks.xml"));
    name_ = "Standard IEC Functions";
    _m_libs.insert(name_, new ILibrary(name_, ":/lib/lib/StandardIECFunctions.xml"));

    for(auto i : std::as_const(_m_libs))
        i->load();
}

void StandardLibrary::add(const QString & name_, QDomDocument * doc_, const QString &_name_user)
{
    if(_m_libs.contains(name_))
        delete _m_libs.value(name_);
    _m_libs.insert(name_, new ILibrary(name_, doc_, _name_user));
}

/// возвращяет true, если библиотека содержит dataType с именем name_
bool StandardLibrary::contents_type(const QString &name_) const
{
    for(auto i : std::as_const(_m_libs))
        if(i->contents_type(name_))
            return true;

    return false;
}

/// возвращяет true, если библиотека содержит pou с именем name_
bool StandardLibrary::contents_pou(const QString &name_) const
{
    for(auto i : std::as_const(_m_libs))
        if(i->contents_pou(name_))
            return true;

    return false;
}

/// получение dataType из библиотеки
const QDomNode StandardLibrary::find_type(const QString &name_) const
{
    for(auto i : std::as_const(_m_libs))
    {
        auto node = i->find_type(name_);
        if(!node.isNull())
            return node;
    }

    return {};
}

/// получение POU из библиотеки
const QDomNode StandardLibrary::find_pou(const QString &name_) const
{
    for(auto i : std::as_const(_m_libs))
    {
        auto node = i->find_pou(name_);
        if(!node.isNull())
            return node;
    }

    return {};
}

/// получение списка имен
const QStringList StandardLibrary::objects() const
{
    QStringList result;

    for(auto i : std::as_const(_m_libs))
        result += i->objects();

    return result;
}

/// получение информации об объекте
const ILibrary::ObjectInfo StandardLibrary::object_info(const QString &name_) const
{
    ILibrary::ObjectInfo result;

    for(auto i : std::as_const(_m_libs))
    {
        result = i->object_info(name_);
        if(!result.name.isEmpty())
            return result;
    }

    return {};
}



