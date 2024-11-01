#include "InputAssistantDialog.h"
#include "ui_InputAssistantDialog.h"

InputAssistantDialog::InputAssistantDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputAssistantDialog)
{
    ui->setupUi(this);
}

InputAssistantDialog::~InputAssistantDialog()
{
    delete ui;
}
