#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QStandardItemModel)

class AddDeviceDialog : public QDialog
{
    Q_OBJECT
private:
    enum eDeviceAction
    {
        eDT_Add,
        eDT_Insert,
        eDT_Plug,
        eDT_Update
    };
public:
    AddDeviceDialog();

private:
    void setDeviceModelData(QStandardItemModel *model_);

private slots:
    void slot_action_buttonGroup_toggled(int id_, bool checked_);

private:
    QLineEdit * _m_lineEdit_name;
};

#endif // ADDDEVICEDIALOG_H
