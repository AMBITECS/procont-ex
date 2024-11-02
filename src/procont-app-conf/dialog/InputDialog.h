#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QTreeView)
QT_FORWARD_DECLARE_CLASS(QTextEdit)

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    InputDialog();

private slots:
    void slot_categoryCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slot_typeCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    static QString get_type(const QString &);

private:
    QStringList _m_categories;
    QTreeView * _m_treeview_name;
    QTextEdit * _m_textedit_doc;
};

#endif // INPUTDIALOG_H
