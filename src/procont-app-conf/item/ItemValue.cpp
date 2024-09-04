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
// *** ItemValue_SubNodeValue ***

ItemValue_SubNodeValue::ItemValue_SubNodeValue(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_SubNodeValue::get() const
{
    QString doc = QString();
    for(auto name : m_name.split(';'))
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
    for(auto name : m_name.split(';'))
    {
        if(!node().namedItem(name).isNull())
        {
            doc = name;
            break;
        }
    }

    qDebug() << __PRETTY_FUNCTION__ << value.toUtf8() << parent().nodeName() << node().nodeName() << node().namedItem(doc).toElement().text();

    parent().removeChild(node());

    if(!value.isEmpty())
    {
        QDomText text = parent().ownerDocument().createCDATASection(value); text.setData(value);
        QDomNode xhtml = parent().ownerDocument().createElement("xhtml:p");
        xhtml.appendChild(text);
        QDomNode doc = parent().ownerDocument().createElement("documentation");
        doc.appendChild(xhtml);
        m_node = parent().appendChild(doc);
    }
    qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << node().namedItem(doc).toElement().text();

}

void ItemValue_SubNodeValue::setName(const QString &name)
{
    m_name = name;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_opt ***

ItemValue_Attr_opt::ItemValue_Attr_opt(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
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
        parent().toElement().removeAttributeNode(node().toAttr());
        m_node = QDomNode();
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

ItemValue_Attr_req::ItemValue_Attr_req(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
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
// *** ItemValue_NodeValue ***

ItemValue_StructValue::ItemValue_StructValue(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
}

QString ItemValue_StructValue::get() const
{
    return node().nodeValue();
}

void ItemValue_StructValue::set(const QString &value)
{
    node().setNodeValue(value);
}
// ----------------------------------------------------------------------------
