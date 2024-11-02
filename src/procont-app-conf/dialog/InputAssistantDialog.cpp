#include "InputAssistantDialog.h"
#include "ui_InputAssistantDialog.h"

#include <QTableWidget>
#include <QLabel>

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
