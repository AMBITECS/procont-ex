#ifndef ITEMVALUEVARIABLETABLE_H
#define ITEMVALUEVARIABLETABLE_H

#include "ItemValue.h"

// ----------------------------------------------------------------------------
// *** ItemValueVariableTable ***

/*!
 * \brief The ItemValueVariableTable
 */

class ItemValueVariableTable
{
public:
    // enum ValueType
    // {
    //     valueName = 101,
    //     valueType = 102,
    //     valueAddress = 103,
    //     valueDataType = 103,
    //     valueDataInit = 105,
    //     valueDocumentation = 106
    // };
private:
    ItemValueVariableTable() = default;
};
// ----------------------------------------------------------------------------

typedef ItemValue_NodeValue ItemValue_Name;

// ----------------------------------------------------------------------------
// *** ItemValue_Type ***

/*!
 * \brief The ItemValue_Type class
 */

class ItemValue_Type : public ItemValue
{
public:
    ItemValue_Type(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

public:
    static QString type(const QString &);
    static QHash<QString, QString> modifiers(const QString &);
    static QHash<QString, QString> modifiers(const QDomNode &);

protected:
    static QHash<QString, QString> m_types;
    static QHash<QString, QString> m_modifiers_i;
    static QHash<QString, QString> m_modifiers_o;
    static QHash<QString, QString> m_modifiers_values_i;
    static QHash<QString, QString> m_modifiers_values_o;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Address ***

/*!
 * \brief The ItemValue_Address
 */

class ItemValue_Address : public ItemValue_Attr_opt
{
public:
    ItemValue_Address(const QDomNode &node/*, const QDomNode &parent = {}*/) :
        ItemValue_Attr_opt(node/*, parent*/)
    {
        setName("address");
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_DataType ***

/*!
 * \brief The ItemValue_DataType class
 */

class ItemValue_DataType : public ItemValue
{
public:
    enum class ValueType
    {
        valueSimple,
        valueDerived,
        valueArray
    };
public:
    ItemValue_DataType(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

public:
    [[nodiscard]] static ValueType type(const QDomNode &node);
    [[nodiscard]] static ValueType type(const QString &value);
    [[nodiscard]] static ItemValue * create(const QDomNode &node);
    [[nodiscard]] static ItemValue * create(const QDomNode &node, ValueType type);

private:

private:
    static QStringList m_simpleTypes;

private:
    QSharedPointer<ItemValue> m_value;
};
// ----------------------------------------------------------------------------


typedef ItemValue_NodeName ItemValue_TypeSimple;

// ----------------------------------------------------------------------------
// *** ItemValue_TypeDerived ***

/*!
 * \brief The ItemValue_TypeDerived
 */

class ItemValue_TypeDerived : public ItemValue
{
public:
    ItemValue_TypeDerived(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeArray ***

/*!
 * \brief The ItemValue_TypeArray
 */

class ItemValue_TypeArray : public ItemValue
{
public:
    ItemValue_TypeArray(const QDomNode &node/*, const QDomNode &parent = {}*/);
    ItemValue_TypeArray(const QDomNode &node, const QString &value);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

private:
    QSharedPointer<ItemValue> m_value;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_InitialValue ***

/*!
 * \brief The ItemValue_InitialValue class
 */

class ItemValue_InitialValue : public ItemValue
{
public:
    ItemValue_InitialValue(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

public:
    [[nodiscard]] static ItemValue * create(const QDomNode &node/*, const QDomNode &parent*/);

private:
    QSharedPointer<ItemValue> m_value;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue ***

/*!
 * \brief The ItemValue_SimpleValue
 */

class ItemValue_SimpleValue: public ItemValue_SubNodeAttr
{
public:
    ItemValue_SimpleValue(const QDomNode &node/*, const QDomNode &parent = {}*/) :
        ItemValue_SubNodeAttr(node/*, parent*/)
    {
        setNodeName("initialValue");
        setChNodeName("simpleValue");
        setChAttrName("value");
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_struct ***

/*!
 * \brief The ItemValue_SimpleValue_struct
 */

class ItemValue_SimpleValue_struct : public ItemValue_SubNodeAttr
{
public:
    ItemValue_SimpleValue_struct(const QDomNode &node/*, const QDomNode &parent = {}*/) :
        ItemValue_SubNodeAttr(node/*, parent*/)
    {
        setNodeName("value");
        setChNodeName("simpleValue");
        setChAttrName("value");
    }
    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_array ***

/*!
 * \brief The ItemValue_SimpleValue_array
 */

class ItemValue_SimpleValue_array : public ItemValue_SubNodeAttr
{
public:
    ItemValue_SimpleValue_array(const QDomNode &node/*, const QDomNode &parent = {}*/) :
        ItemValue_SubNodeAttr(node/*, parent*/)
    {
        setNodeName("value");
        setChNodeName("simpleValue");
        setChAttrName("value");
    }
    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_StructValue ***

/*!
 * \brief The ItemValue_StructValue
 */

class ItemValue_StructValue : public ItemValue
{
public:

    ItemValue_StructValue(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

protected:
    QList<QSharedPointer<ItemValue>> m_values;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_ArrayValue ***

/*!
 * \brief The ItemValue_ArrayValue class
 */

class ItemValue_ArrayValue: public ItemValue
{
public:
    ItemValue_ArrayValue(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

protected:
    QList<QSharedPointer<ItemValue>> m_values;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Documentation ***

/*!
 * \brief The ItemValue_Documentation class
 */

class ItemValue_Documentation : public ItemValue_SubNodeValue
{
public:
    ItemValue_Documentation(const QDomNode &node/*, const QDomNode &parent = {}*/) :
        ItemValue_SubNodeValue(node/*, parent*/)
    {
        setName("xhtml;xhtml:p");
    }
};
// ----------------------------------------------------------------------------


#endif // ITEMVALUEVARIABLETABLE_H
