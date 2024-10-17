#include "AddTypeDialog.h"
#include "ui_AddTypeDialog.h"

AddTypeDialog::AddTypeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTypeDialog)
{
    ui->setupUi(this);
}

AddTypeDialog::~AddTypeDialog()
{
    delete ui;
}
