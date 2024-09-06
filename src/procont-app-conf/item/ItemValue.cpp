#include "ItemValue.h"

#include <QtXml>

QScopedPointer<ItemValue_builder> ItemValue_builder::m_instance = QScopedPointer<ItemValue_builder>(nullptr);

// ----------------------------------------------------------------------------
// *** ItemValue interface ***

ItemValue::ItemValue(const QDomNode &node, const QDomNode &parent) :
    m_node(node),
    m_parent(parent)
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_StructValue ***

ItemValue_StructValue::ItemValue_StructValue(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
    QDomNodeList values = node.firstChild().toElement().childNodes();
    for(auto i=0;i<values.count();i++)
        if(values.at(i).nodeName() == "value")
            m_values.append(QSharedPointer<ItemValue>(ItemValue_builder::instance()->build(values.at(i), node.firstChild())));
}

QString ItemValue_StructValue::get() const
{
    QString value = "(";
    for(const auto & i : m_values)
        value += QString("%1, ").arg(i->get());
    if(value.size() > 2)
        value = value.left(value.size() - 2);
    value += ')';

    return value;
}

void ItemValue_StructValue::set(const QString &value)
{
    for(auto & i : m_values)
        i->set(QString());
    m_values.clear();

    ItemValue * item = nullptr;
    for(const auto & i : QString(value).remove('(').remove(')').split(", "))
    {
        qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << parent().nodeName();

        item = new ItemValue_SimpleValue_struct(QDomNode(), node().firstChild());
        item->set(i);
        m_values.append(QSharedPointer<ItemValue>(item));
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_ArrayValue ***

ItemValue_ArrayValue::ItemValue_ArrayValue(const QDomNode &node, const QDomNode &parent) :
    ItemValue(node, parent)
{
    QDomNodeList values = node.firstChild().toElement().childNodes();
    for(auto i=0;i<values.count();i++)
        if(values.at(i).nodeName() == "value")
            m_values.append(QSharedPointer<ItemValue>(ItemValue_builder::instance()->build(values.at(i), node.firstChild())));
}

QString ItemValue_ArrayValue::get() const
{
    QString value = "[";
    for(const auto & i : m_values)
        value += QString("%1, ").arg(i->get());
    if(value.size() > 2)
        value = value.left(value.size() - 2);
    value += ']';

    return value;
}

void ItemValue_ArrayValue::set(const QString &value)
{
    for(auto & i : m_values)
        i->set(QString());
    m_values.clear();

    ItemValue * item = nullptr;
    for(const auto & i : QString(value).remove('[').remove(']').split(", "))
    {
        qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << parent().nodeName();

        item = new ItemValue_SimpleValue_array(QDomNode(), node().firstChild());
        item->set(i);
        m_values.append(QSharedPointer<ItemValue>(item));
    }
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
    // qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << node().nodeValue() << value;

    parent().removeChild(node());
    QDomNode new_node = parent().ownerDocument().createElement(value);
    m_node = parent().appendChild(new_node);

    // qDebug() << __PRETTY_FUNCTION__ << node().nodeName() << node().nodeValue() << new_node.isNull();
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

    // qDebug() << __PRETTY_FUNCTION__ << value.toUtf8() << parent().nodeName() << node().nodeName() << node().namedItem(doc).toElement().text();

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

    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << node().namedItem(doc).toElement().text();
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
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << value;

    parent().removeChild(node());
    m_node = {};

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);

    if(!value.isEmpty())
    {
        qDebug() << __PRETTY_FUNCTION__;

        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, value);
        m_node = parent().appendChild(new_node);
        node().appendChild(new_child);
    }

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
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
// *** ItemValue_SimpleValue_struct ***

QString ItemValue_SimpleValue_struct::get() const
{
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << node().toElement().namedItem(m_nodeName).toElement().attribute(m_chAttrName);

    return QString("%1 := %2")
        .arg(node().toElement().attribute("member"))
        .arg(node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName));
}

void ItemValue_SimpleValue_struct::set(const QString &value)
{
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << value;

    parent().removeChild(node());
    m_node = {};

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);

    if(!value.size())
        return;

    static QRegularExpression re = QRegularExpression("\\s+\\:\\=\\s+");
    QStringList key_value = QString(value).split(re);

    if(key_value.size() > 1 && !key_value.at(1).isEmpty())
    {
        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, key_value.at(1));
        m_node = parent().appendChild(new_node);
        m_node.toElement().setAttribute("member", key_value.at(0));
        node().appendChild(new_child);
    }

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_array ***

QString ItemValue_SimpleValue_array::get() const
{
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << node().toElement().namedItem(m_nodeName).toElement().attribute(m_chAttrName);

    QString value = node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
    if(node().toElement().hasAttribute("repetitionValue"))
        value = QString("%1(%2)").arg(node().toElement().attribute("repetitionValue")).arg(value);

    return value;
}

void ItemValue_SimpleValue_array::set(const QString &value)
{
    // qDebug() << __PRETTY_FUNCTION__ << parent().nodeName() << node().nodeName() << m_nodeName << m_chNodeName << m_chAttrName << value;

    parent().removeChild(node());
    m_node = {};

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);

    if(!value.isEmpty())
    {
        QString repetition = {}, value_set = {};
        int i = value.indexOf("(");
        if(i != -1)
        {
            repetition = value.left(i);
            value_set = value.right(value.size()-i-1);
            value_set = value_set.left(value_set.size()-1);
        }
        else
            value_set = value;

        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        if(repetition.size())
            new_node.toElement().setAttribute("repetitionValue", repetition);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, value_set);
        m_node = parent().appendChild(new_node);
        node().appendChild(new_child);
    }

    // qDebug() << __PRETTY_FUNCTION__ << node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
}
// ----------------------------------------------------------------------------



