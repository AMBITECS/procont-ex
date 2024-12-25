#pragma once

#include <QPlainTextEdit>

class Highlighter;

class QCompleter;
class QAbstractItemModel;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void setPousListName(QStringList list);

    QCompleter * completer();
    Highlighter * highliter() const { return syntaxHighlighter; }


protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

protected:
    QAbstractItemModel * modelFromFile(const QString& fileName);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;

private:
    QWidget *lineNumberArea;
    int currentPositionBlock;
    QStringList words_;

    Highlighter * syntaxHighlighter;

    QCompleter * _completer = nullptr;
};
