#ifndef ADDDUTDIALOG_H
#define ADDDUTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QDomNode>

QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QButtonGroup)

class AddDUTDialog : public QDialog
{
    Q_OBJECT

    enum eDUTType
    {
        eDT_Unknown     = 0,
        eDT_Structure   = 1,
        eDT_Enumeration = 2,
        eDT_Alias       = 3,
        eDT_Union       = 4
    };

public:
    AddDUTDialog();

    QDomNode getNode() const;

    void accept() override;

private slots:
    void slot_toggleRadioButton_struct(bool);
    void slot_toggleRadioButton_enum(bool);
    void slot_toggleRadioButton_alias(bool);
    void slot_toggleRadioButton_union(bool);

    void slot_toggleCheckBox_struct(bool);

private:
    static eDUTType radioId2enumType(int id_);
    static QString pouType2Str(eDUTType type_);


private:
    QLineEdit * _m_lineEdit_name{nullptr};

    QButtonGroup * _m_buttonGroup_type{nullptr};

    QCheckBox * _m_checkBox_struct;
    QLineEdit * _m_lineEdit_struct;
    QPushButton * _m_pushButton_struct;
    QCheckBox * _m_checkBox_enum;
    QLabel * _m_label_alias;
    QLineEdit * _m_lineEdit_alias;
    QPushButton * _m_pushButton_alias;
};

#endif // ADDDUTDIALOG_H
