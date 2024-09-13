#include "Highlighter.h"
#include <QFile>
#include <QCursor>
#include <QApplication>

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

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
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << QString::fromUtf8(line.trimmed());
    }

    words.sort();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    HighlightingRule rule;

    for (const QString & pattern : words) {
        rule.pattern = QRegularExpression((QString("\\b") + pattern + QString("\\b")));
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}
