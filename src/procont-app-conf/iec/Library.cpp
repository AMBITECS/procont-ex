#include "Library.h"

#include "log/Logger.h"

#include <QFile>
#include <QFileInfo>

ILibrary::ILibrary(const QString & _name, const QString &_filepath) :
    _m_name(_name),
    _m_filePath(_filepath)
{
}

const QString ILibrary::filePath() const
{
    return _m_filePath;
}

void ILibrary::load()
{
    info(
        QStringList()
        << QString(QObject::tr("open library '%1'")).arg(_m_name)
        << QString(QObject::tr("library '%1' file: %2")).arg(_m_name).arg(_m_filePath)
        );

    if(!QFileInfo::exists(_m_filePath))
    {
        crit(
            QStringList()
            << QString(QObject::tr("can't open library '%1'")).arg(_m_name)
            << QString(QObject::tr("file not found: %1").arg(_m_filePath))
            );

        return;
    }

    QFile file(_m_filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        crit(
            QStringList()
            << QString(QObject::tr("can't open library '%1'")).arg(_m_name)
            << QString(QObject::tr("can't open file for read: %1").arg(_m_filePath))
            );

        return;
    }
    auto result = _m_library.setContent(&file);
    file.close();

    if(!result)
    {
        warn(
            QStringList()
            << QString(QObject::tr("can't open library '%1'")).arg(_m_name)
            << QString(QObject::tr("file parse error: %1").arg(_m_filePath))
            );

        return;
    }

    info(
        QStringList()
        << QString(QObject::tr("library '%1' opened, version %2")).arg(_m_name).arg(version())
        << QString(QObject::tr("library '%1' file: %2")).arg(_m_name).arg(_m_filePath)
        );
}

QString ILibrary::version() const
{
    return _m_library.namedItem("project").namedItem("fileHeader").toElement().attribute("productVersion");
}

QDomNodeList ILibrary::get_nodes(eNodeType type_) const
{
    if(type_ == eNodeType::eNT_Type)
        return _m_library.namedItem("project").namedItem("types").namedItem("dataTypes").toElement().elementsByTagName("dataType");

    if(type_ == eNodeType::eNT_POU)
        return _m_library.namedItem("project").namedItem("types").namedItem("pous").toElement().elementsByTagName("pou");

    return {};
}

/// возвращяет true, если библиотека содержит сущность типа Type_ с именем name_
bool ILibrary::contents(const QString &name_, eNodeType type_) const
{
    QDomNodeList list = get_nodes(type_);

    for(auto i=0;i<list.size();i++)
    {
        if(list.at(i).toElement().attribute("name") == name_)
            return true;
    }

    return false;
}

/// возвращяет true, если библиотека содержит dataType с именем name_
bool ILibrary::contents_type(const QString &name_) const
{
    return contents(name_, eNodeType::eNT_Type);
}

/// возвращяет true, если библиотека содержит pou с именем name_
bool ILibrary::contents_pou(const QString &name_) const
{
    return contents(name_, eNodeType::eNT_POU);
}

/// возвращяет константный объект QDomNode, если библиотека содержит сущность типа Type_ с именем name_, или
/// пустой QDomNode()
const QDomNode ILibrary::find(const QString &name_, eNodeType type_) const
{
    QDomNodeList list = get_nodes(type_);

    for(auto i=0;i<list.size();i++)
    {
        if(list.at(i).toElement().attribute("name") == name_)
            return list.at(i);
    }

    return {};
}

const QDomNode ILibrary::find_type(const QString &name_) const
{
    return find(name_, eNodeType::eNT_Type);
}

const QDomNode ILibrary::find_pou(const QString &name_) const
{
    return find(name_, eNodeType::eNT_POU);

}
