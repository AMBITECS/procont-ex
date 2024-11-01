#ifndef INPUTASSISTANTDIALOG_H
#define INPUTASSISTANTDIALOG_H

#include <QDialog>

namespace Ui {
class InputAssistantDialog;
}

class InputAssistantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputAssistantDialog(QWidget *parent = nullptr);
    ~InputAssistantDialog();

private:
    Ui::InputAssistantDialog *ui;
};

#endif // INPUTASSISTANTDIALOG_H
