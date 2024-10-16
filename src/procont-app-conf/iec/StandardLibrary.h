#ifndef STANDARD_LIBRARY_H
#define STANDARD_LIBRARY_H

#include <QScopedPointer>
#include <QDomDocument>

class StandardLibrary
{
public:
    static StandardLibrary * instance();

    static void test();

public:
    enum class eNodeType
    {
        eNT_POU,
        eNT_Type
    };

public:
    void load(const QString &path_ = {});
    QString version() const;
    const QString fileName() const;

    /// проверка на существование dataType в библиотеке
    bool contents_type(const QString &name_) const;
    /// проверка на существование POU в библиотеке
    bool contents_pou(const QString &name_) const;
    /// получение dataType из библиотеки
    const QDomNode find_type(const QString &name_) const;
    /// получение POU из библиотеки
    const QDomNode find_pou(const QString &name_) const;

private:
    /// возвращяет true, если библиотека содержит сущность типа type_ с именем name_
    bool contents(const QString &name_, eNodeType type_) const;
    /// возвращяет константный объект QDomNode, если библиотека содержит сущность типа type_ с именем name_, или
    /// пустой QDomNode()
    const QDomNode find(const QString &name_, eNodeType type_) const;

    QDomNodeList get_nodes(eNodeType type_) const;

private:
    StandardLibrary() = default;
private:
    static QScopedPointer<StandardLibrary> _m_instance;
    const QString _m_fileName = "StandardLibrary.xml";
    QDomDocument _m_library;
};

#endif
