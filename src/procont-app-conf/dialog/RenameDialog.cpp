#include "RenameDialog.h"

#include "iec/StandardLibrary.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>

RenameDialog::RenameDialog(const QString &_current_name)
{
    setWindowTitle(tr("Rename"));
    setMinimumSize(350, 200);

    auto layout = new QVBoxLayout;

    // current name
    auto CurrentNameLayout = new QFormLayout;
    CurrentNameLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    _m_lineEdit_current_name = new QLineEdit; _m_lineEdit_current_name->setText(_current_name);
    _m_lineEdit_current_name->setReadOnly(true);
    CurrentNameLayout->addRow(new QLabel(tr("Current name")), _m_lineEdit_current_name);
    layout->addLayout(CurrentNameLayout);

    // new name
    auto NewNameLayout = new QFormLayout;
    NewNameLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    _m_lineEdit_new_name = new QLineEdit; _m_lineEdit_new_name->setText(_current_name);
    NewNameLayout->addRow(new QLabel(tr("New name")), _m_lineEdit_new_name);
    layout->addLayout(NewNameLayout);

    // standard buttons
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("OK"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

QString RenameDialog::new_name() const
{
    return _m_lineEdit_new_name->text();
}

void RenameDialog::accept()
{
    if(_m_lineEdit_current_name->text() == _m_lineEdit_new_name->text())
    {
        QMessageBox::warning
            (
                this,
                tr("Warning"),
                QString(tr("The current name and the new name are the same\nEnter a new name"))
            );

        return;
    }

    if(!StandardLibrary::instance()->find_pou(_m_lineEdit_new_name->text()).isNull())
    {
        QMessageBox::warning
            (
                this,
                tr("Warning"),
                tr("The name '%1' is already in use, please enter a different name").arg(_m_lineEdit_new_name->text())
                );

        return;
    }

    QDialog::accept();
}
