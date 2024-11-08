#include "AddDUTDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

AddDUTDialog::AddDUTDialog()
{
    setWindowTitle(tr("Add DUT"));
    setMinimumSize(350, 550);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto layout = new QVBoxLayout;
    layout->addWidget(new QLabel(tr("Add DUT")));
    layout->addWidget(buttonBox);

    setLayout(layout);
}
