#ifndef CITEMDELEGATE_H
#define CITEMDELEGATE_H

#include <QItemDelegate>

// *** CNoEditorDelegate ***
class CNoEditorDelegate : public QItemDelegate
{
public:
    CNoEditorDelegate(QObject *);
    virtual QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
};
// ***

#include <QStyledItemDelegate>

// *** CComboBoxDelegate ***
class CComboBoxDelegate : public QStyledItemDelegate
{
public:
    CComboBoxDelegate(const QStringList &items = {}, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QStringList m_items;
};
// ***

// *** CTextEditDelegate ***
class CTextEditDelegate : public QStyledItemDelegate
{
public:
    CTextEditDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
// ***

// *** CSpinBoxDelegate ***
class CSpinBoxDelegate : public QStyledItemDelegate
{
public:
    CSpinBoxDelegate(quint8 decimal = 0, double step = 1, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    quint8 m_decimal = 0;
    double m_step = 1;
};
// ***


#endif // CITEMDELEGATE_H
