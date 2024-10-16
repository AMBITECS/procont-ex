#include "StandardLibrary.h"

#include "log/Logger.h"

#include <QFile>
#include <QFileInfo>

QScopedPointer<StandardLibrary> StandardLibrary::_m_instance;

#include <QDebug>

StandardLibrary * StandardLibrary::instance()
{
    if(_m_instance.get() == nullptr)
        _m_instance.reset(new StandardLibrary);

    return _m_instance.get();
}

void StandardLibrary::test()
{
    qDebug() << StandardLibrary::instance()->contents_type("datatype"); // no such type
    qDebug() << StandardLibrary::instance()->contents_type("datatype0"); // type present
    qDebug() << StandardLibrary::instance()->find_type("datatype").toElement().attribute("name"); // no such type
    qDebug() << StandardLibrary::instance()->find_type("datatype0").toElement().attribute("name"); // type present
    qDebug() << StandardLibrary::instance()->contents_pou("POU"); // no such pou
    qDebug() << StandardLibrary::instance()->contents_pou("TON"); // pou present
    qDebug() << StandardLibrary::instance()->find_pou("POU").toElement().attribute("name"); // no such pou
    qDebug() << StandardLibrary::instance()->find_pou("TON").toElement().attribute("name"); // pou present
}

const QString StandardLibrary::fileName() const
{
    return _m_fileName;
}

void StandardLibrary::load(const QString &path_)
{
    auto default_file = false;
    QString _filePath = QString("%1/iec/StandardLibrary.xml").arg(path_);

    if(path_.isEmpty())
        default_file = true;
    else
        info(
            QStringList()
            << QString(QObject::tr("open library 'StandardLibrary'"))
            << QString(QObject::tr("library 'StandardLibrary' file: %1")).arg(_filePath)
            );

    if(!default_file && !QFileInfo::exists(_filePath))
    {
        warn(
            QStringList()
            << QString(QObject::tr("can't open library 'StandardLibrary'"))
            << QString(QObject::tr("file not found: %1").arg(_filePath))
            );

        default_file = true;
    }

    if(default_file)
    {
        _filePath = ":/lib/lib/StandardLibrary.xml";
        info(
            QStringList()
            << QString(QObject::tr("open library 'StandardLibrary'"))
            << QString(QObject::tr("library 'StandardLibrary' file: %1")).arg(_filePath)
            );
    }

    QFile file(_filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        crit(
            QStringList()
            << QString(QObject::tr("can't open library 'StandardLibrary'"))
            << QString(QObject::tr("can't open file for read: %1").arg(_filePath))
            );

        return;
    }
    auto result = _m_library.setContent(&file);
    file.close();

    if(!result)
    {
        warn(
            QStringList()
            << QString(QObject::tr("can't open library 'StandardLibrary'"))
            << QString(QObject::tr("file parse error: %1").arg(_filePath))
            );

        return;
    }

    info(
        QStringList()
        << QString(QObject::tr("library 'StandardLibrary' opened, version %1")).arg(version())
        << QString(QObject::tr("library 'StandardLibrary' file: %1")).arg(_filePath)
        );
}

QString StandardLibrary::version() const
{
    return _m_library.namedItem("project").namedItem("fileHeader").toElement().attribute("productVersion");
}

QDomNodeList StandardLibrary::get_nodes(eNodeType type_) const
{
    if(type_ == eNodeType::eNT_Type)
        return _m_library.namedItem("project").namedItem("types").namedItem("dataTypes").toElement().elementsByTagName("dataType");

    if(type_ == eNodeType::eNT_POU)
        return _m_library.namedItem("project").namedItem("types").namedItem("pous").toElement().elementsByTagName("pou");

    return {};
}

/// возвращяет true, если библиотека содержит сущность типа Type_ с именем name_
bool StandardLibrary::contents(const QString &name_, eNodeType type_) const
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
    QDomNodeList list = get_nodes(type_);

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
