#ifndef CITEMDELEGATE_COMBOBOX_H
#define CITEMDELEGATE_COMBOBOX_H

#include <QStyledItemDelegate>
#include <QtWidgets>

// *** CComboBoxDelegate_variable_type ***

struct ProcessedText
{
    ProcessedText(const QString &str, const QStringList &lst);

    QString var;
    QStringList items;
};

class CComboBoxDelegate_variable_type : public QStyledItemDelegate
{
public:
    CComboBoxDelegate_variable_type(const QStringList &items = {}, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QStringList m_items;

    ProcessedText processDisplayText(const QString &text) const;
};
// ***

#endif // CITEMDELEGATE_H
