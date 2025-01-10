#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QLineEdit)

class RenameDialog : public QDialog
{
    Q_OBJECT

public:
    RenameDialog(const QString &_current_name);

    QString new_name() const;

public slots:
    void accept() override;

private:
    QLineEdit * _m_lineEdit_current_name;
    QLineEdit * _m_lineEdit_new_name;
};

#endif // RENAMEDIALOG_H
