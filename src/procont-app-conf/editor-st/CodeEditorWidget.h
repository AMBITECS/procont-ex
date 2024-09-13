#ifndef CODEEDITORWIDGET_H
#define CODEEDITORWIDGET_H

#include <QWidget>

class CodeEditor;

class QLineEdit;
class QHBoxLayout;

class CodeEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditorWidget(QWidget *parent = nullptr);

    QString toPlainText() const;
    void setPlainText(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *event) override;

protected slots:
    void slot_textChanged();

private:
    void onSearchText();
    void showSearchPanel();

private:
    QLineEdit * searchLine;
    QHBoxLayout * searchLayout;
    CodeEditor * codeEditor;
};

#endif // CODEEDITORWIDGET_H
