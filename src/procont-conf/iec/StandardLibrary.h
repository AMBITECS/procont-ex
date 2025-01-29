#ifndef STANDARD_LIBRARY_H
#define STANDARD_LIBRARY_H

#include "Library.h"

class StandardLibrary : public ILibrary
{
public:
    ~StandardLibrary();

public:
    static StandardLibrary * instance();

    // static void test();

public:
    void load() override;
    void add(const QString & name_, QDomDocument * doc_, const QString &_name_user) override;
    QString version() const override;
    const QString filePath() const override;

    /// проверка на существование dataType в библиотеке
    bool contents_type(const QString &name_) const override;
    /// проверка на существование POU в библиотеке
    bool contents_pou(const QString &name_) const override;
    /// получение dataType из библиотеки
    const QDomNode find_type(const QString &name_) const override;
    /// получение POU из библиотеки
    const QDomNode find_pou(const QString &name_) const override;
    /// получение списка имен
    const QStringList objects() const override;
    /// получение информации об объекте
    const ObjectInfo object_info(const QString &name_) const override;

private:
    StandardLibrary() = default;

private:
    static StandardLibrary * _m_instance;
    static QMap<QString, ILibrary *> _m_libs;
};

#endif
