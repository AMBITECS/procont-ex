#include "ItemDelegate_combobox.h"

#include <QDebug>

// *** CComboBoxDelegate_variable_type ***

#include "ComboBoxMultiListWidget.h"

ProcessedText::ProcessedText(const QString &str, const QStringList &lst)
    : var(str), items(lst)
{

}

CComboBoxDelegate_variable_type::CComboBoxDelegate_variable_type(const QStringList &items, QObject *parent)
    : QStyledItemDelegate(parent), m_items(items)
{

}

QWidget *CComboBoxDelegate_variable_type::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    // get current string from index
    QString curStr = index.data().toString();
    //qDebug() << "Create Editor - Current string from index" << curStr << '\n';

    ComboBoxMultiListWidget *editor = new ComboBoxMultiListWidget(parent);

    ProcessedText result = processDisplayText(curStr);
    editor->setVarText(result.var);

    editor->addItems(m_items);

    editor->setCheckedItems(result.items);


    //qDebug() << "Create Editor - Var text: " << result.var << '\n';


    return editor;
}

void CComboBoxDelegate_variable_type::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //qDebug() << "*********Start setEditorData*************" << '\n';
    QString current = index.model()->data(index, Qt::DisplayRole).toString();
    //qDebug() << "setEditorData - Model text: " << current <<'\n';

    ComboBoxMultiListWidget *comboBox = static_cast<ComboBoxMultiListWidget*>(editor);

    //QString currentDspTxt = comboBox->displayText();
    //qDebug() << "setEditorData - Display text: " << currentDspTxt <<'\n';

    //QString currentCmbTxt = comboBox->currentText();
    //qDebug() << "setEditorData - Combo text: " << currentCmbTxt <<'\n';

    comboBox->setCurrentText(current);

    //qDebug() << "*********End setEditorData*************" << '\n';
}

void CComboBoxDelegate_variable_type::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //qDebug() << "*********Start setModelData*************" << '\n';
    ComboBoxMultiListWidget *comboBox = static_cast<ComboBoxMultiListWidget*>(editor);
    //QString currentMdlTxt = index.model()->data(index, Qt::DisplayRole).toString();
    //qDebug() << "setModelData - Model text: " << currentMdlTxt <<'\n';

    QString currentDspTxt = comboBox->displayText();
    //qDebug() << "setModelData - Display text after: " << currentDspTxt <<'\n';

    //QString currentVarTxt = comboBox->varText();
    //qDebug() << "setModelData - Var text after: " << currentVarTxt <<'\n';

    model->setData(index, currentDspTxt, Qt::EditRole);
    //qDebug() << "setModelData - Text in model after setup: " << index.data().toString() <<'\n';

    //qDebug() << "*********End setModelData*************" << '\n';
}

void CComboBoxDelegate_variable_type::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

ProcessedText CComboBoxDelegate_variable_type::processDisplayText(const QString &text) const
{
    //qDebug() << "*********Start processDisplayText*************" << '\n';
    QStringList items;
    std::stringstream  strStream(text.toStdString());
    std::string var;
    std::string line;
    //int i = 0;
    while(strStream >> line)
    {
        if(!(line.empty()) && line[0] == 'V')
        {

            var = line;
            //qDebug() << "processDisplayText - var: " << var << '\n';
            continue;
        }

        if(!(line.empty()))
        {
            //++i;
            //qDebug() << "processDisplayText - flag " << i << ": " << line << '\n';
            items.push_back(QString::fromStdString(line));
        }
    }

    ProcessedText result(QString::fromStdString(var),items);

    //qDebug() << "*********End processDisplayText*************" << '\n';
    return result;
}
// ***
