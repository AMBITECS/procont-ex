#ifndef ADDPOUDIALOG_H
#define ADDPOUDIALOG_H

#include <QDialog>

namespace Ui {
class AddPOUDialog;
}

class AddPOUDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPOUDialog(QWidget *parent = nullptr);
    ~AddPOUDialog();

private:
    Ui::AddPOUDialog *ui;
};

#endif // ADDPOUDIALOG_H
