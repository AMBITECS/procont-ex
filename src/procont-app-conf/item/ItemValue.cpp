#include "ItemValue.h"

#include <QtXml>

// ----------------------------------------------------------------------------
// *** ItemValue interface ***

ItemValue::ItemValue(const QDomNode &node, const QDomNode &parent) :
    m_node(node),
    m_parent(parent)
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Default ***

ItemValue_Default::ItemValue_Default(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_Default::get() const
{
    return node().nodeName();
}

void ItemValue_Default::set(const QString &)
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeName ***

ItemValue_NodeName::ItemValue_NodeName(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_NodeName::get() const
{
    return node().nodeName();
}

void ItemValue_NodeName::set(const QString &value)
{
    qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << node().nodeValue() << value;

    parent().removeChild(node());
    QDomNode new_node = parent().ownerDocument().createElement(value);
    m_node = parent().appendChild(new_node);

    qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << node().nodeValue() << new_node.isNull();
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue ***

ItemValue_NodeValue::ItemValue_NodeValue(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_NodeValue::get() const
{
    return node().nodeValue();
}

void ItemValue_NodeValue::set(const QString &value)
{
    node().setNodeValue(value);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_optional ***

ItemValue_Attr_optional::ItemValue_Attr_optional(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_Attr_optional::get() const
{
    return node().nodeValue();
}

void ItemValue_Attr_optional::set(const QString &value)
{
    if(value.isEmpty())
    {
        parent().toElement().removeAttributeNode(node().toAttr());
        m_node = QDomNode();
    }
    else
    {
        parent().toElement().setAttribute(m_name, value);
        m_node = parent().attributes().namedItem(m_name);
    }
}

void ItemValue_Attr_optional::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr ***

ItemValue_Attr::ItemValue_Attr(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_Attr::get() const
{
    return node().toElement().attribute(m_name);
}

void ItemValue_Attr::set(const QString &value)
{
    node().toElement().setAttribute(m_name, value);
}

void ItemValue_Attr::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeAttr ***

ItemValue_SubNodeAttr::ItemValue_SubNodeAttr(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_SubNodeAttr::get() const
{
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << node().toElement().namedItem(m_nodeName).toElement().attribute(m_chAttrName);

    return node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
}

void ItemValue_SubNodeAttr::set(const QString &value)
{
    qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << value;

    parent().removeChild(node());
    m_node = QDomNode();

    qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);

    if(!value.isEmpty())
    {
        qDebug() << __PRETTY_FUNCTION__;

        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, value);
        m_node = parent().appendChild(new_node);
        node().appendChild(new_child);
    }

    qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
}

void ItemValue_SubNodeAttr::setNodeName(const QString &name)
{
    m_nodeName = name;
}

void ItemValue_SubNodeAttr::setChNodeName(const QString &name)
{
    m_chNodeName = name;
}

void ItemValue_SubNodeAttr::setChAttrName(const QString &name)
{
    m_chAttrName = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeNameNodeValue_creator ***

ItemValue * ItemValue_Default_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_Default(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeName_creator ***

ItemValue * ItemValue_NodeName_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_NodeName(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue_creator ***

ItemValue * ItemValue_NodeValue_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_NodeValue(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_optional_creator ***

ItemValue * ItemValue_Attr_optional_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_Attr_optional(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_creator ***

ItemValue * ItemValue_Attr_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_Attr(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeAttr_creator ***

ItemValue * ItemValue_SubNodeAttr_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new ItemValue_SubNodeAttr(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_builder ***

ItemValue_builder::ItemValue_builder()
{
    m_creators.insert(DomItem::valueDefault, new ItemValue_Default_creator);
    m_creators.insert(DomItem::valueNodeName, new ItemValue_NodeName_creator);
    m_creators.insert(DomItem::valueNodeValue, new ItemValue_NodeValue_creator);
    m_creators.insert(DomItem::valueAttr_optional, new ItemValue_Attr_optional_creator);
    m_creators.insert(DomItem::valueAttr, new ItemValue_Attr_creator);
    m_creators.insert(DomItem::valueSubNodeAttr, new ItemValue_SubNodeAttr_creator);
}

ItemValue_builder::~ItemValue_builder()
{
    for(const auto & creator : std::as_const(m_creators))
        delete creator;
}

ItemValue * ItemValue_builder::build(const QDomNode &node, const QDomNode &parent, DomItem::ValueType valueType)
{
    if(m_creators.contains(valueType))
        return m_creators.value(valueType)->create(node, parent);

    return nullptr;
}
// ----------------------------------------------------------------------------
