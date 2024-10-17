#ifndef ADDTYPEDIALOG_H
#define ADDTYPEDIALOG_H

#include <QDialog>

namespace Ui {
class AddTypeDialog;
}

class AddTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTypeDialog(QWidget *parent = nullptr);
    ~AddTypeDialog();

private:
    Ui::AddTypeDialog *ui;
};

#endif // ADDTYPEDIALOG_H
