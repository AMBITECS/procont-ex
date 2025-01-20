#pragma once

#include <QPlainTextEdit>

// igor'
#include <QUndoCommand>

// igor'
QT_FORWARD_DECLARE_CLASS(QUndoStack)
QT_FORWARD_DECLARE_CLASS(Highlighter)
QT_FORWARD_DECLARE_CLASS(QCompleter)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
// *** igor'
private:
    class CUndoCommand_edit : public QUndoCommand
    {
    public:
        CUndoCommand_edit(QPlainTextEdit *_editor, QUndoCommand *_cmd = nullptr) : QUndoCommand(_cmd),
            _m_editor(_editor)
        {
            setText(QObject::tr("Text changed"));
        }

        void undo() override
        {
            _m_editor->undo();
        }

        void redo() override
        {
            _m_editor->redo();
        }

    private:
        QPlainTextEdit * _m_editor{nullptr};
    };
// ***
public:
    CodeEditor(QWidget *parent = nullptr);
// igor'
    virtual ~CodeEditor() override;

    [[nodiscard]] QUndoStack * undoStack() const;
// ***

    void setText(const QString &);

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
    // igor'
    void contextMenuEvent(QContextMenuEvent *_event) override;

protected:
    // igor'
    QAbstractItemModel * modelFromFile(const QString& fileName);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;

// *** igor'
private:
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void slot_focusChanged(QWidget *old_, QWidget *new_);
    void slot_undo_cmd_added();
    void slot_copy_available(bool _available);

private:
    bool _m_text_selected{false};
    QUndoStack * _m_undo_stack{nullptr};
// ***

private:
    QWidget *lineNumberArea;
    int currentPositionBlock;
    QStringList words_;
    Highlighter * syntaxHighlighter;
    QCompleter * _completer = nullptr;
};
