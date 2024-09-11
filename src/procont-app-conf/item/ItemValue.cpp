#include "ItemValue.h"

#include <QtXml>

// ----------------------------------------------------------------------------
// *** ItemValue interface ***

ItemValue::ItemValue(const QDomNode &node) :
    m_node(node),
    m_parent(node.parentNode())
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Default ***

ItemValue_Default::ItemValue_Default(const QDomNode &node) :
    ItemValue(node)
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

ItemValue_NodeName::ItemValue_NodeName(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_NodeName::get() const
{
    return node().nodeName();
}

void ItemValue_NodeName::set(const QString &value)
{
    parent().removeChild(node());
    QDomNode new_node = parent().ownerDocument().createElement(value);
    m_node = parent().appendChild(new_node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue ***

ItemValue_NodeValue::ItemValue_NodeValue(const QDomNode &node) :
    ItemValue(node)
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
// *** ItemValue_SubNodeValue ***

ItemValue_SubNodeValue::ItemValue_SubNodeValue(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_SubNodeValue::get() const
{
    QString doc = QString();
    for(const auto & name : m_name.split(';'))
    {
        if(!node().namedItem(name).isNull())
        {
            doc = name;
            break;
        }
    }

    return node().namedItem(doc).toElement().text();
}

void ItemValue_SubNodeValue::set(const QString &value)
{
    QString doc = QString();
    for(const auto & name : m_name.split(';'))
    {
        if(!node().namedItem(name).isNull())
        {
            doc = name;
            break;
        }
    }

    parent().removeChild(node());
    m_node = {};
    if(!value.isEmpty())
    {
        QDomText text = parent().ownerDocument().createCDATASection(value); text.setData(value);
        QDomNode xhtml = parent().ownerDocument().createElement("xhtml:p");
        xhtml.appendChild(text);
        QDomNode doc = parent().ownerDocument().createElement("documentation");
        doc.appendChild(xhtml);
        m_node = parent().appendChild(doc);
    }
}

void ItemValue_SubNodeValue::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_opt ***

ItemValue_Attr_opt::ItemValue_Attr_opt(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_Attr_opt::get() const
{
    return node().nodeValue();
}

void ItemValue_Attr_opt::set(const QString &value)
{
    if(value.isEmpty())
    {
        if(!node().isNull()) parent().toElement().removeAttributeNode(node().toAttr());
        m_node = {};
    }
    else
    {
        parent().toElement().setAttribute(m_name, value);
        m_node = parent().attributes().namedItem(m_name);
    }
}

void ItemValue_Attr_opt::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_req ***

ItemValue_Attr_req::ItemValue_Attr_req(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_Attr_req::get() const
{
    return node().toElement().attribute(m_name);
}

void ItemValue_Attr_req::set(const QString &value)
{
    node().toElement().setAttribute(m_name, value);
}

void ItemValue_Attr_req::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeAttr ***

ItemValue_SubNodeAttr::ItemValue_SubNodeAttr(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_SubNodeAttr::get() const
{
    return node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
}

void ItemValue_SubNodeAttr::set(const QString &value)
{
    parent().removeChild(node());
    m_node = {};

    if(!value.isEmpty())
    {
        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, value);
        m_node = parent().appendChild(new_node);
        node().appendChild(new_child);
    }
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
