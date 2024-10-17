#include "AddPOUDialog.h"
#include "ui_AddPOUDialog.h"

AddPOUDialog::AddPOUDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPOUDialog)
{
    ui->setupUi(this);
}

AddPOUDialog::~AddPOUDialog()
{
    delete ui;
}
