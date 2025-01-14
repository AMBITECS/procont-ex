#include "CodeEditor.h"

#include "LineNumberArea.h"
#include "Highlighter.h"

#include <QPainter>
#include <QTextBlock>

#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QFocusEvent>
#include <QFile>
#include <QStringListModel>

// *** igor'
#include <QUndoStack>
#include <QUndoGroup>
#include <QMenu>
#include <QApplication>

#include "main/MainWindow.h"
// ***

//QCompleter * CodeEditor::_completer = nullptr;

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent),
// igor'
    _m_undo_stack(new QUndoStack(this))
{
    completer()->setWidget(this);
    QObject::connect(_completer, QOverload<const QString &>::of(&QCompleter::activated),
                     this, &CodeEditor::insertCompletion);

    syntaxHighlighter = new Highlighter(document());
    syntaxHighlighter->wordsFromFile(":/resources/wordlist.txt");

    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    setTabStopDistance(40);

    this->installEventFilter(this);

// *** igor'
    MainWindow::addStack(undoStack());

    connect(document(), &QTextDocument::undoCommandAdded, this, &CodeEditor::slot_undo_cmd_added);
    connect(this, &QPlainTextEdit::undoAvailable, this, &CodeEditor::slot_undo_available);
    connect(this, &QPlainTextEdit::redoAvailable, this, &CodeEditor::slot_redo_available);
    connect(this, &QPlainTextEdit::copyAvailable, this, &CodeEditor::slot_copy_available);
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(slot_focusChanged(QWidget *, QWidget *)));
// ***
}

// *** igor'
CodeEditor::~CodeEditor()
{
    delete _m_undo_stack;
}

void CodeEditor::setText(const QString &_text)
{
    undoStack()->clear();
    setPlainText(_text);
}

QUndoStack * CodeEditor::undoStack() const
{
    return _m_undo_stack;
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    setFocus();

    QPlainTextEdit::mousePressEvent(event);
}

void CodeEditor::slot_focusChanged(QWidget *, QWidget *new_)
{
    if(new_ == this)
        undoStack()->setActive();
    else
        clearFocus();
}

void CodeEditor::slot_undo_cmd_added()
{
    undoStack()->push(new CUndoCommand_edit(this));
}

void CodeEditor::slot_undo_available(bool _available)
{
    qDebug() << __PRETTY_FUNCTION__ << _available;
}

void CodeEditor::slot_redo_available(bool _available)
{
    qDebug() << __PRETTY_FUNCTION__ << _available;
}

void CodeEditor::slot_copy_available(bool _available)
{
    _m_text_selected = _available;
}
void CodeEditor::contextMenuEvent(QContextMenuEvent *event_)
{
    auto _menu = new QMenu(this);

    auto _action = undoStack()->createUndoAction(this);
    _action->setText(tr("Undo"));
    _action->setShortcuts(QKeySequence::Undo);
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _action = undoStack()->createRedoAction(this);
    _action->setText(tr("Redo"));
    _action->setShortcuts(QKeySequence::Redo);
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _menu->addSeparator();

    _action = _menu->addAction(tr("Cut"));
    _action->setShortcuts(QKeySequence::Cut);
    connect(_action, &QAction::triggered, this, &QPlainTextEdit::cut);
    _action->setEnabled(_m_text_selected);
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _action = _menu->addAction(tr("Copy"));
    _action->setShortcuts(QKeySequence::Copy);
    connect(_action, &QAction::triggered, this, &QPlainTextEdit::copy);
    _action->setEnabled(_m_text_selected);
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _action = _menu->addAction(tr("Paste"));
    _action->setShortcuts(QKeySequence::Paste);
    connect(_action, &QAction::triggered, this, &QPlainTextEdit::paste);
    _action->setEnabled(canPaste());
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _action = _menu->addAction(tr("Delete"));
    connect(_action, &QAction::triggered, this, &QPlainTextEdit::cut);
    _action->setEnabled(_m_text_selected);
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _menu->addSeparator();

    _action = _menu->addAction(tr("Select All"));
    _action->setShortcuts(QKeySequence::SelectAll);
    connect(_action, &QAction::triggered, this, &QPlainTextEdit::selectAll);
    _action->setEnabled(toPlainText().length());
    if(isReadOnly()) _action->setEnabled(false);
    _menu->addAction(_action);

    _menu->exec(event_->globalPos());
    delete _menu;
}
// ***

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::setPousListName(QStringList list)
{
    syntaxHighlighter->setNewWords(list);
    for (const auto word : list)
    {
        if (!words_.contains(word))
        {
            qDebug() << word;
            words_.append(word);
        }
    }

    words_.sort();
    _completer->setModel(new QStringListModel(words_, completer()));
    _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
    _completer->setWrapAround(false);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
}

// void CodeEditor::initCompleter(/*QCompleter *completer*/)
// {
//     //if (_completer)
//     //    _completer->disconnect(this);

//     // _completer = completer;

//     // if (!_completer)
//     //     return;

//     // _completer->setWidget(this);
//     // _completer->setCompletionMode(QCompleter::PopupCompletion);
//     // _completer->setCaseSensitivity(Qt::CaseInsensitive);
//     // QObject::connect(_completer, QOverload<const QString &>::of(&QCompleter::activated),
//     //                  this, &CodeEditor::insertCompletion);

//     _completer = new QCompleter;
//     _completer->setModel(modelFromFile(":/resources/wordlist.txt"));
//     _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
//     _completer->setCaseSensitivity(Qt::CaseInsensitive);
//     _completer->setWrapAround(false);
//     // setCompleter(_completer);
//     _completer->setWidget(this);
//     _completer->setCompletionMode(QCompleter::PopupCompletion);
//     _completer->setCaseSensitivity(Qt::CaseInsensitive);
//     QObject::connect(_completer, QOverload<const QString &>::of(&QCompleter::activated),
//                      this, &CodeEditor::insertCompletion);
// }

QCompleter * CodeEditor::completer()
{
    if(!_completer)
    {
        _completer = new QCompleter;
        _completer->setModel(modelFromFile(":/resources/wordlist.txt"));
        _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
        _completer->setCaseSensitivity(Qt::CaseInsensitive);
        _completer->setWrapAround(false);
        _completer->setCompletionMode(QCompleter::PopupCompletion);
        _completer->setCaseSensitivity(Qt::CaseInsensitive);
    }

    return _completer;
}

QAbstractItemModel *CodeEditor::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "NOt file open!!!!";
        return new QStringListModel(completer());
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
    return new QStringListModel(words_, completer());
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::insertCompletion(const QString &completion)
{
    if (_completer->widget() != this)
        return;
    // QString _completion = "kick";
    QTextCursor tc = textCursor();
    // int extra = completion.length() - _completer->completionPrefix().length();
    //tc.movePosition(QTextCursor::StartOfWord);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.select(QTextCursor::WordUnderCursor);
    tc.removeSelectedText();
    tc.insertText(completion);
    setTextCursor(tc);
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

bool CodeEditor::eventFilter(QObject *obj, QEvent *event)
{

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
/*
        if (_completer && _completer->popup()->isVisible()) {
            // The following keys are forwarded by the completer to the widget
            switch (keyEvent->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                event->ignore();
                return false; // let the completer do default behavior
            default:
                break;
            }
        }

        const bool isShortcut = (keyEvent->modifiers().testFlag(Qt::ControlModifier) && keyEvent->key() == Qt::Key_E); // CTRL+E
        if (!_completer || !isShortcut) // do not process the shortcut when we have a completer
            QPlainTextEdit::keyPressEvent(keyEvent);
        //! [7]

        //! [8]
        const bool ctrlOrShift = keyEvent->modifiers().testFlag(Qt::ControlModifier) ||
                                 keyEvent->modifiers().testFlag(Qt::ShiftModifier);
        if (!_completer || (ctrlOrShift && keyEvent->text().isEmpty()))
            return true;

        static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
        const bool hasModifier = (keyEvent->modifiers() != Qt::NoModifier) && !ctrlOrShift;
        QString completionPrefix = textUnderCursor();

        if (!isShortcut && (hasModifier || keyEvent->text().isEmpty()|| completionPrefix.length() < 3
                            || eow.contains(keyEvent->text().right(1)))) {
            _completer->popup()->hide();
            return true;
        }

        if (completionPrefix != _completer->completionPrefix()) {
            _completer->setCompletionPrefix(completionPrefix);
            _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
        }
        QRect cr = cursorRect();
        cr.setWidth(_completer->popup()->sizeHintForColumn(0)
                    + _completer->popup()->verticalScrollBar()->sizeHint().width());
        _completer->complete(cr); // popup it up!
*/
        /*
        if (keyEvent->key() == Qt::Key_Backtab)
        {
            QChar tab_char = '\t';
            auto cur = this->textCursor();
            cur.clearSelection();

            cur.movePosition(QTextCursor::StartOfLine);
            cur.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
            auto sel_text = cur.selectedText();

            if (sel_text.startsWith(tab_char))
            {
                qDebug() << "BackTAb";
                auto text = sel_text.remove(tab_char, Qt::CaseInsensitive);
                //auto text = sel_text.replace(tab_char, ' ', Qt::CaseSensitivity::CaseSensitive);
                cur.insertText(text);
                qDebug("Ate key press %d", keyEvent->key());
                return true;
            }

        if (sel_text.startsWith(' '))
        {
            qDebug() << "BackTAb";
            auto text = sel_text.removeFirst();
            //auto text = sel_text.replace(tab_char, ' ', Qt::CaseSensitivity::CaseSensitive);
            cur.insertText(text);
        }

            //event->accept();
        }
*/


        return false;

    } else {
        // standard event processing
        return false;
    }
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (_completer && _completer->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
        switch (event->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            event->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }

    const bool isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) && event->key() == Qt::Key_E); // CTRL+E
    if (!_completer || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(event);
    //! [7]

    //! [8]
    const bool ctrlOrShift = event->modifiers().testFlag(Qt::ControlModifier) ||
                             event->modifiers().testFlag(Qt::ShiftModifier);
    //if (!_completer || (ctrlOrShift && event->text().isEmpty()))
    //    return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    const bool hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || event->text().isEmpty()|| completionPrefix.length() < 1
                        || eow.contains(event->text().right(1)))) {
        _completer->popup()->hide();
        return;
    }

    if (completionPrefix != _completer->completionPrefix()) {
        _completer->setCompletionPrefix(completionPrefix);
        _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(_completer->popup()->sizeHintForColumn(0)
                + _completer->popup()->verticalScrollBar()->sizeHint().width());
    _completer->complete(cr); // popup it up!
}

void CodeEditor::focusInEvent(QFocusEvent *event)
{
    if (_completer)
        _completer->setWidget(this);

    QPlainTextEdit::focusInEvent(event);
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(180);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
