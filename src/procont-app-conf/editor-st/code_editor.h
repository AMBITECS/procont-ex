#pragma once
#include <QPlainTextEdit>

class QCompleter;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    //completer logic
    void setCompleter(QCompleter *completer);
    QCompleter *completer() const;

protected:
    void resizeEvent(QResizeEvent *event) override;
    //void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

    //completer
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;

private:
    QWidget *lineNumberArea;
    int currentPositionBlock;

    QCompleter * _completer;
};
