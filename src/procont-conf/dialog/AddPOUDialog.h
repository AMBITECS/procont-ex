#ifndef ADDPOUDIALOG_H
#define ADDPOUDIALOG_H

#include <QDialog>
#include <QObject>
#include <QDomNode>

QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QButtonGroup)
QT_FORWARD_DECLARE_CLASS(QComboBox)

class AddPOUDialog : public QDialog
{
    Q_OBJECT

    enum ePOUType
    {
        ePT_Unknown         = 0,
        ePT_Program         = 1,
        ePT_FunctionBlock   = 2,
        ePT_Function        = 3
    };

public:
    AddPOUDialog();

    QDomNode getNode() const;

    void accept() override;

private slots:
    void slot_toggleCheckBox_extends(bool);
    void slot_toggleCheckBox_implements(bool);

    void slot_toggleRadioButton_program(bool);
    void slot_toggleRadioButton_functionblock(bool);
    void slot_toggleRadioButton_function(bool);

    void slot_toggleCheckBox_final(bool);
    void slot_toggleCheckBox_abstract(bool);

private:
    static ePOUType radioId2enumType(int id_);
    static QString pouType2Str(ePOUType type_);

private:
    QLineEdit * _m_lineEdit_name{nullptr};

    QButtonGroup * _m_buttonGroup_type{nullptr};

    QCheckBox * _m_checkbox_extends{nullptr};
    QLineEdit * _m_lineEdit_extends{nullptr};
    QPushButton * _m_pushButton_extends{nullptr};
    QCheckBox * _m_checkbox_implements{nullptr};
    QLineEdit * _m_lineEdit_implements{nullptr};
    QPushButton * _m_pushButton_implements{nullptr};
    QCheckBox * _m_checkbox_final{nullptr};
    QCheckBox * _m_checkbox_abstract{nullptr};
    QLabel * _m_label_access_specifier{nullptr};
    QComboBox * _m_combobox_access_specifier{nullptr};
    QLabel * _m_label_method_implementation{nullptr};
    QComboBox * _m_combobox_method_implementation{nullptr};

    QLabel * _m_label_return_type{nullptr};
    QLineEdit * _m_lineEdit_return_type{nullptr};
    QPushButton * _m_pushButton_return_type{nullptr};

    QComboBox * _m_comboBox_language;
};

#endif // ADDPOUDIALOG_H
