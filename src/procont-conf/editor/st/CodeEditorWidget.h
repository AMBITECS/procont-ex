#ifndef CODEEDITORWIDGET_H
#define CODEEDITORWIDGET_H

#include <QWidget>

// igor'
QT_FORWARD_DECLARE_CLASS(QUndoStack)

class CodeEditor;

class QLineEdit;
class QHBoxLayout;

class CodeEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditorWidget(bool read_only_ = false, QWidget *parent = nullptr);

    QString toPlainText() const;
    void setPlainText(const QString &text);
    void setPousListName(QStringList list);
    // igor'
    QUndoStack * undoStack();

Q_SIGNALS:
    void textChanged();

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
