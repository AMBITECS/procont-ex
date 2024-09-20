#include "CodeEditorWidget.h"

#include "CodeEditor.h"
#include "Highlighter.h"

#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

CodeEditorWidget::CodeEditorWidget(QWidget *parent)
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
    connect(codeEditor, &CodeEditor::textChanged, this, &CodeEditorWidget::slot_textChanged);

    auto layout = new QVBoxLayout;
    layout->addWidget(codeEditor);
    layout->addLayout(searchLayout);

    setLayout(layout);
}

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
    codeEditor->setPlainText(text);
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
