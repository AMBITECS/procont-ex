#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

#include <QDomNode>

QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(QTreeView)
QT_FORWARD_DECLARE_CLASS(QStandardItemModel)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QSortFilterProxyModel)

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    enum eType
    {
        eCT_POU,
        eCT_TYPE,
        eCT_ALL
    };

    InputDialog(eType);

    QDomNode selectedType() const;

private slots:
    void slot_categoryCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slot_typeCurrentChanged_tab1(const QModelIndex &current, const QModelIndex &previous);
    void slot_typeCurrentChanged_tab2(const QModelIndex &current, const QModelIndex &previous);
    void slot_filterTextChanged(const QString &text);
    void slot_currentTabChanged(int index);

private:
    static QString get_type_name(const QString &);
    static bool accept_category(const QString &, eType);
    static void updateVarsInfo(const QModelIndex &current_type_, QTextEdit *vars_info_, QStandardItemModel *vars_model_);
    static QString get_vartype_name(const QDomNode &);

private:
    eType _m_type;
    QStringList _m_categories;

    QTabWidget * _m_tabs;

    QTreeView * _m_tab1_treeview_name;
    QStandardItemModel * _m_tab1_name_model;
    QTextEdit * _m_tab1_textedit_doc;
    QStandardItemModel * _m_tab1_vars_model;

    QTreeView * _m_tab2_treeview_result;
    QSortFilterProxyModel * _m_tab2_filter_proxy;
    QTextEdit * _m_tab2_textedit_doc;
    QStandardItemModel * _m_tab2_vars_model;
};

#endif // INPUTDIALOG_H
