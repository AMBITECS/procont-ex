#ifndef ITEMVALUE_H
#define ITEMVALUE_H

#include <QDomNode>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QDebug>

// #include "DomItem.h"

// ----------------------------------------------------------------------------
// *** ItemValue ***

/*!
 * \brief The ItemValue interface
 */

class ItemValue
{
public:
    enum ValueType
    {
        valueDefault = 11,
        valueName = 21,
        valueAddress = 31,
        valueDataSimple = 41,
        valueDataDerived = 42,
        valueDataArray = 43,
        valueInitSimple = 51,
        valueInitSimple_struct = 52,
        valueInitSimple_array = 53,
        valueInitStruct = 60,
        valueInitArray = 70,
        valueDocumentation = 80
    };

public:

    ItemValue(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] virtual QString get() const = 0;
    virtual void set(const QString &value) = 0;

public:
    [[nodiscard]] inline QDomNode node() const { return m_node; }
    [[nodiscard]] inline QDomNode parent() const { return m_parent; }

protected:
    QDomNode m_node;
    QDomNode m_parent;
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

    [[nodiscard]] virtual QString get() const;
    virtual void set(const QString &value);

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
// *** ItemValue_default ***

/*!
 * \brief The ItemValue_Default class
 */

class ItemValue_Default : public ItemValue
{
public:
    ItemValue_Default(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeName ***

/*!
 * \brief The ItemValue_NodeName class
 */

class ItemValue_NodeName: public ItemValue
{
public:
    ItemValue_NodeName(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};

typedef ItemValue_NodeName ItemValue_TypeSimple;
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue ***

/*!
 * \brief The ItemValue_NodeValue class
 */

class ItemValue_NodeValue: public ItemValue
{
public:
    ItemValue_NodeValue(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};

typedef ItemValue_NodeValue ItemValue_Name;

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeValue ***

/*!
 * \brief The ItemValue_SubNodeValue class
 */

class ItemValue_SubNodeValue: public ItemValue
{
public:
    ItemValue_SubNodeValue(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

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

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_opt ***

/*!
 * \brief The ItemValue_Attr_opt class
 */

class ItemValue_Attr_opt: public ItemValue
{
public:
    ItemValue_Attr_opt(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

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
// *** ItemValue_Attr_req ***

/*!
 * \brief The ItemValue_Attr_req class
 */

class ItemValue_Attr_req: public ItemValue
{
public:
    ItemValue_Attr_req(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

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
// *** ItemValue_SubNodeAttr ***

/*!
 * \brief The ItemValue_SubNodeAttr class
 */

class ItemValue_SubNodeAttr: public ItemValue
{
public:
    ItemValue_SubNodeAttr(const QDomNode &node, const QDomNode &parent = {});

    [[nodiscard]] virtual QString get() const override;
    virtual void set(const QString &value) override;

    void setNodeName(const QString &name);
    void setChNodeName(const QString &name);
    void setChAttrName(const QString &name);

protected:
    QString m_nodeName = QString();
    QString m_chNodeName = QString();
    QString m_chAttrName = QString();
};

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
        m_creators.insert(ItemValue::valueDefault, QSharedPointer<ItemValue_creator>(new ItemValue_Default_creator));
        m_creators.insert(ItemValue::valueName, QSharedPointer<ItemValue_creator>(new ItemValue_Name_creator));
        m_creators.insert(ItemValue::valueAddress, QSharedPointer<ItemValue_creator>(new ItemValue_Address_creator));
        m_creators.insert(ItemValue::valueDataSimple, QSharedPointer<ItemValue_creator>(new ItemValue_TypeSimple_creator));
        m_creators.insert(ItemValue::valueDataDerived, QSharedPointer<ItemValue_creator>(new ItemValue_TypeDerived_creator));
        m_creators.insert(ItemValue::valueInitSimple, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_creator));
        m_creators.insert(ItemValue::valueInitSimple_struct, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_struct_creator));
        m_creators.insert(ItemValue::valueInitSimple_array, QSharedPointer<ItemValue_creator>(new ItemValue_SimpleValue_array_creator));
        m_creators.insert(ItemValue::valueInitStruct, QSharedPointer<ItemValue_creator>(new ItemValue_StructValue_creator));
        m_creators.insert(ItemValue::valueInitArray, QSharedPointer<ItemValue_creator>(new ItemValue_ArrayValue_creator));
        m_creators.insert(ItemValue::valueDocumentation, QSharedPointer<ItemValue_creator>(new ItemValue_Documentation_creator));
    }

public:

    static ItemValue_builder * instance()
    {
        if(m_instance.isNull())
            m_instance.reset(new ItemValue_builder);

        return m_instance.get();
    }

    [[nodsicard]] static ItemValue::ValueType getValueType(const QDomNode &node, const QDomNode &parent = {})
    {
        if(node.nodeName() == "name")
            return ItemValue::valueName;

        if(node.nodeName() == "address")
            return ItemValue::valueAddress;

        if(node.parentNode().nodeName() == "type" && node.nodeName() != "derived")
            return ItemValue::valueDataSimple;

        if(node.parentNode().nodeName() == "type" && node.nodeName() == "derived")
            return ItemValue::valueDataDerived;

        if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "initialValue")
            return ItemValue::valueInitSimple;

        if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "value" && parent.nodeName() == "structValue")
            return ItemValue::valueInitSimple_struct;

        if(node.firstChild().nodeName() == "simpleValue" && node.nodeName() == "value" && parent.nodeName() == "arrayValue")
            return ItemValue::valueInitSimple_array;

        if(node.firstChild().nodeName() == "structValue")
            return ItemValue::valueInitStruct;

        if(node.firstChild().nodeName() == "arrayValue")
            return ItemValue::valueInitArray;

        if(node.nodeName() == "documentation")
            return ItemValue::valueDocumentation;

        return ItemValue::valueDefault;
    }

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent)
    {
        ItemValue::ValueType type = getValueType(node, parent);

        if(m_creators.contains(type))
            return m_creators.value(type)->create(node, parent);

        return nullptr;
    }

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent, ItemValue::ValueType type)
    {
        if(m_creators.contains(type))
            return m_creators.value(type)->create(node, parent);

        return nullptr;
    }

private:
    static QScopedPointer<ItemValue_builder> m_instance;
    QHash<ItemValue::ValueType, QSharedPointer<ItemValue_creator>> m_creators;
};
// ----------------------------------------------------------------------------

#endif // ITEMVALUE_H
