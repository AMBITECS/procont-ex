#include "AddPOUDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>

AddPOUDialog::AddPOUDialog()
{
    setWindowTitle(tr("Add POU"));
    setMinimumSize(350, 550);

    auto layout = new QVBoxLayout;

    // top label
    auto TopLabelLayout = new QHBoxLayout;
    auto TopLabelPixmapLabel = new QLabel;
    TopLabelPixmapLabel->setFixedSize(32, 32);
    TopLabelPixmapLabel->setPixmap(QPixmap(":/icon/images/add.png").scaled(TopLabelPixmapLabel->width(), TopLabelPixmapLabel->height(), Qt::KeepAspectRatio));
    TopLabelLayout->addWidget(TopLabelPixmapLabel);
    TopLabelLayout->addWidget(new QLabel(tr("Create new POU (program organization unit)")));
    layout->addLayout(TopLabelLayout);

    // name
    auto NameLayout = new QFormLayout;
    NameLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    NameLayout->addRow(new QLabel(tr("Name")), new QLineEdit);
    layout->addLayout(NameLayout);

    // type
    auto TypeGroupBox = new QGroupBox(tr("Type"));
    auto TypeRadio1 = new QRadioButton(tr("Program"));
    connect(TypeRadio1, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_program);
    auto TypeRadio2 = new QRadioButton(tr("Function Block"));
    connect(TypeRadio2, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_functionblock);
    auto TypeFunctionBlockLabelEmpty = new QLabel(tr("  ")); TypeFunctionBlockLabelEmpty->setFixedWidth(15);
    auto TypeFunctionBlock2Layout = new QFormLayout;
    TypeFunctionBlock2Layout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    auto TypeFunctionBlock2Row1Layout = new QHBoxLayout;
    TypeFunctionBlock2Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_extends = new QCheckBox(tr("Extends"));
    connect(_m_checkbox_extends, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_extends);
    TypeFunctionBlock2Row1Layout->addWidget(_m_checkbox_extends);
    _m_lineEdit_extends = new QLineEdit;
    _m_lineEdit_extends->setFixedWidth(150); _m_lineEdit_extends->setEnabled(false);
    TypeFunctionBlock2Row1Layout->addWidget(_m_lineEdit_extends);
    _m_pushButton_extends = new QPushButton(tr("..."));
    _m_pushButton_extends->setFixedWidth(30); _m_pushButton_extends->setEnabled(false);
    TypeFunctionBlock2Row1Layout->addWidget(_m_pushButton_extends);

    auto TypeFunctionBlock2Row2Layout = new QHBoxLayout;
    TypeFunctionBlock2Row2Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_implements = new QCheckBox(tr("Implements"));
    connect(_m_checkbox_implements, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_implements);
    TypeFunctionBlock2Row2Layout->addWidget(_m_checkbox_implements);
    _m_lineEdit_implements = new QLineEdit;
    _m_lineEdit_implements->setFixedWidth(150); _m_lineEdit_implements->setEnabled(false);
    TypeFunctionBlock2Row2Layout->addWidget(_m_lineEdit_implements);
    _m_pushButton_implements = new QPushButton(tr("..."));
    _m_pushButton_implements->setFixedWidth(30); _m_pushButton_implements->setEnabled(false);
    TypeFunctionBlock2Row2Layout->addWidget(_m_pushButton_implements);

    auto TypeFunctionBlock2Row3Layout = new QHBoxLayout;
    TypeFunctionBlock2Row3Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_final = new QCheckBox(tr("Final"));
    connect(_m_checkbox_final, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_final);
    TypeFunctionBlock2Row3Layout->addWidget(_m_checkbox_final);
    _m_checkbox_abstract = new QCheckBox(tr("Abstract"));
    connect(_m_checkbox_abstract, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_abstract);
    TypeFunctionBlock2Row3Layout->addWidget(_m_checkbox_abstract);

    auto TypeFunctionBlock2Row4Layout = new QHBoxLayout;
    TypeFunctionBlock2Row4Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_access_specifier = new QLabel(tr("Access specifier"));
    TypeFunctionBlock2Row4Layout->addWidget(_m_label_access_specifier);
    auto TypeFunctionBlock2Row5Layout = new QHBoxLayout;
    TypeFunctionBlock2Row5Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_combobox_access_specifier = new QComboBox;
    _m_combobox_access_specifier->addItem(tr(""));
    _m_combobox_access_specifier->addItem(tr("INTERNAL"));
    _m_combobox_access_specifier->addItem(tr("PUBLIC"));
    TypeFunctionBlock2Row5Layout->addWidget(_m_combobox_access_specifier);

    auto TypeFunctionBlock2Row6Layout = new QHBoxLayout;
    TypeFunctionBlock2Row6Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_method_implementation = new QLabel(tr("Method implementation language"));
    TypeFunctionBlock2Row6Layout->addWidget(_m_label_method_implementation);
    auto TypeFunctionBlock2Row7Layout = new QHBoxLayout;
    TypeFunctionBlock2Row7Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_combobox_method_implementation = new QComboBox;
    auto LanguageItems = QStringList()
                              << tr("Function Block Diagram (FBD)")
                              << tr("Sequential Function Chart (SFC)")
                              << tr("Ladder Diagram (LD)")
                              << tr("Structured Text(ST)");
    _m_combobox_method_implementation->addItems(LanguageItems);
    TypeFunctionBlock2Row7Layout->addWidget(_m_combobox_method_implementation);

    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row1Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row2Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row3Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row4Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row5Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row6Layout);
    TypeFunctionBlock2Layout->addRow(TypeFunctionBlock2Row7Layout);

    auto TypeRadio3 = new QRadioButton(tr("Function"));
    connect(TypeRadio3, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_function);
    auto TypeFunctionBlock3Layout = new QFormLayout;
    auto TypeFunctionBlock3Row1Layout = new QHBoxLayout;
    TypeFunctionBlock3Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_return_type = new QLabel(tr("Return type"));
    TypeFunctionBlock3Row1Layout->addWidget(_m_label_return_type);
    _m_lineEdit_return_type = new QLineEdit;
    _m_lineEdit_return_type->setFixedWidth(150); _m_lineEdit_return_type->setText("INT");
    TypeFunctionBlock3Row1Layout->addWidget(_m_lineEdit_return_type);
    _m_pushButton_return_type = new QPushButton(tr("..."));
    _m_pushButton_return_type->setFixedWidth(30);
    TypeFunctionBlock3Row1Layout->addWidget(_m_pushButton_return_type);
    TypeFunctionBlock3Layout->addRow(TypeFunctionBlock3Row1Layout);

    auto TypeLayout = new QVBoxLayout;
    TypeLayout->addWidget(TypeRadio1);
    TypeLayout->addWidget(TypeRadio2);
    TypeLayout->addLayout(TypeFunctionBlock2Layout);
    TypeLayout->addWidget(TypeRadio3);
    TypeLayout->addLayout(TypeFunctionBlock3Layout);
    TypeGroupBox->setLayout(TypeLayout);
    layout->addWidget(TypeGroupBox);

    // language
    auto LanguageLayout = new QFormLayout;
    LanguageLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    auto LanguageCombo = new QComboBox;
    LanguageCombo->addItems(LanguageItems);
    LanguageLayout->addRow(new QLabel(tr("Implementation language")), LanguageCombo);
    layout->addLayout(LanguageLayout);

    TypeRadio2->setChecked(true);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);

    setLayout(layout);
}

void AddPOUDialog::slot_toggleCheckBox_extends(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_ << _m_lineEdit_extends;

    _m_lineEdit_extends->setEnabled(state_);
    _m_pushButton_extends->setEnabled(state_);
}

void AddPOUDialog::slot_toggleCheckBox_implements(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_ << _m_lineEdit_implements;

    _m_lineEdit_implements->setEnabled(state_);
    _m_pushButton_implements->setEnabled(state_);

    _m_label_method_implementation->setEnabled(state_);
    _m_combobox_method_implementation->setEnabled(state_);
}

void AddPOUDialog::slot_toggleRadioButton_program(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_;

    _m_checkbox_extends->setEnabled(false);
    _m_lineEdit_extends->setEnabled(false);
    _m_pushButton_extends->setEnabled(false);

    _m_checkbox_implements->setEnabled(false);
    _m_lineEdit_implements->setEnabled(false);
    _m_pushButton_implements->setEnabled(false);

    _m_checkbox_final->setEnabled(false);
    _m_checkbox_abstract->setEnabled(false);

    _m_label_access_specifier->setEnabled(false);
    _m_combobox_access_specifier->setEnabled(false);

    _m_label_method_implementation->setEnabled(false);
    _m_combobox_method_implementation->setEnabled(false);

    _m_label_return_type->setEnabled(false);
    _m_lineEdit_return_type->setEnabled(false);
    _m_pushButton_return_type->setEnabled(false);
}

void AddPOUDialog::slot_toggleRadioButton_functionblock(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_;

    _m_checkbox_extends->setEnabled(true);
    _m_lineEdit_extends->setEnabled(_m_checkbox_extends->checkState());
    _m_pushButton_extends->setEnabled(_m_checkbox_extends->checkState());

    _m_checkbox_implements->setEnabled(true);
    _m_lineEdit_implements->setEnabled(_m_checkbox_implements->checkState());
    _m_pushButton_implements->setEnabled(_m_checkbox_implements->checkState());

    _m_checkbox_final->setEnabled(true);
    _m_checkbox_abstract->setEnabled(true);

    _m_label_access_specifier->setEnabled(true);
    _m_combobox_access_specifier->setEnabled(true);

    _m_label_method_implementation->setEnabled(_m_checkbox_implements->checkState());
    _m_combobox_method_implementation->setEnabled(_m_checkbox_implements->checkState());

    _m_label_return_type->setEnabled(false);
    _m_lineEdit_return_type->setEnabled(false);
    _m_pushButton_return_type->setEnabled(false);
}

void AddPOUDialog::slot_toggleRadioButton_function(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_;

    _m_checkbox_extends->setEnabled(false);
    _m_lineEdit_extends->setEnabled(false);
    _m_pushButton_extends->setEnabled(false);

    _m_checkbox_implements->setEnabled(false);
    _m_lineEdit_implements->setEnabled(false);
    _m_pushButton_implements->setEnabled(false);

    _m_checkbox_final->setEnabled(false);
    _m_checkbox_abstract->setEnabled(false);

    _m_label_access_specifier->setEnabled(false);
    _m_combobox_access_specifier->setEnabled(false);

    _m_label_method_implementation->setEnabled(false);
    _m_combobox_method_implementation->setEnabled(false);

    _m_label_return_type->setEnabled(true);
    _m_lineEdit_return_type->setEnabled(true);
    _m_pushButton_return_type->setEnabled(true);
}

void AddPOUDialog::slot_toggleCheckBox_final(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_;

    if(state_) _m_checkbox_abstract->setChecked(!state_);
}

void AddPOUDialog::slot_toggleCheckBox_abstract(bool state_)
{
    qDebug() << __PRETTY_FUNCTION__ << state_;

    if(state_) _m_checkbox_final->setChecked(!state_);
}
