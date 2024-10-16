#include "StandardLibrary.h"

#include "log/Logger.h"

#include <QFile>

QScopedPointer<StandardLibrary> StandardLibrary::_m_instance;

#include <QDebug>

StandardLibrary * StandardLibrary::instance()
{
    qDebug() << _m_instance.get();

    if(_m_instance.get() == nullptr)
        _m_instance.reset(new StandardLibrary);

    return _m_instance.get();
}

const QString StandardLibrary::fileName() const
{
    return _m_fileName;
}

void StandardLibrary::load(const QString &path_)
{
    QString filePath = QString("%1/iec/StandardLibrary_.xml").arg(path_);

    info(QString(QObject::tr("load library 'StandardLibrary' from file: %1")).arg(filePath));

    if(filePath.isEmpty())
    {
        crit(QString(QObject::tr("failed to load library 'StandardLibrary': no such file")));
        return;
    }

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        crit(QString(QObject::tr("failed to load library 'StandardLibrary': can' open file")));
        return;
    }

    if(!_m_library.setContent(&file))
    {
        crit(QString(QObject::tr("failed to load library 'StandardLibrary': can't parse content")));
        return;
    }

    info(QString(QObject::tr("loaded library 'StandardLibrary' version %1").arg(version())));
}

QString StandardLibrary::version() const
{
    return _m_library.namedItem("project").namedItem("fileHeader").toElement().attribute("productVersion");
}

/// возвращяет true, если библиотека содержит сущность типа Type_ с именем name_
bool StandardLibrary::contents(const QString &name_, eNodeType type_) const
{
    QDomNodeList list = {};
    if(type_ == eNodeType::eNT_Type)
        list = _m_library.namedItem("project").namedItem("types").namedItem("dataTypes").toElement().elementsByTagName("dataType");
    if(type_ == eNodeType::eNT_POU)
        list = _m_library.namedItem("project").namedItem("types").namedItem("pous").toElement().elementsByTagName("pou");

    for(auto i=0;i<list.size();i++)
    {
        if(list.at(i).toElement().attribute("name") == name_)
            return true;
    }

    return false;
}

/// возвращяет true, если библиотека содержит dataType с именем name_
bool StandardLibrary::contents_type(const QString &name_) const
{
    return contents(name_, eNodeType::eNT_Type);
}

/// возвращяет true, если библиотека содержит pou с именем name_
bool StandardLibrary::contents_pou(const QString &name_) const
{
    return contents(name_, eNodeType::eNT_POU);
}

/// возвращяет константный объект QDomNode, если библиотека содержит сущность типа Type_ с именем name_, или
/// пустой QDomNode()
const QDomNode StandardLibrary::find(const QString &name_, eNodeType type_) const
{
    QDomNodeList list = {};
    if(type_ == eNodeType::eNT_Type)
        list = _m_library.namedItem("project").namedItem("types").namedItem("dataTypes").toElement().elementsByTagName("dataType");
    if(type_ == eNodeType::eNT_POU)
        list = _m_library.namedItem("project").namedItem("types").namedItem("pous").toElement().elementsByTagName("pou");

    for(auto i=0;i<list.size();i++)
    {
        if(list.at(i).toElement().attribute("name") == name_)
            return list.at(i);
    }

    return {};
}

const QDomNode StandardLibrary::find_type(const QString &name_) const
{
    return find(name_, eNodeType::eNT_Type);
}

const QDomNode StandardLibrary::find_pou(const QString &name_) const
{
    return find(name_, eNodeType::eNT_POU);

}
