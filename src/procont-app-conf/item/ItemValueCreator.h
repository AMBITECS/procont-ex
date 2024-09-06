#ifndef ITEMVALUECREATOR_H
#define ITEMVALUECREATOR_H

#include <QDomNode>

#include "ItemValueVariableTable.h"

// ----------------------------------------------------------------------------
// *** ItemValue_creator

/*!
 * \brief The ItemValue_creator interface
 */

class ItemValue_creator
{
public:
    ItemValue_creator() = default;
    virtual ~ItemValue_creator() = default;
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {}) = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Default_creator

class ItemValue_Default_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_Default(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Name_creator

class ItemValue_Name_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_Name(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Address_creator

class ItemValue_Address_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_Address(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeSimple_creator

class ItemValue_TypeSimple_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_TypeSimple(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeDerived_creator

class ItemValue_TypeDerived_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_TypeDerived(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_creator

class ItemValue_SimpleValue_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_SimpleValue(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_struct_creator

class ItemValue_SimpleValue_struct_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_SimpleValue_struct(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_array_creator

class ItemValue_SimpleValue_array_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_SimpleValue_array(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_StructValue_creator

class ItemValue_StructValue_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_StructValue(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_ArrayValue_creator

class ItemValue_ArrayValue_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_ArrayValue(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Documentation_creator

class ItemValue_Documentation_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = {})
    {
        return new ItemValue_Documentation(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_builder

class ItemValue_builder
{
private:
    ItemValue_builder()
    {
        m_creators.insert(0, QSharedPointer<ItemValue_creator>(new ItemValue_Default_creator));
        m_creators.insert(ItemValueVariableTable::valueName, QSharedPointer<ItemValue_creator>(new ItemValue_Name_creator));
        m_creators.insert(ItemValueVariableTable::valueAddress, QSharedPointer<ItemValue_creator>(new ItemValue_Address_creator));

        // m_creators.insert(ItemValue::valueDataSimple, QSharedPointer<ItemValue_creator>(new ItemValue_TypeSimple_creator));
        // m_creators.insert(ItemValue::valueDataDerived, QSharedPointer<ItemValue_creator>(new ItemValue_TypeDerived_creator));
        // m_creators.insert(ItemValue::valueInitSimple, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_creator));
        // m_creators.insert(ItemValue::valueInitSimple_struct, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_struct_creator));
        // m_creators.insert(ItemValue::valueInitSimple_array, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_array_creator));
        // m_creators.insert(ItemValue::valueInitStruct, QSharedPointer<ItemValue_creator>(new ItemValue_StructValue_creator));
        // m_creators.insert(ItemValue::valueInitArray, QSharedPointer<ItemValue_creator>(new ItemValue_ArrayValue_creator));

        m_creators.insert(ItemValueVariableTable::valueDocumentation, QSharedPointer<ItemValue_creator>(new ItemValue_Documentation_creator));
    }

public:

    static ItemValue_builder * instance()
    {
        if(m_instance.isNull())
            m_instance.reset(new ItemValue_builder);

        return m_instance.get();
    }

    [[nodsicard]] static quint32 getValueType(const QDomNode &node, const QDomNode &parent = {})
    {
        quint32 type = 0;

        if(node.nodeName() == "name")
            type = ItemValueVariableTable::valueName;

        if(node.nodeName() == "address")
            type =  ItemValueVariableTable::valueAddress;

        // if(node.parentNode().nodeName() == "type" && node.nodeName() != "derived")
        //     type =  ItemValue::valueDataSimple;

        // if(node.parentNode().nodeName() == "type" && node.nodeName() == "derived")
        //     type =  ItemValue::valueDataDerived;

        // if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "initialValue")
        //     type =  ItemValue::valueInitSimple;

        // if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "value" && parent.nodeName() == "structValue")
        //     type =  ItemValue::valueInitSimple_struct;

        // if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "value" && parent.nodeName() == "arrayValue")
        //     type =  ItemValue::valueInitSimple_array;

        // if(node.firstChild().nodeName() == "structValue")
        //     type =  ItemValue::valueInitStruct;

        // if(node.firstChild().nodeName() == "arrayValue")
        //     type =  ItemValue::valueInitArray;

        if(node.nodeName() == "documentation")
            type =  ItemValueVariableTable::valueDocumentation;

        return type;
    }

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent)
    {
        quint32 type = static_cast<quint32>(getValueType(node, parent));

        if(m_creators.contains(type))
            return m_creators.value(type)->create(node, parent);

        return nullptr;
    }

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent, quint32 type)
    {
        if(m_creators.contains(type))
            return m_creators.value(type)->create(node, parent);

        return nullptr;
    }

private:
    static QScopedPointer<ItemValue_builder> m_instance;
    QHash<quint32, QSharedPointer<ItemValue_creator>> m_creators;
};
// ----------------------------------------------------------------------------


#endif // ITEMVALUECREATOR_H
