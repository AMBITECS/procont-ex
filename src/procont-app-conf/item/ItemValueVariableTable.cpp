#include "ItemValueVariableTable.h"

#include <QRegularExpression>

// ----------------------------------------------------------------------------
// *** ItemValue_Type ***

QHash<QString, QString> ItemValue_Type::m_types = {
    {"localVars", "VAR"}, {"inputVars", "VAR_INPUT"}, {"outputVars", "VAR_OUTPUT"},
    {"inOutVars", "VAR_IN_OUT"}, {"tempVars", "VAR_TEMP"}, {"externalVars", "VAR_EXTERNAL"}, {"globalVars", "VAR_GLOBAL"} };

QHash<QString, QString> ItemValue_Type::m_modifiers_i = {
    {"constant", "CONSTANT"}, {"persistent", "PERSISTENT"}, {"nonpersistent", "PERSISTENT"},
    {"retain", "RETAIN"}, {"nonretain", "RETAIN"}};

QHash<QString, QString> ItemValue_Type::m_modifiers_o = {
    {"constant", "CONSTANT"}, {"persistent", "PERSISTENT"}, {"retain", "RETAIN"}};

QHash<QString, QString> ItemValue_Type::m_modifiers_values_i = {
    {"constant", "true"}, {"persistent", "true"}, {"nonpersistent", "false"},
    {"retain", "true"}, {"nonretain", "false"}};

QHash<QString, QString> ItemValue_Type::m_modifiers_values_o = {
    {"constant", "true"}, {"persistent", "true"}, {"retain", "true"}};


ItemValue_Type::ItemValue_Type(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_Type::type(const QString &value)
{
    static QRegularExpression re("\\s+");
    QStringList list = value.split(re);

    QString type = {};
    for(const auto & i : list)
    {     
        if(std::find(m_types.cbegin(), m_types.cend(), i) != m_types.cend() && type.isEmpty())
            type = m_types.key(i);
    }

    return type;
}

QHash<QString, QString> ItemValue_Type::modifiers(const QString &value)
{
    static QRegularExpression re("\\s+");
    QStringList list = value.split(re);

    QHash<QString, QString> hModifiers;
    for(const auto & i : list)
    {
        if(m_modifiers_o.values().contains(i) && !hModifiers.contains(m_modifiers_o.key(i)))
            hModifiers.insert(m_modifiers_o.key(i), m_modifiers_values_o.value(m_modifiers_o.key(i)));
    }

    return hModifiers;
}

QHash<QString, QString> ItemValue_Type::modifiers(const QDomNode &node)
{
    QHash<QString, QString> hModifiers;
    for(const auto & i : m_modifiers_values_i.keys())
    {
        if(node.toElement().attribute(i).toLower() == m_modifiers_values_i.value(i))
        {
            QString key = m_modifiers_o.key(m_modifiers_i.value(i));
            hModifiers.insert(key, m_modifiers_values_o.value(key));
        }
    }

    return hModifiers;
}

QString ItemValue_Type::get() const
{
    QString value = parent().nodeName();

    if(m_types.keys().contains(value))
        value = m_types.value(value);
    else
        value = "ERROR";

    for(const auto & i : m_modifiers_values_i.keys())
    {
        if(parent().toElement().attribute(i).toLower() == m_modifiers_values_i.value(i))
            value = QString("%1 %2").arg(value, m_modifiers_i.value(i));
    }

    return value;
}

void ItemValue_Type::set(const QString &value_new)
{
    QString value_old = get();
    if(value_new == value_old)
        return;

    QString type_new = type(value_new);

    QHash<QString, QString> hModifiers_new = modifiers(value_new);

    QDomNode parent_act = parent().parentNode();
    QDomNode node_act = parent();

    if(!type_new.isEmpty())
    {
        QDomNode interface = parent_act;
        QDomNode vars_old = node_act;
        QDomNodeList vars_new_list = interface.toElement().elementsByTagName(type_new);

        QDomNode vars_new = {};
        for(auto i=0;i<vars_new_list.count();i++)
            if(modifiers(vars_new_list.at(i)) == hModifiers_new)
                vars_new = vars_new_list.at(i);

        if(vars_new.isNull())
        {
            vars_new = interface.ownerDocument().createElement(type_new);
            vars_new = interface.appendChild(vars_new);
            for(const auto & i : hModifiers_new.keys())
                vars_new.toElement().setAttribute(i, hModifiers_new.value(i));
        }
        QDomNode node_new = vars_new.appendChild(node().cloneNode());
        vars_old.removeChild(node());
        if(vars_old.childNodes().count() == 0)
            interface.removeChild(vars_old);

        m_node = node_new; m_parent = vars_new;
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_DataType ***

QStringList ItemValue_DataType::m_simpleTypes = {
    "BOOL", "BYTE", "WORD", "DWORD", "LWORD", "SINT", "INT", "DINT", "LINT",
    "USINT", "UINT", "UDINT", "ULINT", "REAL", "LREAL", "TIME", "DATE", "DT", "TOD", "string", "wstring" };

ItemValue_DataType::ItemValue_DataType(const QDomNode &node) :
    ItemValue(node),
    m_value(create(node))
{
}

ItemValue_DataType::ValueType ItemValue_DataType::type(const QDomNode &node)
{
    if(node.firstChild().nodeName() == "derived")
        return ValueType::valueDerived;

    if(node.firstChild().nodeName() == "array")
        return ValueType::valueArray;

    return ValueType::valueSimple;
}

ItemValue_DataType::ValueType ItemValue_DataType::type(const QString &value)
{
    static QRegularExpression re_array("ARRAY\\s+\\[\\d+\\.\\.\\d+\\]\\s+OF\\s+");
    QRegularExpressionMatch match = re_array.match(value);
    if(match.hasMatch() && match.capturedStart() == 0)
        return ValueType::valueArray;

    if(m_simpleTypes.contains(value))
        return ValueType::valueSimple;

    return ValueType::valueDerived;
}

ItemValue * ItemValue_DataType::create(const QDomNode &node, ValueType type)
{
    if(type == ValueType::valueDerived)
        return new ItemValue_TypeDerived(node);

    if(type == ValueType::valueArray)
        return new ItemValue_TypeArray(node);

    return new ItemValue_TypeSimple(node);
}

ItemValue * ItemValue_DataType::create(const QDomNode &node)
{
    return create(node, type(node));
}

QString ItemValue_DataType::get() const
{
    return m_value->get();
}

void ItemValue_DataType::set(const QString &value)
{
    ValueType type_old = type(node());
    ValueType type_new = type(value);

    if(type_new != type_old)
        m_value.reset(create(node(), type_new));

    m_value->set(value);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeSimple ***

ItemValue_TypeSimple::ItemValue_TypeSimple(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_TypeSimple::get() const
{
    return node().firstChild().nodeName();
}

void ItemValue_TypeSimple::set(const QString &value)
{
    node().removeChild(node().firstChild());
    QDomNode new_node = node().ownerDocument().createElement(value);
    node().appendChild(new_node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeDerived ***

ItemValue_TypeDerived::ItemValue_TypeDerived(const QDomNode &node) :
    ItemValue(node)
{
}

QString ItemValue_TypeDerived::get() const
{
    return node().firstChild().toElement().attribute("name");
}

void ItemValue_TypeDerived::set(const QString &value)
{
    node().removeChild(node().firstChild());
    QDomNode new_node = node().ownerDocument().createElement("derived");
    new_node.toElement().setAttribute("name", value);
    node().appendChild(new_node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_TypeArray ***

ItemValue_TypeArray::ItemValue_TypeArray(const QDomNode &node) :
    ItemValue(node),
    m_value(ItemValue_DataType::create(node.firstChild().namedItem("baseType")))
{
}

ItemValue_TypeArray::ItemValue_TypeArray(const QDomNode &node, const QString &value) :
    ItemValue(node),
    m_value(ItemValue_DataType::create(node.firstChild().namedItem("baseType"), ItemValue_DataType::type(value)))
{
}

QString ItemValue_TypeArray::get() const
{
    auto dim = node().firstChild().namedItem("dimension").toElement();

    return QString("ARRAY [%1..%2] OF %3").arg(dim.attribute("lower"), dim.attribute("upper"), m_value->get());
}

void ItemValue_TypeArray::set(const QString &value)
{
    node().removeChild(node().firstChild());

    static QRegularExpression re_array("ARRAY\\s+\\[\\d+\\.\\.\\d+\\]\\s+OF\\s+");
    static QRegularExpression re_digit("\\d+");
    static QRegularExpression space("\\s+$");
    auto value_current = QString(value);
    QRegularExpressionMatch match_array, match_digit;

    match_array = re_array.match(value_current);
    if(match_array.hasMatch())
    {
        auto array = match_array.captured(); array = array.remove(space);
        value_current = value_current.right(value_current.size()-match_array.capturedEnd());
        QDomNode node_new = parent().ownerDocument().createElement("array");
        QDomNode dimension = parent().ownerDocument().createElement("dimension");
        match_digit = re_digit.match(array);
        dimension.toElement().setAttribute("lower", match_digit.captured());
        match_digit = re_digit.match(array, match_digit.capturedEnd());
        dimension.toElement().setAttribute("upper", match_digit.captured());
        node_new.appendChild(dimension);
        node_new.appendChild(parent().ownerDocument().createElement("baseType"));
        node().appendChild(node_new);
    }

    match_array = re_array.match(value_current);
    if(match_array.hasMatch())
        m_value.reset(new ItemValue_TypeArray(node().firstChild().namedItem("baseType"), value_current));
    else
        m_value.reset(ItemValue_DataType::create(node().firstChild().namedItem("baseType"), ItemValue_DataType::type(value_current)));
    m_value->set(value_current);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_InitialValue ***

ItemValue_InitialValue::ItemValue_InitialValue(const QDomNode &node) :
    ItemValue(node),
    m_value(create(node))
{
}

ItemValue_InitialValue::ValueType ItemValue_InitialValue::type(const QDomNode &node)
{
    if(node.firstChild().nodeName() == "structValue")
        return ValueType::valueStruct;

    if(node.firstChild().nodeName() == "arrayValue")
        return ValueType::valueArray;

    if(node.firstChild().nodeName() == "simpleValue" && node.toElement().hasAttribute("member"))
        return ValueType::valueSimple_struct;
    if(node.firstChild().nodeName() == "simpleValue" && !node.toElement().hasAttribute("member"))
        return ValueType::valueSimple_array;

    return ValueType::valueSimple;
}

ItemValue_InitialValue::ValueType ItemValue_InitialValue::type(const QString &value, ItemValue_InitialValue::ValueType parentType)
{
    if(value.at(0) == '[')
        return ValueType::valueArray;

    if(value.at(0) == '(')
        return ValueType::valueStruct;

    if(parentType == ValueType::valueStruct)
        return ValueType::valueSimple_struct;

    if(parentType == ValueType::valueArray)
        return ValueType::valueSimple_array;

    return ValueType::valueSimple;
}

ItemValue * ItemValue_InitialValue::create(const QDomNode &node, ItemValue_InitialValue::ValueType type)
{
    if(type == ValueType::valueStruct)
        return new ItemValue_StructValue(node);

    if(type == ValueType::valueArray)
        return new ItemValue_ArrayValue(node);

    if(type == ValueType::valueSimple_struct)
        return new ItemValue_SimpleValue_struct(node);

    if(type == ValueType::valueSimple_array)
        return new ItemValue_SimpleValue_array(node);

    return new ItemValue_SimpleValue(node);
}

ItemValue * ItemValue_InitialValue::create(QDomNode & node, ItemValue_InitialValue::InitialValue value)
{
    if(value.type == ValueType::valueStruct)
        return new ItemValue_StructValue(node, value);

    if(value.type == ValueType::valueArray)
        return new ItemValue_ArrayValue(node, value);

    if(value.type == ValueType::valueSimple_struct)
        return new ItemValue_SimpleValue_struct(node);

    if(value.type == ValueType::valueSimple_array)
        return new ItemValue_SimpleValue_array(node);

    return new ItemValue_SimpleValue(node);
}

ItemValue * ItemValue_InitialValue::create(const QDomNode &node)
{
    return create(node, type(node));
}

QString ItemValue_InitialValue::get() const
{
    return m_value->get();
}

void ItemValue_InitialValue::set(const QString &value)
{
    InitialValue v;
    qDebug() << __PRETTY_FUNCTION__ << InitialValue_parser::parse(value, ItemValue_InitialValue::ValueType::valueEmpty, v);
    qDebug() << v.print();

    parent().removeChild(node());
    m_node = parent().ownerDocument().createElement("initialValue");
    m_node = parent().appendChild(m_node);

    m_value.reset(create(m_node, v));
    m_value->set({});
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_struct ***

QString ItemValue_SimpleValue_struct::get() const
{
    QString value = QString("%1 := %2")
                        .arg(node().toElement().attribute("member"))
                        .arg(node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName));

    if(node().toElement().hasAttribute("repetitionValue"))
        value = QString("%1(%2)").arg(node().toElement().attribute("repetitionValue")).arg(value);

    return value;
}

void ItemValue_SimpleValue_struct::set(const QString &value)
{
    parent().removeChild(node());
    m_node = {};

    if(!value.size())
        return;

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


    static QRegularExpression re = QRegularExpression("\\:\\=");
    QStringList key_value = QString(value_set).split(re);

    if(key_value.size() > 1 && !key_value.at(1).isEmpty())
    {
        QDomNode new_node = parent().ownerDocument().createElement(m_nodeName);
        if(repetition.size())
            new_node.toElement().setAttribute("repetitionValue", repetition);
        QDomNode new_child = parent().ownerDocument().createElement(m_chNodeName);
        new_child.toElement().setAttribute(m_chAttrName, key_value.at(1));
        m_node = parent().appendChild(new_node);
        m_node.toElement().setAttribute("member", key_value.at(0));
        node().appendChild(new_child);
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SimpleValue_array ***

QString ItemValue_SimpleValue_array::get() const
{
    QString value = node().toElement().namedItem(m_chNodeName).toElement().attribute(m_chAttrName);
    if(node().toElement().hasAttribute("repetitionValue"))
        value = QString("%1(%2)").arg(node().toElement().attribute("repetitionValue")).arg(value);

    return value;
}

void ItemValue_SimpleValue_array::set(const QString &value)
{
    parent().removeChild(node());
    m_node = {};

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
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_StructValue ***

ItemValue_StructValue::ItemValue_StructValue(const QDomNode &node) :
    ItemValue(node)
{
    QDomNodeList values = node.firstChild().toElement().childNodes();
    for(auto i=0;i<values.count();i++)
        if(values.at(i).nodeName() == "value")
            m_values.append(QSharedPointer<ItemValue>(ItemValue_InitialValue::create(values.at(i))));
}

ItemValue_StructValue::ItemValue_StructValue(QDomNode & node, ItemValue_InitialValue::InitialValue & value) :
    ItemValue(node)
{
    QDomNode node_new = node.ownerDocument().createElement("structValue");
    node_new = node.appendChild(node_new);

    ItemValue * item = nullptr;
    for(auto & i : value.values)
    {
        QDomNode node_child = node.ownerDocument().createElement("value");
        if(i.repeate > 1)
            node_child.toElement().setAttribute("repetitionValue", QString::number(i.repeate));
        node_child = node_new.appendChild(node_child);
        item = ItemValue_InitialValue::create(node_child, i);
        m_values.append(QSharedPointer<ItemValue>(item));
        m_initial.insert(item, i);
    }
}

QString ItemValue_StructValue::get() const
{
    QString value = "(";
    for(const auto & i : m_values)
        value += QString("%1, ").arg(i->get());
    if(value.size() > 2)
        value = value.left(value.size() - 2);
    value += ')';

    if(node().toElement().hasAttribute("repetitionValue"))
        value = QString("%1(%2)").arg(node().toElement().attribute("repetitionValue")).arg(value);

    return value;
}

void ItemValue_StructValue::set(const QString &)
{
    for(auto i : m_initial.keys())
        i->set(m_initial.value(i).value);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_ArrayValue ***

ItemValue_ArrayValue::ItemValue_ArrayValue(const QDomNode &node) :
    ItemValue(node)
{
    QDomNodeList values = node.firstChild().toElement().childNodes();
    for(auto i=0;i<values.count();i++)
        if(values.at(i).nodeName() == "value")
            m_values.append(QSharedPointer<ItemValue>(ItemValue_InitialValue::create(values.at(i))));
}

ItemValue_ArrayValue::ItemValue_ArrayValue(QDomNode & node, ItemValue_InitialValue::InitialValue & value) :
    ItemValue(node)
{
    QDomNode node_new = node.ownerDocument().createElement("arrayValue");
    node_new = node.appendChild(node_new);

    ItemValue * item = nullptr;
    for(auto & i : value.values)
    {
        QDomNode node_child = node.ownerDocument().createElement("value");
        if(i.repeate > 1)
            node_child.toElement().setAttribute("repetitionValue", QString::number(i.repeate));
        node_child = node_new.appendChild(node_child);
        item = ItemValue_InitialValue::create(node_child, i);
        m_values.append(QSharedPointer<ItemValue>(item));
        m_initial.insert(item, i);
    }
}

QString ItemValue_ArrayValue::get() const
{
    QString value = "[";
    for(const auto & i : m_values)
        value += QString("%1, ").arg(i->get());
    if(value.size() > 2)
        value = value.left(value.size() - 2);
    value += ']';

    if(node().toElement().hasAttribute("repetitionValue"))
        value = QString("%1(%2)").arg(node().toElement().attribute("repetitionValue")).arg(value);

    return value;
}

void ItemValue_ArrayValue::set(const QString &)
{
    for(auto i : m_initial.keys())
        i->set(m_initial.value(i).value);
}
// ----------------------------------------------------------------------------
