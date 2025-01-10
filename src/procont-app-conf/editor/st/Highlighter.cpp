#include "Highlighter.h"
#include <QFile>
#include <QCursor>
#include <QApplication>

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    redLineFormat.setBaselineOffset(10);
    redLineFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    redLineFormat.setUnderlineColor(Qt::red);

    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);

    ariphmeticFormat.setFontWeight(QFont::Bold);
    ariphmeticFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("[$&+,:;=?|'<>.^*()%!-/\\\\]"));
    rule.format = ariphmeticFormat;
    highlightingRules.append(rule);

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);


    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));

    searchFormat.setBackground(Qt::green);
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    checkType(text);


    QRegularExpressionMatchIterator matchIterator = searchPattern.globalMatch(text);
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), searchFormat);
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = text.indexOf(commentStartExpression);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

void Highlighter::checkType(const QString &text)
{
    QRegularExpression rule(R"((\w+):\s*(\w+)\s*)");
    QRegularExpressionMatchIterator matchIterator = rule.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString name = match.captured(1);
        QString type = match.captured(2);
        if (!words_.contains(type))
        {
            setFormat(match.capturedStart(), match.capturedLength(), redLineFormat);
        }
    }
}

void Highlighter::searchText(const QString &text)
{
    searchPattern = QRegularExpression(text);
    rehighlight();
}

void Highlighter::wordsFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "NOt file open!!!!";
        return;
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    //QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words_ << QString::fromUtf8(line.trimmed());
    }

    words_.sort();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    HighlightingRule rule;

    for (const QString & pattern : words_) {
        rule.pattern = QRegularExpression((QString("\\b") + pattern + QString("\\b")));
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}

void Highlighter::setNewWords(const QStringList &list)
{
    for (const auto word : list)
    {
        if (!words_.contains(word))
        {
            qDebug() << word;
            words_.append(word);
        }
    }

    words_.sort();
/*
    HighlightingRule rule;

    for (const QString & pattern : words_) {
        rule.pattern = QRegularExpression((QString("\\b") + pattern + QString("\\b")));
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
*/
}
