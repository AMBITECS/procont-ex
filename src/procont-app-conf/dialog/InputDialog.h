#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QTreeView)

class InputDialog : public QDialog
{
public:
    InputDialog();

private slots:
    void slot_categoryCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    static QString get_type(const QString &);

private:
    QStringList _m_categories;
    QTreeView * tab1_treewidget_lib;
};

#endif // INPUTDIALOG_H
