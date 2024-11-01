#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDomDocument>

class ILibrary
{
protected:
    enum class eNodeType
    {
        eNT_POU,
        eNT_Type
    };

public:
    ILibrary() = default;
    ILibrary(const QString & _name, const QString & _filepath = {});

public:
    virtual void load();
    virtual QString version() const;
    virtual const QString filePath() const;

    /// проверка на существование dataType в библиотеке
    virtual bool contents_type(const QString &name_) const;
    /// проверка на существование POU в библиотеке
    virtual bool contents_pou(const QString &name_) const;
    /// получение dataType из библиотеки
    virtual const QDomNode find_type(const QString &name_) const;
    /// получение POU из библиотеки
    virtual const QDomNode find_pou(const QString &name_) const;

private:
    /// возвращяет true, если библиотека содержит сущность типа type_ с именем name_
    bool contents(const QString &name_, eNodeType type_) const;
    /// возвращяет константный объект QDomNode, если библиотека содержит сущность типа type_ с именем name_, или
    /// пустой QDomNode()
    const QDomNode find(const QString &name_, eNodeType type_) const;

    QDomNodeList get_nodes(eNodeType type_) const;

private:
    const QString _m_name = {};
    const QString _m_filePath = {};
    QDomDocument _m_library {};
};

#endif // LIBRARY_H
