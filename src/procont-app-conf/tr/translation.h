#include <QObject>
#include <QMap>

class tr_str : public QObject
{
    Q_OBJECT
public:
    tr_str();

    QString ru(const QString &);
    QString en(const QString &);
public:
    static tr_str * instance();
private:
    static tr_str * _m_instance;
    QMap<QString, QString> _m_strings;
};
