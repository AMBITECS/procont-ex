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
    enum ValueType
    {
        valueName = 101,
        valueAddress = 102,
        valueType = 103,
        valueData = 103,
        valueInit = 105,
        valueDocumentation = 106
    };
private:
    ItemValueVariableTable() = default;
};
// ----------------------------------------------------------------------------

typedef ItemValue_NodeValue ItemValue_Name;
typedef ItemValue_NodeName ItemValue_TypeSimple;

// ----------------------------------------------------------------------------
// *** ItemValue_Address ***

/*!
 * \brief The ItemValue_Address
 */

class ItemValue_Address : public ItemValue_Attr_opt
{
public:
    ItemValue_Address(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_Attr_opt(node, parent)
    {
        setName("address");
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeDerived ***

/*!
 * \brief The ItemValue_TypeDerived
 */

class ItemValue_TypeDerived: public ItemValue_Attr_req
{
public:
    ItemValue_TypeDerived(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_Attr_req(node, parent)
    {
        setName("name");
    }
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
    ItemValue_SimpleValue(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_SubNodeAttr(node, parent)
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
    ItemValue_SimpleValue_struct(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_SubNodeAttr(node, parent)
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
    ItemValue_SimpleValue_array(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_SubNodeAttr(node, parent)
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

    ItemValue_StructValue(const QDomNode &node, const QDomNode &parent = {});

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
    ItemValue_ArrayValue(const QDomNode &node, const QDomNode &parent = {});

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
    ItemValue_Documentation(const QDomNode &node, const QDomNode &parent = {}) :
        ItemValue_SubNodeValue(node, parent)
    {
        setName("xhtml;xhtml:p");
    }
};
// ----------------------------------------------------------------------------


#endif // ITEMVALUEVARIABLETABLE_H
