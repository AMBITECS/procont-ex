#include "AddDUTDialog.h"

#include "iec/StandardLibrary.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QMessageBox>

AddDUTDialog::AddDUTDialog()
{
    setWindowTitle(tr("Add DUT"));
    setMinimumSize(350, 450);

    auto layout = new QVBoxLayout;

    // top label
    auto TopLabelLayout = new QHBoxLayout;
    auto TopLabelPixmapLabel = new QLabel;
    TopLabelPixmapLabel->setFixedSize(32, 32);
    TopLabelPixmapLabel->setPixmap(QPixmap(":/icon/images/add.png").scaled(TopLabelPixmapLabel->width(), TopLabelPixmapLabel->height(), Qt::KeepAspectRatio));
    TopLabelLayout->addWidget(TopLabelPixmapLabel);
    auto TopLabelTextLabel = new QLabel(tr("Create new data user type"));
    TopLabelTextLabel->setMinimumHeight(50);
    TopLabelLayout->addWidget(TopLabelTextLabel);
    layout->addLayout(TopLabelLayout);

    // name
    auto NameLayout = new QFormLayout;
    NameLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    _m_lineEdit_name = new QLineEdit; _m_lineEdit_name->setText("DUT");
    NameLayout->addRow(new QLabel(tr("Name")), _m_lineEdit_name);
    layout->addLayout(NameLayout);

    // type
    auto TypeGroupBox = new QGroupBox(tr("Type"));
    _m_buttonGroup_type = new QButtonGroup;
    auto TypeFunctionBlockLabelEmpty = new QLabel(tr("  ")); TypeFunctionBlockLabelEmpty->setFixedWidth(15);

    auto TypeRadio1 = new QRadioButton(tr("Structure"));
    auto radioFont = TypeRadio1->font(); radioFont.setBold(true);
    TypeRadio1->setFont(radioFont);
    connect(TypeRadio1, &QRadioButton::toggled, this, &AddDUTDialog::slot_toggleRadioButton_struct);
    _m_buttonGroup_type->addButton(TypeRadio1, eDUTType::eDT_Structure);
    auto TypeFunctionBlock1Layout = new QFormLayout;
    auto TypeFunctionBlock1Row1Layout = new QHBoxLayout;
    TypeFunctionBlock1Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkBox_struct = new QCheckBox(tr("Extends")); _m_checkBox_struct->setEnabled(false);
    connect(_m_checkBox_struct, &QCheckBox::toggled, this, &AddDUTDialog::slot_toggleCheckBox_struct);
    TypeFunctionBlock1Row1Layout->addWidget(_m_checkBox_struct);
    _m_lineEdit_struct = new QLineEdit; _m_lineEdit_struct->setEnabled(false);
    _m_lineEdit_struct->setFixedWidth(150); _m_lineEdit_struct->setEnabled(false);
    TypeFunctionBlock1Row1Layout->addWidget(_m_lineEdit_struct);
    _m_pushButton_struct = new QPushButton(tr("...")); _m_pushButton_struct->setEnabled(false);
    _m_pushButton_struct->setFixedWidth(30); _m_pushButton_struct->setEnabled(false);
    TypeFunctionBlock1Row1Layout->addWidget(_m_pushButton_struct);
    TypeFunctionBlock1Layout->addRow(TypeFunctionBlock1Row1Layout);

    auto TypeRadio2 = new QRadioButton(tr("Enumeration"));
    TypeRadio2->setFont(radioFont);
    connect(TypeRadio2, &QRadioButton::toggled, this, &AddDUTDialog::slot_toggleRadioButton_enum);
    _m_buttonGroup_type->addButton(TypeRadio2, eDUTType::eDT_Enumeration);
    auto TypeFunctionBlock2Layout = new QFormLayout;
    auto TypeFunctionBlock2Row1Layout = new QHBoxLayout;
    TypeFunctionBlock2Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkBox_enum = new QCheckBox(tr("Text list support")); _m_checkBox_enum->setEnabled(false);
    TypeFunctionBlock2Row1Layout->addWidget(_m_checkBox_enum);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row1Layout);

    auto TypeRadio3 = new QRadioButton(tr("Alias"));
    TypeRadio3->setEnabled(false);
    TypeRadio3->setFont(radioFont);
    connect(TypeRadio3, &QRadioButton::toggled, this, &AddDUTDialog::slot_toggleRadioButton_alias);
    _m_buttonGroup_type->addButton(TypeRadio3, eDUTType::eDT_Alias);
    auto TypeFunctionBlock3Layout = new QFormLayout;
    auto TypeFunctionBlock3Row1Layout = new QHBoxLayout;
    TypeFunctionBlock3Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_alias = new QLabel(tr("Base Type")); _m_label_alias->setEnabled(false);
    TypeFunctionBlock3Row1Layout->addWidget(_m_label_alias);
    _m_lineEdit_alias = new QLineEdit; _m_lineEdit_alias->setEnabled(false);
    _m_lineEdit_alias->setFixedWidth(150); _m_lineEdit_alias->setEnabled(false);
    TypeFunctionBlock3Row1Layout->addWidget(_m_lineEdit_alias);
    _m_pushButton_alias = new QPushButton(tr(" > ")); _m_pushButton_alias->setEnabled(false);
    _m_pushButton_alias->setFixedWidth(30); _m_pushButton_alias->setEnabled(false);
    TypeFunctionBlock3Row1Layout->addWidget(_m_pushButton_alias);
    TypeFunctionBlock3Layout->addRow(TypeFunctionBlock3Row1Layout);

    auto TypeRadio4 = new QRadioButton(tr("Union"));
    TypeRadio4->setEnabled(false);
    TypeRadio4->setFont(radioFont);
    connect(TypeRadio4, &QRadioButton::toggled, this, &AddDUTDialog::slot_toggleRadioButton_union);
    _m_buttonGroup_type->addButton(TypeRadio4, eDUTType::eDT_Union);

    auto TypeLayout = new QVBoxLayout;
    TypeLayout->addWidget(TypeRadio1);
    TypeLayout->addLayout(TypeFunctionBlock1Layout);
    TypeLayout->addWidget(TypeRadio2);
    TypeLayout->addLayout(TypeFunctionBlock2Layout);
    TypeLayout->addWidget(TypeRadio3);
    TypeLayout->addLayout(TypeFunctionBlock3Layout);
    TypeLayout->addWidget(TypeRadio4);    
    TypeGroupBox->setLayout(TypeLayout);
    layout->addWidget(TypeGroupBox);
    layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));

    TypeRadio1->setChecked(true);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);

    setLayout(layout);
}

void AddDUTDialog::slot_toggleRadioButton_struct(bool state_)
{
    // _m_checkBox_struct->setEnabled(true);
    // _m_lineEdit_struct->setEnabled(_m_checkBox_struct->checkState());
    // _m_pushButton_struct->setEnabled(_m_checkBox_struct->checkState());

    _m_checkBox_enum->setEnabled(false);

    _m_label_alias->setEnabled(false);
    _m_lineEdit_alias->setEnabled(false);
    _m_pushButton_alias->setEnabled(false);
}

void AddDUTDialog::slot_toggleRadioButton_enum(bool state_)
{
    _m_checkBox_struct->setEnabled(false);
    _m_lineEdit_struct->setEnabled(false);
    _m_pushButton_struct->setEnabled(false);

    // _m_checkBox_enum->setEnabled(true);

    _m_label_alias->setEnabled(false);
    _m_lineEdit_alias->setEnabled(false);
    _m_pushButton_alias->setEnabled(false);
}

void AddDUTDialog::slot_toggleRadioButton_alias(bool state_)
{
    _m_checkBox_struct->setEnabled(false);
    _m_lineEdit_struct->setEnabled(false);
    _m_pushButton_struct->setEnabled(false);

    _m_checkBox_enum->setEnabled(false);

    // _m_label_alias->setEnabled(true);
    // _m_lineEdit_alias->setEnabled(true);
    // _m_pushButton_alias->setEnabled(true);
}

void AddDUTDialog::slot_toggleRadioButton_union(bool state_)
{
    _m_checkBox_struct->setEnabled(false);
    _m_lineEdit_struct->setEnabled(false);
    _m_pushButton_struct->setEnabled(false);

    _m_checkBox_enum->setEnabled(false);

    _m_label_alias->setEnabled(false);
    _m_lineEdit_alias->setEnabled(false);
    _m_pushButton_alias->setEnabled(false);
}

void AddDUTDialog::slot_toggleCheckBox_struct(bool state_)
{
    _m_lineEdit_struct->setEnabled(state_);
    _m_pushButton_struct->setEnabled(state_);
}

void AddDUTDialog::accept()
{
    auto name_ = _m_lineEdit_name->text();
    if(name_.isEmpty())
    {
        QMessageBox::warning
            (
                this,
                tr("Warning"),
                tr("Please enter DUT name").arg(name_)
                );

        return;
    }

    if(!StandardLibrary::instance()->find_type(name_).isNull())
    {
        QMessageBox::warning
            (
                this,
                tr("Warning"),
                tr("The name '%1' is already in use, please enter a different name").arg(name_)
                );

        return;
    }

    QDialog::accept();
}

QDomNode AddDUTDialog::getNode() const
{
    QDomDocument _doc;
    auto _dataType = _doc.createElement("dataType"); _doc.appendChild(_dataType);
    _dataType.setAttribute("name", _m_lineEdit_name->text());
    auto _baseType = _doc.createElement("baseType"); _dataType.appendChild(_baseType);
    _baseType.appendChild(_doc.createElement(pouType2Str(radioId2enumType(_m_buttonGroup_type->checkedId()))));

    return _doc;
}

AddDUTDialog::eDUTType AddDUTDialog::radioId2enumType(int id_)
{
    switch(id_)
    {
    case 1:
        return eDUTType::eDT_Structure;
        break;
    case 2:
        return eDUTType::eDT_Enumeration;
        break;
    case 3:
        return eDUTType::eDT_Alias;
        break;
    case 4:
        return eDUTType::eDT_Union;
        break;
    }

    return eDUTType::eDT_Unknown;
}

QString AddDUTDialog::pouType2Str(eDUTType type_)
{
    switch(type_)
    {
    case eDUTType::eDT_Structure:
        return "struct";
        break;
    case eDUTType::eDT_Enumeration:
        return "enum";
        break;
    case eDUTType::eDT_Alias:
        return "";
        break;
    case eDUTType::eDT_Union:
        return "";
        break;
    }

    return {};
}

