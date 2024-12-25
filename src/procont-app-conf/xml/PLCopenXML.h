#ifndef PLCOPENXML_H
#define PLCOPENXML_H

#include <QDomNode>
#include <QMap>

class PLCopenXMLUtils
{
public:
    static bool is_type_derived(const QDomNode &node_);
    static QString type_derived_name(const QDomNode &node_);
};

class PLCopenXMLVariableType
{
public:
    enum eVariableType
    {
        eVT_Elementary,
        eVT_Derived
    };
public:
    PLCopenXMLVariableType(const QDomNode &node_);
    virtual QString name() const = 0;
protected:
    const QDomNode & _m_node;
};

class PLCopenXMLVariableType_elementary : public PLCopenXMLVariableType
{
public:
    PLCopenXMLVariableType_elementary(const QDomNode &node_);
    QString name() const override;
};

class PLCopenXMLVariableType_derived : public PLCopenXMLVariableType
{
public:
    PLCopenXMLVariableType_derived(const QDomNode &node_);
    QString name() const override;
};

class PLCopenXMLVariableCreator
{
public:
    PLCopenXMLVariableCreator() = default;
    virtual PLCopenXMLVariableType * create(const QDomNode &node_) = 0;
};

class PLCopenXMLVariableCreator_elementary : public PLCopenXMLVariableCreator
{
public:
    PLCopenXMLVariableCreator_elementary() = default;
    PLCopenXMLVariableType * create(const QDomNode &node_) override;
};

class PLCopenXMLVariableCreator_derived : public PLCopenXMLVariableCreator
{
public:
    PLCopenXMLVariableCreator_derived() = default;
    PLCopenXMLVariableType * create(const QDomNode &node_) override;
};

class PLCopenXMLVariableBuilder
{
public:
    PLCopenXMLVariableBuilder();

    static PLCopenXMLVariableBuilder * instance();

    std::shared_ptr<PLCopenXMLVariableType> build(const QDomNode &node_);

private:
    static PLCopenXMLVariableType::eVariableType get_type(const QDomNode &);

private:
    QMap<PLCopenXMLVariableType::eVariableType, std::shared_ptr<PLCopenXMLVariableCreator>> _m_creators;
    static std::shared_ptr<PLCopenXMLVariableBuilder> _m_instance;
};

#endif
