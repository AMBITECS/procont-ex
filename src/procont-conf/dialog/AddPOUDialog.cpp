#include "AddPOUDialog.h"

#include "iec/StandardLibrary.h"

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
#include <QMessageBox>
#include <QButtonGroup>

AddPOUDialog::AddPOUDialog()
{
    setWindowTitle(tr("Add POU"));
    setMinimumSize(350, 570);

    auto layout = new QVBoxLayout;

    // top label
    auto TopLabelLayout = new QHBoxLayout;
    auto TopLabelPixmapLabel = new QLabel;
    TopLabelPixmapLabel->setFixedSize(32, 32);
    TopLabelPixmapLabel->setPixmap(QPixmap(":/icon/images/add.png").scaled(TopLabelPixmapLabel->width(), TopLabelPixmapLabel->height(), Qt::KeepAspectRatio));
    TopLabelLayout->addWidget(TopLabelPixmapLabel);
    auto TopLabelTextLabel = new QLabel(tr("Create new POU (program organization unit)"));
    TopLabelTextLabel->setMinimumHeight(50);
    TopLabelLayout->addWidget(TopLabelTextLabel);
    layout->addLayout(TopLabelLayout);

    // name
    auto NameLayout = new QFormLayout;
    NameLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    _m_lineEdit_name = new QLineEdit; _m_lineEdit_name->setText("POU");
    NameLayout->addRow(new QLabel(tr("Name")), _m_lineEdit_name);
    layout->addLayout(NameLayout);

    // type
    auto TypeGroupBox = new QGroupBox(tr("Type"));
    _m_buttonGroup_type = new QButtonGroup;
    auto TypeRadio1 = new QRadioButton(tr("Program"));
    auto radioFont = TypeRadio1->font(); radioFont.setBold(true);
    TypeRadio1->setFont(radioFont);
    connect(TypeRadio1, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_program);
    _m_buttonGroup_type->addButton(TypeRadio1, ePOUType::ePT_Program);

    auto TypeRadio2 = new QRadioButton(tr("Function Block"));
    TypeRadio2->setFont(radioFont);
    connect(TypeRadio2, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_functionblock);
    _m_buttonGroup_type->addButton(TypeRadio2, ePOUType::ePT_FunctionBlock);
    auto TypeFunctionBlockLabelEmpty = new QLabel(tr("  ")); TypeFunctionBlockLabelEmpty->setFixedWidth(15);
    auto TypeFunctionBlock2Layout = new QFormLayout;
    TypeFunctionBlock2Layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    auto TypeFunctionBlock2Row1Layout = new QHBoxLayout;
    TypeFunctionBlock2Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_extends = new QCheckBox(tr("Extends")); _m_checkbox_extends->setEnabled(false);
    connect(_m_checkbox_extends, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_extends);
    TypeFunctionBlock2Row1Layout->addWidget(_m_checkbox_extends);
    _m_lineEdit_extends = new QLineEdit; _m_lineEdit_extends->setEnabled(false);
    _m_lineEdit_extends->setFixedWidth(150); _m_lineEdit_extends->setEnabled(false);
    TypeFunctionBlock2Row1Layout->addWidget(_m_lineEdit_extends);
    _m_pushButton_extends = new QPushButton(tr("...")); _m_pushButton_extends->setEnabled(false);
    _m_pushButton_extends->setFixedWidth(30); _m_pushButton_extends->setEnabled(false);
    TypeFunctionBlock2Row1Layout->addWidget(_m_pushButton_extends);
    auto TypeFunctionBlock2Row2Layout = new QHBoxLayout;
    TypeFunctionBlock2Row2Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_implements = new QCheckBox(tr("Implements")); _m_checkbox_implements->setEnabled(false);
    connect(_m_checkbox_implements, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_implements);
    TypeFunctionBlock2Row2Layout->addWidget(_m_checkbox_implements);
    _m_lineEdit_implements = new QLineEdit; _m_lineEdit_implements->setEnabled(false);
    _m_lineEdit_implements->setFixedWidth(150); _m_lineEdit_implements->setEnabled(false);
    TypeFunctionBlock2Row2Layout->addWidget(_m_lineEdit_implements);
    _m_pushButton_implements = new QPushButton(tr("...")); _m_pushButton_implements->setEnabled(false);
    _m_pushButton_implements->setFixedWidth(30); _m_pushButton_implements->setEnabled(false);
    TypeFunctionBlock2Row2Layout->addWidget(_m_pushButton_implements);
    auto TypeFunctionBlock2Row3Layout = new QHBoxLayout;
    TypeFunctionBlock2Row3Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_checkbox_final = new QCheckBox(tr("Final")); _m_checkbox_final->setEnabled(false);
    connect(_m_checkbox_final, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_final);
    TypeFunctionBlock2Row3Layout->addWidget(_m_checkbox_final);
    _m_checkbox_abstract = new QCheckBox(tr("Abstract")); _m_checkbox_abstract->setEnabled(false);
    connect(_m_checkbox_abstract, &QCheckBox::toggled, this, &AddPOUDialog::slot_toggleCheckBox_abstract);
    TypeFunctionBlock2Row3Layout->addWidget(_m_checkbox_abstract);
    auto TypeFunctionBlock2Row4Layout = new QHBoxLayout;
    TypeFunctionBlock2Row4Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_access_specifier = new QLabel(tr("Access specifier")); _m_label_access_specifier->setEnabled(false);
    TypeFunctionBlock2Row4Layout->addWidget(_m_label_access_specifier);
    auto TypeFunctionBlock2Row5Layout = new QHBoxLayout;
    TypeFunctionBlock2Row5Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_combobox_access_specifier = new QComboBox; _m_combobox_access_specifier->setEnabled(false);
    _m_combobox_access_specifier->addItem(tr(""));
    _m_combobox_access_specifier->addItem(tr("INTERNAL"));
    _m_combobox_access_specifier->addItem(tr("PUBLIC"));
    TypeFunctionBlock2Row5Layout->addWidget(_m_combobox_access_specifier);
    auto TypeFunctionBlock2Row6Layout = new QHBoxLayout;
    TypeFunctionBlock2Row6Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_method_implementation = new QLabel(tr("Method implementation language")); _m_label_method_implementation->setEnabled(false);
    TypeFunctionBlock2Row6Layout->addWidget(_m_label_method_implementation);
    auto TypeFunctionBlock2Row7Layout = new QHBoxLayout;
    TypeFunctionBlock2Row7Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_combobox_method_implementation = new QComboBox; _m_combobox_method_implementation->setEnabled(false);
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
    TypeRadio3->setFont(radioFont);
    connect(TypeRadio3, &QRadioButton::toggled, this, &AddPOUDialog::slot_toggleRadioButton_function);
    _m_buttonGroup_type->addButton(TypeRadio3, ePOUType::ePT_Function);
    auto TypeFunctionBlock3Layout = new QFormLayout;
    auto TypeFunctionBlock3Row1Layout = new QHBoxLayout;
    TypeFunctionBlock3Row1Layout->addWidget(TypeFunctionBlockLabelEmpty);
    _m_label_return_type = new QLabel(tr("Return type"));
    TypeFunctionBlock3Row1Layout->addWidget(_m_label_return_type);
    _m_lineEdit_return_type = new QLineEdit;
    _m_lineEdit_return_type->setFixedWidth(150); _m_lineEdit_return_type->setText("INT");
    TypeFunctionBlock3Row1Layout->addWidget(_m_lineEdit_return_type);
    _m_pushButton_return_type = new QPushButton(tr("...")); _m_pushButton_return_type->setEnabled(false);
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
    _m_comboBox_language = new QComboBox;
    _m_comboBox_language->addItems(LanguageItems);
    LanguageLayout->addRow(new QLabel(tr("Implementation language")), _m_comboBox_language);
    layout->addLayout(LanguageLayout);
    layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));

    TypeRadio2->setChecked(true);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Add"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);

    setLayout(layout);
}

void AddPOUDialog::slot_toggleCheckBox_extends(bool state_)
{
    _m_lineEdit_extends->setEnabled(state_);
    _m_pushButton_extends->setEnabled(state_);
}

void AddPOUDialog::slot_toggleCheckBox_implements(bool state_)
{
    _m_lineEdit_implements->setEnabled(state_);
    _m_pushButton_implements->setEnabled(state_);

    _m_label_method_implementation->setEnabled(state_);
    _m_combobox_method_implementation->setEnabled(state_);
}

void AddPOUDialog::slot_toggleRadioButton_program(bool state_)
{
    // _m_checkbox_extends->setEnabled(false);
    // _m_lineEdit_extends->setEnabled(false);
    // _m_pushButton_extends->setEnabled(false);

    // _m_checkbox_implements->setEnabled(false);
    // _m_lineEdit_implements->setEnabled(false);
    // _m_pushButton_implements->setEnabled(false);

    // _m_checkbox_final->setEnabled(false);
    // _m_checkbox_abstract->setEnabled(false);

    // _m_label_access_specifier->setEnabled(false);
    // _m_combobox_access_specifier->setEnabled(false);

    // _m_label_method_implementation->setEnabled(false);
    // _m_combobox_method_implementation->setEnabled(false);

    _m_label_return_type->setEnabled(false);
    _m_lineEdit_return_type->setEnabled(false);
    // _m_pushButton_return_type->setEnabled(false);
}

void AddPOUDialog::slot_toggleRadioButton_functionblock(bool state_)
{
    // _m_checkbox_extends->setEnabled(true);
    // _m_lineEdit_extends->setEnabled(_m_checkbox_extends->checkState());
    // _m_pushButton_extends->setEnabled(_m_checkbox_extends->checkState());

    // _m_checkbox_implements->setEnabled(true);
    // _m_lineEdit_implements->setEnabled(_m_checkbox_implements->checkState());
    // _m_pushButton_implements->setEnabled(_m_checkbox_implements->checkState());

    // _m_checkbox_final->setEnabled(true);
    // _m_checkbox_abstract->setEnabled(true);

    // _m_label_access_specifier->setEnabled(true);
    // _m_combobox_access_specifier->setEnabled(true);

    // _m_label_method_implementation->setEnabled(_m_checkbox_implements->checkState());
    // _m_combobox_method_implementation->setEnabled(_m_checkbox_implements->checkState());

    _m_label_return_type->setEnabled(false);
    _m_lineEdit_return_type->setEnabled(false);
    // _m_pushButton_return_type->setEnabled(false);
}

void AddPOUDialog::slot_toggleRadioButton_function(bool state_)
{
    // _m_checkbox_extends->setEnabled(false);
    // _m_lineEdit_extends->setEnabled(false);
    // _m_pushButton_extends->setEnabled(false);

    // _m_checkbox_implements->setEnabled(false);
    // _m_lineEdit_implements->setEnabled(false);
    // _m_pushButton_implements->setEnabled(false);

    // _m_checkbox_final->setEnabled(false);
    // _m_checkbox_abstract->setEnabled(false);

    // _m_label_access_specifier->setEnabled(false);
    // _m_combobox_access_specifier->setEnabled(false);

    // _m_label_method_implementation->setEnabled(false);
    // _m_combobox_method_implementation->setEnabled(false);

    _m_label_return_type->setEnabled(true);
    _m_lineEdit_return_type->setEnabled(true);
    // _m_pushButton_return_type->setEnabled(true);
}

void AddPOUDialog::slot_toggleCheckBox_final(bool state_)
{
    if(state_) _m_checkbox_abstract->setChecked(!state_);
}

void AddPOUDialog::slot_toggleCheckBox_abstract(bool state_)
{
    if(state_) _m_checkbox_final->setChecked(!state_);
}

void AddPOUDialog::accept()
{
    auto name_ = _m_lineEdit_name->text();
    if(name_.isEmpty())
    {
        QMessageBox::warning
            (
                this,
                tr("Warning"),
                tr("Please enter POU name").arg(name_)
                );

        return;
    }

    if(!StandardLibrary::instance()->find_pou(name_).isNull())
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

QDomNode AddPOUDialog::getNode() const
{
    QDomDocument doc_;
    auto pou_ = doc_.createElement("pou"); doc_.appendChild(pou_);
    pou_.setAttribute("name", _m_lineEdit_name->text());
    pou_.setAttribute("pouType", pouType2Str(radioId2enumType(_m_buttonGroup_type->checkedId())));
    auto interface_ = doc_.createElement("interface"); pou_.appendChild(interface_);
    auto localVars_ = doc_.createElement("localVars"); interface_.appendChild(localVars_);
    auto variable_ = doc_.createElement("variable"); localVars_.appendChild(variable_);
    variable_.setAttribute("name", "localVar1");
    auto type_ = doc_.createElement("type"); variable_.appendChild(type_);
    auto type_int_ = doc_.createElement("INT"); type_.appendChild(type_int_);
    if(radioId2enumType(_m_buttonGroup_type->checkedId()) == ePT_Function)
    {
        auto returnType_ = doc_.createElement("returnType"); interface_.appendChild(returnType_);
        auto returnTypeName_ = _m_lineEdit_return_type->text();
        if(returnTypeName_.isEmpty())
            returnTypeName_ = "INT";
        returnType_.appendChild(doc_.createElement(returnTypeName_));
    }
    auto body_ = doc_.createElement("body"); pou_.appendChild(body_);
    auto language_ = _m_comboBox_language->currentText();
    language_ = language_.mid(language_.indexOf('(')+1, language_.indexOf(')')-language_.indexOf('(')-1);
    body_.appendChild(doc_.createElement(language_));

    return doc_;
}

AddPOUDialog::ePOUType AddPOUDialog::radioId2enumType(int id_)
{
    switch(id_)
    {
    case 1:
        return ePOUType::ePT_Program;
        break;
    case 2:
        return ePOUType::ePT_FunctionBlock;
        break;
    case 3:
        return ePOUType::ePT_Function;
        break;
    }

    return ePOUType::ePT_Unknown;
}

QString AddPOUDialog::pouType2Str(ePOUType type_)
{
    switch(type_)
    {
    case ePOUType::ePT_Program:
        return "program";
        break;
    case ePOUType::ePT_FunctionBlock:
        return "functionBlock";
        break;
    case ePOUType::ePT_Function:
        return "function";
        break;
    }

    return {};
}
