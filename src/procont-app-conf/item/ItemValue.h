#ifndef ITEMVALUE_H
#define ITEMVALUE_H

#include <QDomNode>

#include "DomItem.h"

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
        valueDefault = 1,
        valueName = 2,
        valueAddress = 3,
        valueDataSimple = 4,
        valueDataDerived = 5,
        valueInitSimple = 6,
        valueInitStruct = 7,
        valueInitArray = 8,
        valueDocumentation = 9
    };

public:

    ItemValue(const QDomNode &node, const QDomNode &parent = QDomNode());

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
// *** ItemValue_default ***

/*!
 * \brief The ItemValue_Default class
 */

class ItemValue_Default : public ItemValue
{
public:
    ItemValue_Default(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_NodeName(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_NodeValue(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_SubNodeValue(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

class ItemValue_Documentation : public ItemValue_SubNodeValue
{
public:
    ItemValue_Documentation(const QDomNode &node, const QDomNode &parent = QDomNode()) :
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
    ItemValue_Attr_opt(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

class ItemValue_Address : public ItemValue_Attr_opt
{
public:
    ItemValue_Address(const QDomNode &node, const QDomNode &parent = QDomNode()) :
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
    ItemValue_Attr_req(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};

class ItemValue_TypeDerived: public ItemValue_Attr_req
{
public:
    ItemValue_TypeDerived(const QDomNode &node, const QDomNode &parent = QDomNode()) :
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
    ItemValue_SubNodeAttr(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

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
    ItemValue_SimpleValue(const QDomNode &node, const QDomNode &parent = QDomNode()) :
        ItemValue_SubNodeAttr(node, parent)
    {
        setNodeName("initialValue");
        setChNodeName("simpleValue");
        setChAttrName("value");
    }
};

// ----------------------------------------------------------------------------
// *** ItemValue_StructValue ***

/*!
 * \brief The ItemValue_StructValue class
 */

class ItemValue_StructValue: public ItemValue
{
public:
    ItemValue_StructValue(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode()) = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Default_creator

class ItemValue_Default_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
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
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
    {
        return new ItemValue_SimpleValue(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Documentation_creator

class ItemValue_Documentation_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode())
    {
        return new ItemValue_Documentation(node, parent);
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_builder

class ItemValue_builder
{
public:
    ItemValue_builder()
    {
        m_creators.insert(ItemValue::valueDefault, new ItemValue_Default_creator);
        m_creators.insert(ItemValue::valueName, new ItemValue_Name_creator);
        m_creators.insert(ItemValue::valueAddress, new ItemValue_Address_creator);
        m_creators.insert(ItemValue::valueDataSimple, new ItemValue_TypeSimple_creator);
        m_creators.insert(ItemValue::valueDataDerived, new ItemValue_TypeDerived_creator);
        m_creators.insert(ItemValue::valueInitSimple, new ItemValue_SimpleValue_creator);
        m_creators.insert(ItemValue::valueDocumentation, new ItemValue_Documentation_creator);
    }

    ~ItemValue_builder()
    {
        for(auto creator : std::as_const(m_creators))
            delete creator;

    }

    [[nodsicard]] static ItemValue::ValueType getValueType(const QDomNode &node, const QDomNode &parent = QDomNode())
    {
        Q_UNUSED(parent);

        if(node.nodeName() == "name")
            return ItemValue::valueName;
        if(node.nodeName() == "address")
            return ItemValue::valueAddress;
        if(node.parentNode().nodeName() == "type" && node.nodeName() != "derived")
            return ItemValue::valueDataSimple;
        if(node.parentNode().nodeName() == "type" && node.nodeName() == "derived")
            return ItemValue::valueDataDerived;
        if(node.firstChild().nodeName() == "simpleValue")
            return ItemValue::valueInitSimple;
        // if(node.firstChild().nodeName() == "structValue")
        //     return ItemValue::valueInitStruct;
        if(node.nodeName() == "documentation")
            return ItemValue::valueDocumentation;

        return ItemValue::valueDefault;
    }

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent)
    {
        ItemValue::ValueType type = getValueType(node, parent);

        qDebug() << getValueType(node, parent) << node.nodeName() << parent.nodeName() << m_creators.contains(type);

        if(m_creators.contains(type))
            return m_creators.value(type)->create(node, parent);

        return nullptr;
    }

private:
    QHash<ItemValue::ValueType, ItemValue_creator*> m_creators;
};
// ----------------------------------------------------------------------------

#endif // ITEMVALUE_H
