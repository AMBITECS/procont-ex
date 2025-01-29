#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

    void searchText(const QString& text);
    void wordsFromFile(const QString& fileName);
    void setNewWords(const QStringList& list);

protected:
    void highlightBlock(const QString &text) override;

private:
    void checkType(const QString &text);

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression searchPattern; // Regular expression to search for, in our case, this word or text
    QTextCharFormat searchFormat;     // Text formatting, highlighting

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat ariphmeticFormat;
    QTextCharFormat valuesFormat;
    QTextCharFormat redLineFormat;

    QStringList words_;

};


