#include <string>
#include <iostream>
#include <stack>

#include <QString>
#include <QStack>
#include <QRegularExpression>

#include <QDebug>

using namespace std;

int find_close_bracket(const QString & expression, int index, QChar open, QChar close)
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

int find_open_bracket(const QString & expression, int index, QChar open, QChar close)
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

bool is_open_bracket_balanced(const QString & expression, QChar open, QChar close)
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

bool is_close_bracket_balanced(const QString & expression, QChar open, QChar close)
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

bool is_bracket_balanced(const QString & expression)
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

QString get_type(QChar c)
{
    if(c == QChar('['))
        return "array";
    if(c == QChar('('))
        return "struct";
}

QChar get_close_bracket(QChar c)
{
   if(c == QChar('['))
        return QChar(']');

   if(c == QChar('('))
       return QChar(')');

   return QChar('\0');
}

bool is_open_bracket(QChar c)
{
    return (c == QChar('(') || c == QChar('['));
}

class InitialValue
{
public:
    InitialValue() = default;

public:
    int repeate = 1;
    QString type = {};
    QString value = {};
    QList<InitialValue> values;
};

bool is_identifier(const QString &identifier)
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

bool is_simple_format(const QString &value, const QString &parent)
{
    if(parent == "struct")
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

int parse_expression(const QString & expression, const QString & parent, InitialValue &v)
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
        v.type = get_type(c);
        v.repeate = count;
        qDebug() << v.repeate << v.type;
    }
    else
    {
        v.type = "simple" + (parent.size() ? QString("_%1").arg(parent) : QString());
        v.repeate = count;
        if(!is_simple_format(value, parent))
        {
            qDebug() << value;
            return 5;
        }
        v.value = value;
        qDebug() << v.repeate << v.type << value;
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
            int r = parse_expression(value.left(index), v.type, c);
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

int main(int, char **)
{
    QString str = "[[3([2(())])]], [[(CD := TRUE, PV := 1), ()], 2([2([ertert])])], 2([3([2(())])])]";
    cout << is_bracket_balanced(str) << endl;
    InitialValue v;
    cout << parse_expression(str, {}, v);

    return 0;
}
