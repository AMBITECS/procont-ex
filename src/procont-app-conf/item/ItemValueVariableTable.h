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


// ----------------------------------------------------------------------------
// *** ItemValue_TypeSimple***

/*!
 * \brief The ItemValue_TypeSimple
 */

class ItemValue_TypeSimple : public ItemValue
{
public:
    ItemValue_TypeSimple(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

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

#include <QRegularExpression>
#include <QStack>

// ----------------------------------------------------------------------------
// *** ItemValue_InitialValue ***

/*!
 * \brief The ItemValue_InitialValue class
 */

class ItemValue_InitialValue : public ItemValue
{
public:
    enum class ValueType
    {
        valueEmpty,
        valueSimple,
        valueSimple_struct,
        valueSimple_array,
        valueStruct,
        valueArray
    };
public:
    ItemValue_InitialValue(const QDomNode &node/*, const QDomNode &parent = {}*/);
    ItemValue_InitialValue(const QDomNode &node, const QString &);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

public:
    [[nodiscard]] static ValueType type(const QDomNode &node);
    [[nodiscard]] static ValueType type(const QString &value, ItemValue_InitialValue::ValueType parentType = ValueType::valueEmpty);
    [[nodiscard]] static ItemValue * create(const QDomNode &node);
    [[nodiscard]] static ItemValue * create(const QDomNode &node, ValueType type);

private:
    struct InitialValue
    {
        int repeate = 1;
        ItemValue_InitialValue::ValueType type = ItemValue_InitialValue::ValueType::valueEmpty;
        QString value = {};
        QList<InitialValue> values;

        QStringList print() const
        {
            QStringList str; str << QString("%1, %2, %3").arg(static_cast<int>(type)).arg(repeate).arg(value);

            for(auto i : values)
                str << i.print();

            return str;
        }

    };
    class InitialValue_parser
    {
    public:
        InitialValue_parser() = default;

        static int parse(const QString & expression, ItemValue_InitialValue::ValueType parentType, InitialValue & v)
        {
            // remove blanks
            static QRegularExpression blank("\\s+");
            QString value = expression; value = value.remove(blank);

            // bracket error
            if(!is_bracket_balanced(value))
                return 1;

            // repeate
            static QRegularExpression digit("^\\d+\\(");
            int count = 1;
            if(digit.match(value).hasMatch())
            {
                static QRegularExpression repeate("^\\d+\\(.*\\)");
                // repeate format error
                if(!repeate.match(value).hasMatch())
                    return 3;
                count = value.left(value.indexOf('(')).toInt();
                if(value.indexOf('(')+1 >= value.lastIndexOf(')'))
                    return 4;
                value = value.mid(value.indexOf('(')+1, value.lastIndexOf(')'));
            }

            QChar c = value.at(0);
            if(is_open_bracket(c))
            {
                v.type = type(value);
                v.repeate = count;
            }
            else
            {
                v.type = type(value, parentType);
                qDebug() << "--" << static_cast<int>(parentType) << static_cast<int>(v.type);
                v.repeate = count;
                if(!is_simple_format(value, parentType))
                    return 5;
                v.value = value;
                return 0;
            }

            int index = find_close_bracket(value, 0, c, get_close_bracket(c));
            value = QString(value).mid(1, index-1);
            while(value.length())
            {
                c = value.at(0);
                int comma_find = 0;
                if(is_open_bracket(c))
                    comma_find = find_close_bracket(value, 0, c, get_close_bracket(c));

                index = value.indexOf(QChar(','), comma_find);

                if(index)
                {
                    InitialValue c;
                    int r = parse(value.left(index), v.type, c);
                    if(r) return r;
                    v.values.append(c);
                }
                else
                    // comma error
                    return 2;

                if(index != -1)
                    value = value.right(value.length()-index-1);
                else
                    break;
            }

            return 0;
        }

    private:

        static int find_close_bracket(const QString & expression, int index, QChar open, QChar close)
        {
            if(expression[index] != open)
                return -1;
            QStack<QChar> st;
            for(auto i=index;i<expression.length(); i++)
            {
                if(expression[i] == open)
                    st.push(expression[i]);
                else if(expression[i] == close)
                {
                    st.pop();
                    if(st.empty())
                        return i;
                }
            }
            return -1;
        }

        static int find_open_bracket(const QString & expression, int index, QChar open, QChar close)
        {
            if(expression[index] != close)
                return -1;
            QStack<QChar> st;
            for(auto i=index;i>=0; i--)
            {
                if(expression[i] == close)
                    st.push(expression[i]);
                else if(expression[i] == open)
                {
                    st.pop();
                    if(st.empty())
                        return i;
                }
            }
            return -1;
        }

        static bool is_open_bracket_balanced(const QString & expression, QChar open, QChar close)
        {
            auto result = true;
            qsizetype i = 0;
            while((i = expression.indexOf(open, i)) != -1)
            {
                if(find_close_bracket(expression, i, open, close) == -1)
                {
                    result = false;
                    break;
                }
                i++;
            }
            return result;
        }

        static bool is_close_bracket_balanced(const QString & expression, QChar open, QChar close)
        {
            auto result = true;
            qsizetype i = expression.length();
            while((i = expression.lastIndexOf(close, i)) != -1)
            {
                if(find_open_bracket(expression, i, open, close) == -1)
                {
                    result = false;
                    break;
                }
                i--;
            }
            return result;
        }

        static bool is_bracket_balanced(const QString & expression)
        {
            bool result;

            result = is_open_bracket_balanced(expression, QChar('['), QChar(']'));
            if(!result) return result;
            result = is_close_bracket_balanced(expression, QChar('['), QChar(']'));
            if(!result) return result;

            result = is_open_bracket_balanced(expression, QChar('('), QChar(')'));
            if(!result) return result;
            result = is_close_bracket_balanced(expression, QChar('('), QChar(')'));
            if(!result) return result;

            return true;
        }

        static QChar get_close_bracket(QChar c)
        {
            if(c == QChar('['))
                return QChar(']');

            if(c == QChar('('))
                return QChar(')');

            return QChar('\0');
        }

        static bool is_open_bracket(QChar c)
        {
            return (c == QChar('(') || c == QChar('['));
        }

        static bool is_identifier(const QString &identifier)
        {
            static QRegularExpression re_w("^[A-Za-z_]\\w*$");
            if(!re_w.match(identifier).hasMatch())
                return false;

            static QRegularExpression re_a("_{2,}");
            if(re_a.match(identifier).hasMatch())
                return false;

            static QRegularExpression re_b("_{1,}$");
            if(re_b.match(identifier).hasMatch())
                return false;

            return true;
        }

        static bool is_simple_format(const QString &value, ItemValue_InitialValue::ValueType parentType)
        {
            if(parentType == ItemValue_InitialValue::ValueType::valueStruct)
            {
                static QRegularExpression re = QRegularExpression("\\:\\=");
                if(re.match(value).hasMatch())
                {
                    QStringList vars = value.split(re);
                    if(vars.size() == 2 && is_identifier(vars.at(0)))
                        return true;
                }
            }
            else
                return is_identifier(value);

            return false;
        }
    };
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
