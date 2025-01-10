#include <QObject>
#include <QMap>

class tr_str : public QObject
{
    Q_OBJECT
public:
    enum class eTranslateLetters
    {
        eTL_Lowercase,
        eTL_Uppercase,
        eTL_Capital
    };
public:
    tr_str();

    [[nodiscard]] QString ru(const QString &word_en_, eTranslateLetters letter_ = eTranslateLetters::eTL_Lowercase);
    [[nodiscard]] QString en(const QString &word_ru_);

    [[nodiscard]] QString letter(const QString &word_en_, eTranslateLetters letter_ = eTranslateLetters::eTL_Lowercase);
public:
    [[nodiscard]] static tr_str * instance();

private:
    [[nodiscard]] static QString letterToStr(eTranslateLetters letter_);

private:
    static tr_str * _m_instance;
    QMap<QString, QString> _m_strings_ru;
    QMap<QString, QString> _m_strings_letter;
    const std::list<QString> _m_letterKeywords = { "#1", "#2" };
};
