#include "ItemDelegate.h"

#include "item/DomItem.h"
#include "model/DomModel.h"

#include <QMessageBox>

#include <QDebug>

// *** CNoEditorDelegate ***
CNoEditorDelegate::CNoEditorDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget* CNoEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)

    return 0;
}
// ***

// *** CLineEditDelegate ***

#include <QLineEdit>

CLineEditDelegate::CLineEditDelegate( QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget *CLineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    auto *editor = new QLineEdit(parent);

    return editor;
}

void CLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString current = index.model()->data(index, Qt::EditRole).toString();

    auto * lineedit = static_cast<QLineEdit*>(editor);
    lineedit->setText(current);
}

void CLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto * lineedit = static_cast<QLineEdit*>(editor);

    auto _text = lineedit->text();
    auto _item = DomModel::toItem(index)->parentItem();

    Q_ASSERT(_item);

    if(_item->hasChild(_text, index.row()))
        QMessageBox::critical(nullptr, tr("Error"),
            QString(tr("The variable named \'%1\' already exists\nPlease, enter different variable name")).arg(_text));
    else
        model->setData(index, _text, Qt::EditRole);
}

void CLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
// ***

// *** CComboBoxDelegate ***

#include <QComboBox>

CComboBoxDelegate::CComboBoxDelegate(const QStringList &items, QObject *parent) : QStyledItemDelegate(parent),
    m_items(items)
{
}

QWidget *CComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(true);
    editor->addItems(m_items);

    return editor;
}

void CComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString current = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(current);
}

void CComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);

    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void CComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
// ***

// *** CTextEditDelegate ***

#include <QPlainTextEdit>

CTextEditDelegate::CTextEditDelegate( QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget *CTextEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    auto *editor = new QPlainTextEdit(parent);

    return editor;
}

void CTextEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString current = index.model()->data(index, Qt::EditRole).toString();

    auto * texteditor = static_cast<QPlainTextEdit*>(editor);
    texteditor->setPlainText(current);
}

void CTextEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto * texteditor = static_cast<QPlainTextEdit*>(editor);

    model->setData(index, texteditor->toPlainText(), Qt::EditRole);
}

void CTextEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
// ***

// *** CSpinBoxDelegate ***

#include "SpinBoxMultiRange.h"

CSpinBoxDelegate::CSpinBoxDelegate(quint8 decimal, double step, QObject *parent)
    : QStyledItemDelegate(parent),
    m_decimal(decimal), m_step(step)
{
}

QWidget *CSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    CMultiRangeSpinBox *editor = new CMultiRangeSpinBox(parent);
    editor->setFrame(false);
    editor->setDecimals(m_decimal);
    editor->setSingleStep(m_step);

    return editor;
}

void CSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QString values = index.model()->data(index, Qt::UserRole).toString();

    CMultiRangeSpinBox *spinBox = static_cast<CMultiRangeSpinBox*>(editor);

    QStringList list = values.split(";");

    for(auto &i : list)
    {
        if(i.indexOf("[") != -1 && i.indexOf("]") != -1)
        {
            i.remove('['); i.remove(']');
            QStringList lstr = i.split(",");
            bool bOk;
            double min = lstr.at(0).toDouble(&bOk);
            if(!bOk) continue;
            double max = lstr.at(1).toDouble(&bOk);
            if(!bOk) continue;
            spinBox->addRange(min, max);
        }
        else
        {
            bool bOk;
            double real = i.toDouble(&bOk);
            if(!bOk) continue;
            spinBox->addRange(real, real);
        }
    }

    spinBox->setValue(value);
}

void CSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CMultiRangeSpinBox *spinBox = static_cast<CMultiRangeSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void CSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
// ***
