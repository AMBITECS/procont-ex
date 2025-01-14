#include "CodeEditorWidget.h"

#include "CodeEditor.h"
#include "Highlighter.h"

#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

CodeEditorWidget::CodeEditorWidget(bool read_only_, QWidget *parent)
    : QWidget{parent}
{
    searchLine = new QLineEdit();
    searchLine->hide();
    auto searchButton = new QPushButton(QString(tr("Find")));
    QObject::connect(searchButton, &QPushButton::clicked, this, &CodeEditorWidget::onSearchText);
    searchButton->hide();

    searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLine);
    searchLayout->addWidget(searchButton);

    codeEditor = new CodeEditor;
    codeEditor->setReadOnly(read_only_);
    connect(codeEditor, &CodeEditor::textChanged, this, &CodeEditorWidget::slot_textChanged);

    auto layout = new QVBoxLayout;
    layout->addWidget(codeEditor);
    layout->addLayout(searchLayout);

    setLayout(layout);
}

// *** igor'
QUndoStack * CodeEditorWidget::undoStack()
{
    return codeEditor->undoStack();
}
// ***

void CodeEditorWidget::slot_textChanged()
{
    emit textChanged();
}

QString CodeEditorWidget::toPlainText() const
{
    return codeEditor->toPlainText();
}

void CodeEditorWidget::setPlainText(const QString &text)
{
    codeEditor->setText(text);
}

void CodeEditorWidget::setPousListName(QStringList list)
{
    codeEditor->setPousListName(list);
}

void CodeEditorWidget::onSearchText()
{
    codeEditor->highliter()->searchText(searchLine->text());
}

void CodeEditorWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_F)
        {
            showSearchPanel();
            event->accept();
        }
    }
}

void CodeEditorWidget::showSearchPanel()
{
    for(int i = 0; i < searchLayout->count(); ++i)
    {
        if (searchLayout->itemAt(i)->widget()->isVisible())
        {
            searchLayout->itemAt(i)->widget()->hide();
        } else {
            searchLayout->itemAt(i)->widget()->show();
        }
    }
}
